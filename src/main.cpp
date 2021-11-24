#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "domain/system/core/ports/incoming/ifilesystemwatcher.hpp"
#include "domain/system/infrastructure/filesystemwatcherfactory.hpp"
#include "domain/system/core/models/directorymodel.hpp"
#include "domain/system/core/models/filemodel.hpp"

using namespace Domain::System::Core::Ports::Incoming;
using namespace Domain::System::Infrastructure;
using namespace Domain::System::Core::Models;

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);


    qmlRegisterType<Domain::System::Core::Models::FileModel>("File", 1, 0, "FileModel");
    qmlRegisterType<Domain::System::Core::Models::DirectoryModel>("Dir", 1, 0, "DirModel");
    IFileSystemWatcher *fileSystemWatcher = FileSystemWatcherFactory::createFileSystemWatcher("");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/src/ui/main.qml"));
    engine.rootContext()->setContextProperty("fileSystemWatcher", fileSystemWatcher);
    engine.load(url);

    try {
        int code = app.exec();

        delete fileSystemWatcher;
        return code;

    }  catch (std::exception &ex) {
        qCritical() << ex.what();
    }
}
