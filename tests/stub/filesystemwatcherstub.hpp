#ifndef FILESYSTEMWATCHERSTUB_HPP
#define FILESYSTEMWATCHERSTUB_HPP

#include "domain/system/core/ports/incoming/ifilesystemwatcher.hpp"

using namespace Domain::System::Ports::Incoming;

namespace Stub
{
    class FileSystemWatcherStub : public IFileSystemWatcher
    {
        public:
            explicit FileSystemWatcherStub(QObject *parent = nullptr);
            ~FileSystemWatcherStub() = default;

            void start() noexcept override;
            void stop() noexcept override;
            void clear() noexcept override;

            void addPath(const QString &path) noexcept override;
            void removePath(const QString &path) noexcept override;
            const QStringList getDirectories() const override;

        public:
            void addFile(const FileItem &file);

            void emitFileAppend();
            void emitFileAppended();

            void emitDirectoryAppend();
            void emitDirectoryAppended();
            void emitDirectoryRemove(const int index);
            void emitDirectoryRemoved();
         private:
            bool _isStarted = false;
            QStringList _dirList;
    };
}

#endif // FILESYSTEMWATCHERSTUB_HPP
