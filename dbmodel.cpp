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

QVariant DBModel::data(const QModelIndex &index, int role) const
{

    QVariant value = QSqlTableModel::data(index, role);

        if (role == Qt::DecorationRole) {
            //The Played col show nice icon indicating played
            if (index.column() == 0){
                if(value.toInt()== 0){
                    return qVariantFromValue(QIcon::fromTheme("view-refresh"));
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


