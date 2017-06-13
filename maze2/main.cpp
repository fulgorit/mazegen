#include <iostream>
#include <vector>
#include <list>
#include <string>
#include "maze.h"
#include <unistd.h>
#include <algorithm>
#include <sys/time.h>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::list;
using std::string;

int main(int argc, char** argv) {

    string maze_path;
    SearchStrategy strategy = BFS;
    int c;
    string strategy_str;
    bool interactive = false;
    bool compare = false;

    // Get options
    while ((c = getopt (argc, argv, "is:a")) != -1){
        switch(c) {

            case'a': {

              compare = true;

            } break;


            case's': {
                strategy_str = optarg;
                if (strategy_str == "DFS") {
                    strategy = DFS;
                } else if(strategy_str == "BFS") {
                    strategy = BFS;
                } else if(strategy_str == "BEFS") {
                    strategy = BEFS;
                } else {
                    cout << strategy_str << " is not a valid strategy." << endl;
                    return 1;
                } break;
            }
            case 'i': {
                    interactive = true;
            } break;
        }
    }
    // Get filename
    if (optind < argc){
        maze_path = (string)argv[optind];
    } else {
        cout << "No filename passed" << endl;
        return 1;
    }

if(compare==false) {

    Maze itaca = Maze("Itaca");
    itaca.LoadFromFile(maze_path);
    static struct timeval startTime;
    static struct timeval stopTime;
    gettimeofday(&startTime, NULL);
    vector<MazeArc> closed_arcs = itaca.solve(strategy, interactive);
    gettimeofday(&stopTime, NULL);
    long ticks = (stopTime.tv_sec - startTime.tv_sec) * 1000 + (stopTime.tv_usec - startTime.tv_usec) / 1000;
    itaca.setSolution(closed_arcs, interactive);
    itaca.PrintMaze();
    cout << "Time to solve: " << ticks << "ms"<< endl ;
    cout << "Path lenght: " << itaca.getSolutionSathLenght() << endl;

}

if(compare==true) {

  Maze itaca1 = Maze("Itaca1");
  itaca1.LoadFromFile(maze_path);
  Maze itaca2 = Maze("Itaca2");
  itaca2.LoadFromFile(maze_path);
  Maze itaca3 = Maze("Itaca3");
  itaca3.LoadFromFile(maze_path);
  static struct timeval startTime;
  static struct timeval stopTime;

  gettimeofday(&startTime, NULL);
  vector<MazeArc> closed_arcs_1 = itaca1.solve(BFS, interactive);
  gettimeofday(&stopTime, NULL);
  long ticks_1 = (stopTime.tv_sec - startTime.tv_sec) * 1000 + (stopTime.tv_usec - startTime.tv_usec) / 1000;
  itaca1.setSolution(closed_arcs_1, interactive);

  gettimeofday(&startTime, NULL);
  vector<MazeArc> closed_arcs_2 = itaca2.solve(DFS, interactive);
  gettimeofday(&stopTime, NULL);
  long ticks_2 = (stopTime.tv_sec - startTime.tv_sec) * 1000 + (stopTime.tv_usec - startTime.tv_usec) / 1000;
  itaca2.setSolution(closed_arcs_2, interactive);

  gettimeofday(&startTime, NULL);
  vector<MazeArc> closed_arcs_3 = itaca3.solve(BEFS, interactive);
  gettimeofday(&stopTime, NULL);
  long ticks_3 = (stopTime.tv_sec - startTime.tv_sec) * 1000 + (stopTime.tv_usec - startTime.tv_usec) / 1000;
  itaca3.setSolution(closed_arcs_3, interactive);
  
  cout << "Method\tPath lenght\tTime to solve" << endl;
  cout << "BFS\t" << itaca1.getSolutionSathLenght() << "\t\t" << ticks_1 << "ms" << endl;
  cout << "DFS\t" << itaca2.getSolutionSathLenght() << "\t\t" << ticks_2 << "ms" << endl;
  cout << "BEFS\t" << itaca3.getSolutionSathLenght() << "\t\t" << ticks_3 << "ms" << endl;



}

    return 0;
}
