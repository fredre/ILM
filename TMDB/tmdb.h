//API TARGET 2.1

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

#ifndef TMDB_H
#define TMDB_H

#include <QCoreApplication>
#include <QString>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>

class TMDB:public QObject
{

    Q_OBJECT
public:
    TMDB(QString);
    QString getRootUrl();
    void ammendQueryMethod(QString);
    void exeQuery();

     virtual void Genres_getList(){};
     virtual void getInfo(QString){};

    void ammendCustom(QString); //Adds custom params to url. They will be added after the API must start with the start or end must not contain /


signals:
    void dataReady(QByteArray); //This wil be emitten when data is ready
    void dataError(qint32); //This wil be emitten when data is ready

protected:
    QString APIKEY;

private:
    QUrl tmdbFetchUrl;
    QString language;
    QString returnFormat;

    QNetworkAccessManager* namFetcher;

    void ammendLanguage();
    void ammendFormat();
    void ammendApi();


public Q_SLOTS:
    void finishedSlot(QNetworkReply*); //Used by networkmanager to notify internally about data gathered




};

#endif // TMDB_H1
