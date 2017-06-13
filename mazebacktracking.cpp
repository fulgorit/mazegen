#include "mazebacktracking.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <QDebug>

#include <maze.h>

#include <algorithm>
#include "Cell.h"
#include "Matrix.h"

#define UP 0     //-y
#define DOWN 1   //+y
#define LEFT 2   //-x
#define RIGHT 3  //+x

#define prim
#define nodeadend

int mazeBacktracking::copy(mazeBacktracking * mm)
{


    for(int i=0;i<MAX;i++)

    {

        for(int j=0;j<MAX;j++)

        {



            setVal(i,j,0);

        }
    }


    size=mm->size;



    for(int i=0;i<size;i++)

    {

        for(int j=0;j<size;j++)

        {

                    if (mm->maze->maze_data[i][j]==PATH)  this->maze->setPath(i,j);
                    if (mm->maze->maze_data[i][j]==WALL)  this->maze->setWall(i,j);


        }
    }

    return 1;

}

mazeBacktracking::mazeBacktracking(int ssize,bool gen,int n)
{

    size=ssize;

    srand((unsigned)time(NULL));

    maze=new mazeData(size+1);

    for (int i=0;i<size+1;i++)
    {
        for (int j=0;j<size+1;j++)
        {

            MAZZZ[i][j]=new cellA();

        }
    }

    indeks = 0;

    backtrack_x[indeks] = 1;
    backtrack_y[indeks] = 1;


    init_maze();
    if(gen)
    {
    if(n==0) maze_generator_1();
    if(n==1) maze_generator_2();
    if(n==2) maze_generator_3();
    }


}

void mazeBacktracking::init_maze_back()
{
     for(int a = 0; a < MAX; a++)
     {
         for(int b = 0; b < MAX; b++)
         {
             if(a % 2 == 0 || b % 2 == 0)
                 maze->setWall(a,b);
             else
                 maze->setPath(a,b);
         }
     }
}

void mazeBacktracking::maze_generator_3()
{

     //qDebug() << "gen maze 3";
     init_maze_back();
     //qDebug() << "gen maze 3b";

     maze_generator_backtracking(indeks, backtrack_x, backtrack_y, 1, 1, size-2, 1);

     mazeData m1;




     for(int i=0;i<(size-2)*2+1;i++)
     {
         for(int j=0;j<(size-2)*2+1;j++)
         {

             if (maze->maze_data[i][j]) m1.setWall(i,j);
                else m1.setPath(i,j);

         }
     }

     for(int i=0;i<MAX;i++)
     {
         for(int j=0;j<MAX;j++)
         {

              maze->setPath(i,j);

         }
     }

     for(int i=0;i<MAX;i++)
     {
         for(int j=0;j<MAX;j++)
         {

             if (m1.maze_data[i][j]) maze->setWall(i,j);
                else maze->setPath(i,j);

         }
     }







     //maze->display();

}


void mazeBacktracking::init_maze()
{

    //qDebug() << "size init :"<<size;

    int xsize=size;
    int ysize=size;

    for(int x=0;x<xsize;x++){
            for(int y=0;y<ysize;y++){
                    MAZZZ[x][y]->in   = (x==0||x==xsize-1||y==0||y==ysize-1)?1:0;
                    MAZZZ[x][y]->up   = (x==0||x==xsize-1||y==0)?0:1;
                    MAZZZ[x][y]->left = (x==0||y==0||y==ysize-1)?0:1;
            }
    }

    //qDebug() << "MAZE INIT";
    return;

}

