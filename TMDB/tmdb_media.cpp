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
#include "tmdb_media.h"

using namespace std;

TMDB_Media::TMDB_Media(QString apiKey)
    :TMDB(apiKey)
{
}

 void TMDB_Media::getInfo(QString path)
 {
     //The Media.getInfo method is used to retrieve specific information about a movie
     //but instead of passing a TMDb ID, you pass a file hash & bytesize.

     ammendQueryMethod("Media.getInfo");

     //Work out the file hash for path
     ifstream f;
     quint64 myhash;

     f.open("/media/Storage/Movies/Gullivers Travels [2010 DVD].avi", ios::in|ios::binary|ios::ate);
     if (!f.is_open()) {
        cerr << "Error opening file" << endl;
     }

     myhash = compute_hash(f);

     QString hexadecimal;
     hexadecimal.setNum(myhash,16);

     //qDebug()<<hexadecimal;

     ammendCustom(hexadecimal);

     //Also ammend the file size
     f.seekg(0, ios::end);
     quint64  fileSize = f.tellg();
     f.seekg(0, ios::beg);

     ammendCustom(QString::number(fileSize));

     exeQuery();
 }

 int TMDB_Media::MAX(int x, int y)
 {
        if((x) > (y))
                return x;
        else
                return y;
 }

 quint64 TMDB_Media::compute_hash(ifstream& f)
 {
        quint64 hash, fsize;

        f.seekg(0, ios::end);
        fsize = f.tellg();
        f.seekg(0, ios::beg);

        hash = fsize;
        for(quint64 tmp = 0, i = 0; i < 65536/sizeof(tmp) && f.read((char*)&tmp, sizeof(tmp)); i++, hash += tmp);
       // qDebug("First hash %x",hash);

        f.seekg(MAX(0, (quint64)fsize - 65536), ios::beg);
        for(quint64 tmp = 0, i = 0; i < 65536/sizeof(tmp) && f.read((char*)&tmp, sizeof(tmp)); i++, hash += tmp);
        //qDebug("Second hash %x",hash);

        return hash;
 }

