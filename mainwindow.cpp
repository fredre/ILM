#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Setup the QStringList that will keep the tblMovies headers
    strlstMovieHeaders = new QStringList();
    strlstMovieHeaders->append("File Name");
    strlstMovieHeaders->append("Full Path");

    //Setup the QStringList that will keep the types of movies that should be loaded
    strlstMovieTypes = new QStringList();
    strlstMovieTypes->append("*.avi");

    //Setup tblMovies
    ui->tblMovies->clear();
    ui->tblMovies->setColumnCount(strlstMovieHeaders->count());
    ui->tblMovies->setHorizontalHeaderLabels(*strlstMovieHeaders);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionE_xit_triggered()
{
    //Close the application
    this->close();
}

void MainWindow::on_actionRefresh_triggered()
{

  //We must load all the movies files in the current directory into the table
  QDir *dirCurrent =  new QDir(QDir::currentPath());

  QStringList *strlstFiles = new QStringList(dirCurrent->entryList(*strlstMovieTypes, QDir::Files | QDir::NoSymLinks));

  qDebug()<<*strlstFiles;

  //Add to table (Move to seprate function)
  int row,column =0;
  ui->tblMovies->setRowCount(strlstFiles->count());
  QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1").arg((row+1)*(column+1)));
  ui->tblMovies->setItem(row, column, newItem);


}
