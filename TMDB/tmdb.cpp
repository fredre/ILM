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

#include "tmdb.h"
#include "qdebug.h"

TMDB::TMDB(QString apiKey)
{
    //Set the language to be used (Currently en only)
    language = "en";

    //The format in what the q will be returned (Currently XML only)
    returnFormat = "xml";

    //Set the API Key
    APIKEY = apiKey;

    //Set the Sceme of the tmbdFetchUrl to be http
    tmdbFetchUrl.setScheme("http");

    //Set the host
    tmdbFetchUrl.setHost("api.themoviedb.org");

    //Adds the api version (Currently 2.1)
    tmdbFetchUrl.setPath("/2.1/");

    //Init the network access manager
    namFetcher = new QNetworkAccessManager(this);
    QObject::connect(namFetcher, SIGNAL(finished(QNetworkReply*)),this, SLOT(finishedSlot(QNetworkReply*)));



}


void TMDB::finishedSlot(QNetworkReply * reply)
{
//This will happen if the nam is finshed
    if (reply->error() == QNetworkReply::NoError)
       {
           QByteArray bytes = reply->readAll();  // bytes

           emit dataReady(bytes);

       }
        //Some http error received. TODO add some propr eroro handling here
       else
       {
          //Emit an error with the coresponding code (QNetworkReply::NetworkError)
          emit dataError(reply->error());

       }


       reply->deleteLater();

}

void TMDB::exeQuery()
{
    namFetcher->get(QNetworkRequest(tmdbFetchUrl));

}

 QString TMDB::getRootUrl()
 {
     //This function is only used for testing purposes.
     //It returns the tmdbFetchUrl.
     return tmdbFetchUrl.toString();
 }

 void TMDB::ammendQueryMethod(QString Method)
{
 //This function will ammend the actual Queryname to the url that will be fetched
 QUrl ammend(Method);

 tmdbFetchUrl = tmdbFetchUrl.resolved(Method);
 ammendLanguage();
 ammendFormat();
 ammendApi();


}

 void TMDB::ammendLanguage()
 {
    //This method will ammend the language to tmdbFetchUrl. It is used internally
     tmdbFetchUrl = tmdbFetchUrl.resolved(tmdbFetchUrl.toString()+QUrl("/"+language).toString());
 }

 void TMDB::ammendFormat()
 {
  //This method will ammend the language to tmdbFetchUrl it is used internally
  tmdbFetchUrl = tmdbFetchUrl.resolved(tmdbFetchUrl.toString()+QUrl("/"+returnFormat).toString());
 }

 void TMDB::ammendApi()
 {
    tmdbFetchUrl = tmdbFetchUrl.resolved(tmdbFetchUrl.toString()+QUrl("/"+APIKEY).toString());
 }
