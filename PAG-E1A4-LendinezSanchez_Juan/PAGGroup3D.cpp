#include "PAGGroup3D.h"

/*
* Default constructor PAGGroup3D
* Nothing here to tell
*/

PAGGroup3D::PAGGroup3D()
{
	this->setModelMatrix(glm::mat4(1.0f));
}

PAGGroup3D::~PAGGroup3D()
{
	for (int i = 0; i < objects.size(); i++) {
		delete objects.at(i);
	}
}

/*
* add_new_object PAGGroup3D
* This function includes a pointer of an PAGElement3D object (or any of his derivated classes) into the vector
* @param new_ob pointer of PAGElement3D (this is the abstract class) or PAGGroup3D (in case that you want a group of groups) or PAGObject3D
*/

void PAGGroup3D::add_new_object(PAGElement3D *new_ob)
{
	objects.push_back(new_ob);
}

/*
* prepareToDraw PAGGroup3D
* This function delegates in every prepareToDraw function of each object we have, even if that object is another group
* @param drawing_type Tell the function how is the object draw... (GL_POINTS,GL_TRIANGLES ect...)
*/

void PAGGroup3D::prepareToDraw(GLenum drawing_type)
{
	for (int i = 0; i < objects.size(); i++)
		objects.at(i)->prepareToDraw(drawing_type);
}

/*
* draw PAGGroup3D
* This function delegates in every draw function of each object we have, even if that object is another group
*/

void PAGGroup3D::draw(PagShaderProgram *shader_used, glm::mat4 model_up, PAGCamera *camera_used, GLuint text)
{
	model_up = model_up * this->getModelMatrix();
	for (int i = 0; i < objects.size(); i++) {
		objects.at(i)->setModelMatrix(this->getModelMatrix()*objects.at(i)->getModelMatrix());
		objects.at(i)->draw(shader_used,model_up,camera_used,text);
	}
}
