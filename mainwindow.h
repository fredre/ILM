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

private:
    Ui::MainWindow *ui;
    QStringList *strlstMovieHeaders; //Headers for tblMovies
    QStringList *strlstMovieTypes; //The types of movies that should be loaded
    QSettings *settings; //Keeps appilcation settings
};

#endif // MAINWINDOW_H
