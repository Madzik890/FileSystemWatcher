#ifndef DIRECTORYMODEL_H
#define DIRECTORYMODEL_H

#include <QAbstractListModel>
#include "domain/system/core/ports/incoming/ifilesystemwatcher.hpp"

using namespace Domain::System::Core::Ports::Incoming;

namespace Domain
{
    namespace System
    {
        namespace Core
        {
            namespace Models
            {
                class DirectoryModel : public QAbstractListModel
                {
                    Q_OBJECT
                    Q_PROPERTY(Domain::System::Core::Ports::Incoming::IFileSystemWatcher *fileSystemWatcher READ getFileSystemWatcher WRITE setFileSystemWatcher)
                    public:
                        explicit DirectoryModel(QObject *parent = nullptr);
                        ~DirectoryModel() = default;

                        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
                        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
                        void setFileSystemWatcher(IFileSystemWatcher *watcher);
                        IFileSystemWatcher *getFileSystemWatcher() const;

                    private:
                        IFileSystemWatcher *_fileSystemWatcher = nullptr;
                };
            }
        }
    }
}

#endif // DIRECTORYMODEL_H
