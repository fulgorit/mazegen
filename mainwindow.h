#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mazebacktracking.h"
//#include "renderthread.h"
#include "mazewidget.h"
#include "mazescene.h"

#define MAX 61  // 30 * 2 + 1
#define CELL 900  // 30 * 30
#define WALL 1
#define PATH 0

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void saveToImage();
    void solveTheMaze();
    void openAMazeTXTFile();
    void saveAMazeTxtFile();
    void renderInImage();
    bool find_path(int x, int y);
    void solveMaze();
    void bt(int x,int y,int stepmatrix[MAX][MAX]);

    void createMenu();

    QMenuBar *menuBar;
    QMenu *fileMenu;
    QAction *exitAction;

    RenderThread thread;
    mazeBacktracking * mmaze;
    mazeBacktracking * mmazeRead;
    MazeWidget * mw;

    mazeData * maze1;

    View * view;

    bool viewResolution;

    mazeData * m_backup;

    QPixmap withoutSolver;


private:
    Ui::MainWindow *ui;

private slots:

    void on_pushButton_3_clicked();
    void on_pushButton_clicked();
    void on_pushButton_4_clicked();
    //void on_pushButton_5_clicked();
    void viewOpenGl();

    void displayPosCamera();


    void on_pushButton_2_toggled(bool checked);
    void quit();

	
};

#endif // MAINWINDOW_H