void mazeBacktracking::maze_generator_1()
{

  //  qDebug() << "Maze gen beginning";

    int xsize=size;
    int ysize=size;




    long numin=1;     //Number of cells in the maze.

    int xcur=1, ycur=1;//start growing from the corner. It could theoretically start growing from anywhere, doesn't matter.
        MAZZZ[xcur][ycur]->in = 1;
        int whichway;
        bool success;
        do{

#ifdef nodeadend
                if( MAZZZ[xcur][ycur-1]->in&&MAZZZ[xcur][ycur+1]->in&&
                           MAZZZ[xcur-1][ycur]->in&&MAZZZ[xcur+1][ycur]->in ){
                                   //If at a dead end, randomly destroy a wall to make it not a dead end!
                        do{
                                success=0;
                                whichway=rand()%4;
                                switch(whichway){
                                case UP:
                                        if(MAZZZ[xcur][ycur]->up&&ycur!=1){
                                                success=1;
                                                MAZZZ[xcur][ycur]->up=0;
                                        }
                                        break;
                                case DOWN:
                                        if(MAZZZ[xcur][ycur+1]->up&&ycur!=ysize-2){
                                                success=1;
                                                MAZZZ[xcur][ycur+1]->up=0;
                                        }
                                        break;
                                case LEFT:
                                        if(MAZZZ[xcur][ycur]->left&&xcur!=1){
                                                success=1;
                                                MAZZZ[xcur][ycur]->left=0;
                                        }
                                        break;
                                case RIGHT:
                                        if(MAZZZ[xcur+1][ycur]->left&&xcur!=xsize-2){
                                                success=1;
                                                MAZZZ[xcur+1][ycur]->left=0;
                                        }
                                        break;
                                }
                        }while(!success);
                }
#endif


                do{
                        //randomly find a cell that's in the maze
                        xcur=rand()%(xsize-2)+1;
                        ycur=rand()%(ysize-2)+1;
                }while(!MAZZZ[xcur][ycur]->in ||
                        (MAZZZ[xcur][ycur-1]->in&&MAZZZ[xcur][ycur+1]->in&&
                        MAZZZ[xcur-1][ycur]->in&&MAZZZ[xcur+1][ycur]->in));

                do{
                        //Randomly grow the maze if possible.
                        success=0;
                        whichway=rand()%4;
                        switch(whichway){
                        case UP:
                                if(!MAZZZ[xcur][ycur-1]->in){
                                        success=1;
                                        MAZZZ[xcur][ycur]->up=0;
                                        MAZZZ[xcur][ycur-1]->prevx=xcur;
                                        MAZZZ[xcur][ycur-1]->prevy=ycur;
                                        ycur--;
                                }
                                break;
                        case DOWN:
                                if(!MAZZZ[xcur][ycur+1]->in){
                                        success=1;
                                        MAZZZ[xcur][ycur+1]->up=0;
                                        MAZZZ[xcur][ycur+1]->prevx=xcur;
                                        MAZZZ[xcur][ycur+1]->prevy=ycur;
                                        ycur++;
                                }
                                break;
                        case LEFT:
                                if(!MAZZZ[xcur-1][ycur]->in){
                                        success=1;
                                        MAZZZ[xcur][ycur]->left=0;
                                        MAZZZ[xcur-1][ycur]->prevx=xcur;
                                        MAZZZ[xcur-1][ycur]->prevy=ycur;
                                        xcur--;
                                }
                                break;
                        case RIGHT:
                                if(!MAZZZ[xcur+1][ycur]->in){
                                        success=1;
                                        MAZZZ[xcur+1][ycur]->left=0;
                                        MAZZZ[xcur+1][ycur]->prevx=xcur;
                                        MAZZZ[xcur+1][ycur]->prevy=ycur;
                                        xcur++;
                                }
                                break;
                        }
                }while(!success);
                MAZZZ[xcur][ycur]->in=1;
                numin++; //Every iteration of this loop, one maze cell is added to the maze.
        }while(numin<(xsize-2)*(ysize-2));




        int width=(xsize-1)*2-1;
        int height=(ysize-1)*2-1;

          for(int y = 0; y <= height - 1; y++){
                  for(int x = 0; x <= width - 1; x++){
                          if(x%2 == 1 && y%2 == 1){
                                          if(MAZZZ[x/2+1][y/2+1]->in) maze->setPath(x,y);
                                                  else maze->setWall(x,y);
                          }
                          if(x%2 == 0 && y%2 == 0){
                                  maze->setWall(x,y);
                                  }
                          if(x%2 == 0 && y%2 == 1){
                              if(MAZZZ[x/2+1][y/2+1]->left) maze->setWall(x,y); else  maze->setPath(x,y);
                          }
                          if(x%2 == 1 && y%2 == 0){
                                  if(MAZZZ[x/2+1][y/2+1]->up)  maze->setWall(x,y); else maze->setPath(x,y);
                                  }


}}

          //qDebug() <<  "total cells :" << numin;
          //qDebug() << "MAZE GEN";


}




