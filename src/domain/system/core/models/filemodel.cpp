#include "filemodel.hpp"
#include <QtDebug>

using namespace Domain::System::Core::Models;

const QString FileEventTypeToString(const FileEventType &type)
{
    switch(type)
    {
        case FileEventType::created:
            return "Created";
        case FileEventType::deleted:
            return "Deleted";
        case FileEventType::edited:
            return "Edited";
        case FileEventType::renamed:
            return "Renamed";
    }

    return "";
}

FileModel::FileModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

int FileModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    if (!_fileSystemWatcher)
        return 0;
    return _fileSystemWatcher->getFileItems().size();
}

int FileModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QVariant FileModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !_fileSystemWatcher)
        return QVariant();

    const FileItem item = _fileSystemWatcher->getFileItems().at(index.row());
    switch(role)
    {
        case EventRole:
            return QVariant(FileEventTypeToString(item._eventType));

        case PathRole:
            return QVariant(item._path);

        case IsFolderRole:        
            return QVariant(item._isFolder);

        case TimestampRole:        
            return QVariant(item._timeStamp.toString("dd/MM/yyyy hh:mm"));
    }

    return QVariant();
}

QVariant FileModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(section);
    if(orientation == Qt::Horizontal)
    {
        switch(role)
        {
            case EventRole:
                return QVariant("Event type");

            case PathRole:
                return QVariant("Path");

            case IsFolderRole:
                return QVariant("Is folder");

            case TimestampRole:
                return QVariant("Timestamp");
        }
    }

    return QVariant();
}

QHash<int, QByteArray> FileModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[EventRole] = "event";
    names[PathRole] = "path";
    names[IsFolderRole] = "isFolder";
    names[TimestampRole] = "timestamp";
    return names;
}

void FileModel::setFileSystemWatcher(IFileSystemWatcher *watcher)
{
    _fileSystemWatcher = watcher;

    if(_fileSystemWatcher)
    {
        beginResetModel();
        _fileSystemWatcher->disconnect(this);

        QObject::connect(_fileSystemWatcher, &IFileSystemWatcher::fileAppend, this, [=]()
        {
            const int index = _fileSystemWatcher->getFileItems().size();
            beginInsertRows(QModelIndex(), index, index);
        });

        QObject::connect(_fileSystemWatcher, &IFileSystemWatcher::fileAppended, this, [=]()
        {
            endInsertRows();
        });


        endResetModel();
    }
}

IFileSystemWatcher *FileModel::getFileSystemWatcher() const
{
    return _fileSystemWatcher;
}
