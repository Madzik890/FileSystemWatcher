#include "directorywatcher.hpp"
#include <QDir>

using namespace Domain::System::Infrastructure;

DirectoryWatcher::DirectoryWatcher(QObject *parent)
    : IDirectoryWatcher(parent),
      QThread(parent),
      _dirThreadEnd(true)
{
    this->start();
}

DirectoryWatcher::~DirectoryWatcher()
{
    _dirThreadEnd.exchange(false);
    this->quit();
    this->wait();
}

bool DirectoryWatcher::addPath(const QString &path) noexcept
{
    QMutexLocker locker(&_dirListMutex);
    const QDir dir(path);
    if(dir.exists())
    {
        const QFileInfoList fileList = dir.entryInfoList(QDir::AllDirs | QDir::Files);
        _dirList.push_back(std::make_pair(path, fileList));
        return true;
    }
    else
    {
        return false;
    }
}

bool DirectoryWatcher::removePath(const QString &path) noexcept
{
    QMutexLocker locker(&_dirListMutex);
    for(auto & dir : _dirList)
    {
        if(dir.first == path)
        {
            _dirList.removeOne(dir);
            return true;
        }
    }

    return false;
}

QStringList DirectoryWatcher::getDirectory() noexcept
{
    QMutexLocker locker(&_dirListMutex);
    QStringList list;

    for(auto &dir : _dirList)
    {
        list.append(dir.first);
    }

    return list;
}

void DirectoryWatcher::run()
{
    while(_dirThreadEnd.load())
    {
        QThread::msleep(100);
        _dirListMutex.lock();
        for(auto & dir : _dirList)
        {
            const QDir dirInfo(dir.first);
            if(dirInfo.exists())
            {
                const QFileInfoList fileList = dirInfo.entryInfoList(QDir::AllDirs | QDir::Files);
                if(dir.second != fileList)
                {
                    dir.second = fileList;
                    emit fileChanged(dir.first);
                }
            }
            else
            {
                _dirList.removeOne(dir);
                emit fileChanged(dir.first);
            }

        }
        _dirListMutex.unlock();
    }
}
