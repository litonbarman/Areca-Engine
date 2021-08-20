#ifndef __ARRECAMODELBUFFER_HPP__
#define __ARRECAMODELBUFFER_HPP__

#include <vector>
#include <stdio.h>
#include <GL/glewCustom.h>
#include <GLFW/glfw3.h>


#include "ArrecaShader.hpp"
#include "ArrecaBufferQueue.hpp"
#include "ArrecaModel.hpp"

namespace Arreca {
	
	struct ArrecaModelBuffer_Node {
		Arreca::ArrecaModel model;
		Arreca::ArrecaShader shader;
	};
	
	class ArrecaModelBuffer {
		
	    private:
		    
			Arreca::ArrecaBufferQueue<ArrecaModelBuffer_Node>* buffer;
			short size;
		
		public:
		    
			ArrecaModelBuffer(short size) : size(size) {

				this->buffer = new Arreca::ArrecaBufferQueue<ArrecaModelBuffer_Node>();

			}
			
			~ArrecaModelBuffer(){

				this->buffer->~ArrecaBufferQueue();

			}
			
			void enqueue(const ArrcaModelBuffer_Node &node){
				
				this->buffer->enqueue(node);
				
			}
			
			ArrecaModelBuffer_Node* dequeue(){
				this->buffer->dequeue();
			}
		
	};
	
}



#endif