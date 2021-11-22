#ifndef FILESYSTEMWATCHERNATVIE_HPP
#define FILESYSTEMWATCHERNATVIE_HPP

#include "domain/system/core/ports/incoming/ifilesystemwatcher.hpp"

namespace Domain
{
    namespace System
    {
        namespace Infrastructure
        {
            class FileSystemWatcherNative : public Domain::System::Ports::Incoming::IFileSystemWatcher
            {
                public:
                    FileSystemWatcherNative(QObject *parent = nullptr);
                    ~FileSystemWatcherNative();

                    const QStringList getDirectories() const override;
                public slots:
                    Q_INVOKABLE void start() noexcept override;
                    Q_INVOKABLE void stop() noexcept override;

                    Q_INVOKABLE void addPath(const QString &path) noexcept override;
                    void addPaths(const QStringList &pathsList) noexcept override;
                    Q_INVOKABLE void removePath(const QString &path) noexcept override;
                    void removePaths(const QStringList &paths) noexcept override;
            };
        }
    }
}

#endif // FILESYSTEMWATCHERNATVIE_HPP
