#include "filesystemwatchernatvie.hpp"
#include "directorywatcher.hpp"
#include <QDir>

using namespace Domain::System::Infrastructure;
using namespace Domain::System::Core::Ports::Incoming;

FileSystemWatcherNative::FileSystemWatcherNative(IDirectoryWatcher *watcher, QObject *parent)
    : IFileSystemWatcher(parent)
{
    if(watcher)
    {
        _ownWatcher = false;
        _directoryWatcher = watcher;
    }
    else
    {
        _ownWatcher = true;
        _directoryWatcher = new DirectoryWatcher(this);
    }

    Q_ASSERT(_directoryWatcher);
}

FileSystemWatcherNative::~FileSystemWatcherNative()
{
    if(_ownWatcher && _directoryWatcher)
    {
        delete _directoryWatcher;
    }
}

const QStringList FileSystemWatcherNative::getDirectories() const
{
    return _directoryWatcher->getDirectory();
}

void FileSystemWatcherNative::start() noexcept
{
    stop();
    QObject::connect(_directoryWatcher, &IDirectoryWatcher::fileChanged, this, &FileSystemWatcherNative::onFileChanged);
}

void FileSystemWatcherNative::stop() noexcept
{
    QObject::disconnect(_directoryWatcher, &IDirectoryWatcher::fileChanged, this, &FileSystemWatcherNative::onFileChanged);
}

void FileSystemWatcherNative::addPath(const QString &path) noexcept
{
    if(_directoryWatcher->addPath(path))
    {
        emit IFileSystemWatcher::directoryAppend();
        const QDir dir(path);
        _fileInfoList.push_back(std::make_pair(path, dir.entryInfoList(QDir::AllDirs | QDir::Files)));
        emit IFileSystemWatcher::directoryAppended();
    }
}

void FileSystemWatcherNative::addPath(const QUrl &path) noexcept
{
    Q_UNUSED(path);
}

void FileSystemWatcherNative::removePath(const QString &path) noexcept
{    
    const int index = _directoryWatcher->getDirectory().indexOf(path);
    if(index >= 0 && _directoryWatcher->removePath(path))
    {
        emit IFileSystemWatcher::directoryRemove(index);
        emit IFileSystemWatcher::directoryRemoved();
    }
}
