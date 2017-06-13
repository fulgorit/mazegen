
#ifndef MANDELBROTWIDGET_H
#define MANDELBROTWIDGET_H

#include <QPixmap>
#include <QWidget>
#include "renderthread.h"

class MazeWidget: public QWidget
{
    Q_OBJECT

public:
    MazeWidget(QWidget *parent = 0);

    RenderThread * thread;

    int m_size;
    int m_input_output;

    void buildMaze(int ssize,int inout,int n);
    void solveTheMaze();
    void setCameraPos(int a, int b);

    QString strategy;
    QString length;
    QString paths;

    int camposx;
    int camposy;


    mazeData * m1;

    int running;
    int dis;

    int debut;

signals:
    void renderedImage();

protected:
    void paintEvent(QPaintEvent *event);



public slots:

    void renderThisMaze(mazeData m, int ssize);

    void updatePixmap();
    void updatePixmap2();

    void display(QPixmap pm);

    void setDis(int a);



private:



    int m_renderThisMaze;

    QPixmap pixmap;
    QPoint pixmapOffset;
    QPoint lastDragPos;
    double centerX;
    double centerY;
    double pixmapScale;
    double curScale;
    bool first;



};


#endif
