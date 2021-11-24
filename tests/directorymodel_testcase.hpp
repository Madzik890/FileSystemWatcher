#ifndef DIRECTORYMODEL_TESTCASE_HPP
#define DIRECTORYMODEL_TESTCASE_HPP

#include "multitest.h"
#include "domain/system/core/models/directorymodel.hpp"
#include "stub/filesystemwatcherstub.hpp"
#include "tools/qstring.hpp"
#include <QtDebug>

#define DIR_NAME_LENGHT 50

using namespace Domain::System::Core::Ports::Incoming;
using namespace Domain::System::Core::Models;
using namespace Stub;

class DirectoryModelTestCase : public QObject
{
    Q_OBJECT
public:
    ~DirectoryModelTestCase()
    {
        if(_watcher)
        {
            delete _watcher;
            _watcher = nullptr;
        }

        if(_dirModel)
        {
            delete _dirModel;
            _dirModel = nullptr;
        }
    }

private slots:
    void init()
    {
        _watcher = new FileSystemWatcherStub();
        _dirModel = new DirectoryModel();
        Q_ASSERT(_watcher);
        Q_ASSERT(_dirModel);

        _dirModel->setFileSystemWatcher(_watcher);
        QCOMPARE(_watcher, _dirModel->getFileSystemWatcher());
    }

    void directoryAppend()
    {
        const QString directory = Tools::GetRandomString(DIR_NAME_LENGHT);
        QSignalSpy spy(_dirModel, &DirectoryModel::rowsInserted);

        _watcher->emitDirectoryAppend();
        _watcher->addPath(directory);
        _watcher->emitDirectoryAppended();

        spy.wait(100);

        QCOMPARE(spy.count(), 1);
        QCOMPARE(_dirModel->rowCount(), 1);
        QVariant _variant = _dirModel->data(QModelIndex());
        QCOMPARE(_variant.isValid(), false);
    }

    void directoryRemove()
    {
        QSignalSpy spy(_dirModel, &DirectoryModel::rowsInserted);

        _watcher->emitDirectoryAppend();
        _watcher->addPath(_directory);
        _watcher->emitDirectoryAppended();

        _watcher->emitDirectoryRemove(0);
        _watcher->removePath(_directory);
        _watcher->emitDirectoryRemoved();

        spy.wait(100);

        QCOMPARE(spy.count(), 1);
        QCOMPARE(_dirModel->rowCount(), 0);
        QVariant _variant = _dirModel->data(QModelIndex());
        QCOMPARE(_variant.isValid(), false);
    }

    void directoryInvalidRemove()
    {
        const QString directory = Tools::GetRandomString(DIR_NAME_LENGHT);
        QSignalSpy spy(_dirModel, &DirectoryModel::rowsInserted);

        _watcher->emitDirectoryAppend();
        _watcher->addPath(_directory);
        _watcher->emitDirectoryAppended();

        _watcher->emitDirectoryRemove(0);
        _watcher->removePath(directory);
        _watcher->emitDirectoryRemoved();

        spy.wait(100);

        QCOMPARE(spy.count(), 1);
        QCOMPARE(_dirModel->rowCount(), 1);
        QVariant _variant = _dirModel->data(QModelIndex());
        QCOMPARE(_variant.isValid(), false);
    }

    void close()
    {
        delete _watcher;
        _watcher = nullptr;

        delete _dirModel;
        _dirModel = nullptr;
    }

private:
    QString _directory;
    FileSystemWatcherStub *_watcher = nullptr;
    DirectoryModel *_dirModel = nullptr;
};

TEST_DECLARE(DirectoryModelTestCase);

#endif // DIRECTORYMODEL_TESTCASE_HPP
