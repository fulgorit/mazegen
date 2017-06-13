#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <time.h>
#include <QGraphicsItem>
#include <QPicture>
#include <QPainter>
#include <QDebug>
#include <QDir>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QHBoxLayout>
#include  "mazescene.h"
#include "QPixmapCache"
#include <QTimer>

#define MAX 61  // 30 * 2 + 1
#define CELL 900  // 30 * 30
#define WALL 1
#define PATH 0
#define RED  2
#define S  3
#define G  4
#define TRUE 1
#define FALSE 0


void MainWindow::createMenu()
{
    menuBar = new QMenuBar;

    fileMenu = new QMenu(tr("&File"), this);
    exitAction = fileMenu->addAction(tr("E&xit"));
    menuBar->addMenu(fileMenu);

    connect(exitAction, SIGNAL(triggered()), this, SLOT(quit()));

}

void MainWindow::quit()
{

QApplication::quit();

}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->retranslateUi(this);

    menuBar = new QMenuBar;
    fileMenu = new QMenu(tr("&File"), this);
    exitAction = fileMenu->addAction(tr("E&xit"));
    menuBar->addMenu(fileMenu);
    connect(exitAction, SIGNAL(triggered()), this, SLOT(quit()));

    setMenuBar(menuBar);

    ui->spinBox->setMinimum(4);
    ui->spinBox->setMaximum(26);
    ui->pushButton_2->setEnabled(false);

    setWindowTitle("Maze Qt5.7.1 with OpenGL support (test)");

    ui->spinBox->setValue(10);

    viewResolution=false;
    ui->pushButton_2->setCheckable(true);

    mw=new MazeWidget();
    QHBoxLayout *layout = new QHBoxLayout;


    layout->addWidget(mw);


    mw->setGeometry(0,0,300,300);
    ui->frame->setLayout(layout);

    //ui->pushButton_4->setVisible(false);
    QPixmapCache::setCacheLimit(100 * 1024); // 100 MB


    QVector<Light> lights;
    lights << Light(QPointF(3.5, 2.5), 1)
           << Light(QPointF(3.5, 6.5), 1)
           << Light(QPointF(1.5, 10.5), 0.3);


    view=new View();

    view->hide();

    QHBoxLayout *layout2 = new QHBoxLayout;
    layout2->addWidget(view);

    ui->frame_2->setLayout(layout2);

    qRegisterMetaType<QPicture>("QPicture");

    //createMenu();



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    mw->update();
    //viewResolution=false;
    ui->pushButton_2->setChecked(false);
    ui->pushButton_2->setText("Not solved");


    renderInImage();
    QTimer::singleShot(200, this, SLOT(viewOpenGl()));


}

void MainWindow::renderInImage()
{

    int size=ui->spinBox->value();

    int n=ui->comboBox->currentIndex();
   // qDebug() << "Current index" << n;

    mw->buildMaze(size,1,n);

    withoutSolver = QPixmap::grabWidget(mw);
    ui->pushButton_2->setEnabled(true);

    mw->m1->display();

}

void MainWindow::displayPosCamera()
{

    //qDebug() << "X:1" << int(view->getCameraX()/10);
    //qDebug() << "Y:1" << int(view->getCameraY()/10);

    mw->setCameraPos(int(view->getCameraX()),int(view->getCameraY()));
    mw->update();

}

void MainWindow::viewOpenGl()
{


    maze1=new mazeData(mw->m1);

    QVector<Light> lights;
    lights << Light(QPointF(3.5, 2.5), 1)
           << Light(QPointF(3.5, 6.5), 1)
           << Light(QPointF(1.5, 10.5), 0.3);

    MazeScene *scene = new MazeScene(lights, maze1, 61, 61);



    view->setScene(scene);

    view->show();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(displayPosCamera()));
    timer->start(500);



     update();


}


void MainWindow::on_pushButton_3_clicked()
{

    saveToImage();

}

void MainWindow::saveToImage()
{

    QPixmap originalPixmap = QPixmap::grabWidget(mw);
    originalPixmap.save("maze.png", "png");


}

void MainWindow::solveTheMaze()
{


}

