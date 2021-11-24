#ifndef FILESYSTEMWATCHERQT_TESTCASE_H
#define FILESYSTEMWATCHERQT_TESTCASE_H

#include "multitest.h"
#include "domain/system/core/ports/incoming/ifilesystemwatcher.hpp"
#include "domain/system/infrastructure/filesystemwatcherqt.hpp"
#include <QFile>

using namespace Domain::System::Core::Ports::Incoming;
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

    void createDirectory()
    {
        const QString dirPath = QDir::homePath() + "/TestDir";
        removeDirectory(dirPath);

        _watcher->clear();
        _watcher->addPath(QDir::homePath());
        _watcher->start();
        QSignalSpy spy(_watcher, &IFileSystemWatcher::fileAppend);

        QCOMPARE(createDirectory(dirPath), true);
        spy.wait(100);

        QCOMPARE(spy.count(), 1);
        const QVector<FileItem> filesItem = _watcher->getFileItems();
        QCOMPARE(filesItem.size(), 1);
        QVERIFY(filesItem[0]._eventType == FileEventType::created);
        QVERIFY(filesItem[0]._path == dirPath);
        QVERIFY(filesItem[0]._isFolder == true);
        QVERIFY(removeDirectory(dirPath) == true);
    }

    void createFile()
    {
        const QString filePath = QDir::homePath() + "/TestFile.txt";
        _watcher->clear();
        _watcher->addPath(QDir::homePath());
        _watcher->start();

        QSignalSpy spy(_watcher, &IFileSystemWatcher::fileAppend);
        QCOMPARE(createFile(filePath), true);
        spy.wait(100);

        QCOMPARE(spy.count(), 1);
        const QVector<FileItem> filesItem = _watcher->getFileItems();
        QCOMPARE(filesItem.size(), 1);
        QVERIFY(filesItem[0]._eventType == FileEventType::created);
        QVERIFY(filesItem[0]._path == filePath);
        QVERIFY(filesItem[0]._isFolder == false);
        QVERIFY(removeFile(filePath) == true);
    }

    void deleteDirectory()
    {
        const QString dirPath = QDir::homePath() + "/TestDir";
        QCOMPARE(createDirectory(dirPath), true);

        _watcher->clear();
        _watcher->addPath(QDir::homePath());
        _watcher->start();
        QSignalSpy spy(_watcher, &IFileSystemWatcher::fileAppend);
        QCOMPARE(removeDirectory(dirPath), true);

        spy.wait(100);

        QCOMPARE(spy.count(), 1);
        const QVector<FileItem> filesItem = _watcher->getFileItems();
        QCOMPARE(filesItem.size(), 1);
        QVERIFY(filesItem[0]._eventType == FileEventType::deleted);
        QVERIFY(filesItem[0]._path == dirPath);
        QVERIFY(filesItem[0]._isFolder == true);
    }

    void deleteFile()
    {
        const QString filePath = QDir::homePath() + "/TestFile.txt";
        QCOMPARE(createFile(filePath), true);

        _watcher->clear();
        _watcher->addPath(QDir::homePath());
        _watcher->start();
        QSignalSpy spy(_watcher, &IFileSystemWatcher::fileAppend);
        QCOMPARE(removeFile(filePath), true);

        spy.wait(100);

        QCOMPARE(spy.count(), 1);
        const QVector<FileItem> filesItem = _watcher->getFileItems();
        QCOMPARE(filesItem.size(), 1);
        QVERIFY(filesItem[0]._eventType == FileEventType::deleted);
        QVERIFY(filesItem[0]._path == filePath);
        QVERIFY(filesItem[0]._isFolder == false);
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

    bool createDirectory (const QString &dirName)
    {
        QDir dir;
        return dir.mkdir(dirName);
    }

    bool removeDirectory(const QString &dirName)
    {
        QDir dir;
        return dir.rmdir(dirName);
    }

    bool createFile(const QString &path)
    {
        QFile file(path);
        return file.open(QFile::WriteOnly);
    }

    bool removeFile(const QString &path)
    {
        QFile file(path);
        return file.remove();
    }
};

TEST_DECLARE(FileSystemWatcherQtTestCase);

#endif // FILESYSTEMWATCHERQT_TESTCASE_H
