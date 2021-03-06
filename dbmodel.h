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

#ifndef DBMODEL_H
#define DBMODEL_H

#include <QSqlTableModel>
#include <QString>
#include <QSqlDatabase>

class  DBModel : public QSqlTableModel
{
    Q_OBJECT

public:
     DBModel(QObject *parent = 0);

    QVariant data(const QModelIndex &item, int role) const;
    QVariant headerData(int section,Qt::Orientation orientation, int role) const;

};


#endif // DBMODEL_H
