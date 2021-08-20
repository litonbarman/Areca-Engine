#ifndef __ARRECACONTROLS_HPP__
#define __ARRECSCONTROLS_HPP__

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;
//using namespace Arreca;



namespace Arreca {
	
	
	class ArrecaControls {
		
		private:

			GLFWwindow* window;
		
		    mat4 ViewMatrix, ProjectionMatrix;	
			vec3 position;
			
			float horizontalAngle;                           //  = 3.14f see constructor
            float verticalAngle;                             // = 0.0f see constructor
            float initialFoV;                                // = 45.0f see constructor
            float speed;                                     // = 3.0f; // 3 units per second  see constructor            
			float mouseSpeed;                                // = 0.005f see constructor

        public:
            
			//----------------------------------------------------------------------------
            
			ArrecaControls(GLFWwindow* window) : window(window), position(0, 0, 5), horizontalAngle(3.14f), verticalAngle(0.0f), initialFoV(45.0f), speed(3.0f), mouseSpeed(0.005f)	{
				
			}
			
			
			~ArrecaControls(){
				delete this;
			}
			
			//----------------------------------------------------------------------------
			
			
			//----------------------------------------------------------------------------
			// getter functions
			
			mat4 getViewMatrix(){
	            return this->ViewMatrix;
            }
            
			mat4 getProjectionMatrix(){
	            return this->ProjectionMatrix;
            }
			
			vec3 getViewPos(){
				return this->position;
			}

			//---------------------------------------------------------------------------
			
			
			//---------------------------------------------------------------------------
			// functions that compute vector math
			
			void computeMatricesFreeTransform(){

	            // glfwGetTime is called only once, the first time this function is called
	            static double lastTime = glfwGetTime();

	            // Compute time difference between current and last frame
	            double currentTime = glfwGetTime();
	            float deltaTime = float(currentTime - lastTime);

	            // Get mouse position
	            double xpos, ypos;
	            glfwGetCursorPos(window, &xpos, &ypos);

	            // Reset mouse position for next frame
	            glfwSetCursorPos(window, 1024/2, 768/2);

	            // Compute new orientation
	            horizontalAngle += mouseSpeed * float(1024/2 - xpos );
	            verticalAngle   += mouseSpeed * float( 768/2 - ypos );

	            
				
				
				// Direction : Spherical coordinates to Cartesian coordinates conversion
	            vec3 direction(    
                    cos(verticalAngle) * sin(horizontalAngle), 
		            sin(verticalAngle),
		            cos(verticalAngle) * cos(horizontalAngle)
				);
	
	            // Right vector
	            vec3 right = glm::vec3(
		            sin(horizontalAngle - 3.14f/2.0f), 
		            0,
		            cos(horizontalAngle - 3.14f/2.0f)
	            );
	
	            
				// Up vector
	            vec3 up = glm::cross( right, direction );

	            
				
				
				// Move forward				
				if (glfwGetKey( window, GLFW_KEY_W ) == GLFW_PRESS){
		            
					position += direction * deltaTime * speed;
	            
				}
	            
				// Move backward
	            if (glfwGetKey( window, GLFW_KEY_S ) == GLFW_PRESS){
		            
					position -= direction * deltaTime * speed;
	            
				}
	            
				
				// Strafe right
	            if (glfwGetKey( window, GLFW_KEY_D ) == GLFW_PRESS){
		            
					position += right * deltaTime * speed;
	            
				}
	            
				
				
				// Strafe left
	            if (glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS){
		            position -= right * deltaTime * speed;
	            }

	            float FoV = initialFoV;
	
	            
				// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	            ProjectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
	
	
	            // Camera matrix
	            ViewMatrix  = glm::lookAt(
								position,           // Camera is here
								position+direction, // and looks here : at the same position, plus "direction"
								up                  // Head is up (set to 0,-1,0 to look upside-down)
						    );

	            // For the next frame, the "last time" will be "now"
	            lastTime = currentTime;
            }
			
			
			void computeMatricesRotateAroundNot(){    // when keys not pressed, it means character will not move only camera will rotate around it
				
				// nahi hua mere se
				
			}
			
			
			void computeMatricesRotateAround(){      //  whem key pressed along with mouse movement
				
				
				// nahi hua mere se
				
			}
	};
	
}




#endif

