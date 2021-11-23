#include "filesystemwatcherqt.hpp"
#include <QDir>
#include <QUrl>

using namespace Domain::System::Ports::Incoming;
using namespace Domain::System::Infrastructure;

FileSystemWatcherQt::FileSystemWatcherQt(QFileSystemWatcher *watcher, QObject *parent)
    : IFileSystemWatcher(parent)
{
    if(watcher)
    {
        _fileWatcher = watcher;
        _ownFileWatcher = false;
    }
    else
    {
        _fileWatcher = new QFileSystemWatcher(this);
        _ownFileWatcher = true;
    }

    Q_ASSERT(_fileWatcher);
}

FileSystemWatcherQt::~FileSystemWatcherQt()
{
    if(_ownFileWatcher)
    {
        delete _fileWatcher;
        _fileWatcher = nullptr;
    }
}

void FileSystemWatcherQt::start() noexcept
{
    stop();
    QObject::connect(_fileWatcher, &QFileSystemWatcher::directoryChanged, this, &FileSystemWatcherQt::onDirChanged);
}

void FileSystemWatcherQt::stop() noexcept
{
    QObject::disconnect(_fileWatcher, &QFileSystemWatcher::directoryChanged, this, &FileSystemWatcherQt::onDirChanged);
}

void FileSystemWatcherQt::addPath(const QString &path) noexcept
{
    if(_fileWatcher->addPath(path))
    {
        emit IFileSystemWatcher::directoryAppend();
        const QDir dir(path);
        _fileInfoList.push_back(std::make_pair(path, dir.entryInfoList(QDir::AllDirs | QDir::Files)));
        emit IFileSystemWatcher::directoryAppended();
    }
}

void FileSystemWatcherQt::addPath(const QUrl &path) noexcept
{
    addPath(path.path().mid(1));
}

void FileSystemWatcherQt::removePath(const QString &path) noexcept
{    
    const int index = _fileWatcher->directories().indexOf(path);
    if(index >= 0 && _fileWatcher->removePath(path))
    {
        emit IFileSystemWatcher::directoryRemove(index);
        emit IFileSystemWatcher::directoryRemoved();
    }
}

const QStringList FileSystemWatcherQt::getDirectories() const
{
    return _fileWatcher->directories();
}
