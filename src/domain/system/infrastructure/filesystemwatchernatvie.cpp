#include "filesystemwatchernatvie.hpp"

using namespace Domain::System::Infrastructure;
using namespace Domain::System::Ports::Incoming;

FileSystemWatcherNative::FileSystemWatcherNative(QObject *parent)
    : IFileSystemWatcher(parent)
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
    Q_UNUSED(path);
}

void FileSystemWatcherNative::removePath(const QString &path) noexcept
{
    Q_UNUSED(path);
}
