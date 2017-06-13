

class Walls {
	public:
	float* vertexArray;
	float* normalArray;
	float* texcoordArray;

	unsigned int vertexNumber;

	Walls () {
		vertexArray = NULL;
		normalArray = NULL;
		texcoordArray = NULL;
	};
	
	~Walls () {
//		delete vertexArray;
//		delete normalArray;
//		delete texcoordArray;
	}

	Walls (const Matrix<char>& theField) {
		// each wall is responsible for adding a wall (quad) considering the normals (1, 0, 0) and (0, 0, 1) from its position.
		// for each coord, the vertex positions are calculated, and the lower/left (considering 2D) positions of the matrix are verified.
		// if I'm on a matrix position containing a wall, I should add a wall to normal 1,0,0 only if the left matrix position is not a wall.
		// also, I should only add a normal 0,0,1 wall if the lower position is 

		std::vector<glm::vec3> wallVertices;
		std::vector<glm::vec3> wallNormals;
		std::vector<glm::vec2> wallTexcoords;

		glm::vec2 texcoords[4] = {
			glm::vec2 (0.0f, 0.0f),
			glm::vec2 (1.0f, 0.0f),
			glm::vec2 (1.0f, 1.0f),
			glm::vec2 (0.0f, 1.0f)
		};

		MatrixCoord fieldSize = theField.getSize();
		for (int i=0; i<fieldSize.x; ++i) {
			for (int j=0; j<fieldSize.y; ++j) { // for each position
				MatrixCoord currentCoord (i, j);

				glm::vec3 vertices[6] = {
					glm::vec3 (pitchX * glm::vec3 (currentCoord.x - 1.0f, 0.0f, currentCoord.y - 1.0f)),
					glm::vec3 (pitchX * glm::vec3 (currentCoord.x       , 0.0f, currentCoord.y - 1.0f)),
					glm::vec3 (pitchX * glm::vec3 (currentCoord.x       , 1.0f, currentCoord.y - 1.0f)),
					glm::vec3 (pitchX * glm::vec3 (currentCoord.x - 1.0f, 1.0f, currentCoord.y - 1.0f)),
					glm::vec3 (pitchX * glm::vec3 (currentCoord.x - 1.0f, 0.0f, currentCoord.y       )),
					glm::vec3 (pitchX * glm::vec3 (currentCoord.x - 1.0f, 1.0f, currentCoord.y       ))
				};


				// ---- DOWN!
				{


					MatrixCoord down = currentCoord + MatrixCoord (0,-1);
					if (!theField.outOfBounds (down)) {
						// will only add wall if the adjacent position is different!
						if (theField[down] != theField[currentCoord]) { 
							if (theField[currentCoord] == '#') {
								// If I am on a # and down is a blank, the wall must be facing down.
								// counterclockwise X!
								int vert_cw_x[6] = { 1, 0, 2, 0, 3, 2 };
								int tc_cw_x[6] = { 1, 0, 2, 0, 3, 2 };
								for (unsigned int n=0; n<6; ++n) {
									wallVertices.push_back (vertices[vert_cw_x[n]]);
									wallTexcoords.push_back (texcoords[tc_cw_x[n]]);
									wallNormals.push_back (glm::vec3 (0.0f, 0.0f, -1.0f));
								}
							}
							else {
								int vert_ccw_x[6] = { 0, 1, 2, 0, 2, 3 };
								int tc_ccw_x[6] = { 0, 1, 2, 0, 2, 3 };
								for (unsigned int n=0; n<6; ++n) {
									wallVertices.push_back (vertices[vert_ccw_x[n]]);
									wallTexcoords.push_back (texcoords[tc_ccw_x[n]]);
									wallNormals.push_back (glm::vec3 (0.0f, 0.0f, 1.0f));
								}
							}
				//			std::cout << "adding wall down at " << currentCoord << std::endl;
						}
					}
				}

				// ----- LEFT!
				{

					MatrixCoord left = currentCoord + MatrixCoord (-1,0);
					if (!theField.outOfBounds (left)) {
						// will only add wall if the adjacent position is different!
						if (theField[left] != theField[currentCoord]) { 
							if (theField[currentCoord] == '#') {
								// if I am on a # and left is a blank, it must be facing left
								// counterclockwise Z!
								int vert_cw_z[6] = { 0, 4, 3, 4, 5, 3 };
								int tc_cw_z[6] = { 1, 0, 2, 0, 3, 2 };
								for (unsigned int n=0; n<6; ++n) {
									wallVertices.push_back (vertices[vert_cw_z[n]]);
									wallTexcoords.push_back (texcoords[tc_cw_z[n]]);
									wallNormals.push_back (glm::vec3 (0.0f, 0.0f, -1.0f));
								}
							}
							else {
								int vert_ccw_z[6] = { 4, 0, 3, 4, 3, 5 };
								int tc_ccw_z[6] = { 0, 1, 2, 0, 2, 3 };
								for (unsigned int n=0; n<6; ++n) {
									wallVertices.push_back (vertices[vert_ccw_z[n]]);
									wallTexcoords.push_back (texcoords[tc_ccw_z[n]]);
									wallNormals.push_back (glm::vec3 (0.0f, 0.0f, 1.0f));
								}
							}
						}
					}
				//	std::cout << "adding wall left at " << currentCoord << std::endl;
				}

			}
		}

		// Vectors are filled here
		// must convert to vertex arrays!

		vertexArray = new float[3*wallVertices.size()];
		normalArray = new float[3*wallNormals.size()];
		texcoordArray = new float[2*wallTexcoords.size()];

		vertexNumber = wallVertices.size();

		for (unsigned int i=0; i<vertexNumber; ++i) {
			vertexArray[i*3  ] = wallVertices[i][0];
			vertexArray[i*3+1] = wallVertices[i][1];
			vertexArray[i*3+2] = wallVertices[i][2];

			normalArray[i*3  ] = wallNormals[i][0];
			normalArray[i*3+1] = wallNormals[i][1];
			normalArray[i*3+2] = wallNormals[i][2];

			texcoordArray[i*2  ] = wallTexcoords[i][0];
			texcoordArray[i*2+1] = wallTexcoords[i][1];
		}

	}
};
