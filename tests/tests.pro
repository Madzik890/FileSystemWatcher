QT += testlib widgets
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  \
    ../src/domain/system/core/models/directorymodel.cpp \
    ../src/domain/system/core/models/filemodel.cpp \
    ../src/domain/system/core/ports/incoming/idirectorywatcher.cpp \
    ../src/domain/system/core/ports/incoming/ifilesystemwatcher.cpp \
    ../src/domain/system/infrastructure/directorywatcher.cpp \
    ../src/domain/system/infrastructure/filesystemwatchernatvie.cpp \
    ../src/domain/system/infrastructure/filesystemwatcherqt.cpp \
    main.cpp \
    stub/filesystemwatcherstub.cpp \
    stub/qfilesystemwatcherstub.cpp \
    tools/qstring.cpp

HEADERS += \
    ../src/domain/system/core/models/directorymodel.hpp \
    ../src/domain/system/core/models/filemodel.hpp \
    ../src/domain/system/core/ports/incoming/idirectorywatcher.hpp \
    ../src/domain/system/core/ports/incoming/ifilesystemwatcher.hpp \
    ../src/domain/system/infrastructure/directorywatcher.hpp \
    ../src/domain/system/infrastructure/filesystemwatchernatvie.hpp \
    ../src/domain/system/infrastructure/filesystemwatcherqt.hpp \
    directorymodel_testcase.hpp \
    filemodel_testcase.hpp \
    filesystemwatchernative_testcase.hpp \
    filesystemwatcherqt_testcase.hpp \
    multitest.h \
    stub/filesystemwatcherstub.hpp \
    stub/qfilesystemwatcherstub.hpp \
    tools/qstring.hpp

INCLUDEPATH += ../src
