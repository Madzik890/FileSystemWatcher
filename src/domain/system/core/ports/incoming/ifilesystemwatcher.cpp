#include "ifilesystemwatcher.hpp"
#include <QFileInfo>
#include <QFileInfoList>
#include <QDir>
#include <QUrl>

using namespace Domain::System::Core::Ports::Incoming;

#define CREATE_FILE(eventType, path, isDir)                                                      \
        Q_EMIT Domain::System::Core::Ports::Incoming::IFileSystemWatcher::fileAppend();                \
        _fileItemModel.push_back(FileItem(eventType, path, isDir));                              \
        Q_EMIT Domain::System::Core::Ports::Incoming::IFileSystemWatcher::fileAppended();

IFileSystemWatcher::IFileSystemWatcher(QObject *parent)
    :QObject(parent)
{

}

void IFileSystemWatcher::clear() noexcept
{
    emit fileAppend();
    _fileItemModel.clear();
    emit fileAppended();
}

void IFileSystemWatcher::addPath(const QUrl &path) noexcept
{
    addPath(path.path().mid(1));
}

const QVector<FileItem> IFileSystemWatcher::getFileItems() const
{
    return _fileItemModel;
}

void IFileSystemWatcher::onFileChanged(const QString &path)
{       
    if(checkDirExists(path))
    {
        const QDir dir(path);
        const QFileInfoList fileList = dir.entryInfoList(QDir::AllDirs | QDir::Files);
        for(auto &list : _fileInfoList)
        {
            if(list.first == path)
            {
                detectChanges(fileList, list.second);
                _fileInfoList.removeOne(list);//remove outdated list
                _fileInfoList.push_back(std::make_pair(path, fileList));//update
                break;
            }
        }
    }
    else
    {
        emit fileAppend();
        _fileItemModel.push_back(FileItem(FileEventType::deleted, path, true));
        emit fileAppended();
    }
}

bool IFileSystemWatcher::checkDirExists(const QString &path)
{
    const QFileInfo info(path);
    return info.exists();
}

void IFileSystemWatcher::detectChanges(const QFileInfoList &first, const QFileInfoList &second)
{
    const int firstListSize = first.size();
    const int secondListSize = second.size();
    if(firstListSize == secondListSize) //edited or rename
    {
        for(auto &fileFirst : first)
        {
            for(auto &fileSecond : second)
            {
                if(fileFirst.fileName() == "." || fileFirst.fileName() == ".." ||
                   fileSecond.fileName() == "." || fileSecond.fileName() == "..")
                    continue;

                if(fileFirst.filePath() != fileSecond.filePath() && fileFirst.birthTime() == fileSecond.birthTime())
                {
                    CREATE_FILE(FileEventType::renamed, fileFirst.filePath(), fileFirst.isDir());
                    goto exitLoop;
                } else if (fileFirst.lastModified() != fileSecond.lastModified())
                {
                    CREATE_FILE(FileEventType::edited, fileFirst.filePath(), fileFirst.isDir());
                    goto exitLoop;
                }
            }
        }
        exitLoop:
        return;
    }
    else if (firstListSize > secondListSize) //new file
    {
        for(auto &file : first)
        {
            if(!second.contains(file))
            {
                CREATE_FILE(FileEventType::created, file.filePath(), file.isDir());
                break;
            }
        }
    }
    else if(firstListSize < secondListSize) // removed file
    {
        for(auto &file : second)
        {
            if(!first.contains(file))
            {
                CREATE_FILE(FileEventType::deleted, file.filePath(), file.isDir());
                break;
            }
        }
    }
}