void mazeBacktracking::maze_generator_2()
{

    //qDebug() << "Maze gen beginning";

    int xsize=size;
    int ysize=size;



    long numin=1;     //Number of cells in the maze.

    int xcur=1, ycur=1;//start growing from the corner. It could theoretically start growing from anywhere, doesn't matter.
        MAZZZ[xcur][ycur]->in = 1;
        int whichway;
        bool success;
        do{

#ifdef nodeadend
                if( MAZZZ[xcur][ycur-1]->in&&MAZZZ[xcur][ycur+1]->in&&
                           MAZZZ[xcur-1][ycur]->in&&MAZZZ[xcur+1][ycur]->in ){
                                   //If at a dead end, randomly destroy a wall to make it not a dead end!
                        do{
                                success=0;
                                whichway=rand()%4;
                                switch(whichway){
                                case UP:
                                        if(MAZZZ[xcur][ycur]->up&&ycur!=1){
                                                success=1;
                                                MAZZZ[xcur][ycur]->up=0;
                                        }
                                        break;
                                case DOWN:
                                        if(MAZZZ[xcur][ycur+1]->up&&ycur!=ysize-2){
                                                success=1;
                                                MAZZZ[xcur][ycur+1]->up=0;
                                        }
                                        break;
                                case LEFT:
                                        if(MAZZZ[xcur][ycur]->left&&xcur!=1){
                                                success=1;
                                                MAZZZ[xcur][ycur]->left=0;
                                        }
                                        break;
                                case RIGHT:
                                        if(MAZZZ[xcur+1][ycur]->left&&xcur!=xsize-2){
                                                success=1;
                                                MAZZZ[xcur+1][ycur]->left=0;
                                        }
                                        break;
                                }
                        }while(!success);
                }
#endif

                while( MAZZZ[xcur][ycur-1]->in&&MAZZZ[xcur][ycur+1]->in&&
                           MAZZZ[xcur-1][ycur]->in&&MAZZZ[xcur+1][ycur]->in ){
                                   //If all the neighbourhood cells are in, backtrack.
                                int xcur2=MAZZZ[xcur][ycur]->prevx;
                                ycur=MAZZZ[xcur][ycur]->prevy;
                                xcur=xcur2;
                }

                do{
                        //Randomly grow the maze if possible.
                        success=0;
                        whichway=rand()%4;
                        switch(whichway){
                        case UP:
                                if(!MAZZZ[xcur][ycur-1]->in){
                                        success=1;
                                        MAZZZ[xcur][ycur]->up=0;
                                        MAZZZ[xcur][ycur-1]->prevx=xcur;
                                        MAZZZ[xcur][ycur-1]->prevy=ycur;
                                        ycur--;
                                }
                                break;
                        case DOWN:
                                if(!MAZZZ[xcur][ycur+1]->in){
                                        success=1;
                                        MAZZZ[xcur][ycur+1]->up=0;
                                        MAZZZ[xcur][ycur+1]->prevx=xcur;
                                        MAZZZ[xcur][ycur+1]->prevy=ycur;
                                        ycur++;
                                }
                                break;
                        case LEFT:
                                if(!MAZZZ[xcur-1][ycur]->in){
                                        success=1;
                                        MAZZZ[xcur][ycur]->left=0;
                                        MAZZZ[xcur-1][ycur]->prevx=xcur;
                                        MAZZZ[xcur-1][ycur]->prevy=ycur;
                                        xcur--;
                                }
                                break;
                        case RIGHT:
                                if(!MAZZZ[xcur+1][ycur]->in){
                                        success=1;
                                        MAZZZ[xcur+1][ycur]->left=0;
                                        MAZZZ[xcur+1][ycur]->prevx=xcur;
                                        MAZZZ[xcur+1][ycur]->prevy=ycur;
                                        xcur++;
                                }
                                break;
                        }
                }while(!success);
                MAZZZ[xcur][ycur]->in=1;
                numin++; //Every iteration of this loop, one maze cell is added to the maze.
        }while(numin<(xsize-2)*(ysize-2));




        int width=(xsize-1)*2-1;
        int height=(ysize-1)*2-1;

          for(int y = 0; y <= height - 1; y++){
                  for(int x = 0; x <= width - 1; x++){
                          if(x%2 == 1 && y%2 == 1){
                                          if(MAZZZ[x/2+1][y/2+1]->in) maze->setPath(x,y);
                                                  else maze->setWall(x,y);
                          }
                          if(x%2 == 0 && y%2 == 0){
                                  maze->setWall(x,y);
                                  }
                          if(x%2 == 0 && y%2 == 1){
                              if(MAZZZ[x/2+1][y/2+1]->left) maze->setWall(x,y); else  maze->setPath(x,y);
                          }
                          if(x%2 == 1 && y%2 == 0){
                                  if(MAZZZ[x/2+1][y/2+1]->up)  maze->setWall(x,y); else maze->setPath(x,y);
                                  }


}}

       //   qDebug() <<  "total cells :" << numin;
     //     qDebug() << "MAZE GEN";


}


