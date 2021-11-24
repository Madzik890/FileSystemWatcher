#ifndef IFILESYSTEMWATCHER_HPP
#define IFILESYSTEMWATCHER_HPP

#include <QObject>
#include <QFileInfoList>
#include "domain/system/core/models/fileitem.hpp"

using namespace Domain::System::Core::Models;

namespace Domain
{
    namespace System
    {
        namespace Core
        {
            namespace Ports
            {
                namespace Incoming
                {
                    class IFileSystemWatcher : public QObject
                    {
                        Q_OBJECT
                        public:
                            explicit IFileSystemWatcher(QObject *parent = nullptr);
                            virtual ~IFileSystemWatcher() = default;

                            Q_INVOKABLE virtual void start() noexcept = 0;
                            Q_INVOKABLE virtual void stop() noexcept = 0;
                            Q_INVOKABLE virtual void clear() noexcept;

                            Q_INVOKABLE virtual void addPath(const QString &path) noexcept = 0;
                            Q_INVOKABLE virtual void addPath(const QUrl &path) noexcept;
                            Q_INVOKABLE virtual void removePath(const QString &path) noexcept = 0;

                            virtual const QStringList getDirectories() const = 0;
                            virtual const QVector<FileItem> getFileItems() const;

                        signals:
                            void fileAppend();
                            void fileAppended();

                            void directoryAppend();
                            void directoryAppended();
                            void directoryRemove(const int index);
                            void directoryRemoved();

                        protected://model
                            QVector<FileItem> _fileItemModel;

                        protected:
                            QVector<std::pair<QString, QFileInfoList>> _fileInfoList;

                        protected slots:
                            void onFileChanged(const QString &path);

                        private:
                            bool checkDirExists(const QString &path);
                            void detectChanges(const QFileInfoList &first, const QFileInfoList &second);
                    };
                }
            }
        }
    }
}

#endif // IFILESYSTEMWATCHER_HPP
