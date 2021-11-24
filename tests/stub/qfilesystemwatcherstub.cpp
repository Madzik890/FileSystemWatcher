#include "qfilesystemwatcherstub.hpp"

using namespace Stub;

QFileSystemWatcherStub::QFileSystemWatcherStub(QObject *parent)
    :QFileSystemWatcher(parent)
{

}

void QFileSystemWatcherStub::emitDirectoryChanged(const QString &path)
{
    Q_UNUSED(path);
    //emit QFileSystemWatcher::directoryChanged(path);
}

void QFileSystemWatcherStub::emitFileChanged(const QString &path)
{
    Q_UNUSED(path);
    //emit QFileSystemWatcher::directoryChanged(path);
}
