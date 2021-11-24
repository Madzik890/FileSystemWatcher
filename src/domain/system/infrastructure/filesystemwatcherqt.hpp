#ifndef FILESYSTEMWATCHERQT_HPP
#define FILESYSTEMWATCHERQT_HPP

#include "domain/system/core/ports/incoming/ifilesystemwatcher.hpp"
#include <QFileSystemWatcher>

using namespace Domain::System::Core::Ports::Incoming;

namespace Domain
{
    namespace System
    {
        namespace Infrastructure
        {
            class FileSystemWatcherQt : public IFileSystemWatcher
            {
                public:
                    explicit FileSystemWatcherQt(QFileSystemWatcher *watcher = nullptr, QObject *parent = nullptr);
                   ~FileSystemWatcherQt();

                    Q_INVOKABLE void start() noexcept override;
                    Q_INVOKABLE void stop() noexcept override;

                    Q_INVOKABLE void addPath(const QString &path) noexcept override;
                    Q_INVOKABLE void removePath(const QString &path) noexcept override;

                    const QStringList getDirectories() const override;

                private:
                    bool _ownFileWatcher = false;
                    QFileSystemWatcher *_fileWatcher = nullptr;
            };
        }
    }
}

#endif // FILESYSTEMWATCHERQT_HPP
