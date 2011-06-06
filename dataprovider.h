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

#ifndef DATAPROVIDER_H
#define DATAPROVIDER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlTableModel>
#include <QFile>
#include <QSqlQuery>

class DataProvider : public QObject
{
    Q_OBJECT
public:
    explicit DataProvider(QObject *parent = 0);
    QSqlTableModel *getModel();
    void addVirginMovie(QString,QString);
    void startBigTransaction();
    void endBigTransaction();

signals:

public slots:

private:
     QSqlDatabase db;
     QSqlTableModel *dbmodel;

     bool CreateMovieTable();


};

#endif // DATAPROVIDER_H
