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


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qglobal.h"
#include "QFileDialog"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Setup the icon for refresh toobaritem TODO:(Provide fallback for windows)
    //btw: here are the standard names as defined by freedesktop [http://standards.freedesktop.org/icon-naming-spec/latest/ar01s04.html]
    QIcon refreshIcon = QIcon::fromTheme("view-refresh");
    ui->actionRefresh->setIcon(refreshIcon);

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

    //Setup the settings class
    settings = new QSettings();



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
  //Ask user to select directory
  QString dir = QFileDialog::getExistingDirectory(this, tr("Open Movie Directory"),settings->value("MovieDir","/home").toString(),QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);

  //We must load all the movies files in the directory that the user selected
  QDir *dirCurrent =  new QDir(dir);

  QList <QFileInfo> filstFiles(dirCurrent->entryInfoList(*strlstMovieTypes, QDir::Files | QDir::NoSymLinks));

  //Save opened dir as "MovieDir"
  settings->setValue("MovieDir",dir);

  //qDebug()<<*strlstFiles;

  //Add to table (Move to seprate function)
  int row=0;
  ui->tblMovies->setRowCount(filstFiles.count());

   //Set the filenames
   foreach (const QFileInfo &i, filstFiles) {
    ui->tblMovies->setItem(row, 0, new QTableWidgetItem(i.fileName()));
    ui->tblMovies->setItem(row, 1, new QTableWidgetItem(i.absoluteFilePath()));
    row++;
   }

}

void MainWindow::on_tblMovies_cellClicked(int row, int column)
{
    qDebug()<<row<<column;
}

void MainWindow::on_actionMovie_Information_triggered()
{
  //If the user closed ui->dckWdgtMovieInfo show it again
  ui->dckWdgtMovieInfo->showNormal();

}
