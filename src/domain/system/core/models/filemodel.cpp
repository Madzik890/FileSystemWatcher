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
    if (!parent.isValid() || !_fileSystemWatcher)
        return 0;

    return _fileSystemWatcher->getFileItems().size();
}

int FileModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid() || !_fileSystemWatcher)
        return 0;
    return 4;
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
            return QVariant(item._timeStamp);
    }

    return QVariant();
}

void FileModel::setFileSystemWatcher(IFileSystemWatcher *watcher)
{
    _fileSystemWatcher = watcher;
    Q_ASSERT(watcher);

    beginResetModel();
    _fileSystemWatcher->disconnect(this);

    QObject::connect(_fileSystemWatcher, &IFileSystemWatcher::fileAppend, this, [=]()
    {
        const int index = _fileSystemWatcher->getFileItems().size();
        beginInsertRows(QModelIndex(), 0, index);
    });

    QObject::connect(_fileSystemWatcher, &IFileSystemWatcher::fileAppended, this, [=]()
    {
        endInsertRows();
    });


    endResetModel();
}

IFileSystemWatcher *FileModel::getFileSystemWatcher() const
{
    return _fileSystemWatcher;
}
