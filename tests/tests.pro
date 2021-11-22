QT += testlib widgets
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  \
    ../src/domain/system/core/ports/incoming/ifilesystemwatcher.cpp \
    ../src/domain/system/infrastructure/filesystemwatcherqt.cpp \
    main.cpp \
    stub/qfilesystemwatcherstub.cpp

HEADERS += \
    ../src/domain/system/core/ports/incoming/ifilesystemwatcher.hpp \
    ../src/domain/system/infrastructure/filesystemwatcherqt.hpp \
    filesystemwatcherqt_testcase.h \
    multitest.h \
    stub/qfilesystemwatcherstub.hpp

INCLUDEPATH += ../src
