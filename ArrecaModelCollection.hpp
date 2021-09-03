#ifndef __ARRECAMODELCOLLECTION_HPP__
#define __ARRECAMODELCOLLECTION_HPP__

#include "ArrecaModelCollection_DB.hpp"
#include "ArrecaShader_type.hpp"
#include "ArrecaModel.hpp"

#include <stdio.h>


using namespace Arreca;


namespace Arreca {

	class ArrecaModelCollection : public Arreca::ArrecaModelCollection_DB {

		private:

			int getSIDFSName(const char* shaderName) {
				if (strcmp( shaderName, "ARRECA_SHADER_GENERAL")){
					return ARRECA_SHADER_GENERAL;
				}
				else if (strcmp(shaderName, "ARRECA_SHADER_NONSHADOW")){
					return ARRECA_SHADER_NONSHADOW;
			    }
				else if (strcmp(shaderName, "ARRECA_SHADER_NONSHALIGHT")) {
					return ARRECA_SHADER_NONSHALIGHT;
				}
				else if (strcmp(shaderName, "ARRECA_SHADER_NON_TEXTURE")) {
					return ARRECA_SHADER_NONTEXTURE;
				}
				else {
					return ARRECA_SHADER_ERROR;
				}	          
			};


	    public:

			ArrecaModelCollection() : ArrecaModelCollection_DB() {

				printf("constructor...\n");
				Arreca::ArrecaModel  model("cyborg/cyborg.obj");
				
				

			}

			~ArrecaModelCollection() {
				printf("Destructor\n");
			}

	};

};

#endif