#include "maze.h"
#include <stdio.h>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <QDebug>
//#include <fstream>
//using namespace std;

mazeData::mazeData()
{

    for(int i=0;i<MAX;i++)

    {
        for(int j=0;j<MAX;j++)

        {
            maze_data[i][j]=PATH;
        }


    }

   // int cameraX=1;
   // int cameraY=1;

    m_size=MAX;
}


mazeData::mazeData(mazeData *m)
{

    int dim=0;

    for (int y=0; y <  MAX; y++)
    {
      for (int x=0; x < MAX; x++)
      {

       if(m->getValue(x,y)==WALL) { setWall(x,y); if(y==0) dim++; }
       if(m->getValue(x,y)==PATH) setPath(x,y);
       if(m->getValue(x,y)==RED)  setRed(x,y);
       if(m->getValue(x,y)==S) setStart(x,y);
       if(m->getValue(x,y)==G) setEnd(x,y);


      }

    }
    m_size=dim;

}


mazeData::mazeData(int size)
{

    for(int i=0;i<MAX;i++)

    {
        for(int j=0;j<MAX;j++)

        {
            maze_data[i][j]=PATH;
        }


    }

    m_size=size;
}

void mazeData::setPath(int x,int y)
{


    maze_data[x][y]=PATH;


}

void mazeData::setWall(int x,int y)
{


    maze_data[x][y]=WALL;


}

int mazeData::getValue(int x,int y)
{

    return maze_data[x][y];

}

void mazeData::display()
{

    int b=borderEnd();


    for(int i=0;i<b;i++) {
    for(int j=0;j<b;j++) {


        if (maze_data[j][i]==4) std::cout << "G";
        if (maze_data[j][i]==3) std::cout << "S";
        if (maze_data[j][i]==2) std::cout << "R";
        if (maze_data[j][i]==1) std::cout << "#";
        if (maze_data[j][i]==0) std::cout << " ";



           }

        std::cout <<  std::endl;

    }

    return;

}

void mazeData::writeToFile()
{

    int b=borderEnd();

    //qDebug() << "function call";

    QFile file("maze.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);

    for(int i=0;i<b;i++) {
        for(int j=0;j<b;j++) {


        if (maze_data[j][i]==4) out << "G";
        if (maze_data[j][i]==3) out << "S";
        if (maze_data[j][i]==2) out << "R";
        if (maze_data[j][i]==1) out << "#";
        if (maze_data[j][i]==0) out << " ";

           }

        out << "\n";

    }

     //qDebug() << "File should be written";

     file.flush();
     file.close();

     return;

}

void mazeData::setStart(int x,int y)
{
        maze_data[x][y]=S;
}

void mazeData::setEnd(int x,int y)
{
        maze_data[x][y]=G;
}
void mazeData::setRed(int x,int y)
{
        maze_data[x][y]=RED;
}

int mazeData::borderEnd()
{
    int border=0;

    for(int i=0;i<m_size;i++) {
    for(int j=0;j<m_size;j++) {


        if (maze_data[i][j]==4){


            border=j+2;
            return border;

        }

    }


    }


    return 0;



}
