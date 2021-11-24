#include "directorymodel.hpp"
#include <QtDebug>

using namespace Domain::System::Core::Models;

DirectoryModel::DirectoryModel(QObject *parent)
    :QAbstractListModel(parent)
{

}

int DirectoryModel::rowCount(const QModelIndex &parent) const
{
    (void)parent;
    if (!_fileSystemWatcher)
        return 0;
    return _fileSystemWatcher->getDirectories().size();
}

QVariant DirectoryModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !_fileSystemWatcher)
        return QVariant();

    const QStringList dirList = _fileSystemWatcher->getDirectories();
    if(role == Qt::DisplayRole && dirList.size() > index.row())
    {
        const QString dir = dirList[index.row()];
        return QVariant(dir);
    }

    return QVariant();
}

void DirectoryModel::setFileSystemWatcher(IFileSystemWatcher *watcher)
{
    _fileSystemWatcher = watcher;

    if(_fileSystemWatcher)
    {
        beginResetModel();
        _fileSystemWatcher->disconnect(this);

        QObject::connect(_fileSystemWatcher, &IFileSystemWatcher::directoryAppend, this, [=]()
        {
            const int index = _fileSystemWatcher->getDirectories().size() - 1;
            beginInsertRows(QModelIndex(), index, index);
        });

        QObject::connect(_fileSystemWatcher, &IFileSystemWatcher::directoryAppended, this, [=]()
        {
            endInsertRows();
        });

        QObject::connect(_fileSystemWatcher, &IFileSystemWatcher::directoryRemove, this, [=](const int index)
        {
            beginRemoveRows(QModelIndex(), index, index);
        });

        QObject::connect(_fileSystemWatcher, &IFileSystemWatcher::directoryRemoved, this, [=]()
        {
            endRemoveRows();
        });

        endResetModel();
    }
}

IFileSystemWatcher *DirectoryModel::getFileSystemWatcher() const
{
    return _fileSystemWatcher;
}
