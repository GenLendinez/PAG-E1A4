#pragma once
#include <vector>
#include <iostream>
#include "PAGElement3D.h"

/*
* Class PAGGroup3D
* This class will contain several objects as a group with all their functions, or several groups of objects or groups of groups of groups ect. xd
*/

class PAGGroup3D: public PAGElement3D {
private:
	std::vector<PAGElement3D*> objects;
public:
	PAGGroup3D();
	~PAGGroup3D();
	void add_new_object(PAGElement3D *new_ob);
	void prepareToDraw(GLenum drawing_type);
	void draw(PagShaderProgram *shader_used, glm::mat4 model_up, PAGCamera *camera_used, GLuint text);
};
