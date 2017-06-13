#ifndef MAZE_H
#define MAZE_H

#define MAX 61  // 30 * 2 + 1
#define CELL 900  // 30 * 30
#define WALL 1
#define PATH 0
#define RED  2
#define S  3
#define G  4
#define CAMERA 5

class mazeData
{

public:
    mazeData();

    mazeData(int n);
    mazeData(mazeData * m);

    void setWall(int x,int y);
    void setPath(int x,int y);
    void setStart(int x,int y);
    void setEnd(int x,int y);
    void setRed(int x,int y);
    int cameraX;
    int cameraY;

    int getValue(int x,int y);
    void display();
    void writeToFile();

    int borderEnd(void);

    int maze_data[MAX][MAX];
    int m_size;


};

#endif // MAZE_H
