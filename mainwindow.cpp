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