void mazeBacktracking::setVal(int a,int b,int val)
{


    if ((a<MAX)&&(b<MAX)&&(val==PATH)) maze->setPath(a,b);

    if ((a<MAX)&&(b<MAX)&&(val==WALL)) maze->setWall(a,b);
}

int mazeBacktracking::getValue(int x,int y)
{

    return maze->getValue(x,y);

}


void mazeBacktracking::maze_generator_backtracking(int indeks, int backtrack_x[CELL], int backtrack_y[CELL], int x, int y, int n, int visited)
{
    if(visited < n * n)
    {
        int neighbour_valid = -1;
        int neighbour_x[4];
        int neighbour_y[4];
        int step[4];

        int x_next;
        int y_next;

        if(x - 2 > 0 && is_closed(maze->maze_data, x - 2, y))  // upside
        {
            neighbour_valid++;
            neighbour_x[neighbour_valid]=x - 2;;
            neighbour_y[neighbour_valid]=y;
            step[neighbour_valid]=1;
        }

        if(y - 2 > 0 && is_closed(maze->maze_data, x, y - 2))  // leftside
        {
            neighbour_valid++;
            neighbour_x[neighbour_valid]=x;
            neighbour_y[neighbour_valid]=y - 2;
            step[neighbour_valid]=2;
        }

        if(y + 2 < n * 2 + 1 && is_closed(maze->maze_data, x, y + 2))  // rightside
        {
            neighbour_valid++;
            neighbour_x[neighbour_valid]=x;
            neighbour_y[neighbour_valid]=y + 2;
            step[neighbour_valid]=3;

        }

        if(x + 2 < n * 2 + 1 && is_closed(maze->maze_data, x + 2, y))  // downside
        {
            neighbour_valid++;
            neighbour_x[neighbour_valid]=x+2;
            neighbour_y[neighbour_valid]=y;
            step[neighbour_valid]=4;
        }

        if(neighbour_valid == -1)
        {
            // backtrack
            x_next = backtrack_x[indeks];
            y_next = backtrack_y[indeks];
            indeks--;
        }

        if(neighbour_valid!=-1)
        {
            int randomization = neighbour_valid + 1;
            int random = rand()%randomization;
            x_next = neighbour_x[random];
            y_next = neighbour_y[random];
            indeks++;
            backtrack_x[indeks] = x_next;
            backtrack_y[indeks] = y_next;

            int rstep = step[random];

            if(rstep == 1)
                maze->maze_data[x_next+1][y_next] = PATH;
            else if(rstep == 2)
                maze->maze_data[x_next][y_next + 1] = PATH;
            else if(rstep == 3)
                maze->maze_data[x_next][y_next - 1] = PATH;
            else if(rstep == 4)
                maze->maze_data[x_next - 1][y_next] = PATH;
            visited++;
        }
       // qDebug() << "maze gen call";
        maze_generator_backtracking(indeks, backtrack_x, backtrack_y, x_next, y_next, n, visited);
    }
}

int mazeBacktracking::is_closed(int mmmaze[MAX][MAX], int x, int y)
{
    if(mmmaze[x - 1][y]  == WALL
       && mmmaze[x][y - 1] == WALL
       && mmmaze[x][y + 1] == WALL
       && mmmaze[x + 1][y] == WALL
    )
        return 1;

    return 0;
}


