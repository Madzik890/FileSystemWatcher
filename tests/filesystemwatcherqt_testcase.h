#ifndef FILESYSTEMWATCHERQT_TESTCASE_H
#define FILESYSTEMWATCHERQT_TESTCASE_H

#include "multitest.h"
#include <QtTest>
#include <QSignalSpy>
#include <QObject>
#include "domain/system/core/ports/incoming/ifilesystemwatcher.hpp"
#include "domain/system/infrastructure/filesystemwatcherqt.hpp"

using namespace Domain::System::Ports::Incoming;
using namespace Domain::System::Infrastructure;

#define EXAMPLE_PATH Q_FUNC_INFO
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
        QSignalSpy spy(_watcher, &IFileSystemWatcher::directoryAppend);
        _watcher->addPath(EXAMPLE_PATH);
        spy.wait(100);
        QCOMPARE(spy.count(), 1);
    }

    void addPaths()
    {
        QSignalSpy spy(_watcher, &IFileSystemWatcher::directoryAppend);
        _watcher->addPaths(EXAMPLE_PATH_LIST);
        spy.wait(100);
        QCOMPARE(spy.count(), 1);
    }

    void removePath()
    {
        QSignalSpy spy(_watcher, &IFileSystemWatcher::directoryAppend);
        _watcher->removePath(EXAMPLE_PATH);
        spy.wait(100);
        QCOMPARE(spy.count(), 1);
    }

    void removePaths()
    {
        QSignalSpy spy(_watcher, &IFileSystemWatcher::directoryAppend);
        _watcher->removePaths(EXAMPLE_PATH_LIST);
        spy.wait(100);
        QCOMPARE(spy.count(), 1);
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
