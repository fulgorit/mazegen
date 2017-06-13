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

#ifndef RENDERTHREAD_H
#define RENDERTHREAD_H

#include <QMutex>
#include <QSize>
#include <QThread>
#include <QWaitCondition>
#include "mazebacktracking.h"
#include <QImage>
#include <QPicture>
#include "maze2/maze2.h"


#define MAX 61  // 30 * 2 + 1
#define CELL 900  // 30 * 30
#define WALL 1
#define PATH 0

//#define N 61

#define TRUE 1
#define FALSE 0

QT_BEGIN_NAMESPACE
class QPicture;
QT_END_NAMESPACE


class RenderThread : public QThread
{
    Q_OBJECT

public:
    RenderThread(QObject *parent = 0);
    ~RenderThread();

    void render(int size,int n);

    void init_maze(int maze[MAX][MAX]);
    void maze_generator(int indeks, int maze[MAX][MAX], int backtrack_x[CELL], int bactrack_y[CELL], int x, int y, int n, int visited);
    //mazeData *print_maze(mazeData *m1, int maze_size, bool input_output);
    int is_closed(int maze[MAX][MAX], int x, int y);


    void bt(int x,int y,int stepmatrix[MAX][MAX]);
    bool find_path(int x, int y);
    void solve();

    void countPaths(int maze[MAX][MAX], int x, int y, int visited[MAX][MAX], int& count, int startx, int starty, int endx, int endy);
    bool isValidCell(int x, int y);

    void paths(int maze_data[MAX][MAX], int row, int col);

    int pathsFrom(int i, int j);
    bool isInBounds(int i, int j, int n);

    mazeBacktracking * mmaze;
    mazeBacktracking * mmazeRead;

    int m_size;

    int running;

    mazeData * toSolve1;

    int rowLen, colLen, count;

    QString strategy;
    QString length;
    QString nb_paths_txt;

  //  int paths_a[MAX][MAX];


signals:
    void renderedImage();
    void mazeSolved();

protected:
    void run();

private:


    QMutex mutex;
    QWaitCondition condition;

};


#endif
