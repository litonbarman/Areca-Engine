// under development

#ifndef __ARRECAGLBUFFER_HPP__
#define __ARRECAGLBUFFER_HPP__

#include "Arreca.hpp"
#include "ArrecaGameData.hpp"
#include "ArrecaMain.hpp"
#include "ArrecaMesh.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include <vector>


unsing namespace std;
unsing namespace Arreca;


namespace Arreca {
	
	unsigned int Arreca_createVAO(){
		
		unsigned int VAO;
		
		glGenVertexArrays(1, &VAO);
		
		return VAO;
		
	}
	
	
	unsigned int Arreca_GenBO(){
		
		unsigned int BO;
		
		glGenBuffers(1, &BO);
		
		return BO;
		
	}
	
	
	void Arreca_BindVAO(unsigned int const VAO){
		
		glBindVertexArray(VAO);
		
	}
	
	
	void Arreca_BindVBO(unsigned int const VBO){
		
		glBindBuffer( GL_ARRAY_BUFFER, VBO);
		
	}
	
	
	void Arreca_BindEBO(unsigned int const EBO){
		
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO);
		
	}
	
	
	void Arreca_uploadABD_static(vector<ArrecaMesh_vertex>* vertices){
		
		glBufferData( GL_ARRAY_BUFFER, (vertices.size() * sizeof(ArrecaMesh_vertex)), &vertices[0], GL_STATIC_DRAW );
		
	}
	
	void Arreca_uploadEBD_static(vector<unsigned int>* indices){
		
		glBufferData( GL_ELEMENT_ARRAY_BUFFER, (indices.size() * sizeof(unsigned int)), &indices[0], GL_STATIC_DRAW );
		
	}
	
	
	void Arreca_uploadABD_dynamic(vector<ArrecaMesh_vertex>* vertices){
		
		glBufferData( GL_ARRAY_BUFFER, (vertices.size() * sizeof(ArrecaMesh_vertex)), &vertices[0], GL_DYNAMIC_DRAW );
		
	}
	
	void Arreca_uploadEBD_dynamic(vector<unsigned int>* indices){
		
		glBufferData( GL_ELEMENT_ARRAY_BUFFER, (indices.size() * sizeof(unsigned int)), &indices[0], GL_DYNAMIC_DRAW );
		
	}
	
}

#endif