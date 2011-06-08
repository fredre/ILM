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

#include <QtNetwork>
#include <QCheckBox>
#include <QPushButton>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Setup the icon for refresh toobaritem TODO:(Provide fallback for windows)
    //btw: here are the standard names as defined by freedesktop [http://standards.freedesktop.org/icon-naming-spec/latest/ar01s04.html]
    QIcon refreshIcon = QIcon::fromTheme("view-refresh");
    ui->actionRefresh->setIcon(refreshIcon);

   /*
    //Old code brav
    //Setup the QStringList that will keep the tblMovies headers
    strlstMovieHeaders = new QStringList();
    strlstMovieHeaders->append("File Name");
    strlstMovieHeaders->append("Full Path");
   */
    //Setup the QStringList that will keep the types of movies that should be loaded
    strlstMovieTypes = new QStringList();
    strlstMovieTypes->append("*.avi");

    /*
    //Setup tblMovies
    ui->tblMovies->clear();
    ui->tblMovies->setColumnCount(strlstMovieHeaders->count());
    ui->tblMovies->setHorizontalHeaderLabels(*strlstMovieHeaders);
   */

    //Setup the settings class
    settings = new QSettings();

    //Hide the loading progress bar
    ui->pbLoading->hide();

    //Setup the database
    myData = new DataProvider();



    //Get the model for our one and only table and set to tblMoviesSql
    ui->tblMoviesSql->setModel(myData->getModel());


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


  //First step put myData in Insert mode (This has to do with speed improvements) we want to wrap all in one Transaction
  myData->startBigTransaction();
  foreach (const QFileInfo &i, filstFiles) {
    myData->addVirginMovie(i.fileName(),i.absoluteFilePath());
  }
  myData->endBigTransaction();

 // updatePlayedIcn();//Show nice playd icn to user in tblview
}

void MainWindow::updatePlayedIcn()
{
    //TODO add to resourses and figure out how to use icon in treeview
   // QPushButton *button = new QPushButton;
    //button->setIcon(QIcon::fromTheme("view-refresh"));
    //button->setFlat(true);


    //Adds an icon to show if the movie has been played
    //ui->tblMoviesSql->setIndexWidget(myData->getModel()->index(2,2),button);
}

void MainWindow::on_tblMovies_cellClicked(int row, int column)
{
    qDebug()<<row<<column;

    //Get only the movie name
    QString name = ui->tblMovies->item(row,0)->text();

    //Remove the ext
    name = name.remove(name.count()-4,4);

    //Set the cache
    QNetworkDiskCache *diskCache = new QNetworkDiskCache(this);
    //Cache directory should be the current movie directory
    diskCache->setCacheDirectory(settings->value("MovieDir").toString());
    ui->wbVwMovieInfi->page()->networkAccessManager()->setCache(diskCache);



    //Set the search URL
    ui->wbVwMovieInfi->setUrl(QUrl("http://www.themoviedb.org/search?search="+name));

}

void MainWindow::on_actionMovie_Information_triggered()
{
  //If the user closed ui->dckWdgtMovieInfo show it again
  ui->dckWdgtMovieInfo->showNormal();

}

void MainWindow::on_wbVwMovieInfi_loadStarted()
{
  //Show the progress bar
  ui->pbLoading->show();
}

void MainWindow::on_wbVwMovieInfi_loadProgress(int progress)
{
   //Update the progress bar
   ui->pbLoading->setValue(progress);
}

void MainWindow::on_wbVwMovieInfi_loadFinished(bool )
{
  ui->pbLoading->hide();
}



