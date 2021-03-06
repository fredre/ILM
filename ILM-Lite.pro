#-------------------------------------------------
#
# Project created by QtCreator 2011-04-28T17:03:45
#
#-------------------------------------------------

QT       += core gui
QT       += webkit
QT       += network
QT       += sql
QT       += phonon
QT       += xml


TARGET = ILM-Lite
TEMPLATE = app

INCLUDEPATH += ./../../TMDB/

#The QTXML Lib
INCLUDEPATH += ./OpenSub/libmaia/trunk
LIBS += /home/fredre/ILMNEW/ILM-Lite/OpenSub/libmaia/trunk/libmaia.a


SOURCES += main.cpp\
        mainwindow.cpp \
    ./TMDB/tmdb.cpp \
    ./TMDB/tmdb_misc.cpp \
    ./TMDB/tmdb_auth.cpp \
    ./TMDB/tmdb_media.cpp \
    ./TMDB/tmdb_movies.cpp \
    ./TMDB/tmdb_people.cpp \
    dataprovider.cpp \
    dbmodel.cpp \
    about.cpp\


HEADERS  += mainwindow.h \
    ./TMDB/tmdb.h \
    ./TMDB/tmdb_misc.h \
    ./TMDB/tmdb_auth.h \
    ./TMDB/tmdb_media.h \
    ./TMDB/tmdb_movies.h \
    ./TMDB/tmdb_people.h \
    dataprovider.h \
    dbmodel.h \
    about.h







 CONFIG(release, debug|release):
 QMAKE_CFLAGS+=-pg
 QMAKE_CXXFLAGS+=-pg
 QMAKE_LFLAGS+=-pg

FORMS    += mainwindow.ui \
    about.ui

RESOURCES += \
    silk.qrc

OTHER_FILES += \
    ScreenShots/screen1.png \
    README.markdown \
