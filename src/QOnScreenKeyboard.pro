#-------------------------------------------------
#
# Project created by QtCreator 2016-11-24T15:16:05
#
#-------------------------------------------------

QT       += widgets

TARGET = QOnScreenKeyboard
TEMPLATE = lib

DEFINES += QONSCREENKEYBOARD_LIBRARY

SOURCES += qonscreenkeyboard.cpp \
    numpadkeyboard.cpp \
    fullkeyboard.cpp

HEADERS += qonscreenkeyboard.h\
        numpadkeyboard.h \
        IKeyboard.h \
        fullkeyboard.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    numpadkeyboard.ui \
    fullkeyboard.ui

INSTALL_PREFIX = /usr/include/
INSTALL_HEADERS = qonscreenkeyboard.h \ 

include(installheaders.pri)
