#ifndef FILESYSTEMWATCHERFACTORY_HPP
#define FILESYSTEMWATCHERFACTORY_HPP

#include "domain/system/core/ports/incoming/ifilesystemwatcher.hpp"

using namespace Domain::System::Core::Ports::Incoming;

namespace Domain
{
    namespace System
    {
        namespace Infrastructure
        {
            class FileSystemWatcherFactory
            {
                public:
                    static IFileSystemWatcher *createFileSystemWatcher(const QString &param);
            };
        }
    }
}

#endif // FILESYSTEMWATCHERFACTORY_HPP
