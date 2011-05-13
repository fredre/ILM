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


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qdir.h>
#include <QtDebug>
#include <qsettings.h>




namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionE_xit_triggered();

    void on_actionRefresh_triggered();

    void on_tblMovies_cellClicked(int row, int column);

    void on_actionMovie_Information_triggered();

    void on_wbVwMovieInfi_loadStarted();

    void on_wbVwMovieInfi_loadProgress(int progress);

    void on_wbVwMovieInfi_loadFinished(bool );

private:
    Ui::MainWindow *ui;
    QStringList *strlstMovieHeaders; //Headers for tblMovies
    QStringList *strlstMovieTypes; //The types of movies that should be loaded
    QSettings *settings; //Keeps appilcation settings
};

#endif // MAINWINDOW_H
