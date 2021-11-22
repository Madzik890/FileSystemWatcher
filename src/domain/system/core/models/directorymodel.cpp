#include "directorymodel.hpp"

using namespace Domain::System::Core::Models;
/*
DirectoryModel::DirectoryModel(QObject *parent)
    : QAbstractItemModel(parent)
{
}

QVariant DirectoryModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

QModelIndex DirectoryModel::index(int row, int column, const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

QModelIndex DirectoryModel::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
}

int DirectoryModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid() || !_fileSystemWatcher)
        return 0;

    return _fileSystemWatcher->getDirectories().size();
}

int DirectoryModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid() || !_fileSystemWatcher)
        return 0;

    return 1;
}

bool DirectoryModel::hasChildren(const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

bool DirectoryModel::canFetchMore(const QModelIndex &parent) const
{
    // FIXME: Implement me!
    return false;
}

void DirectoryModel::fetchMore(const QModelIndex &parent)
{
    // FIXME: Implement me!
}

QVariant DirectoryModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !_fileSystemWatcher)
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}

void DirectoryModel::setFileSystemWatcher(IFileSystemWatcher *watcher)
{
    _fileSystemWatcher = watcher;
    Q_ASSERT(watcher);

    beginResetModel();
    _fileSystemWatcher->disconnect(this);
}

IFileSystemWatcher *DirectoryModel::getFileSystemWatcher() const
{
    return _fileSystemWatcher;
}
*/
