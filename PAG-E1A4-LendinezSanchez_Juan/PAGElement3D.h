#pragma once
#include "PagShaderProgram.h"
#include "PAGCamera.h"
#include "PAGTexture.h"
/*
* Abstract class PAGElement3D 
* Link between PAGObject3D and PAGGroup3D
*/

class PAGElement3D {
private:
	glm::mat4 model_matrix;
public:

	/*
	* Virtual functions, they shall be implemented in every derivated class
	*/

	virtual void draw(PagShaderProgram *shader_used, glm::mat4 model_up, PAGCamera *camera_used, GLuint text) = 0;
	virtual void prepareToDraw(GLenum drawing_mode) {

		//This is just a test, still learning about polimorfism

		std::cout << "Executing" << std::endl;
	}

	/*
	* Get and set functions
	*/

	glm::mat4 getModelMatrix() {
		return model_matrix;
	};
	void setModelMatrix(glm::mat4 new_matrix) {
		model_matrix = new_matrix;
	};
};
