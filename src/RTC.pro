#-------------------------------------------------
#
# Project created by QtCreator 2013-09-18T15:43:33
#
#-------------------------------------------------

QT       += core gui

TARGET = RTC
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    monster.cpp \
    player.cpp \
    level.cpp \
    menulabel.cpp \
    score.cpp \
    definitions.cpp

HEADERS  += mainwindow.h \
    monster.h \
    player.h \
    level.h \
    menulabel.h \
    score.h \
    definitions.h

FORMS    += mainwindow.ui

RC_FILE = appres.rc

OTHER_FILES += \
    appres.rc
