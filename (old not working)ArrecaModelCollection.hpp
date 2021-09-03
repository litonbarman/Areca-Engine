#ifndef __ARRECAMODELCOLLECTION_HPP__
#define __ARRECAMODELCOLLECTION_HPP__


#include "ArrecaShader_type.hpp"
#include "ArrecaShader.hpp"
#include "ArrecaShaderCollection.hpp"
#include "ArrecaModel.hpp"
#include "ArrecaModelCollection_DB.hpp"

#include <vector>
#include <string.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


using namespace std;
using namespace Arreca;



namespace Arreca {
	
	struct ArrecaModelCollection_Node {
		
		Arreca::ArrecaModel* model;
		int shaderID;
		
		glm::vec3 position;
		glm::vec3 scale;
		glm::vec3 rotate;
		glm::mat4 mat;
		
	};
	
	class ArrecaModelCollection {
		
		private:
		    
			int getSIDFSName( const char* shaderName){
				
				if( strcmp(shaderName, "ARRECA_SHADER_GENERAL") ){
                    return ARRECA_SHADER_GENERAL;					
				}
				else if( strcmp(shaderName, "ARRECA_SHADER_NONSHADOW") ){
					return ARRECA_SHADER_NONSHADOW;
				}
				else if( strcmp(shaderName, "ARRECA_SHADER_NONSHALIGHT") ){
					return ARRECA_SHADER_NONSHALIGHT;
				}
				else if( strcmp(shaderName, "ARRECA_SHADER_NONTEXTURE") ){
					return ARRECA_SHADER_NONTEXTURE;
				}
				else {
					return ARRECA_SHADER_ERROR;
				}
				
			}
		
			std::vector<ArrecaModelCollection_Node> collection;
			Arreca::ArrecaShaderCollection shaders;
		
		public:
		    
			
			ArrecaModelCollection(){
				
				Arreca::ArrecaModelCollection_DB* database = new Arreca::ArrecaModelCollection_DB();
				
				printf("Model Collection\n");
				system("pause");

				for(int x=0; x < database->getSize(); x++){
					
					Arreca::ArrecaModelCollection_DB_NODE* temp = database->getFileName();
					
					ArrecaModelCollection_Node tempNode;
                       
					
					tempNode.model = new Arreca::ArrecaModel("test.obj");//temp->modelName );
					tempNode.shaderID = this->getSIDFSName( temp->shaderName);
					
					tempNode.position = temp->position;
					tempNode.scale    = temp->scale;
					tempNode.rotate   = temp->rotate;
					tempNode.mat      = temp->mat;
					
					this->collection.push_back( tempNode );
					
				}

			    delete database;                              // no use, so release the memory
			}

			~ArrecaModelCollection() {
				collection.empty();
				delete this;
			}
		    
			
			
	};
	
}


#endif