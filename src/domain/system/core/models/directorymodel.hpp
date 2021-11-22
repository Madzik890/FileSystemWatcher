#ifndef DIRECTORYMODEL_H
#define DIRECTORYMODEL_H

#include <QAbstractItemModel>
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
                /*class DirectoryModel : public QAbstractTableModel
                {
                    Q_OBJECT
                    Q_PROPERTY(Domain::System::Ports::Incoming::IFileSystemWatcher *list READ getFileSystemWatcher WRITE setFileSystemWatcher)
                    public:
                        explicit DirectoryModel(QObject *parent = nullptr);

                        // Header:
                        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

                        // Basic functionality:
                        QModelIndex index(int row, int column,
                        const QModelIndex &parent = QModelIndex()) const override;
                        QModelIndex parent(const QModelIndex &index) const override;

                        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
                        int columnCount(const QModelIndex &parent = QModelIndex()) const override;

                        // Fetch data dynamically:
                        bool hasChildren(const QModelIndex &parent = QModelIndex()) const override;

                        bool canFetchMore(const QModelIndex &parent) const override;
                        void fetchMore(const QModelIndex &parent) override;

                        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

                        void setFileSystemWatcher(IFileSystemWatcher *watcher);
                        IFileSystemWatcher *getFileSystemWatcher() const;

                    private:
                        IFileSystemWatcher *_fileSystemWatcher = nullptr;
                };*/
            }
        }
    }
}

#endif // DIRECTORYMODEL_H
