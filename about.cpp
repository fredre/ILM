#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);

    //Make sure the windows is mazimized
    this->setWindowState(Qt::WindowMaximized);
}

About::~About()
{
    delete ui;
}
