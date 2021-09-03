#ifndef __ARRECAMODELLIST_HPP__
#define __ARRECAMODELLIST_HPP__

#include <vector>
#include <stdio.h>
#include <string.h>



namespace Arreca {
	
	struct ArrecaModelList_list {
		
		char modelName[500];                            // path included
		char shaderName[500];                           // path included
		
	};
	
	class ArrecaModelList {
		
		private:
		    
			std::vector<ArrecaModelList_list> list;
			short size;
		
		
		public:
		    
			ArrecaModelList() : retriveSize(0){
				
				FILE* file = fopen("ArrecaData.db", "r");
				
				printf("Constructor...\n");
				
				if( file == NULL ){
					fprintf( stderr, "ERROR::ArrecaDatabaseReader: ArrecaData.db not found or unable to read\n" );
				}
				else{
					printf("File open \n");
					char fileName[500];
					
					bool bufferOK = true;
					
					while(bufferOK){
						
						int res = fscanf(file, "%s", &fileName);
						
						if( res == EOF){
							break;
						}
						else{
							
							char shaderName[500];
							
							int resS = fscanf(file, "%s", &shaderName);
							
							if( resS == EOF){
								fprintf( stderr, "ERROR::AccecaDatabaceReader: ShaderName not found for %s, EOF reached\n", shaderName );
								bufferOK = false;
								break;
							}
							else{
								
								ArrecaModelList_list templist;
								strcpy(templist.modelName, fileName);
								strcpy(templist.shaderName, shaderName);
								
								this->list.push_back(templist);
								
							}
							
						}
						
					}
					
					
				}
				
				fclose(file);
				this->size = this->list.size();
				
			}
		

		
			~ArrecaModelList(){
				
				this->list.empty();
				delete this;
				
			}
		
            
			short retriveSize;
			
            Arreca::ArrecaModelList_list* getFileName(){
				
				if(retriveSize < this->size){
					
					return &this->list[retriveSize++];
					
				}
				
			}
			
			short getSize(){
				return this->size;
			}
	};
	
}


#endif