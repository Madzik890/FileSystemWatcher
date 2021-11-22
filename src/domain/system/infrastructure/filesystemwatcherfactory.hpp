#ifndef FILESYSTEMWATCHERFACTORY_HPP
#define FILESYSTEMWATCHERFACTORY_HPP

#include "domain/system/core/ports/incoming/ifilesystemwatcher.hpp"

using namespace Domain::System::Ports::Incoming;

namespace Domain
{
    namespace System
    {
        namespace Infrastructure
        {
            class FileSystemWatcherFactory
            {
                public:
                    static IFileSystemWatcher *createFileSystemWatcher(const char *param);
            };
        }
    }
}

#endif // FILESYSTEMWATCHERFACTORY_HPP
