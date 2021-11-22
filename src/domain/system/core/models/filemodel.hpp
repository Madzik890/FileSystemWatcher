#ifndef FILEMODEL_HPP
#define FILEMODEL_HPP

#include <QAbstractTableModel>
#include "domain/system/core/ports/incoming/ifilesystemwatcher.hpp"

using namespace Domain::System::Ports::Incoming;

namespace Domain
{
    namespace System
    {
        namespace Core
        {
            namespace Models
            {
                class FileModel : public QAbstractTableModel
                {
                    Q_OBJECT
                    Q_PROPERTY(Domain::System::Ports::Incoming::IFileSystemWatcher *fileSystemWatcher READ getFileSystemWatcher WRITE setFileSystemWatcher)
                    public:
                        enum { EventRole = Qt::UserRole, PathRole, IsFolderRole, TimestampRole };
                        explicit FileModel(QObject *parent = nullptr);
                        ~FileModel() = default;

                        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
                        int columnCount(const QModelIndex &parent = QModelIndex()) const override;
                        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
                        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
                        QHash<int, QByteArray> roleNames() const override;

                        void setFileSystemWatcher(IFileSystemWatcher *watcher);
                        IFileSystemWatcher *getFileSystemWatcher() const;

                    private:
                        IFileSystemWatcher *_fileSystemWatcher = nullptr;
                };
            }
        }
    }
}

#endif // FILEMODEL_HPP
