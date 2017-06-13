#include "Cell.h"

Cell::Cell() {
        directions.clear();
        up = down = right = left = false;
        visited = 0;
}

std::ostream& operator<< (std::ostream& out, Cell& theCell) {
        out << theCell.up << theCell.down << theCell.right << theCell.left << theCell.visited << "(" << theCell.tree << ")";
        return out;
}
