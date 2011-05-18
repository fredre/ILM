#-------------------------------------------------
#
# Project created by QtCreator 2011-04-28T17:03:45
#
#-------------------------------------------------

QT       += core gui
QT       += webkit
QT       += network

TARGET = ILM-Lite
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tmdb.cpp \
    tmdb_misc.cpp \
    tmdb_auth.cpp \
    tmdb_media.cpp \
    tmdb_movies.cpp \
    tmdb_people.cpp

HEADERS  += mainwindow.h \
    tmdb.h \
    tmdb_misc.h \
    tmdb_auth.h \
    tmdb_media.h \
    tmdb_movies.h \
    tmdb_people.h

FORMS    += mainwindow.ui

RESOURCES += \
    Resources.qrc

OTHER_FILES += \
    ScreenShots/screen1.png \
    README.markdown \
<<<<<<< HEAD
