#ifndef __ARRECAMODELBUFFER_HPP__
#define __ARRECAMODELBUFFER_HPP__

#include <vector>
#include <stdio.h>

#include <GL/glewCustom.h>
#include <GLFW/glfw3.h>


#include "ArrecaModel.hpp"
#include "ArrecaShader.hpp"
#include "ArrecaControls.hpp"
#include "ArrecaBufferQueue.hpp"



namespace Arreca {
	
	struct ArrecaModelBuffer_Node {
		Arreca::ArrecaModel model;
		Arreca::ArrecaShader shader;
	};
	
	
	class ArrecaModelBuffer {
		
		private:
		
		    std::vector<ArrecaModelBuffer_Node> model;
			
		public:
		    
			ArrecaModelBuffer(){
				
				
				
			}
			
	};
	
	
	
}



#endif