void mazeBacktracking::generateKruskal (Matrix<Cell>& theMatrix) {
        // In this algorithm, each vertex gets called a 'tree' which has its own number.
        // When expanding a vertex, it checks if the two adjacent vertices have different tree numbers.
        // In that case, I must change >ALL THE VERTICES THAT HAVE THE VISITED TREE NUMBER TO THE EXPANDING TREE NUMBER<.
        // To make that, I use a list for each possible number. This is stored on a vector.
        // Each position of the vector contains the list to all the coordinates to vertices that currently have that (the vector position number) as tree number.
        // availableVector contains all the coordinates, and is used to randomly select a non-finished vertex so that none gets selected twice. It is removed from there when it gets non expandable.
        // There are no requirements whether the visiting vertex has or has not been visited, they just need to belong to different trees.
        std::vector<MatrixCoord> availableVector;
        std::vector<std::list<MatrixCoord> > treeVector;

        MatrixCoord matrixSize = theMatrix.getSize();
        for (int i=0; i<matrixSize.x; i++) {
                for (int j=0; j<matrixSize.y; j++) {
                        theMatrix[MatrixCoord(i,j)].visited = 0;
                        theMatrix[MatrixCoord(i,j)].directions.clear();
                        theMatrix[MatrixCoord(i,j)].directions.push_back (0);
                        theMatrix[MatrixCoord(i,j)].directions.push_back (1);
                        theMatrix[MatrixCoord(i,j)].directions.push_back (2);
                        theMatrix[MatrixCoord(i,j)].directions.push_back (3);

                        theMatrix[MatrixCoord(i,j)].tree = i*matrixSize.y + j;

                        availableVector.push_back (MatrixCoord(i, j));

                        std::list<MatrixCoord> tempList;
                        tempList.push_back (MatrixCoord (i, j));

                        treeVector.push_back (tempList);
                }
        }

        while (availableVector.size() > 0) {
                std::random_shuffle (availableVector.begin(), availableVector.end());
                MatrixCoord toExpand = availableVector.back();
        //	int randomIndex = rand() % availableVector.size(); // select one that can possibly expand
//		MatrixCoord toExpand = availableVector[randomIndex];
                if (theMatrix[toExpand].directions.size() == 0) { // means toExpand cell already tried all dir
                //	availableVector.erase(availableVector.begin()+randomIndex);
                        availableVector.pop_back();
                        theMatrix[toExpand].visited = 2;
                }
                else { // this one still can expand!
                        std::random_shuffle (theMatrix[toExpand].directions.begin(), theMatrix[toExpand].directions.end());
//			int randomRemainingIndex = rand() % theMatrix[toExpand].directions.size(); // select one of remaining dirs
//			int direction = theMatrix[toExpand].directions[randomRemainingIndex];
                        int direction = theMatrix[toExpand].directions.back();
//			theMatrix[toExpand].directions.erase(theMatrix[toExpand].directions.begin()+randomRemainingIndex);
                        theMatrix[toExpand].directions.pop_back();

                        MatrixCoord visiting;
                        switch (direction) {
                                case 0: // up from here
                                        visiting = toExpand + MatrixCoord(0,1);
                                        if (!theMatrix.outOfBounds(visiting)) {
                                                if (theMatrix[toExpand].tree != theMatrix[visiting].tree) {
                                                        std::list<MatrixCoord>& toExpandTree = treeVector[theMatrix[toExpand].tree]; // easier to read
                                                        std::list<MatrixCoord>& visitingTree = treeVector[theMatrix[visiting].tree];

                                                        for (std::list<MatrixCoord>::iterator it = visitingTree.begin(); it != visitingTree.end(); it++) {
                                                                // this loop changes all the 'tree' fields to the same of the expanding one
                                                                MatrixCoord& coord = *it;
                                                                theMatrix[coord].tree = theMatrix[toExpand].tree;
                                                        }
                                                        toExpandTree.splice (toExpandTree.end(), visitingTree);
                                                        // this method joins visitingTree to end of toExpandTree and clears visitingTree.

                                                        theMatrix[visiting].visited = 1;
                                                        theMatrix[visiting].down = true;
                                                        theMatrix[toExpand].up = true;
                                                }
                                        }
                                        break;
                                case 1: // down from here
                                        visiting = toExpand + MatrixCoord(0,-1);
                                        if (!theMatrix.outOfBounds(visiting)) {
                                                if (theMatrix[toExpand].tree != theMatrix[visiting].tree) {
                                                        std::list<MatrixCoord>& toExpandTree = treeVector[theMatrix[toExpand].tree]; // easier to read
                                                        std::list<MatrixCoord>& visitingTree = treeVector[theMatrix[visiting].tree];
                                                        for (std::list<MatrixCoord>::iterator it = visitingTree.begin(); it != visitingTree.end(); it++) {
                                                                MatrixCoord& coord = *it;
                                                                theMatrix[coord].tree = theMatrix[toExpand].tree;
                                                        }
                                                        toExpandTree.splice (toExpandTree.end(), visitingTree);

                                                        theMatrix[visiting].visited = 1;
                                                        theMatrix[visiting].up = true;
                                                        theMatrix[toExpand].down = true;
                                                }
                                        }
                                        break;
                                case 2: // right from here
                                        visiting = toExpand + MatrixCoord(1,0);
                                        if (!theMatrix.outOfBounds(visiting)) {
                                                if (theMatrix[toExpand].tree != theMatrix[visiting].tree) {
                                                        std::list<MatrixCoord>& toExpandTree = treeVector[theMatrix[toExpand].tree]; // easier to read
                                                        std::list<MatrixCoord>& visitingTree = treeVector[theMatrix[visiting].tree];
                                                        for (std::list<MatrixCoord>::iterator it = visitingTree.begin(); it != visitingTree.end(); it++) {
                                                                MatrixCoord& coord = *it;
                                                                theMatrix[coord].tree = theMatrix[toExpand].tree;
                                                        }
                                                        toExpandTree.splice (toExpandTree.end(), visitingTree);

                                                        theMatrix[visiting].visited = 1;
                                                        theMatrix[visiting].left = true;
                                                        theMatrix[toExpand].right = true;
                                                }
                                        }
                                        break;
                                case 3:
                                        visiting = toExpand + MatrixCoord(-1,0);
                                        if (!theMatrix.outOfBounds(visiting)) {
                                                if (theMatrix[toExpand].tree != theMatrix[visiting].tree) {
                                                        std::list<MatrixCoord>& toExpandTree = treeVector[theMatrix[toExpand].tree]; // easier to read
                                                        std::list<MatrixCoord>& visitingTree = treeVector[theMatrix[visiting].tree];
                                                        for (std::list<MatrixCoord>::iterator it = visitingTree.begin(); it != visitingTree.end(); it++) {
                                                                MatrixCoord& coord = *it;
                                                                theMatrix[coord].tree = theMatrix[toExpand].tree;
                                                        }
                                                        toExpandTree.splice (toExpandTree.end(), visitingTree);

                                                        theMatrix[visiting].visited = 1;
                                                        theMatrix[visiting].right = true;
                                                        theMatrix[toExpand].left = true;
                                                }
                                        }
                                        break;
                        }
                }
        }
}


