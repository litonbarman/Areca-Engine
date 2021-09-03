#ifndef __ARRECAMODELCOLLECTION_DB_HPP__
#define __ARRECAMODELCOLLECTION_DB_HPP__


#include <vector>
#include <stdio.h>
#include <string.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


using namespace glm;



namespace Arreca {

	struct ArrecaModelCollection_DB_NODE {

		char modelName[500];
		char shaderName[500];

		glm::vec3 position;
		glm::vec3 scale;
		glm::vec3 rotate;
		glm::mat4 mat;                // glm::mat4

	};



	class ArrecaModelCollection_DB {

		private:
			
			std::vector<ArrecaModelCollection_DB_NODE> list;
			short size;

		public:

			short retriveSize;

			ArrecaModelCollection_DB() : retriveSize(0), size(0) {

				FILE* file = fopen("ArrecaData.db", "r");


				if (file == NULL) {

					fprintf(stderr, "ERROR::DATABASE_READER:ArrecaData.db not found or unable to open\n");
					return;
				}

				else {

					char fileName[500];
					bool bufferOK = true;

					while (bufferOK) {

						int res = fscanf( file, "%s", &fileName);

						if (res == EOF) {
							break;
						}
						else {

							char shaderName[500];
							int resS = fscanf( file, "%s", &shaderName );

							float xP, yP, zP;
							float xS, yS, zS;
							float xR, yR, zR;
							float positionState;

							if (resS == EOF) {
								fprintf(stderr, "ERROR::ArrecaDatabaseReader:ShaderName not found %s, EOF reached\n", shaderName);
								bufferOK = false;
								break;
							}
							else {
								resS = fscanf(file, "%f %f %f", &xP, &yP, &zP);

								if (resS == EOF) {
									fprintf(stderr, "ERROR::ArrecaDatabaseReader:ModelPosition not found %s, EOF reached\n", shaderName);
									bufferOK = false;
									break;
								}
								else {
									resS = fscanf(file, "%f %f %f", &xS, &yS, &zS);

									if (resS == EOF) {
										fprintf(stderr, "ERROR::ArrecaDatabaseReader:ModelScale not found %s, EOF reached\n", shaderName);
										bufferOK = false;
										break;
									}
									else {
										resS = fscanf(file, "%f %f %f", &xR, &yR, &zR);

										if (resS == EOF) {
											fprintf(stderr, "ERROR::ArrecaDatabaseReader:ModelRotation not found %s, EOF reached\n", shaderName);
											bufferOK = false;
											break;
										}
										else {
											resS = fscanf(file, "%f", &positionState);
										}
									}
								}
							}
							


							if (resS == EOF) {

								fprintf( stderr, "ERROR::ArrecaDatabaseReader:ModelMat4 not found %s, EOF reached\n", shaderName);
								bufferOK = false;
								break;

							}
							else {
								
								ArrecaModelCollection_DB_NODE tempNode;
								strcpy(tempNode.modelName, fileName);
								strcpy(tempNode.shaderName, shaderName);
								tempNode.position = glm::vec3(xP, yP, zP);
								tempNode.scale    = glm::vec3(xS, yS, zS);
								tempNode.scale    = glm::vec3(xR, yR, zR);
								tempNode.mat      = glm::mat4(positionState);


								this->list.push_back(tempNode);

							}

						}

					}

				}

				fclose(file);
				this->size = this->list.size();
			}


			~ArrecaModelCollection_DB() {

				this->list.empty();
				delete this;

			}

			
			ArrecaModelCollection_DB_NODE* getFileName() {

				if (this->retriveSize < this->size) {
					return &this->list[this->retriveSize++];
				}
				else {
					this->retriveSize = 0;
					return &this->list[this->retriveSize++];
				}

			}

			short getSize() {
				return this->size;
			}
	};

}


#endif