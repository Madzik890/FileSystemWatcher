#include "filesystemwatchernatvie.hpp"

using namespace Domain::System::Infrastructure;

FileSystemWatcherNative::FileSystemWatcherNative(QObject *parent)
{

}

FileSystemWatcherNative::~FileSystemWatcherNative()
{

}

const QStringList FileSystemWatcherNative::getDirectories() const
{
    return QStringList();
}

void FileSystemWatcherNative::start() noexcept
{

}

void FileSystemWatcherNative::stop() noexcept
{

}

void FileSystemWatcherNative::addPath(const QString &path) noexcept
{

}

void FileSystemWatcherNative::addPaths(const QStringList &pathsList) noexcept
{

}

void FileSystemWatcherNative::removePath(const QString &path) noexcept
{

}

void FileSystemWatcherNative::removePaths(const QStringList &paths) noexcept
{

}
