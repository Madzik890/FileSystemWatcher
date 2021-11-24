#ifndef FILESYSTEMWATCHERNATIVE_TESTCASE_HPP
#define FILESYSTEMWATCHERNATIVE_TESTCASE_HPP

#include "multitest.h"
#include "filesystemwatcherqt_testcase.hpp"
#include "domain/system/infrastructure/filesystemwatchernatvie.hpp"

using namespace Domain::System::Core::Ports::Incoming;
using namespace Domain::System::Infrastructure;

#define EXAMPLE_PATH "./"
#define EXAMPLE_PATH_LIST QStringList({ Q_FUNC_INFO, Q_FUNC_INFO, Q_FUNC_INFO })

class FileSystemWatcherNativeTestCase : public FileSystemWatcherQtTestCase
{
    Q_OBJECT

public:
    explicit FileSystemWatcherNativeTestCase(QObject *parent = nullptr)
        : FileSystemWatcherQtTestCase(parent)
    {

    }

    ~FileSystemWatcherNativeTestCase()
    {
        if(_watcher)
        {
            delete _watcher;
            _watcher = nullptr;
        }
    }

private slots:
    virtual void init()
    {
        _watcher = dynamic_cast<IFileSystemWatcher*>(new FileSystemWatcherNative());
        Q_ASSERT(_watcher);
    }

    void close()
    {
        _watcher->stop();
        delete _watcher;
        _watcher = nullptr;
    }
};

TEST_DECLARE(FileSystemWatcherNativeTestCase);

#endif // FILESYSTEMWATCHERNATIVE_TESTCASE_HPP
