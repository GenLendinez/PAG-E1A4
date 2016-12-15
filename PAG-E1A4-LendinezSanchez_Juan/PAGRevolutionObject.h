#pragma once
#include <iostream>
#include "PAGSubdivisionProfile.h"
#include <math.h>
#include <glew.h>
#include <glfw3.h>
#include "PAGElement3D.h"

#define Texture_Color 1
#define Texture_Shiny 2
#define Texture_BoomMaping 3
#define Texture_Shadows 4


/*
* Class PAGRevolutionObject
* This class will revolutionize a given profile, besides its also related with PAGSubdivisionProfile because it will be the one who calls
* PAGSubdivisionProfile methods.
*/


class PAGRevolutionObject: public PAGElement3D  {
private:
	//Variables para dibujar
	PAGSubdivisionProfile original_profile, subdivided_profile;
	GLuint vao_body, vao_up, vao_down, vbo_body1, vbo_body2, vbo_up1, vbo_up2, vbo_down1, vbo_down2, ibo_body, ibo_down, ibo_up;
	GLuint *index_body;
	GLenum drawing_mode;
	glm::mat4 model_m;

	//Variables para texturas
	PAGTexture *textures;
	std::vector<int> id_revolTop;
	std::vector<int> id_revolBot;
	std::vector<int> id_revol;

	//Variables para revolucionar
	int size_points, size_triangles, size_vertex, size_texture, slices;
	PAGTexture *texturesPack;
	bool closed_y_first, closed_y_last;
	glm::vec3 *vertex, *normals, *tangents;
	int *triangles, *triangles_down, *triangles_up;
	glm::vec2 *texture, *texture_up, *texture_down;
public:
	PAGRevolutionObject(glm::vec3 *points_new, int size_points, bool closed_y_first, bool closed_y_last, bool keep_original_profile);
	PAGRevolutionObject();
	PAGRevolutionObject(PAGRevolutionObject const& copy);
	~PAGRevolutionObject();


	/*
	* Revolutionize functions
	*/

	void Revolutionize(int slices);
	void Subdivide_Profile(int subdivisions);

	/*
	* Draw functions
	*/

	void setModel_m(glm::mat4 mod);
	void prepareToDraw(GLenum drawing_mode);
	void draw(PagShaderProgram *shader_used, glm::mat4 model_up, PAGCamera *camera_used, GLuint text);

	/*
	*/

	void addTexture(int pos_texture, int typeTexture);
	void addTextureTop(int pos_texture, int typeTexture);
	void addTextureBot(int pos_texture, int typeTexture);
	void setTexturesPack(PAGTexture *texturesPack);


	/*
	* Get functions
	*/

	glm::vec3 *get_vertex();
	glm::vec3 *get_normals();
	glm::vec3 *get_tangets();
	glm::vec2 *get_texture();
	glm::vec2 *get_texture_down();
	glm::vec2 *get_texture_up();
	int *get_triangles();
	int *get_triangles_down();
	int *get_triangles_up();
	int get_size_vertex();
	int get_size_triangles();
	int get_size_texture();
};
