
#ifndef MATRIX_COORD_H
#define MATRIX_COORD_H

#include <cstdlib>
#include <iostream>

class MatrixCoord {
	public:

	int x;
	int y;
	MatrixCoord ();
	MatrixCoord (int newX, int newY);
	MatrixCoord (int* newMatrixCoord);
	~MatrixCoord ();
	
	void operator+= (const MatrixCoord& otherMatrixCoord);
	void operator-= (const MatrixCoord& otherMatrixCoord);
	MatrixCoord operator+ (const MatrixCoord& otherMatrixCoord);
	MatrixCoord operator- (const MatrixCoord& otherMatrixCoord);
	MatrixCoord operator- ();
	bool operator== (MatrixCoord& otherMatrixCoord);
	bool operator== (const MatrixCoord& otherMatrixCoord);
};

int distance (MatrixCoord pos1, MatrixCoord pos2);
std::ostream& operator<< (std::ostream& out, MatrixCoord& theMatrixCoord);
std::istream& operator>> (std::istream& in, MatrixCoord& theMatrixCoord);

//----


#endif

