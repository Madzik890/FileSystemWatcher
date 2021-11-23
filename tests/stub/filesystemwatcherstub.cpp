#include "filesystemwatcherstub.hpp"

using namespace Stub;

FileSystemWatcherStub::FileSystemWatcherStub(QObject *parent)
    : IFileSystemWatcher(parent)
{

}

void FileSystemWatcherStub::start() noexcept
{

}

void FileSystemWatcherStub::stop() noexcept
{

}

void FileSystemWatcherStub::clear() noexcept
{
    _fileItemModel.clear();
}

void FileSystemWatcherStub::addPath(const QString &path) noexcept
{
    _dirList.push_back(path);
}

void FileSystemWatcherStub::removePath(const QString &path) noexcept
{
    _dirList.removeOne(path);
}

const QStringList FileSystemWatcherStub::getDirectories() const
{
    return _dirList;
}

void FileSystemWatcherStub::addFile(const FileItem &file)
{
    _fileItemModel.push_back(file);
}

void FileSystemWatcherStub::emitFileAppend()
{
    emit fileAppend();
}

void FileSystemWatcherStub::emitFileAppended()
{
    emit fileAppended();
}

void FileSystemWatcherStub::emitDirectoryAppend()
{
    emit directoryAppend();
}

void FileSystemWatcherStub::emitDirectoryAppended()
{
    emit directoryAppended();
}

void FileSystemWatcherStub::emitDirectoryRemove(const int index)
{
    emit directoryRemove(index);
}

void FileSystemWatcherStub::emitDirectoryRemoved()
{
    emit directoryRemoved();
}
