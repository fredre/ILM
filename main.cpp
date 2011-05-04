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
