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

#ifndef TMDB_MEDIA_H
#define TMDB_MEDIA_H

#include <iostream>
#include <fstream>
#include <QtCore/QCoreApplication>

using namespace std;

class TMDB_Media : public TMDB
{
public:
    TMDB_Media(QString);
    void getInfo(QString); //Must supply the path
private:
    //Methods used to get file hash
    int MAX(int,int);
    quint64 compute_hash(ifstream&);

};

#endif // TMDB_MEDIA_H
