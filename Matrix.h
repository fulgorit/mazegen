
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include "MatrixCoord.h"
#include "maze.h"

template <typename T>
class Matrix {
        public:
	std::vector<T> data;
	int sizeX, sizeY;
	int vectorSize;

	public:
	Matrix ();
	Matrix (int newSizeX, int newSizeY);
	Matrix (MatrixCoord gridSize);
	~Matrix ();

	MatrixCoord getSize () const;


	int computeIndex (MatrixCoord& matrixCoord) const;
	bool outOfBounds (MatrixCoord& matrixCoord) const;

	T& operator[] (MatrixCoord matrixCoord);
	T operator[] (MatrixCoord matrixCoord) const;
};

template <typename T>
std::ostream& operator<< (std::ostream& out, Matrix<T>& theMatrix);

template <typename T>
Matrix<T>::Matrix () {
	sizeX = 0;
	sizeY = 0;
	vectorSize = 0;
}

template <typename T>
Matrix<T>::Matrix (int newSizeX, int newSizeY) {
	sizeX = newSizeX;
	sizeY = newSizeY;
	vectorSize = sizeX * sizeY;
	data = std::vector<T>(vectorSize);
}

template <typename T>
Matrix<T>::Matrix (MatrixCoord newMatrixSize) {
	sizeX = newMatrixSize.x;
	sizeY = newMatrixSize.y;
	vectorSize = sizeX * sizeY;
	data = std::vector<T>(vectorSize);
}

template <typename T>
Matrix<T>::~Matrix () {
//	std::cout << "deleting points " << vectorSize << std::endl;
}

template <typename T>
MatrixCoord Matrix<T>::getSize () const {
	return MatrixCoord (sizeX, sizeY);
}


template <typename T>
int Matrix<T>::computeIndex (MatrixCoord& matrixCoord) const {
	int x = matrixCoord.x;
	int y = matrixCoord.y;
	return x + sizeX*y;
}

template <typename T>
bool Matrix<T>::outOfBounds (MatrixCoord& matrixCoord) const {
	int x = matrixCoord.x;
	int y = matrixCoord.y;
	return ((x<0) || (y<0) || (x>=sizeX) || (y>=sizeY));
}

template <typename T>
T& Matrix<T>::operator[] (MatrixCoord matrixCoord) {
	return data[computeIndex(matrixCoord)];
}

template <typename T>
T Matrix<T>::operator[] (MatrixCoord matrixCoord) const {
	return data[computeIndex(matrixCoord)];
}

template <typename T>
std::ostream& operator<< (std::ostream& out, Matrix<T>& theMatrix) {
	MatrixCoord matrixSize = theMatrix.getSize();
	for (int j=matrixSize.y-1; j>=0; j--) {
		for (int i=0; i<matrixSize.x; i++) {
			std::cout << theMatrix[MatrixCoord(i, j)] << " ";
		}
		std::cout << std::endl;
	}
	return out;
}






#endif

