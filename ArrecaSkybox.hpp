#ifndef __ARRECASKYBOX_HPP__
#define __ARRECASKYBOX_HPP__


#include "ArrecaShaderDirect.hpp"
#include "stb_image.h"

#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>




using namespace Arreca;
using namespace std;




namespace Arreca {
	
	
	class ArrecaSkybox {
		
		private:

			unsigned int skyboxVAO;
			unsigned int skyboxVBO;
			
			unsigned int skyboxShaderID;
			unsigned int skyboxInt;
			unsigned int skyboxModel;
			unsigned int skyboxView;
			unsigned int skyboxProjection;

			glm::mat4 skybox_model;
			
			unsigned int cubemapTexture;

			unsigned int loadCubemap(std::vector<std::string> faces) {

				unsigned int textureID;

				glGenTextures(1, &textureID);
				glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

				int width, height, nrChannels;

				for (unsigned int i = 0; i < faces.size(); i++) {

					unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);

					if (data) {

						glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
						stbi_image_free(data);
					}
					else {

						std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
						stbi_image_free(data);
					}
				}

				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

				return textureID;

			}
			
			
	    public:

			ArrecaSkybox(){
				
				float skyboxVertices[] = {
		                // positions only         
		                -1.0f,  1.0f, -1.0f,
		                -1.0f, -1.0f, -1.0f,
		                 1.0f, -1.0f, -1.0f,
		                 1.0f, -1.0f, -1.0f,
		                 1.0f,  1.0f, -1.0f,
		                -1.0f,  1.0f, -1.0f,

		                -1.0f, -1.0f,  1.0f,
		                -1.0f, -1.0f, -1.0f,
		                -1.0f,  1.0f, -1.0f,
		                -1.0f,  1.0f, -1.0f,
		                -1.0f,  1.0f,  1.0f,
		                -1.0f, -1.0f,  1.0f,

		                 1.0f, -1.0f, -1.0f,
		                 1.0f, -1.0f,  1.0f,
		                 1.0f,  1.0f,  1.0f,
		                 1.0f,  1.0f,  1.0f,
		                 1.0f,  1.0f, -1.0f,
		                 1.0f, -1.0f, -1.0f,

		                -1.0f, -1.0f,  1.0f,
		                -1.0f,  1.0f,  1.0f,
		                 1.0f,  1.0f,  1.0f,
		                 1.0f,  1.0f,  1.0f,
		                 1.0f, -1.0f,  1.0f,
		                -1.0f, -1.0f,  1.0f,

		                -1.0f,  1.0f, -1.0f,
		                 1.0f,  1.0f, -1.0f,
		                 1.0f,  1.0f,  1.0f,
		                 1.0f,  1.0f,  1.0f,
		                -1.0f,  1.0f,  1.0f,
		                -1.0f,  1.0f, -1.0f,

		                -1.0f, -1.0f, -1.0f,
		                -1.0f, -1.0f,  1.0f,
		                 1.0f, -1.0f, -1.0f,
		                 1.0f, -1.0f, -1.0f,
		                -1.0f, -1.0f,  1.0f,
		                 1.0f, -1.0f,  1.0f
	                };
					
                this->skyboxShaderID = Arreca::ArrecaLoadShader("skybox/skyboxVertex.sl", "skybox/skyboxFragment.sl");

                this->skyboxInt = glGetUniformLocation(this->skyboxShaderID, "skybox");
                this->skyboxModel = glGetUniformLocation(this->skyboxShaderID, "model");
                this->skyboxView = glGetUniformLocation(this->skyboxShaderID, "view");
                this->skyboxProjection = glGetUniformLocation(this->skyboxShaderID, "projection");			    
				
				glGenVertexArrays(1, &this->skyboxVAO);
				glGenBuffers(1, &this->skyboxVBO);
				
				glBindVertexArray(this->skyboxVAO);
				glBindBuffer(GL_ARRAY_BUFFER, this->skyboxVAO);
				glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0 );
				
				std::vector<std::string> faces
				{
					"skybox/right.jpg",
					"skybox/left.jpg",
					"skybox/top.jpg",
					"skybox/bottom.jpg",
					"skybox/front.jpg",
					"skybox/back.jpg"
				};
				
				this->cubemapTexture = loadCubemap(faces);

				skybox_model = glm::mat4(1.0f);
				skybox_model = glm::scale(skybox_model, glm::vec3(100.1, 100.1, 100.1));
				
			}
			

			~ArrecaSkybox() {

				glDeleteProgram(this->skyboxShaderID);
				glDeleteBuffers(1, &this->skyboxVBO);
				glDeleteVertexArrays(1, &this->skyboxVAO);
				glDeleteTextures(1, &this->cubemapTexture);
			
			}


			
			
			void Draw( glm::mat4 VIEW, glm::mat4 PROJECTION ){
				
				glm::mat4 skybox_view = glm::mat4( glm::mat3(VIEW) );
				
				glDepthFunc(GL_LEQUAL);
				
				glUseProgram(this->skyboxShaderID);
				
				glUniform1i(this->skyboxInt, 0);
		
				glUniformMatrix4fv(this->skyboxModel, 1, GL_FALSE, &this->skybox_model[0][0]);
				glUniformMatrix4fv(this->skyboxView, 1, GL_FALSE, &skybox_view[0][0]);
				glUniformMatrix4fv(this->skyboxProjection, 1, GL_FALSE, &PROJECTION[0][0]);
				
				glBindVertexArray(this->skyboxVAO);
				glBindTexture(GL_TEXTURE_CUBE_MAP, this->cubemapTexture);
				glDrawArrays(GL_TRIANGLES, 0, 36);
				glBindVertexArray(0);
				glDepthFunc(GL_LESS);
				
			}
			
			
		
	};
	
	
}


#endif