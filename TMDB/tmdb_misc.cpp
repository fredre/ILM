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
#include "tmdb_misc.h"


TMDB_Misc::TMDB_Misc(QString apiKey)
    :TMDB(apiKey)
{

}

void TMDB_Misc::Genres_getList()
{
    /*
    The Genres.getList method is used to retrieve a list of valid genres within TMDb.
    You can also request the translated values by passing the language option.
    */
    ammendQueryMethod("Genres.getList");
    exeQuery();
}
