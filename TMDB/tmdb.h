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

#include <QString>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class TMDB
{

public:
    TMDB(QString);
    QString getRootUrl();
    void ammendQueryMethod(QString);

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




};

#endif // TMDB_H1
