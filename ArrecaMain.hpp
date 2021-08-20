#ifndef __ARRECAMAIN_HPP__
#define __ARRECAMAIN_HPP__

#include "ArrecaGameData.hpp"
#include "ArrecaShader.hpp"
#include "ArrecaShaderDirect.hpp"
#include "ArrecaBufferQueue.hpp"
#include "ArrecaModel.hpp"

#include "ArrecaControls.hpp"


#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <stdio.h>
#include <GL/glewCustom.h>
#include <GLFW/glfw3.h>



extern void ArrecaUserLogic(Arreca::Arreca_BufferQueue<int>*);
extern void ArrecaUserRenderer(GLFWwindow* window, Arreca::Arreca_BufferQueue<int>*);

namespace Arreca {
	std::atomic_bool ArrecaRunning = true;

	std::vector<GLuint> VertexArrayID;
	GLuint vertexBuffer;
	GLuint programId;

	Arreca::Arreca_BufferQueue<int>* globalArrecaBuffer = new Arreca::Arreca_BufferQueue<int>();

	
	void LogicRender() {
		 while(ArrecaRunning) {
			ArrecaUserLogic(globalArrecaBuffer);
		 }
	}

	void GraphicRender() {

		GLFWwindow* window;
		glewExperimental = true;
		
		if (!glfwInit()) {
			fprintf(stderr, "Error : Failed to initialized GLFW\n");
			exit(-1);
		}
		
		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);               // not necessary for windows OS
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(1024, 768, "Arreca Engine", NULL, NULL);

		if (window == NULL) {
			fprintf(stderr, "Error : Failed creating window\n");
			glfwTerminate();
			exit(-1);
		}
		
		glfwMakeContextCurrent(window);

		if (glewInit() != GLEW_OK) {
			fprintf(stderr, "Error : Failed initializing GLEW\n");
			glfwTerminate();
			exit(-1);
		}
        
		glEnable(GL_DEPTH_TEST);
		glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
		glClearColor(0.0f, 0.0f, 1.0f, 0.0f);

		//////////////////////////

		
		VertexArrayID.resize(VertexArrayID.size() + 1);
		glGenVertexArrays(1, &VertexArrayID[0]);
		glBindVertexArray(VertexArrayID[0]);

		static const GLfloat gl_vertex_buffer[] = {
			-1.0f, -1.0f, 0.0f,
			 1.0f, -1.0f, 0.0f,
			 0.0f,  1.0f, 0.0f
		};

		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(gl_vertex_buffer), gl_vertex_buffer, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FLOAT, 0, (void*)0);

		//programId = LoadShader("(old)Shaders/vertex.sl", "(old)Shaders/fragment.sl");
		//glUseProgram(programId);


		//////////////////////////
		
		Arreca::ArrecaShader ourShader("vertex.sl", "fragment.sl");
		Arreca::ArrecaModel ourModel("cyborg/cyborg.obj");

		Arreca::ArrecaControls ourContorls(window);

		
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));

		do {

			ourContorls.computeMatricesFreeTransform();
			
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


			ourShader.use();
			ourShader.setMat4("projection", ourContorls.getProjectionMatrix());
			ourShader.setMat4("view", ourContorls.getViewMatrix());
			ourShader.setMat4("model", model);


			ourShader.setVec3("lightColor", vec3(1.0f, 1.0f, 1.0f));
			ourShader.setVec3("lightPos", vec3(0, 20.0f, 0));
			ourShader.setVec3("viewPos", ourContorls.getViewPos());


            ArrecaUserRenderer(window, globalArrecaBuffer);
			ourModel.Draw(ourShader);

			glfwSwapBuffers(window);
			glfwPollEvents();
			Sleep(10);
		}
		while (ArrecaRunning && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

		glfwTerminate();
		ArrecaRunning = false;
		
		glDeleteBuffers(1, &vertexBuffer);
		glDeleteVertexArrays(1, &VertexArrayID[0]);
		
	}

	class ArrecaMainLogic {
		public:
			ArrecaMainLogic();
			~ArrecaMainLogic();
			
			void join(){
				this->ArrecaMainLogicThread->join();
			}

			friend void LogicRender();

		private:
			std::thread* ArrecaMainLogicThread;

	};

	class ArrecaMainRenderer {
		public:
			ArrecaMainRenderer();
			~ArrecaMainRenderer();

			void join() {

			}
		private:
			std::thread* ArrecaMainRenderThread;

	};
}

#include "ArrecaMain.cpp"

#endif




/*glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	static const GLfloat trianle_Vertices[] = {
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f
	};

	glGenBuffers(1, &VBO);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(trianle_Vertices), trianle_Vertices, GL_STATIC_DRAW);
	*/