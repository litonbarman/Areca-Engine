#ifndef __ARRECA_HPP__
#define __ARRECA_HPP__

#include "ArrecaEngineGlobal.hpp"
#include "ArrecaMain.hpp"
#include "ArrecaBufferQueue.hpp"

#include <vector>
#include <atomic>
#include <stdio.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Arreca {

	typedef std::atomic_short  Arreca_short;
	typedef std::atomic_ushort Arreca_ushort;
	typedef std::atomic_int    Arreca_int;
	typedef std::atomic_uint   Arreca_uint;
	typedef std::atomic_long   Arreca_long;
	typedef std::atomic_ulong  Arreca_ulong;
	typedef std::atomic_bool   Arreca_bool;
	typedef std::atomic_char   Arreca_char;
	typedef std::atomic_uchar  Arreca_uchar;
	typedef glm::mat2          Arreca_mat2;
	typedef glm::mat3          Arreca_mat3;
	typedef glm::mat4          Arreca_mat4;


	struct ArrecaShared_short {
		Arreca_short ArrecaD[2];
	};

	struct ArrecaShared_ushort {
		Arreca_ushort ArrecaD[2];
	};

	struct ArrecaShared_int {
		Arreca_int ArrecaD[2];
	};

	struct ArrecaShared_uint {
		Arreca_int ArrecaD[2];
	};

	struct ArrecaShared_long {
		Arreca_long ArrecaD[2];
	};

	struct ArrecaShared_ulong {
		Arreca_ulong ArrecaD[2];
	};

	struct ArrecaShared_bool {
		Arreca_bool ArrecaD[2];
	};

	struct ArrecaShared_char {
		Arreca_char ArrecaD[2];
	};

	struct ArrecaShared_uchar {
		Arreca_uchar ArrecaD[2];
	};

	struct ArrecaShared_mat2 {
		Arreca_mat2 ArrecaD[2];
	};

	struct ArrecaShared_mat3 {
		Arreca_mat3 ArrecaD[2];
	};

	struct ArrecaShared_mat4 {
		Arreca_mat4 ArrecaD[2];
	};


	Arreca_ushort ArrecaBufferState;         // double buffer so 0/1







	void ArrecaInit() {
		mainLogic = new Arreca::ArrecaMainLogic();
		mainRender = new Arreca::ArrecaMainRenderer();

		//mainLogic->join();
		//mainRender->join();
	};

	void ArrecaTerminate() {
		Arreca::ArrecaRunning = false;
    //	it should be automactically called by the below code: mainLogic->~ArrecaMainLogic();
		delete mainLogic;

	//	it should be automactically called by the below code:  mainRender->~ArrecaMainRenderer();
		delete mainRender;

	}
}

#endif