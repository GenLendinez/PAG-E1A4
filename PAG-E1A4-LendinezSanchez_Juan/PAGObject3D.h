#pragma once
#include "PAGElement3D.h"
#include "PAGFileManager.h"

/*
* Class PAGObject3D
* This class represents an object with severals revolution objects and severals shaders that can be use.
* There will be just one shader active at time.
*/

class PAGObject3D: public PAGElement3D {
private:
	std::vector<PAGRevolutionObject> revolutione_objects;
	GLfloat shininess;
public:
	PAGObject3D();
	~PAGObject3D();

	/*
	* Revolution objects functions
	*/

	void add_revolution_object(std::string name_file, int slices);
	void add_revolution_object(PAGRevolutionObject new_object);

	void setShininess(GLfloat new_shin);
	int getSize();

	/*
	* Draw Functions
	*/

	void drawPeon();
	void drawLegs(PAGTexture *textures);
	void drawLowerBodySpiderAndHead(PAGTexture *textures);
	void prepareToDraw(GLenum drawing_type);
	void draw(PagShaderProgram *shader_used, glm::mat4 model_up, PAGCamera *camera_used, GLuint text);
};
