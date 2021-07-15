QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    syntaxhighlighter.cpp \
    ../../Core/balance_tags.cpp \
    ../../Core/compress.cpp \
    ../../Core/minify.cpp \
    ../../Core/parse_tree.cpp \
    ../../Core/prettifying.cpp \
    ../../Core/xml2json.cpp

HEADERS += \
    mainwindow.h \
    syntaxhighlighter.h \
    ../../Core/types.h \
    ../../Core/balance_tags.h \
    ../../Core/compress.h \
    ../../Core/minify.h \
    ../../Core/parse_tree.h \
    ../../Core/prettifying.h \
    ../../Core/xml2json.h



FORMS += \
    mainwindow.ui

QMAKE_CXXFLAGS+= -openmp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

