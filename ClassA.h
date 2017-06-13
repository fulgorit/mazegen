#ifndef CLASSA_H
#define CLASSA_H

#endif // CLASSA_H

class cellA{

public:
        bool in;  //Is this cell in the maze?
        bool up;  //Does the wall above this cell exist?
        bool left;//Does the wall to the left of this cell exist?
        int prevx, prevy; //The coordinates of the previous cell, used for backtracking.
};
