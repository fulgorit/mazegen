/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtGui>

#include <math.h>

#include "mazewidget.h"

#define MAX 61  // 30 * 2 + 1
#define CELL 900 // 30 * 30
#define WALL 1
#define PATH 0
#define RED  2
#define S  3
#define G  4

MazeWidget::MazeWidget(QWidget *parent)
    : QWidget(parent)
{

    debut=0;
    dis=0;

    camposx=1;
    camposy=1;

    first=true;

    //qDebug() << "New maze";
    m1=new mazeData();

    qRegisterMetaType<QImage>("QImage");

    thread=new RenderThread();

    connect(thread, SIGNAL(renderedImage()),
            this, SLOT(updatePixmap()));

    connect(thread, SIGNAL(mazeSolved()),
            this, SLOT(updatePixmap2()));


    m_renderThisMaze=0;

}

void  MazeWidget::setCameraPos(int a,int b)
{

camposx=a;
camposy=b;


}


void MazeWidget::buildMaze(int ssize,int inout,int n)
{

       debut=1;

       if(ssize<MAX) m_size=MAX;
           else m_size=ssize;

       m_input_output=inout;

       if(first)
       {
       thread->render(ssize,n);
       first=false;
       }
       else {   thread->render(ssize,n);       }


}

void MazeWidget::renderThisMaze(mazeData m,int ssize)
{

/*
    m1->m_size=ssize;


    for (int y=0; y <  MAX; y++)
    {
      for (int x=0; x < MAX; x++)
      {

       if(m.getValue(x,y)==WALL) { m1->setWall(x,y); }
       if(m.getValue(x,y)==PATH) m1->setPath(x,y);
       if(m.getValue(x,y)==RED)  m1->setRed(x,y);
       if(m.getValue(x,y)==S) m1->setStart(x,y);
       if(m.getValue(x,y)==G) m1->setEnd(x,y);


      }

    }

    update();
*/

}

void MazeWidget::display(QPixmap pm)
{

    pixmap=pm;

    //if(dis==1) dis=0;
    //if(dis==0) dis=1;
    dis=1;
    update();

}

void MazeWidget::setDis(int a)
{

    dis=a;
    update();

}


void MazeWidget::updatePixmap()
{

    m_renderThisMaze=0;

    running=1;

    update();

}


void MazeWidget::updatePixmap2()
{

    m_renderThisMaze=1;

    running=0;

    strategy=thread->strategy;
    length=thread->length;
    paths=thread->nb_paths_txt;
  
    update();

}


void MazeWidget::solveTheMaze()
{

     m_renderThisMaze=1;
     running=0;
     thread->solve();
     debut=1;


}

