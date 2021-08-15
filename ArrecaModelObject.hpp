#ifndef __ARRECAMODELOBJECT_HPP__
#define __ARRECAMODELOBJECT_HPP__

#include <vector>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include "ArrecaShader.hpp"

#define ARRECA_SHADER_SHADOW        0          // only shadow
#define ARRECA_SHADER_REFLECT       1          // only reflect
#define ARRECA_SHADER_REFRACT       2          // only refract
#define ARRECA_SHADER_NORMAL        3          // only black & white
#define ARRECA_SHADER_RGB           4          // only RGB
#define ARRECA_SHADER_RGBA          6          // only RGBA
#define ARRECA_SHADER_TRANS         7          // only transparent
#define ARRECA_SHADER_RRRT          8          // only reflect refract RGB transparent
#define ARRECA_SHADER_RRRAT         9          // only reflect refract RGBA trasparent

#define ARRECA_SHADER_SIZE          10

namespace Arreca {
	
	char* directoryFromShaderCode(int code){
		
	}
	
	class ArrecaShaderBank {

		private:
		    ArrecaShaderBank() {
				this->shader.resize(ARRECA_SHADER_SIZE);

				for (int a = 0; a <= ARRECA_SHADER_SIZE; a++) {

					this->shader[a] = new ArrecaShader();
				}
			}

			~ArrecaShaderBank() {
				
			}
			
		public:
			std::vector<Arreca::ArrecaShader>  shader;
	};

	class ArrecaModelObject {

		private:
			
	};

}


#endif