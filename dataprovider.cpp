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

#include "dataprovider.h"
#include <QDir>
#include <QDebug>

DataProvider::DataProvider(QObject *parent) :
    QObject(parent)
{
  //Create database connection. We will use the name ILM.db
  db = QSqlDatabase::addDatabase("QSQLITE");

  #ifdef Q_OS_LINUX
  QString path(QDir::home().path());
  path.append(QDir::separator()).append("ilmdb.sqlite");
  path = QDir::toNativeSeparators(path);

  db.setDatabaseName(path);

  qDebug() <<db.open();
  #endif

  //Create the movie table
 CreateMovieTable();


  dbmodel = new QSqlTableModel(this,db);
  dbmodel->setTable("MovieInfo");
  dbmodel->select();

  qDebug() << dbmodel->lastError();
}

bool DataProvider::CreateMovieTable()
{
   //The project contains only one table called "MovieInfo"
   bool ret = false;
   if (db.isOpen())
       {
       QSqlQuery query;
       ret = query.exec("CREATE TABLE MovieInfo("
                            "Name  TEXT,"
                            "Path NUMERIC"
                            ");"
                        );
       }
   return ret;
   }

QSqlTableModel *DataProvider::getModel()
{
    return dbmodel;
}
