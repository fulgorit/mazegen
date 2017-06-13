#ifndef MAZEBACKTRACKING_H
#define MAZEBACKTRACKING_H

#include <maze.h>
#include <algorithm>
#include "Cell.h"
#include "Matrix.h"
#include "ClassA.h"

#define MAX 61  // 30 * 2 + 1
#define CELL 900  // 30 * 30
#define WALL 1
#define PATH 0
#define RED  2
#define S  3
#define G  4

class mazeBacktracking
{
public:
    mazeBacktracking(int s, bool gen, int n);
    void init_maze();
    void maze_generator_1();
    void maze_generator_2();
    void maze_generator_3();

    void maze_generator_backtracking(int indeks, int backtrack_x[CELL], int bactrack_y[CELL], int x, int y, int n, int visited);
    int is_closed(int maze[MAX][MAX], int x, int y);
    void init_maze_back();

    int is_closed(int x, int y);
    void setVal(int a,int b,int val);
    int getValue(int x,int y);
    int copy(mazeBacktracking * mm);
    void generateKruskal (Matrix<Cell>& theMatrix);
    void generatePrim (Matrix<Cell>& theMatrix);
    Matrix<char> generateField (Matrix<Cell>& theMatrix);

public:
    mazeData * maze;
    int size;

    int indeks;

    int backtrack_x[CELL];
    int backtrack_y[CELL];


    cellA * MAZZZ[31][31];

};

#endif // MAZEBACKTRACKING_H
