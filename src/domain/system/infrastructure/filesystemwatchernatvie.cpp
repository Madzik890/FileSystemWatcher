#include "filesystemwatchernatvie.hpp"
#include "directorywatcher.hpp"

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
    return QStringList();
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
    _directoryWatcher->addPath(path);
}

void FileSystemWatcherNative::removePath(const QString &path) noexcept
{
    _directoryWatcher->removePath(path);
}
