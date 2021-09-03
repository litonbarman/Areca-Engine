#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS

#include <thread>
#include <atomic>
#include <mutex>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Windows.h>

#include "Arreca.hpp"
#include "ArrecaBufferQueue.hpp"
#include "ArrecaModel.hpp"
#include "ArrecaShader.hpp"
#include "ArrecaShaderDirect.hpp"

#include "ArrecaModelCollection.hpp"                // not working and still trying to figure out whats going on...

using namespace Arreca;


double timePre = glfwGetTime(), timeNow = glfwGetTime();
int countT=0;

void ArrecaUserLogic(Arreca::Arreca_BufferQueue<int>*);
void ArrecaUserRenderer(GLFWwindow*, Arreca::Arreca_BufferQueue<int>*);

std::mutex mu;



int main(void) {
/*
//----------------------------------------------------------
	ArrecaInit();


	do{
		Sleep(200);
	} 
	while(!GetAsyncKeyState(VK_SPACE));
	
	system("pause");

	ArrecaTerminate();
//---------------------------------------------------------
*/
	
	
	Arreca::ArrecaModelCollection* modelCol;
	modelCol = new Arreca::ArrecaModelCollection();

	Sleep(400);
	system("pause");
	
	delete modelCol;
	

	


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

		Arreca::Arreca_BufferNode<int>* temp = buffer->dequeue();    // buffer is global located in ArrecaEngineGlobal
		Arreca::Arreca_BufferNode<int>* hold;

		while ((hold = buffer->dequeue()) != 0) {
			delete temp;
			temp = hold;
		}

		std::cout << temp->data << " \n";
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


}


