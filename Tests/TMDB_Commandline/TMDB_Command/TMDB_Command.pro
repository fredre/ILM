#-------------------------------------------------
#
# Project created by QtCreator 2011-05-22T15:06:39
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = TMDB_Command
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

SOURCES += ./../../TMDB/*.cpp

HEADERS  += ./../../TMDB/*.h

INCLUDEPATH += ./../../TMDB/
