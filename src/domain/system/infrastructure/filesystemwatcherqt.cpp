#include "filesystemwatcherqt.hpp"

using namespace Domain::System::Ports::Incoming;
using namespace Domain::System::Infrastructure;

FileSystemWatcherQt::FileSystemWatcherQt(QFileSystemWatcher *watcher, QObject *parent)
    :IFileSystemWatcher(parent)
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
    _fileWatcher->addPath("C:\\Users\\Marcin\\Desktop\\powder toy");
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
    QObject::connect(_fileWatcher, &QFileSystemWatcher::fileChanged, this, &FileSystemWatcherQt::onFileChanged);
    QObject::connect(_fileWatcher, &QFileSystemWatcher::directoryChanged, this, &FileSystemWatcherQt::onFileChanged);
}

void FileSystemWatcherQt::stop() noexcept
{
    QObject::disconnect(_fileWatcher, &QFileSystemWatcher::fileChanged, this, &FileSystemWatcherQt::onFileChanged);
    QObject::disconnect(_fileWatcher, &QFileSystemWatcher::directoryChanged, this, &FileSystemWatcherQt::onFileChanged);
}

void FileSystemWatcherQt::addPath(const QString &path) noexcept
{
    _fileWatcher->addPath(path);
    emit IFileSystemWatcher::directoryAppend();
}

void FileSystemWatcherQt::addPaths(const QStringList &pathsList) noexcept
{
    _fileWatcher->addPaths(pathsList);
    emit IFileSystemWatcher::directoryAppend();
}

void FileSystemWatcherQt::removePath(const QString &path) noexcept
{
    _fileWatcher->removePath(path);
    emit IFileSystemWatcher::directoryAppend();
}

void FileSystemWatcherQt::removePaths(const QStringList &paths) noexcept
{
    _fileWatcher->removePaths(paths);
    emit IFileSystemWatcher::directoryAppend();
}

const QStringList FileSystemWatcherQt::getDirectories() const
{
    return _fileWatcher->directories();
}
