
#ifndef UTILS_H
#define UTILS_H

#include <cstdlib>
#include <cmath>
#include <vector>
#include <list>
#include <iostream>
//#include <glm/glm.hpp>

inline float degToRad (int deg) {
	return ((float)((2.0*M_PI*deg)/360.0));
}

inline bool compareFloat (float f1, float f2, float error) {
	return (fabs(f2 - f1) < error);
//	return false;
}

inline bool compareVector (glm::vec3 v1, glm::vec3 v2, float error) {
	return ((fabs(v2[0] - v1[0]) < error) &&
		(fabs(v2[1] - v1[1]) < error) &&
		(fabs(v2[2] - v1[2]) < error));
//	return false;
}

template <typename T>
std::ostream& operator<< (std::ostream& out, const std::vector<T>& theVector) {
	for (unsigned int i=0; i<theVector.size(); i++) {
		out << theVector[i] << std::endl;
	}
	return out;
}


template <typename T>
std::ostream& operator<< (std::ostream& out, const std::list<T>& theList) {
	for (typename std::list<T>::const_iterator it = theList.begin(); it != theList.end(); ++it) {
		const T& i = *it;
		out << i << std::endl;
	}
	return out;
}

std::ostream& operator<< (std::ostream& out, const glm::vec3& c) {
	out << c[0] << " " << c[1] << " " << c[2];
	return out;
}

#endif

