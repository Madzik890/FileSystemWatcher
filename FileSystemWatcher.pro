QT += quick

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        ./src/main.cpp \
        src/domain/system/core/models/directorymodel.cpp \
        src/domain/system/core/models/filemodel.cpp \
        src/domain/system/core/ports/incoming/idirectorywatcher.cpp \
        src/domain/system/core/ports/incoming/ifilesystemwatcher.cpp \
        src/domain/system/infrastructure/directorywatcher.cpp \
        src/domain/system/infrastructure/filesystemwatcherfactory.cpp \
        src/domain/system/infrastructure/filesystemwatchernatvie.cpp \
        src/domain/system/infrastructure/filesystemwatcherqt.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    src/domain/system/core/dictionaries/fileeventtype.hpp \
    src/domain/system/core/models/directorymodel.hpp \
    src/domain/system/core/models/fileitem.hpp \
    src/domain/system/core/models/filemodel.hpp \
    src/domain/system/core/ports/incoming/idirectorywatcher.hpp \
    src/domain/system/core/ports/incoming/ifilesystemwatcher.hpp \
    src/domain/system/infrastructure/directorywatcher.hpp \
    src/domain/system/infrastructure/filesystemwatcherfactory.hpp \
    src/domain/system/infrastructure/filesystemwatchernatvie.hpp \
    src/domain/system/infrastructure/filesystemwatcherqt.hpp

INCLUDEPATH += src
