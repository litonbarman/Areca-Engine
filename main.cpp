#include <thread>
#include <atomic>
#include <mutex>
#include <stdio.h>
#include <GL/glewCustom.h>
#include <GLFW/glfw3.h>

#include <Windows.h>

#include "Arreca.hpp"
#include "ArrecaBufferQueue.hpp"

#include "ArrecaModel.hpp"
#include "ArrecaShader.hpp"

#include "ArrecaShaderDirect.hpp"

using namespace Arreca;


double timePre = glfwGetTime(), timeNow = glfwGetTime();
int countT=0;

void ArrecaUserLogic(Arreca::Arreca_BufferQueue<int>*);
void ArrecaUserRenderer(GLFWwindow*, Arreca::Arreca_BufferQueue<int>*);

std::mutex mu;



int main(void) {

	ArrecaInit();


	do{
		Sleep(200);
	} 
	while(!GetAsyncKeyState(VK_SPACE));
	
	system("pause");

	ArrecaTerminate();
	
	return 0;
}

int a = 0;

void ArrecaUserLogic(Arreca::Arreca_BufferQueue<int>* buffer) {
//	printf("User Logic\n");

	
	buffer->enqueue(a++);

	Sleep(100);
}

void ArrecaUserRenderer(GLFWwindow* window, Arreca::Arreca_BufferQueue<int>* buffer) {
	timeNow = glfwGetTime();
	double timeDif = timeNow - timePre;
	timePre = timeNow;

	if (countT >= 50) {

		Arreca::Arreca_BufferNode<int>* temp = buffer->dequeue();    // buffer is global located in ArrecaGameData
		Arreca::Arreca_BufferNode<int>* hold;

		while ((hold = buffer->dequeue()) != 0) {
			delete temp;
			temp = hold;
		}

		//std::cout << temp->data << " \n";
		delete temp;

	//	printf("User Renderer\n");

		/*
		mu.lock();
		printf("FPS : %.3f\n", (double)(1 / timeDif));
		mu.unlock();
		*/
		countT = 0;
	}
	else {
		countT++;
	}

	//glEnableVertexAttribArray(0);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);

}


