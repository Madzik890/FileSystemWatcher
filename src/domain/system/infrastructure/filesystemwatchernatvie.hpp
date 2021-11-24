#ifndef FILESYSTEMWATCHERNATVIE_HPP
#define FILESYSTEMWATCHERNATVIE_HPP

#include "domain/system/core/ports/incoming/ifilesystemwatcher.hpp"

using namespace Domain::System::Core::Ports::Incoming;

namespace Domain
{
    namespace System
    {
        namespace Infrastructure
        {
            class FileSystemWatcherNative : public IFileSystemWatcher
            {
                public:
                    FileSystemWatcherNative(QObject *parent = nullptr);
                    ~FileSystemWatcherNative();

                    const QStringList getDirectories() const override;
                public slots:
                    Q_INVOKABLE void start() noexcept override;
                    Q_INVOKABLE void stop() noexcept override;

                    Q_INVOKABLE void addPath(const QString &path) noexcept override;
                    Q_INVOKABLE void removePath(const QString &path) noexcept override;
            };
        }
    }
}

#endif // FILESYSTEMWATCHERNATVIE_HPP
