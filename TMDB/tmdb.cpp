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



TMDB::TMDB(QString apiKey)
{
    //Set the API Key
    APIKEY = apiKey;

    //Set the Sceme of the tmbdFetchUrl to be http
    tmdbFetchUrl.setScheme("http");

    //Set the host
    tmdbFetchUrl.setHost("api.themoviedb.org");

    //Adds the api version (Currently 2.1)
    tmdbFetchUrl.resolved(QString("/2.1"));


}
