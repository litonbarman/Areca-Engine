#ifndef _ARRECASHADERCOLLECTION_HPP__
#define _ARRECASHADERCOLLECTION_HPP__

#include "ArrecaShader.hpp"
#include "ArrecaShader_type.hpp"

#include <vector>

using namespace std;
using namespace Arreca;

namespace Arreca {
	
    class ArrecaShaderCollection {
		
		private:
		    
			std::vector<Arreca::ArrecaShader> shaderCollection;

	    public:
			
			ArrecaShaderCollection(){

				shaderCollection.push_back(Arreca::ArrecaShader("shaderCollection/ARRECA_SHADER_GENERAL_VERTEX.sl", "shaderCollection/ARRECA_SHADER_GENERAL_FRAGMENT.sl"));
				shaderCollection.push_back(Arreca::ArrecaShader("shaderCollection/ARRECA_SHADER_NONSHADOW_VERTEX.sl", "shaderCollection/ARRECA_SHADER_NONSHADOW_FRAGMENT.sl"));
				shaderCollection.push_back(Arreca::ArrecaShader("shaderCollection/ARRECA_SHADER_NONSHALIGHT_VERTEX.sl", "shaderCollection/ARRECA_SHADER_NONSHALIGHT_FRAGMENT.sl"));
				shaderCollection.push_back(Arreca::ArrecaShader("shaderCollection/ARRECA_SHADER_NONTEXTURE_VERTEX.sl", "shaderCollection/ARRECA_SHADER_NONTEXTURE_FRAGMENT.sl"));

			}
			

		    
			~ArrecaShaderCollection(){
				this->shaderCollection.empty();
				delete this;
			}
			
			Arreca::ArrecaShader& getShader(const int shaderID){
				return this->shaderCollection[shaderID];
			}
	
    };
	
}

#endif