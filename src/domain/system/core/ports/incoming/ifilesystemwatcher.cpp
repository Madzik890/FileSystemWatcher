#include "ifilesystemwatcher.hpp"
#include <QFileInfo>

using namespace Domain::System::Ports::Incoming;

IFileSystemWatcher::IFileSystemWatcher(QObject *parent)
    :QObject(parent)
{

}

void IFileSystemWatcher::clear() noexcept
{
    emit fileAppend();
    _fileItemVector.clear();
    emit fileAppended();
}

const QVector<FileItem> IFileSystemWatcher::getFileItems() const
{
    return _fileItemVector;
}

void IFileSystemWatcher::onFileChanged(const QString &path)
{
    emit fileAppend();
    QFileInfo info(path);
    FileEventType eventType = FileEventType::created;
    const bool isDir = info.isDir();

    if(info.exists())
    {
        for(auto &file : _fileItemVector)
        {
            if(file._path == path)
            {
                eventType = FileEventType::edited;
                break;
            }
        }
    }
    else
    {
        eventType = FileEventType::deleted;
    }

    _fileItemVector.push_back(FileItem(eventType, path, isDir));
    emit fileAppended();
}
