#ifndef IDIRECTORYWATCHER_HPP
#define IDIRECTORYWATCHER_HPP

#include <QObject>

namespace Domain
{
    namespace System
    {
        namespace Core
        {
            namespace Ports
            {
                namespace Incoming
                {
                    class IDirectoryWatcher : public QObject
                    {
                        Q_OBJECT
                        public:
                            explicit IDirectoryWatcher(QObject *parent = nullptr);
                            virtual ~IDirectoryWatcher() = default;

                            virtual bool addPath(const QString &path) noexcept = 0;
                            virtual bool removePath(const QString &path) noexcept = 0;
                            virtual QStringList getDirectory() noexcept = 0;

                        signals:
                            void fileChanged(const QString &path);
                    };
                }
            }
        }
    }
}

#endif // IDIRECTORYWATCHER_HPP
