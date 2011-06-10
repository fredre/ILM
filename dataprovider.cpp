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
#include <QModelIndex>
#include <QDate>

DataProvider::DataProvider(QObject *parent) :
    QObject(parent)
{
  //Create database connection. We will use the name ILM.db
  db = QSqlDatabase::addDatabase("QSQLITE");

  #ifdef Q_OS_LINUX
  QString path(QDir::home().path());
  path.append(QDir::separator()).append("ilmdb.sqlite");
  path = QDir::toNativeSeparators(path);

  //db.setDatabaseName(path);
  db.setDatabaseName(":memory:");



  qDebug() <<db.open();
  #endif

  //We Dont care about cates failure so speed things up and turn waiting for OS off
  //This can be commented out for a big speed hit but db will be more reliable if power goes
  db.exec("PRAGMA synchronous = OFF");
  db.exec("PRAGMA journal_mode = MEMORY");

  //Create the movie table
  CreateMovieTable();


  dbmodel = new DBModel(this);
  dbmodel->setTable("MovieInfo");
  dbmodel->select();

  //Get the date today
  todayDate = new QDate(QDate::currentDate());


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
                            "Played NUMERIC,"                //If the user has played the movie before
                            "FileName  TEXT,"
                            "DateAdded NUMERIC,"
                            "Path NUMERIC"

                            ");"
                        );
       }
   return ret;
   }

DBModel *DataProvider::getModel()
{
    //Returns the model for the Table MovieInfo
    return dbmodel;
}

void DataProvider::startBigTransaction()
{
    db.transaction();
}

void DataProvider::endBigTransaction()
{
    db.commit();


}


void DataProvider::addVirginMovie(QString fName,QString fPath)
{
    //Adds a Virgin movie to the Table. A movie is assummed virgin if it has never been added before
    //We want to add the Filename and the FilePath
    if (db.isOpen())
        {
        QSqlQuery query;



        query.exec(QString("INSERT INTO MovieInfo values('%3','%1','%4','%2')").arg(fName).arg(fPath).arg("0").arg(todayDate->toString()));
        }
    dbmodel->select();
}



