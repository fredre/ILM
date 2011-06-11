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

#include <QtGui>

#include "dbmodel.h"



DBModel::DBModel(QObject *parent)
    : QSqlTableModel(parent)
{

}

 QVariant DBModel::headerData(int section,Qt::Orientation orientation, int role) const
 {


//     if(role==Qt::SizeHintRole && orientation == Qt::Horizontal){
//         //Change the size of the firs col
//         if(section ==0)
//         {

//            return(qVariantFromValue(QSize(2,2)));
//         }

//     }

      if(role==Qt::DisplayRole){
          //Dont display any text for the Played col.
          if(section ==0 && orientation == Qt::Horizontal){
              return( QString( "" ) );
          }
      }

      if (role == Qt::DecorationRole) {

          //Display a nice icon istread of the default text
          if(section ==0 && orientation == Qt::Horizontal)
          {
              return qVariantFromValue(QIcon::fromTheme("video-x-generic"));
          }
      }

     return QSqlTableModel::headerData( section, orientation, role );

 }

QVariant DBModel::data(const QModelIndex &index, int role) const
{

    QVariant value = QSqlTableModel::data(index, role);

        if (role == Qt::DecorationRole) {
            //The Played col show nice icon indicating played
            if (index.column() == 0){
                if(value.toInt()== 1){
                    return qVariantFromValue(QIcon::fromTheme("media-playback-start"));
                }
            }

        }

        if(role==Qt::DisplayRole)
        {
           //Dont show any text for the Played col we have icon
            if(index.column()==0)
            {
                return "";
            }
        }

       //Only for every 2nd background
       if (role == Qt::BackgroundRole && (index.row()%2)==1 ){
            return qVariantFromValue(QColor(231,231,231,255));
        }

        return value;

}


