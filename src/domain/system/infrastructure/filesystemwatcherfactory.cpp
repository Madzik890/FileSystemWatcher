#include "filesystemwatcherfactory.hpp"
#include "domain/system/infrastructure/filesystemwatchernatvie.hpp"
#include "domain/system/infrastructure/filesystemwatcherqt.hpp"

using namespace Domain::System::Infrastructure;

IFileSystemWatcher *FileSystemWatcherFactory::createFileSystemWatcher(const QString &param)
{
    IFileSystemWatcher *watcher = nullptr;
    if(param == "-n")
    {
        watcher = new FileSystemWatcherNative();
    }
    else
    {
        watcher = new FileSystemWatcherQt();
    }

    Q_ASSERT(watcher);

    return watcher;
}
