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

    QVariant value = QSqlQueryModel::data(index, role);
        if (value.isValid() && role == Qt::DisplayRole) {
            if (index.column() == 0)
                return value.toString().prepend("#");
            else if (index.column() == 2)
                return value.toString().toUpper();
        }
        if (role == Qt::TextColorRole && index.column() == 1)
            return qVariantFromValue(QColor(Qt::blue));
        return value;

}
