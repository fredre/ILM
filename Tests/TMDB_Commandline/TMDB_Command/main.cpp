/*
This file is part of ILM.

    ILM is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    ILM is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with ILM.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <QtCore/QCoreApplication>
#include <QDebug>
#include <tmdb.h>
#include <tmdb_misc.h>

// main.cpp
#include <QtCore>

class Task : public QObject
{
    Q_OBJECT
public:
    Task(QObject *parent = 0) : QObject(parent) {}

public slots:
    void run()
    {
        // Test the Genres.getList method
        //TMDB_Misc *misc = new TMDB_Misc("39ad119048b5408cb0fa038e929a3517");

        //QObject::connect(misc, SIGNAL(dataReady(QByteArray)), this, SLOT(showData(QByteArray)));
        //QObject::connect(misc, SIGNAL(dataError(qint32)), this, SLOT(dataError(qint32)));

        TMDB *tm = new TMDB_Misc("39ad119048b5408cb0fa038e929a3517");

        QObject::connect(tm, SIGNAL(dataReady(QByteArray)), this, SLOT(showData(QByteArray)));
        QObject::connect(tm, SIGNAL(dataError(qint32)), this, SLOT(dataError(qint32)));


        tm->Genres_getList();

    }

    void showData(QByteArray by)
    {
        QString show(by);
        qDebug()<<show;
        emit finished();
    }

    void dataError(qint32 ercode)
    {
        qDebug()<<"OOPS ERROR: "<<ercode;
    }

signals:
    void finished();
};

#include "main.moc"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Task parented to the application so that it
    // will be deleted by the application.
    Task *task = new Task(&a);

    // This will cause the application to exit when
    // the task signals finished.
    QObject::connect(task, SIGNAL(finished()), &a, SLOT(quit()));

    // This will run the task from the application event loop.
    QTimer::singleShot(0, task, SLOT(run()));

    return a.exec();
}