void MainWindow::solveMaze(){


    int dx[4] = {-1,0,1,0};
    int dy[4] = {0,-1,0,1};

    QList<QPoint> q;

    bool found = false;

    int arr[MAX][MAX];

    arr[1][0] = 0;

    QPoint p1(1,0);

    q.insert(0,p1);

    while( q.length() > 0 ){

        QPoint entry = q.takeFirst();
        int x = entry.x();
        int y = entry.y();


        for( int i = 0; i < 4; ++i ){
                   if( maze1->maze_data[ y + dy[i] ][ x + dx[i] ] == 0 ){
                                                        if( maze1->maze_data[ y + dy[i] ][ x + dx[i] ] == PATH ){
                                                                arr[ y + dy[i] ][ x + dx[i] ] = arr[y][x] + 1;

                                                                QPoint p2( x + dx[i], y + dy[i] );
                                                                q.insert(q.length(),p2);
                                                        } else if( maze1->maze_data[ y + dy[i] ][ x + dx[i] ] == 'G' ){
                                                                found = true;
                                                                arr[ y + dy[i] ][ x + dx[i] ] = arr[y][x] + 1;
                                                                QPoint p3(x + dx[i], y + dy[i]);

                                                                q.insert(q.length(),p3);

                                                        } else {
                                                                continue;
                                                        }
                                                }
                                                if( found ){ break; }
                                        }
                                        if( found ){ break; }
                                }
    if( found ){ QPoint g = q.takeLast(); bt(g.x(),g.y(),arr); } else {qDebug() << "error"; }


   }


void MainWindow::bt(int x,int y,int stepmatrix[MAX][MAX]){

    int dx[4] = {-1,0,1,0};
    int dy[4] = {0,-1,0,1};

    int currentsteps = stepmatrix[y][x];
    if( maze1->maze_data[y][x] == S ){
                                        return;
                                } else if( maze1->maze_data[y][x] == WALL ){
                                        return;
                                } else if( maze1->maze_data[y][x] == PATH ){
                                        maze1->maze_data[y][x] = RED;
                                }

                                for( int i = 0; i < 4; ++i ){
                                        if( currentsteps - stepmatrix[dy[i]+y][dx[i]+x] == 1 ){
                                                bt( dx[i]+x, dy[i]+y, stepmatrix );
                                        }
                                }
  }


bool MainWindow::find_path(int x, int y)
{

    qDebug() << "find path fct";


        int maze_size=ui->spinBox->value();

        if ( x < 0 || x > maze_size*2  || y < 0 || y > maze_size*2  ) return FALSE;

        if ( maze1->maze_data[y][x] == G ) return TRUE;

        if ( maze1->maze_data[y][x] != PATH && maze1->maze_data[y][x] != S ) return FALSE;

        maze1->maze_data[y][x] = RED;


        if ( find_path(x, y - 1) == TRUE ) return TRUE;

        if ( find_path(x + 1, y) == TRUE ) return TRUE;

        if ( find_path(x, y + 1) == TRUE ) return TRUE;

        if ( find_path(x - 1, y) == TRUE ) return TRUE;

        maze1->maze_data[y][x] = PATH;
        return FALSE;


}

void MainWindow::on_pushButton_4_clicked()
{

viewOpenGl();
//ui->pushButton_4->setEnabled(false);


}

void MainWindow::openAMazeTXTFile()
{

    QString fileName = QFileDialog::getOpenFileName(this,tr("Open MAZE"), ".", tr("Text Files (*.txt)"));

    int b=0,n=0;

    QFile file(fileName);
         if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
             return;

            QByteArray line = file.readAll();

            if(!line.length()) return;

            qDebug() << line.length() << " character(s) reads";


            for(int i=0;i<line.length();i++)

            {


                if(line.at(i)=='\n') { n++; }

            }

             qDebug() << n << "LINE(S)";


             n=0;


             for(int i=0;i<line.length();i++)

             {


                 if((line.at(i)=='#')||(line.at(i)=='S')||(line.at(i)=='G')) {

                     mw->m1->setWall(n,b);
                      b++; }

                 if((line.at(i)=='.')||(line.at(i)=='R')) {

                      mw->m1->setPath(n,b);
                     b++;
                 }

                 if(line.at(i)=='\n') { n++; b=0;  }



             }

            ui->spinBox->setValue(n/2);

            mw->updatePixmap2();



}



void MainWindow::saveAMazeTxtFile()
{


}

void MainWindow::on_pushButton_2_toggled(bool checked)
{


    if(viewResolution==false) {

        mw->solveTheMaze();  viewResolution=true; ui->pushButton_2->setText("Try to solve");

        //QThread::sleep (1);

        mw->setDis(1);

        QString strategy=mw->strategy;
        QString length=mw->length;
        QString paths=mw->paths;

        ui->label_5->setText(length);
        ui->label_6->setText(strategy);
        ui->label_7->setText(paths);

        ui->pushButton_2->setChecked(true);

    }
    else {

        //mw->display(withoutSolver);

        viewResolution=false;  ui->pushButton_2->setText("Not solved"); mw->setDis(2);

        ui->label_5->setText("");
        ui->label_6->setText("");
        ui->label_7->setText("");

        ui->pushButton_2->setChecked(false);


    }


}
