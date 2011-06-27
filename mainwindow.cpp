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

     //The player
     player = new Phonon::VideoPlayer(Phonon::VideoCategory);

    //The position slider
     Phonon::SeekSlider *slider = new Phonon::SeekSlider;
     slider->setMediaObject(player->mediaObject());
     slider->show();

     //The volume controll
     Phonon::VolumeSlider *volumeSlider = new Phonon::VolumeSlider;
     volumeSlider->setAudioOutput(player->audioOutput());

     //First add the player
     ui->VidWinMainVertical->addWidget(player,5);

     //Then add slider
     ui->VidWinMainVertical->addWidget(slider);

     //Add the volume
     ui->VidMinMainHor->addWidget(volumeSlider);


    //Setup the icon for refresh toobaritem TODO:(Provide fallback for windows)
    //btw: here are the standard names as defined by freedesktop [http://standards.freedesktop.org/icon-naming-spec/latest/ar01s04.html]
    QIcon refreshIcon = QIcon::fromTheme("folder-new");
    ui->actionRefresh->setIcon(refreshIcon);

    //Setup the icopn for the play button
    ui->btnPreviewPlay->setIcon(QIcon::fromTheme("media-playback-start"));
    ui->btnPrevieStop->setIcon(QIcon::fromTheme("media-playback-stop"));

    //Setup the QStringList that will keep the types of movies that should be loaded
    strlstMovieTypes = new QStringList();
    strlstMovieTypes->append("*.avi");


    //Setup the settings class
    settings = new QSettings();

    //Hide the loading progress bar
    ui->pbLoading->hide();

    //Setup the database
    myData = new DataProvider();


    //Get the model for our one and only table and set to tblMoviesSql
    ui->tblMoviesSql->setModel(myData->getModel());

    ui->tblMoviesSql->resizeColumnsToContents();

    ui->tblMoviesSql->horizontalHeader()->setStretchLastSection( true );

    //Make sure the windows is mazimized
    this->setWindowState(Qt::WindowMaximized);

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
  //TODO: Not using settings anymore !!!!
  QString dir = QFileDialog::getExistingDirectory(this, tr("Open Movie Directory"),settings->value("MovieDir","/home").toString(),QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);

  //We must load all the movies files in the directory that the user selected
  QDir *dirCurrent =  new QDir(dir);


  //Write open dir to Watch table. If false is returned the folder is already part of the watch list yo"
  bool load = myData->addWatchFolder(dir);

  //Call scanfolder that wil go looki looki snooki rap husssle
  if(load){

      //QFuture<void> future = QtConcurrent::run(this, &MainWindow::scanFolder,dirCurrent); //Once off thread
      scanFolder(dirCurrent);
  }

}

void MainWindow::scanFolder(QDir *scanme)
{
    QList <QFileInfo> filstFiles(scanme->entryInfoList(*strlstMovieTypes, QDir::Files | QDir::NoSymLinks));

    //First step put myData in Insert mode (This has to do with speed improvements) we want to wrap all in one Transaction
    myData->startBigTransaction();
    foreach (const QFileInfo &i, filstFiles) {
      myData->addVirginMovie(i.fileName(),i.absoluteFilePath());
    }
    myData->endBigTransaction();

    ui->tblMoviesSql->resizeColumnsToContents();

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




void MainWindow::on_tblMoviesSql_clicked(QModelIndex index)
{

   //Get the filename
   QString name = index.sibling(index.row(),1).data(Qt::DisplayRole).toString();

   //Get the full path
   QString path = index.sibling(index.row(),3).data(Qt::DisplayRole).toString();



   //Set the name of the preview for the preview window
   ui->lblPreViewTitle->setText(name);

   //Set the correct vid path for when the preview play button is clicked
   player->load(Phonon::MediaSource(path));

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

void MainWindow::on_btnPreviewPlay_clicked()
{
  player->play();
}

void MainWindow::on_btnPrevieStop_clicked()
{
    player->stop();
}

void MainWindow::on_action_About_triggered()
{
    //Show a nice about box
    QString date = QString::fromLocal8Bit(__DATE__);
    QString time = QString::fromLocal8Bit(__TIME__);
    QMessageBox::about(this,"About ILM","Non Gnome/KDE icons by: http://www.famfamfam.com/lab/icons/silk/");
}
