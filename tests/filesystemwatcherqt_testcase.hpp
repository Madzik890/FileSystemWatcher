#ifndef FILESYSTEMWATCHERQT_TESTCASE_H
#define FILESYSTEMWATCHERQT_TESTCASE_H

#include "multitest.h"
#include "domain/system/core/ports/incoming/ifilesystemwatcher.hpp"
#include "domain/system/infrastructure/filesystemwatcherqt.hpp"

using namespace Domain::System::Ports::Incoming;
using namespace Domain::System::Infrastructure;

#define EXAMPLE_PATH "./"
#define EXAMPLE_PATH_LIST QStringList({ Q_FUNC_INFO, Q_FUNC_INFO, Q_FUNC_INFO })

class FileSystemWatcherQtTestCase : public QObject
{
    Q_OBJECT

public:
    ~FileSystemWatcherQtTestCase()
    {
        if(_watcher)
        {
            delete _watcher;
            _watcher = nullptr;
        }
    }

private slots:
    void init()
    {
        _fileSystemWatcher = new QFileSystemWatcher();
        Q_ASSERT(_fileSystemWatcher);

        _watcher = dynamic_cast<IFileSystemWatcher*>(new FileSystemWatcherQt(_fileSystemWatcher));
        Q_ASSERT(_watcher);
    }

    void addPath()
    {
        QSignalSpy spyAppend(_watcher, &IFileSystemWatcher::directoryAppend);
        QSignalSpy spyAppended(_watcher, &IFileSystemWatcher::directoryAppended);

        _watcher->addPath(EXAMPLE_PATH);

        spyAppend.wait(100);
        spyAppended.wait(100);

        QCOMPARE(spyAppend.count(), 1);
        QCOMPARE(spyAppended.count(), 1);
    }

    void removePath()
    {
        QSignalSpy spyRemove(_watcher, &IFileSystemWatcher::directoryRemove);
        QSignalSpy spyRemoved(_watcher, &IFileSystemWatcher::directoryRemoved);

        _watcher->addPath(EXAMPLE_PATH);
        spyRemove.wait(100);

        _watcher->removePath(EXAMPLE_PATH);

        spyRemove.wait(100);
        spyRemoved.wait(100);

        QCOMPARE(spyRemove.count(), 1);

        QList<QVariant> arguments = spyRemove.takeFirst();
        QVERIFY(arguments.at(0).type() == QVariant::Int);
        QCOMPARE(arguments.at(0).toInt(), 0);
        QCOMPARE(spyRemoved.count(), 1);
    }

    void close()
    {
        _watcher->stop();
        delete _watcher;
        _watcher = nullptr;
    }

private:
    QFileSystemWatcher *_fileSystemWatcher = nullptr;
    IFileSystemWatcher *_watcher = nullptr;
};

TEST_DECLARE(FileSystemWatcherQtTestCase);

#endif // FILESYSTEMWATCHERQT_TESTCASE_H

