#ifndef FILEITEM_HPP
#define FILEITEM_HPP

#include <QDateTime>
#include <QString>
#include "domain/system/core/dictionaries/fileeventtype.hpp"

using namespace Domain::System::Core::Dictionaries;

namespace Domain
{
    namespace System
    {
        namespace Core
        {
            namespace Models
            {
                struct FileItem
                {
                    FileItem() = default;
                    FileItem(const FileEventType &type, const QString &path, const bool &isFolder = false)
                        :_eventType(type),
                         _path(path),
                         _isFolder(isFolder),
                         _timeStamp(QDateTime::currentDateTime())
                    {

                    }
                    ~FileItem() = default;

                    FileEventType _eventType = FileEventType::created;
                    QString _path = "";
                    bool _isFolder = false;
                    QDateTime _timeStamp;
                };
            }
        }
    }
}

#endif // FILEITEM_HPP
