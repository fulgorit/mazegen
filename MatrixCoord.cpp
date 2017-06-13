#include "MatrixCoord.h"

MatrixCoord::MatrixCoord () {
        x = y = 0;
}

MatrixCoord::MatrixCoord (int newX, int newY) {
        x = newX;
        y = newY;
}

MatrixCoord::MatrixCoord (int* newMatrixCoord) {
        x = newMatrixCoord[0];
        y = newMatrixCoord[1];
}

MatrixCoord::~MatrixCoord () {
}

void MatrixCoord::operator+= (const MatrixCoord& otherMatrixCoord) {
        x += otherMatrixCoord.x;
        y += otherMatrixCoord.y;
}

void MatrixCoord::operator-= (const MatrixCoord& otherMatrixCoord) {
        x -= otherMatrixCoord.x;
        y -= otherMatrixCoord.y;
}

MatrixCoord MatrixCoord::operator+ (const MatrixCoord& otherMatrixCoord) {
        return MatrixCoord (x+otherMatrixCoord.x,
                        y+otherMatrixCoord.y);
}

MatrixCoord MatrixCoord::operator- (const MatrixCoord& otherMatrixCoord) {
        return MatrixCoord (x-otherMatrixCoord.x,
                        y-otherMatrixCoord.y);
}
MatrixCoord MatrixCoord::operator- () {
        return MatrixCoord (-x,
                        -y);
}

bool MatrixCoord::operator== (MatrixCoord& otherMatrixCoord) {
        return ((x == otherMatrixCoord.x) &&
                (y == otherMatrixCoord.y));

}

bool MatrixCoord::operator== (const MatrixCoord& otherMatrixCoord) {
        return ((x == otherMatrixCoord.x) &&
                (y == otherMatrixCoord.y));
}

std::ostream& operator<< (std::ostream& out, MatrixCoord& theMatrixCoord) {
        out << theMatrixCoord.x << " " << theMatrixCoord.y;
        return out;
}

std::istream& operator>> (std::istream& in, MatrixCoord& theMatrixCoord) {
        in >> theMatrixCoord.x;
        in >> theMatrixCoord.y;
        return in;
}