void mazeBacktracking::generatePrim (Matrix<Cell>& theMatrix) {
        MatrixCoord matrixSize = theMatrix.getSize();
        for (int i=0; i<matrixSize.x; i++) {
                for (int j=0; j<matrixSize.y; j++) {
                        theMatrix[MatrixCoord(i,j)].visited = 0; // 0 unvisited | 1 visited | 2 finished
                        theMatrix[MatrixCoord(i,j)].directions.clear();
                        theMatrix[MatrixCoord(i,j)].directions.push_back (0);
                        theMatrix[MatrixCoord(i,j)].directions.push_back (1);
                        theMatrix[MatrixCoord(i,j)].directions.push_back (2);
                        theMatrix[MatrixCoord(i,j)].directions.push_back (3);
                }
        }

        MatrixCoord start (rand() % matrixSize.x, rand() % matrixSize.y); // first is random

        std::vector<MatrixCoord> visitedVector; // this vector stores started cells that still can possibly expand

        visitedVector.push_back (start); // push the first
        theMatrix[start].visited = 1;

        while (visitedVector.size() != 0) {
                std::random_shuffle (visitedVector.begin(), visitedVector.end());
//		int randomIndex = visitedVector.back();
//		int randomIndex = rand() % visitedVector.size(); // select one that can possibly expand
                MatrixCoord toExpand = visitedVector.back();
                if (theMatrix[toExpand].directions.size() == 0) { // means toExpand cell already tried all dir
                        visitedVector.pop_back();
                        theMatrix[toExpand].visited = 2;
                }
                else { // this one still can expand!
                        std::random_shuffle (theMatrix[toExpand].directions.begin(), theMatrix[toExpand].directions.end());
//			int randomRemainingIndex = rand() % theMatrix[toExpand].directions.size(); // select one of remaining dirs
                        int direction = theMatrix[toExpand].directions.back();
                        theMatrix[toExpand].directions.pop_back();

                        MatrixCoord visiting;
                        switch (direction) {
                                case 0: // up from here
                                        visiting = toExpand + MatrixCoord(0,1);
                                        if (!theMatrix.outOfBounds(visiting)) {
                                                if (theMatrix[visiting].visited == 0) {
                                                        visitedVector.push_back(visiting);
                                                        theMatrix[visiting].visited = 1;
                                                        theMatrix[visiting].down = true;
                                                        theMatrix[toExpand].up = true;
                                                }
                                        }
                                        break;
                                case 1: // down from here
                                        visiting = toExpand + MatrixCoord(0,-1);
                                        if (!theMatrix.outOfBounds(visiting)) {
                                                if (theMatrix[visiting].visited == 0) {
                                                        visitedVector.push_back(visiting);
                                                        theMatrix[visiting].visited = 1;
                                                        theMatrix[visiting].up = true;
                                                        theMatrix[toExpand].down = true;
                                                }
                                        }
                                        break;
                                case 2: // right from here
                                        visiting = toExpand + MatrixCoord(1,0);
                                        if (!theMatrix.outOfBounds(visiting)) {
                                                if (theMatrix[visiting].visited == 0) {
                                                        visitedVector.push_back(visiting);
                                                        theMatrix[visiting].visited = 1;
                                                        theMatrix[visiting].left = true;
                                                        theMatrix[toExpand].right = true;
                                                }
                                        }
                                        break;
                                case 3:
                                        visiting = toExpand + MatrixCoord(-1,0);
                                        if (!theMatrix.outOfBounds(visiting)) {
                                                if (theMatrix[visiting].visited == 0) {
                                                        visitedVector.push_back(visiting);
                                                        theMatrix[visiting].visited = 1;
                                                        theMatrix[visiting].right = true;
                                                        theMatrix[toExpand].left = true;
                                                }
                                        }
                                        break;
                        }
                }
                //Matrix<char> field = generateField(theMatrix);
                //std::cout << field << std::endl;
        }
}



