#ifndef FILEEVENTTYPE_HPP
#define FILEEVENTTYPE_HPP

#include <QMetaType>

namespace Domain
{
    namespace System
    {
        namespace Core
        {
            namespace Dictionaries
            {
                enum class FileEventType
                {
                    created,
                    deleted,
                    edited,
                    renamed
                };
            }
        }
    }
}

Q_DECLARE_METATYPE(Domain::System::Core::Dictionaries::FileEventType);

#endif // FILEEVENTTYPE_HPP
