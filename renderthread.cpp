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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mazebacktracking.h"
#include "maze.h"
#include <stdlib.h>
#include <time.h>
#include <QGraphicsItem>
#include <QPicture>
#include <QPainter>
#include <QDebug>
#include <QDir>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
//#include "maze2/maze2.h"

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <unistd.h>
#include <math.h>

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::vector;
using std::find;
using std::sort;


#define MAX 61  // 30 * 2 + 1
#define CELL 900  // 30 * 30
#define WALL 1
#define PATH 0
#define RED  2
#define S  3
#define G  4

#include <QtGui>
#include <math.h>
#include "renderthread.h"

RenderThread::RenderThread(QObject *parent)
    : QThread(parent)
{

   running=0;

}

RenderThread::~RenderThread()
{


}

void RenderThread::render(int size,int n)
{

    m_size=size;

    QMutexLocker locker(&mutex);

    // qDebug() << "render";

    mmaze=new mazeBacktracking(m_size,false,1);

    if(n==0) mmaze->maze_generator_1();
    if(n==1) mmaze->maze_generator_2();
    if(n==2) mmaze->maze_generator_3();
    running=1;

    //qDebug() << running;
    emit renderedImage();

}



void RenderThread::paths(int maze[MAX][MAX], int row, int col) {

  //qDebug() << "(" << row << "," << col << ")";
  if (row == rowLen && col == colLen) {
   count++;
   return;
  }
  /* move left
  if (col > 0 )
   { if (maze[row][col - 1] == 0)
       paths(maze, row, col - 1);  }
  */
  // move right
  if (col < colLen && maze[row][col + 1] == 0)
   paths(maze, row, col + 1);

  /* move up
  if(row > 0)
  { if (maze[row - 1][col] == 0)
       paths(maze, row - 1, col);  }
  */
  // move down
  if (row < rowLen && maze[row + 1][col] == 0)
   paths(maze, row + 1, col);

 }

void RenderThread::solve()
{

    toSolve1=new mazeData(mmaze->maze);
    //toSolve1->setStart(0, 1);
    //toSolve1->setEnd(toSolve1->m_size-1,toSolve1->m_size-2);

    toSolve1->setStart(1,0);
    toSolve1->setEnd(toSolve1->m_size-2,toSolve1->m_size-1);

    // stores number of unique paths from source to destination
     //int count = 0;
    // 2D matrix to keep track of cells involved in current path
     //int visited[MAX][MAX];

    //memset(visited, 0, sizeof visited);
/*
 for (int i = 0; i < toSolve1->m_size; i++)
		for (int j = 0; j < toSolve1->m_size; j++)
			visited[i][j] = 0;
*/

//    qDebug() << toSolve1->m_size << endl;

    //start from source cell (0, 0)
    //countPaths(toSolve1->maze_data, 0, 1, visited, count,0,1,toSolve1->m_size-1,toSolve1->m_size-2);
    //countPaths(toSolve1->maze_data, 1, 0, visited, count,1,0,toSolve1->m_size-2,toSolve1->m_size-1);
    //countPaths(toSolve1->maze_data, 0, 1, visited, count,0,1,toSolve1->m_size-1,toSolve1->m_size-2);

    rowLen = toSolve1->m_size-2;
    colLen = toSolve1->m_size-2;

    qDebug() << rowLen << colLen;

    count=0;
/*
     for (int i = 0; i < toSolve1->m_size; i++)
    		for (int j = 0; j < toSolve1->m_size; j++)
    			paths_a[j][i] = toSolve1->maze_data[j][i];
*/

     //paths(toSolve1->maze_data,1,1);

     toSolve1->writeToFile();

     Maze2 itaca1 = Maze2("Itaca");
     itaca1.LoadFromFile("maze.txt");
     Maze2 itaca2 = Maze2("Itaca");
     itaca2.LoadFromFile("maze.txt");
     Maze2 itaca3 = Maze2("Itaca");
     itaca3.LoadFromFile("maze.txt");

     //itaca.LoadFromBuffer(toSolve1->maze_data);
  int x,y,z,min;

  vector<MazeArc> closed_arcs1 = itaca1.solve(DFS, false);
  itaca1.setSolution(closed_arcs1, false);
  //itaca.PrintMaze();
  x=itaca1.getSolutionSathLenght();
  qDebug() << "Path lenght DFS: " << itaca1.getSolutionSathLenght();

  vector<MazeArc> closed_arcs2 = itaca2.solve(BFS, false);
  itaca2.setSolution(closed_arcs2, false);
  //itaca.PrintMaze();
  y=itaca2.getSolutionSathLenght();
  qDebug() << "Path lenght BFS: " << itaca2.getSolutionSathLenght();

  vector<MazeArc> closed_arcs3 = itaca3.solve(BEFS, false);
  itaca3.setSolution(closed_arcs3, false);
  //itaca.PrintMaze();
  z=itaca3.getSolutionSathLenght();
  qDebug() << "Path lenght BEFS: " << itaca3.getSolutionSathLenght();


  min = x;

	if (y < min) {
		min = y;
	}

	if (z < min) {
		min = z;
	}

	//qDebug() << min;

    //if(find_path(1,1)) emit mazeSolved();

if((x==y)&&(x==y)&&(x==z)) count=1;
if((x!=y)&&(x==z)&&(y==z)) count=2;
if((x==z)&&(x!=y)) count=2;
if((x!=y)&&(y==z)) count=2;
if((x==y)&&(x!=z)&&(y!=z)) count=3;
if((x!=y)&&(x!=z)&&(y!=z)) count=3;


    nb_paths_txt = QString::number(count);

    qDebug() << "Number of path(s) (not accurate): " << count;

    if(min==itaca1.getSolutionSathLenght()) { itaca1.PrintMaze(); toSolve1=itaca1.toArray(toSolve1);
    strategy="DFS";
    length=QString::number(min); emit mazeSolved(); return; }
    if(min==itaca2.getSolutionSathLenght()) { itaca2.PrintMaze(); toSolve1=itaca2.toArray(toSolve1);
    strategy="BFS";
    length=QString::number(min); emit mazeSolved(); return; }
    if(min==itaca3.getSolutionSathLenght()) { itaca3.PrintMaze(); toSolve1=itaca3.toArray(toSolve1);
    strategy="BEFS";
    length=QString::number(min);
     }

   emit mazeSolved(); return;

}

void RenderThread::run()
{

    //emit renderedImage();

}

int RenderThread::pathsFrom(int x, int y)
{

}

bool RenderThread::isInBounds(int i, int j, int n)
{
        return i>=0 && j >=0 && i < n && j < n;
}

bool RenderThread::isValidCell(int x, int y)
{
	if (x < 0 || y < 0 || x >= MAX || y >= MAX)
		return false;

	return true;
}

bool RenderThread::find_path(int x, int y)
{

        int maze_size=mmaze->size*2;

        if ( x < 0 || x > maze_size  || y < 0 || y > maze_size  ) return FALSE;

        if ( toSolve1->maze_data[y][x] == G ) return TRUE;

        if ( toSolve1->maze_data[y][x] != PATH && toSolve1->maze_data[y][x] != S ) return FALSE;

        toSolve1->setRed(y,x);

        if ( find_path(x, y - 1) == TRUE ) return TRUE;

        if ( find_path(x + 1, y) == TRUE ) return TRUE;

        if ( find_path(x, y + 1) == TRUE ) return TRUE;

        if ( find_path(x - 1, y) == TRUE ) return TRUE;

        toSolve1->setPath(y,x);

        return FALSE;


}
