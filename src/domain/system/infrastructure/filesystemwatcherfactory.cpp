#include "filesystemwatcherfactory.hpp"
#include "domain/system/infrastructure/filesystemwatchernatvie.hpp"
#include "domain/system/infrastructure/filesystemwatcherqt.hpp"

using namespace Domain::System::Infrastructure;

IFileSystemWatcher *FileSystemWatcherFactory::createFileSystemWatcher(const char *param)
{
    IFileSystemWatcher *watcher = nullptr;
    if(strcmp(param, "-n") == 0)
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
