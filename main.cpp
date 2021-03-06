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

#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    //Default names so that settings can use it later
    QCoreApplication::setOrganizationName("The ILM project");
    QCoreApplication::setOrganizationDomain("Get gitbub page !!!");
    QCoreApplication::setApplicationName("ILM");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
