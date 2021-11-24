#ifndef DIRECTORYWATCHER_HPP
#define DIRECTORYWATCHER_HPP

#include <QThread>
#include <QMutex>
#include <QString>
#include <QFileInfoList>
#include "domain/system/core/ports/incoming/idirectorywatcher.hpp"

using namespace Domain::System::Core::Ports::Incoming;

namespace Domain
{
    namespace System
    {
        namespace Infrastructure
        {
            class DirectoryWatcher : public IDirectoryWatcher, public QThread
            {
                public:
                    explicit DirectoryWatcher(QObject *parent = nullptr);
                    ~DirectoryWatcher();

                    bool addPath(const QString &path) noexcept override;
                    bool removePath(const QString &path) noexcept override;
                    QStringList getDirectory() noexcept override;

                protected:
                    void run() override;

                private:
                    QMutex _dirListMutex;
                    QList<std::pair<QString, QFileInfoList>> _dirList;
            };
        }
    }
}

#endif // DIRECTORYWATCHER_HPP
