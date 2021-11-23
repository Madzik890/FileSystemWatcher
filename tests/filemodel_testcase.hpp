#ifndef FILEMODEL_TESTCASE_HPP
#define FILEMODEL_TESTCASE_HPP

#include "multitest.h"
#include "domain/system/core/models/filemodel.hpp"
#include "stub/filesystemwatcherstub.hpp"
#include "tools/qstring.hpp"
#include <QtDebug>

#define FILE_NAME_LENGTH 15

using namespace Domain::System::Ports::Incoming;
using namespace Domain::System::Core::Models;
using namespace Stub;

class FileModelTestCase : public QObject
{
    Q_OBJECT
public:
    ~FileModelTestCase()
    {
        if(_watcher)
        {
            delete _watcher;
            _watcher = nullptr;
        }

        if(_fileModel)
        {
            delete _fileModel;
            _fileModel = nullptr;
        }
    }

private slots:
    void init()
    {
        _watcher = new FileSystemWatcherStub();
        _fileModel = new FileModel();
        Q_ASSERT(_watcher);
        Q_ASSERT(_fileModel);

        _fileModel->setFileSystemWatcher(_watcher);
        QCOMPARE(_watcher, _fileModel->getFileSystemWatcher());
    }

    void createdFile()
    {
        const QString filePath = Tools::GetRandomString(FILE_NAME_LENGTH);
        QSignalSpy spy(_fileModel, &FileModel::rowsInserted);

        _watcher->emitFileAppend();
        const FileItem item(FileEventType::created, filePath, qrand() % UINT8_MAX);
        _watcher->addFile(item);
        _watcher->emitFileAppended();

        spy.wait(100);

        QCOMPARE(spy.count(), 1);
        QCOMPARE(_fileModel->rowCount(), 1);
        QVariant _variant = _fileModel->data(QModelIndex());
        QCOMPARE(_variant.isValid(), false);
    }

    void renamedFile()
    {
        const QString filePath = Tools::GetRandomString(FILE_NAME_LENGTH);
        QSignalSpy spy(_fileModel, &FileModel::rowsInserted);

        _watcher->emitFileAppend();
        const FileItem item(FileEventType::created, filePath, qrand() % UINT8_MAX);
        _watcher->addFile(item);
        _watcher->emitFileAppended();

        spy.wait(100);

        QCOMPARE(spy.count(), 1);
        QCOMPARE(_fileModel->rowCount(), 1);
        QVariant _variant = _fileModel->data(QModelIndex());
        QCOMPARE(_variant.isValid(), false);
    }

    void editedFile()
    {
        const QString filePath = Tools::GetRandomString(FILE_NAME_LENGTH);
        QSignalSpy spy(_fileModel, &FileModel::rowsInserted);

        _watcher->emitFileAppend();
        const FileItem item(FileEventType::edited, filePath, qrand() % UINT8_MAX);
        _watcher->addFile(item);
        _watcher->emitFileAppended();

        spy.wait(100);

        QCOMPARE(spy.count(), 1);
        QCOMPARE(_fileModel->rowCount(), 1);
        QVariant _variant = _fileModel->data(QModelIndex());
        QCOMPARE(_variant.isValid(), false);
    }

    void deletedFile()
    {
        const QString filePath = Tools::GetRandomString(FILE_NAME_LENGTH);
        QSignalSpy spy(_fileModel, &FileModel::rowsInserted);

        _watcher->emitFileAppend();
        const FileItem item(FileEventType::deleted, filePath, qrand() % UINT8_MAX);
        _watcher->addFile(item);
        _watcher->emitFileAppended();

        spy.wait(100);

        QCOMPARE(spy.count(), 1);
        QCOMPARE(_fileModel->rowCount(), 1);
        QVariant _variant = _fileModel->data(QModelIndex());
        QCOMPARE(_variant.isValid(), false);
    }

    void clearFiles()
    {
        QSignalSpy spy(_fileModel, &FileModel::rowsInserted);

        _watcher->emitFileAppend();
        _watcher->clear();
        _watcher->emitFileAppended();

        spy.wait(100);

        QCOMPARE(spy.count(), 1);
        QCOMPARE(_fileModel->rowCount(), 0);
        QVariant _variant = _fileModel->data(QModelIndex());
        QCOMPARE(_variant.isValid(), false);
    }

    void close()
    {
        delete _watcher;
        _watcher = nullptr;

        delete _fileModel;
        _fileModel = nullptr;
    }

private:
    FileSystemWatcherStub *_watcher = nullptr;
    FileModel *_fileModel = nullptr;
};

TEST_DECLARE(FileModelTestCase);

#endif // FILEMODEL_TESTCASE_HPP