Matrix<char> mazeBacktracking::generateField (Matrix<Cell>& theMatrix) {
        MatrixCoord theMatrixSize = theMatrix.getSize();
        Matrix<char> rField (2*theMatrixSize.x+1, 2*theMatrixSize.y+1);
        for (int i=0; i<rField.getSize().x; i++) {
                for (int j=0; j<rField.getSize().y; j++) {
                        rField[MatrixCoord(i, j)] = '#';
                        //maze->setWall(i,j);
                }
        }

        for (int i=0; i<theMatrixSize.x; i++) {
                for (int j=0; j<theMatrixSize.y; j++) {
                        MatrixCoord graphCoord(i, j);
                        MatrixCoord rFieldCoord(2*i+1, 2*j+1);

                        rField[rFieldCoord] = '.';


                        if (theMatrix[graphCoord].up) {
                                rField [rFieldCoord+MatrixCoord(0,1)] = '.';

                        }
                        if (theMatrix[graphCoord].down) {
                                rField [rFieldCoord+MatrixCoord(0,-1)] = '.';

                        }
                        if (theMatrix[graphCoord].right) {
                                rField [rFieldCoord+MatrixCoord(1,0)] = '.';

                        }
                        if (theMatrix[graphCoord].left) {
                                rField [rFieldCoord+MatrixCoord(-1,0)] = '.';

                        }
                }
        }
        return rField;
}

