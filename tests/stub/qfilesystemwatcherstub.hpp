#ifndef QFILESYSTEMWATCHERMOCK_HPP
#define QFILESYSTEMWATCHERMOCK_HPP

#include <QFileSystemWatcher>
#include <QVector>

namespace Stub
{
    class QFileSystemWatcherStub : public QFileSystemWatcher
    {
        public:
            QFileSystemWatcherStub(QObject *parent = nullptr);

        public slots:
            void emitDirectoryChanged(const QString &path);
            void emitFileChanged(const QString &path);

        private:
            QVector<QString> _directoriesList;
            QVector<QString> _pathsList;
    };
}

#endif // QFILESYSTEMWATCHERMOCK_HPP
