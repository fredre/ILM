#-------------------------------------------------
#
# Project created by QtCreator 2011-05-20T19:18:45
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_tmdb_testtest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_tmdb_testtest.cpp

SOURCES += ./../../TMDB/*.cpp

HEADERS  += ./../../TMDB/*.h

INCLUDEPATH += ./../../TMDB/





DEFINES += SRCDIR=\\\"$$PWD/\\\"