void MazeWidget::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    painter.fillRect(rect(), Qt::black);



    if (dis==1) {
        /*painter.drawPixmap(0,0,pixmap);

        int mul=8;

        //qDebug() << "camposx" << camposx;
        //qDebug() << "camposy" << camposy;

        bool ok;

        int aa=round(QString::number(camposx,10,0).toInt(&ok,10));
        int bb=round(QString::number(camposy,10,0).toInt(&ok,10));

        painter.fillRect(QRect(aa*mul, bb*mul,mul, mul),Qt::darkCyan);



        painter.end();
        dis=2;



        return;

        */
    }


    if (pixmap.isNull()) {
        if(debut==0) {
        painter.setPen(Qt::white);
        painter.drawText(rect(), Qt::AlignCenter,
                         tr("qMazeGenerator"));

        painter.end();

        update();
        return;
        }
    }

    //qDebug() << thread->running;

    if(m_renderThisMaze){
    running=0;
    }  else running=thread->running;


    if(m_renderThisMaze){


        int mul=8;


        QColor c1;

        c1.setRgb(255,255,255,255);

        painter.fillRect(rect(), Qt::white);



        int x,y,dim=0;

          for (y=0; y <  m_size; y++)
          {
            for (x=0; x < m_size; x++)
            {

             if(thread->toSolve1->getValue(x,y)==WALL) { m1->setWall(x,y); if(y==0) dim++; }
             if(thread->toSolve1->getValue(x,y)==PATH) m1->setPath(x,y);
             if(thread->toSolve1->getValue(x,y)==RED)  m1->setRed(x,y);
             if(thread->toSolve1->getValue(x,y)==S) m1->setStart(x,y);
             if(thread->toSolve1->getValue(x,y)==G) m1->setEnd(x,y);


            }

          }


                //m1->display();


                for (y=0; y < m1->m_size; y++)
                {
                  for (x=0; x < m1->m_size; x++)
                  {


               if(m1->getValue(x,y)==S)
                           {


                                  painter.fillRect(QRect(x*mul, y*mul,mul*3+15, mul*3+15),Qt::red);

                           }


            if(m1->getValue(x,y)==G)
                     {

                         painter.fillRect(QRect(x*mul, y*mul,mul*3+15, mul*3+15),Qt::blue);


                     }



            if(m1->getValue(x,y)==RED)
                 {

                 if(dis!=2)       painter.fillRect(QRect(x*mul, y*mul,mul*3+15, mul*3+15),Qt::green);

                      else  painter.fillRect(QRect(x*mul, y*mul,mul*3+15, mul*3+15),Qt::white);

                  }





             if(m1->getValue(x,y)==WALL)
              {

                     painter.fillRect(QRect(x*mul, y*mul,mul*3+15, mul*3+15),Qt::black);


              }


             if(m1->getValue(x,y)==PATH) {

                    painter.fillRect(QRect(x*mul, y*mul,mul*3+15, mul*3+15),Qt::white);

              }




            }}




          running=0;

        }



    if(running)
    {


    int mul=8;





    QColor c1;

    c1.setRgb(255,255,255,255);

    painter.fillRect(rect(), Qt::white);



    int x,y,dim=0;

      for (y=0; y <  m_size; y++)
      {
        for (x=0; x < m_size; x++)
        {

         if(thread->mmaze->getValue(x,y)==WALL) { m1->setWall(x,y); if(y==0) dim++; }
         if(thread->mmaze->getValue(x,y)==PATH) m1->setPath(x,y);
         if(thread->mmaze->getValue(x,y)==RED)  m1->setRed(x,y);
         if(thread->mmaze->getValue(x,y)==S) m1->setStart(x,y);
         if(thread->mmaze->getValue(x,y)==G) m1->setEnd(x,y);


        }

      }

            if(m_input_output) {

                //qDebug() << "dim:" << dim;

            m1->setStart(1,0);
            m1->setEnd(dim-2,dim-1);


            }

            //m1->display();


            for (y=0; y < m1->m_size; y++)
            {
              for (x=0; x < m1->m_size; x++)
              {


           if(m1->getValue(x,y)==S)
                       {


                              painter.fillRect(QRect(x*mul, y*mul,mul*3+15, mul*3+15),Qt::red);

                       }


        if(m1->getValue(x,y)==G)
                 {

                     painter.fillRect(QRect(x*mul, y*mul,mul*3+15, mul*3+15),Qt::blue);


                 }



        if(m1->getValue(x,y)==RED)
             {

            if(dis!=2) painter.fillRect(QRect(x*mul, y*mul,mul*3+15, mul*3+15),Qt::green);
                else  painter.fillRect(QRect(x*mul, y*mul,mul*3+15, mul*3+15),Qt::white);

              }





         if(m1->getValue(x,y)==WALL)
          {

                 painter.fillRect(QRect(x*mul, y*mul,mul*3+15, mul*3+15),Qt::black);


          }


         if(m1->getValue(x,y)==PATH) {

                painter.fillRect(QRect(x*mul, y*mul,mul*3+15, mul*3+15),Qt::white);

          }




        }}



    }

    int mul=8;


    bool ok;

    int aa=round(QString::number(camposx,10,0).toInt(&ok,10));
    int bb=round(QString::number(camposy,10,0).toInt(&ok,10));


     painter.fillRect(QRect(aa*mul, bb*mul,mul, mul),Qt::darkCyan);
     painter.end();

     // emit renderedImage();

}
