#ifndef __ARRECAMAIN_CPP__
#define __ARRECAMAIN_CPP__

#include "ArrecaMain.hpp"
#include "ArrecaGameData.hpp"

#include <iostream>
#include <thread>
#include <stdio.h>
#include <GL/glewCustom.h>
#include <GLFW/glfw3.h>

#include <Windows.h>


Arreca::ArrecaMainLogic::ArrecaMainLogic(){
	printf("Constuctor\n");


	this->ArrecaMainLogicThread = new std::thread(Arreca::LogicRender);
}

Arreca::ArrecaMainLogic::~ArrecaMainLogic() {
	Arreca::ArrecaRunning = false;
	printf("Destructor called..........................\n");

	this->ArrecaMainLogicThread->detach();
	// should be called by the below code automatically this->ArrecaMainLogicThread->~thread();
	delete this->ArrecaMainLogicThread;
}

Arreca::ArrecaMainRenderer::ArrecaMainRenderer() {
	printf("Constuctor renderer\n");


	this->ArrecaMainRenderThread = new std::thread(Arreca::GraphicRender);
}

Arreca::ArrecaMainRenderer::~ArrecaMainRenderer() {
	Arreca::ArrecaRunning = false;
	printf("Destructor called..........................\n");

	this->ArrecaMainRenderThread->detach();
	// should be called by the below code automatically this->ArrecaMainLogicThread->~thread();
	delete this->ArrecaMainRenderThread;
}



#endif