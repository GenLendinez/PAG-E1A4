#include "PAGRevolutionObject.h"
#include "glm\gtx\rotate_vector.hpp"

/*
* Constructor with parameter PAGRevolutionObject
* @param points_new pointer pointing a vector of point3D, it will be the profile points before being subdivided
* @param size_points size of points_new
* @param closed_y_first boolean which represents if the first point is closed in the y axe
* @param closed_y_last boolean which represents if the last point is closed in the y axe
* @param keep_original_profile boolean which represents if the class should save the original profile
*/

PAGRevolutionObject::PAGRevolutionObject(glm::vec3 *points_new, int size_points, bool closed_y_first, bool closed_y_last, bool keep_original_profile) : subdivided_profile(points_new, size_points)
{
	textures = nullptr;
	keep_original_profile = false;
	if (keep_original_profile) original_profile = PAGSubdivisionProfile(points_new, size_points);
	texture_up = nullptr;
	texture_down = nullptr;
	triangles_down = nullptr;
	triangles_up = nullptr;
	this->size_points = size_points;
	this->closed_y_first = closed_y_first;
	this->closed_y_last = closed_y_last;
	glGenVertexArrays(1, &vao_body);
	glGenBuffers(1, &vbo_body1);
	glGenBuffers(1, &ibo_body);
	//glGenBuffers(1, &vbo_body2);
	if (closed_y_first) {
		glGenVertexArrays(1, &vao_down);
		glGenBuffers(1, &vbo_down1);
		glGenBuffers(1, &ibo_down);
		//glGenBuffers(1, &vbo_down2);
	}
	if (closed_y_last) {
		glGenVertexArrays(1, &vao_up);
		glGenBuffers(1, &vbo_up1);
		glGenBuffers(1, &ibo_up);
		//glGenBuffers(1, &vbo_up2);
	}
	this->setModelMatrix(glm::mat4(1.0f));
	model_m = glm::mat4(1.0f);
}
/*
* Default Constructor PAGRevolutionObject
*/
PAGRevolutionObject::PAGRevolutionObject()
{
	size_points = 0;
	this->setModelMatrix(glm::mat4(1.0f));
}
PAGRevolutionObject::PAGRevolutionObject(PAGRevolutionObject const & copy)
{
	size_points = copy.size_points;
	size_vertex = copy.size_vertex;
	size_texture = copy.size_texture;
	size_triangles = copy.size_triangles;
	vertex = new glm::vec3[size_vertex];
	tangents = new glm::vec3[size_vertex];
	texture = new glm::vec2[size_texture];
	normals = new glm::vec3[size_vertex];
	index_body = new GLuint[size_triangles];
	triangles = new int[size_triangles];
	closed_y_first = copy.closed_y_first;
	closed_y_last = copy.closed_y_last;
	slices = copy.slices;
	if (closed_y_last) {
		id_revolTop = copy.id_revolTop;
		triangles_up = new int[slices + 2];
		texture_up = new glm::vec2[slices + 2];
		for (int i = 0; i < slices + 2; i++) {
			triangles_up[i] = copy.triangles_up[i];
			texture_up[i] = copy.texture_up[i];
		}
	}
	if (closed_y_first) {
		id_revolBot = copy.id_revolBot;
		triangles_down = new int[slices + 2];
		texture_down = new glm::vec2[slices + 2];
		for (int i = 0; i < slices + 2; i++) {
			triangles_down[i] = copy.triangles_down[i];
			texture_down[i] = copy.texture_down[i];
		}
	}
	for (int i = 0; i < size_vertex; i++) {
		vertex[i] = copy.vertex[i];
		tangents[i] = copy.tangents[i];
		normals[i] = copy.normals[i];
	}
	for (int i = 0; i < size_triangles; i++) {
		triangles[i] = copy.triangles[i];
		index_body[i] = 3;
	}
	for (int i = 0; i < size_texture; i++) {
		texture[i] = copy.texture[i];
	}
	this->drawing_mode = copy.drawing_mode;
	this->vao_body = copy.vao_body;
	vao_down = copy.vao_down;
	vao_up = copy.vao_up;
	vbo_body1 = copy.vbo_body1;
	vbo_body2 = copy.vbo_body2;
	ibo_body = copy.ibo_body;
	ibo_down = copy.ibo_down;
	ibo_up = copy.ibo_up;
	vbo_down1 = copy.vbo_down1;
	vbo_down2 = copy.vbo_down2;
	vbo_up1 = copy.vbo_up1;
	vbo_up2 = copy.vbo_up2;
	subdivided_profile = PAGSubdivisionProfile(copy.subdivided_profile);
	this->setModelMatrix(copy.model_m);
	model_m = copy.model_m;
	id_revol = copy.id_revol;
	textures = copy.textures;
}
/*
* Destructor PAGRevolutionObject
* It releases all memory
*/
PAGRevolutionObject::~PAGRevolutionObject()
{
	delete[] vertex;
	delete[] tangents;
	delete[] normals;
	delete[] texture;
	delete[] triangles;
	if (closed_y_first) {
		delete[] texture_down;
		delete[] triangles_down;
	}
	if (closed_y_last) {
		delete[] texture_up;
		delete[] triangles_up;
	}
	delete[] index_body;
}

/*
* Revolutionize PAGRevolutionObject
* @param slices integer which representes numer of slices, it has to be greater than 0
* This function will revolutionize the given profile even if its not subdivided
*/

void PAGRevolutionObject::Revolutionize(int slices)
{
	this->slices = slices;
	const float nPI = 3.14159265;
	if (slices < 1)return;
	float angleIncrement = ((float)nPI * 2) / ((float)slices);
	float stexture_increment = 1.0 / ((float)(slices));
	int update_size = 0, begin = 0;
	if (closed_y_first && closed_y_last) {
		size_vertex = ((slices + 1) * (size_points - 2)) + 2;
	}
	else if (closed_y_first || closed_y_last) {
		size_vertex = ((slices + 1) * (size_points - 1)) + 1;
	}
	else {
		size_vertex = (slices + 1) * size_points;
	}
	size_texture = size_vertex;
	float module_normal, increment_distance = 0.0, total_distance = 0.0;
	glm::vec3 *points_profile = new glm::vec3[size_points];
	for (int i = 0; i < size_points; i++)
		points_profile[i] = subdivided_profile.get_points()[i];
	vertex = new glm::vec3[size_vertex];
	tangents = new glm::vec3[size_vertex];


	if (closed_y_first) size_texture--;
	if (closed_y_last) size_texture--;
	texture = new glm::vec2[size_texture];


	if (closed_y_first) begin = 1;
	if (closed_y_last) size_points--;
	for (int i = begin; i < size_points - 1; i++)
		total_distance += sqrt(pow(abs(points_profile[i + 1].x - points_profile[i].x), 2) + pow(abs(points_profile[i + 1].y - points_profile[i].y), 2));
	if (closed_y_last) size_points++;
	begin = 0;

	if (closed_y_first) {
		texture_down = new glm::vec2[slices + 2];
		for (int i = 1; i <= slices + 1; i++) {
			texture_down[i].s = (cos(angleIncrement * float(i)) / 2) + 0.5;
			texture_down[i].t = (sin(angleIncrement * float(i)) / 2) + 0.5;
		}
		texture_down[0].s = 0.5;
		texture_down[0].t = 0.5;
		begin = 1;
		vertex[0] = glm::vec3(0, points_profile[0].y, 0);
		tangents[0] = glm::vec3(1, 0, 0);
		update_size++;
	}
	if (closed_y_last) size_points--;
	for (int i = begin; i < size_points; i++) {
		for (int j = 0; j <= slices; j++) {

			//Calculo de vertices revolucionados

			vertex[update_size].x = points_profile[i].x * cos(angleIncrement * j);
			vertex[update_size].y = points_profile[i].y;
			vertex[update_size].z = points_profile[i].x * -(sin(angleIncrement * j));

			//Calculo de tangentes revolucionadas

			tangents[update_size].x = -sin(angleIncrement * j);
			tangents[update_size].y = 0;
			tangents[update_size].z = cos(angleIncrement * j);

			update_size++;
		}
	}
	int update_size_texture = 0;
	increment_distance = 0.0;
	for (int i = begin; i < size_points; i++) {
		for (int j = 0; j <= slices; j++) {
			texture[update_size_texture].s = stexture_increment * j;
			if (i == begin) {
				texture[update_size_texture].t = 0;
			}
			else if (i == size_points - 1) {
				texture[update_size_texture].t = 1;
			}
			else {
				texture[update_size_texture].t = increment_distance / total_distance;
			}
			update_size_texture++;
		}
		increment_distance += sqrt(pow((points_profile[i + 1].x - points_profile[i].x), 2) + pow((points_profile[i + 1].y - points_profile[i].y), 2));
	}


	if (closed_y_last) {
		size_points++;
		texture_up = new glm::vec2[slices + 2];
		for (int i = 1; i <= slices + 1; i++) {
			texture_up[i].s = (cos(angleIncrement * float(i)) / 2) + 0.5;
			texture_up[i].t = (sin(angleIncrement * float(i)) / 2) + 0.5;
		}
		texture_up[0].s = 0.5;
		texture_up[0].t = 0.5;
		tangents[update_size] = glm::vec3(1, 0, 0);
		vertex[update_size] = glm::vec3(0, points_profile[size_points - 1].y, 0);
	}

	//Calculo de indices de triangulos

	update_size = 0;
	if (!closed_y_first && !closed_y_last) {
		size_triangles = ((size_points) * 2 * (slices)) + (slices);
		triangles = new int[size_triangles];
		for (int i = 0; i < slices; i++) {
			for (int j = 0; j < size_points; j++) {
				triangles[update_size] = (i + (j*(slices + 1)));
				triangles[update_size + 1] = ((i + 1) + (j*(slices + 1)));
				update_size += 2;
			}
			triangles[update_size] = -1;
			update_size++;
		}
	}
	else if (closed_y_first && closed_y_last) {
		triangles_down = new int[slices + 2];
		triangles_down[update_size] = 0;
		update_size++;
		for (int i = (slices + 1); i >= 1; i--) {
			triangles_down[update_size] = i;
			update_size++;
		}
		update_size = 0;
		triangles_up = new int[slices + 2];
		for (int i = 0; i < (slices + 2); i++) {
			triangles_up[update_size] = i;
			update_size++;
		}

		update_size = 0;
		size_triangles = ((size_points - 2) * 2 * (slices)) + (slices);
		triangles = new int[size_triangles];
		for (int i = 0; i < slices; i++) {
			for (int j = 0; j < size_points - 2; j++) {
				triangles[update_size] = (i + (j*(slices + 1))) + 1;
				triangles[update_size + 1] = ((i + 1) + (j*(slices + 1))) + 1;
				update_size += 2;
			}
			triangles[update_size] = -1;
			update_size++;
		}
	}
	else if (closed_y_first) {
		triangles_down = new int[slices + 2];
		triangles_down[update_size] = 0;
		update_size++;
		for (int i = (slices + 1); i >= 1; i--) {
			triangles_down[update_size] = i;
			update_size++;
		}
		update_size = 0;
		size_triangles = ((size_points - 1) * 2 * (slices)) + (slices);
		triangles = new int[size_triangles];
		for (int i = 0; i < slices; i++) {
			for (int j = 0; j < size_points - 1; j++) {
				triangles[update_size] = (i + (j*(slices + 1))) + 1;
				triangles[update_size + 1] = ((i + 1) + (j*(slices + 1))) + 1;
				update_size += 2;
			}
			triangles[update_size] = -1;
			update_size++;
		}
	}
	else if (closed_y_last) {
		update_size = 1;
		triangles_up = new int[slices + 2];
		for (int i = 0; i < (slices + 2); i++) {
			triangles_up[update_size] = i;
			update_size++;
		}
		update_size = 0;
		size_triangles = ((size_points - 1) * 2 * (slices)) + (slices);
		triangles = new int[size_triangles];
		for (int i = 0; i < slices; i++) {
			for (int j = 0; j < size_points - 1; j++) {
				triangles[update_size] = (i + (j*(slices + 1)));
				triangles[update_size + 1] = ((i + 1) + (j*(slices + 1)));
				update_size += 2;
			}
			triangles[update_size] = -1;
			update_size++;
		}
	}

	//Calculo de normales revolucionadas

	update_size = 0, begin = 0;
	normals = new glm::vec3[size_vertex];

	if (closed_y_first) {
		begin = 1;
		normals[0].x = 0;
		normals[0].y = -1;
		normals[0].z = 0;
		update_size = 1;
	}
	int begin2 = 0;
	if (closed_y_last) {
		begin2 = 1;
	}
	glm::vec3 *normal_profile = new glm::vec3[size_points];
	glm::vec3 before, after;

	//Normales calculadas para el perfil

	float y_a, mod_;
	for (int i = begin; i < size_points - begin2; i++) {
		normal_profile[i].z = 0;
		if (i == 0) {
			normal_profile[i] = points_profile[i + 1] - points_profile[i];
			y_a = normal_profile[i].y;
			normal_profile[i].y = -normal_profile[i].x;
			normal_profile[i].x = y_a;
			mod_ = sqrt(pow(normal_profile[i].x, 2) + pow(normal_profile[i].y, 2));
			normal_profile[i] /= mod_;
		}
		else if (i == size_points - 1) {
			normal_profile[i] = points_profile[i] - points_profile[i - 1];
			y_a = normal_profile[i].y;
			normal_profile[i].y = -normal_profile[i].x;
			normal_profile[i].x = y_a;
			mod_ = sqrt(pow(normal_profile[i].x, 2) + pow(normal_profile[i].y, 2));
			normal_profile[i] /= mod_;
		}
		else {
			before = points_profile[i] - points_profile[i - 1];
			after = points_profile[i + 1] - points_profile[i];
			y_a = before.y;
			mod_ = sqrt(pow(before.x, 2) + pow(before.y, 2));
			before.y = -before.x;
			before.x = y_a;
			before /= mod_;
			y_a = after.y;
			after.y = -after.x;
			after.x = y_a;
			mod_ = sqrt(pow(after.x, 2) + pow(after.y, 2));
			after /= mod_;
			normal_profile[i] = (after + before) / 2.0f;
		}
	}

	//Ahora calculamos las normales en todos los slices
	for (int i = begin; i < size_points - begin2; i++) {
		for (int j = 0; j <= slices; j++) {
			normals[update_size] = glm::rotateY(normal_profile[i], angleIncrement * j);
			update_size++;
		}
	}

	if (closed_y_last) {
		normals[update_size].x = 0;
		normals[update_size].y = 1;
		normals[update_size].z = 0;
	}
	delete[] points_profile;
	delete[] normal_profile;
}

/*
* Subdivide_Profile PAGRevolutionObject
* This function will call the function given in the PAGSubdividedProfile object that its store in this class
*/

void PAGRevolutionObject::Subdivide_Profile(int subdivisions)
{
	subdivided_profile.subdivision_points(subdivisions);
	size_points = subdivided_profile.get_size_points();
}

/*
* prepareToDraw PAGRevolutionObject
* This function will prepare all the buffer data with indexes, vertex, normals, tangents ect.. in order to
* draw, it will also bind the vao,ibo,vbo created in the constructor to that data.
* @param drawing_mode This parameter will tell the function how to draw the data (GL_POINTS,GL_TRIANGLES..ect..)
*/

void PAGRevolutionObject::setModel_m(glm::mat4 mod)
{
	model_m = mod;
}

void PAGRevolutionObject::prepareToDraw(GLenum drawing_mode)
{
	this->drawing_mode = drawing_mode;
	switch (drawing_mode) {
	case GL_POINTS:
		index_body = new GLuint[size_vertex];
		for (int i = 0; i < size_vertex; i++) {
			index_body[i] = i;
		}
		glBindVertexArray(vao_body);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_body1);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, sizeof(glm::vec3) / sizeof(GLfloat),
			GL_FLOAT, GL_FALSE, sizeof(glm::vec3),
			((GLubyte *)NULL + (0)));
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*size_vertex, vertex, GL_STATIC_DRAW);

		glGenBuffers(1, &ibo_body);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_body);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*size_vertex, index_body, GL_STATIC_DRAW);
		break;
	case GL_TRIANGLE_STRIP:

		//Preparing object body

		struct normals_positions {
			glm::vec3 position;
			glm::vec3 normal;
			glm::vec2 texture;
		};
		int i_t = 1;
		normals_positions *geometry = new normals_positions[size_vertex];

		for (int i = 0; i < size_vertex; i++) {
			geometry[i].position = vertex[i];
			geometry[i].normal = normals[i];
			if (closed_y_first) {
				geometry[i + 1].texture = texture[i];
			}
		}

		index_body = new GLuint[size_triangles];
		for (int i = 0; i < size_triangles; i++) {
			if (triangles[i] == -1) {
				index_body[i] = 0xFFFF;
			}
			else {
				index_body[i] = triangles[i];
			}
		}
		glBindVertexArray(vao_body);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_body1);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, sizeof(glm::vec3) / sizeof(GLfloat),
			GL_FLOAT, GL_FALSE, sizeof(normals_positions),
			((GLubyte *)NULL + (0)));

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, sizeof(glm::vec3) / sizeof(GLfloat),
			GL_FLOAT, GL_FALSE, sizeof(normals_positions),
			((GLubyte *)NULL + (sizeof(glm::vec3))));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, sizeof(glm::vec2) / sizeof(GLfloat),
			GL_FLOAT, GL_FALSE, sizeof(normals_positions),
			((GLubyte *)NULL + ((sizeof(glm::vec3) * 2))));

		glBufferData(GL_ARRAY_BUFFER, sizeof(normals_positions)*size_vertex, geometry, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_body);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*(size_triangles), index_body, GL_STATIC_DRAW);

		delete[] geometry;

		//Prepare top down

		if (closed_y_first) {

			normals_positions *geometry_flagdown = new normals_positions[slices + 2];
			for (int i = 0; i < slices + 2; i++) {
				geometry_flagdown[i].position = vertex[i];
				geometry_flagdown[i].normal = normals[i];
				geometry_flagdown[i].texture = texture_down[i];
			}

			glBindVertexArray(vao_down);
			glBindBuffer(GL_ARRAY_BUFFER, vbo_down1);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, sizeof(glm::vec3) / sizeof(GLfloat),
				GL_FLOAT, GL_FALSE, sizeof(normals_positions),
				((GLubyte *)NULL + (0)));

			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, sizeof(glm::vec3) / sizeof(GLfloat),
				GL_FLOAT, GL_FALSE, sizeof(normals_positions),
				((GLubyte *)NULL + (sizeof(glm::vec3))));

			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, sizeof(glm::vec2) / sizeof(GLfloat),
				GL_FLOAT, GL_FALSE, sizeof(normals_positions),
				((GLubyte *)NULL + ((sizeof(glm::vec3) * 2))));

			glBufferData(GL_ARRAY_BUFFER, sizeof(normals_positions)*(slices + 2), geometry_flagdown, GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_down);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*(slices + 2), triangles_down, GL_STATIC_DRAW);
			delete[] geometry_flagdown;
		}

		//Prepare top up

		if (closed_y_last) {
			int update = 1;
			normals_positions *geometry_flagup = new normals_positions[slices + 2];
			geometry_flagup[0].position = vertex[size_vertex - 1];
			geometry_flagup[0].normal = normals[size_vertex - 1];
			geometry_flagup[0].texture = texture_up[0];
			for (int i = (size_vertex - (slices + 2)); i < (size_vertex - 1); i++) {
				geometry_flagup[i - (size_vertex - (slices + 3))].position = vertex[i];
				geometry_flagup[i - (size_vertex - (slices + 3))].normal = normals[i];
				geometry_flagup[i - (size_vertex - (slices + 3))].texture = texture_up[i - (size_vertex - (slices + 3))];
			}

			glBindVertexArray(vao_up);
			glBindBuffer(GL_ARRAY_BUFFER, vbo_up1);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, sizeof(glm::vec3) / sizeof(GLfloat),
				GL_FLOAT, GL_FALSE, sizeof(normals_positions),
				((GLubyte *)NULL + (0)));

			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, sizeof(glm::vec3) / sizeof(GLfloat),
				GL_FLOAT, GL_FALSE, sizeof(normals_positions),
				((GLubyte *)NULL + (sizeof(glm::vec3))));

			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, sizeof(glm::vec2) / sizeof(GLfloat),
				GL_FLOAT, GL_FALSE, sizeof(normals_positions),
				((GLubyte *)NULL + ((sizeof(glm::vec3) * 2))));

			glBufferData(GL_ARRAY_BUFFER, sizeof(normals_positions)*(slices + 2), geometry_flagup, GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_up);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*(slices + 2), triangles_up, GL_STATIC_DRAW);
			delete[] geometry_flagup;
		}

		break;
	}
}

/*
* draw PAGRevolutionObject
* This function will draw the elements previously prepared in "prepareToDraw" with a given vao and ibo
*/

void PAGRevolutionObject::draw(PagShaderProgram *shader_used, glm::mat4 model_up, PAGCamera *camera_used, GLuint text)
{
	shader_used->setUniform("mvpMatrix", camera_used->getProyectionMatrix()*camera_used->getVisionMatrix()*this->getModelMatrix()*model_up);
	shader_used->setUniform("mModelView", camera_used->getVisionMatrix()*this->getModelMatrix()*model_up);
	if (id_revol.size() != 0 && textures != nullptr) {
		for (int i = 0; i < id_revol.size(); i++) {
			shader_used->setUniform("TexSamplerColor", i);
			textures->applyTexture(GL_TEXTURE0 + i, id_revol.at(i));
		}
	}

	if (vao_body == -1) {
		std::cout << "Cant draw, VAO is -1" << std::endl;
		return;
	}

	switch (drawing_mode) {
	case GL_POINTS:
		glBindVertexArray(vao_body);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_body);
		glDrawElements(GL_POINTS, (sizeof(GLuint)*size_vertex) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);
		break;
	case GL_TRIANGLE_STRIP:
		glEnable(GL_PRIMITIVE_RESTART);
		glPrimitiveRestartIndex(0xFFFF);
		glBindVertexArray(vao_body);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_body);
		glDrawElements(GL_TRIANGLE_STRIP, (sizeof(GLuint)*size_triangles) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);
		if (closed_y_first) {
			if (id_revolBot.size() != 0 && textures != nullptr) {
				for (int i = 0; i < id_revolBot.size(); i++) {
					shader_used->setUniform("TexSamplerColor", i);
					textures->applyTexture(GL_TEXTURE0 + i, id_revolBot.at(i));
				}
			}
			glBindVertexArray(vao_down);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_down);
			glDrawElements(GL_TRIANGLE_FAN, (sizeof(int)*(slices + 2)) / sizeof(int), GL_UNSIGNED_INT, NULL);
		}
		if (closed_y_last) {
			if (id_revolTop.size() != 0 && textures != nullptr) {
				for (int i = 0; i < id_revolTop.size(); i++) {
					shader_used->setUniform("TexSamplerColor", i);
					textures->applyTexture(GL_TEXTURE0 + i, id_revolTop.at(i));
				}
			}
			glBindVertexArray(vao_up);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_up);
			glDrawElements(GL_TRIANGLE_FAN, (sizeof(int)*(slices + 2)) / sizeof(int), GL_UNSIGNED_INT, NULL);
		}
		break;
	}
}

void PAGRevolutionObject::addTexture(int pos_texture, int type_Texture)
{
	std::vector<int>::iterator i;
	i = id_revol.begin();
	switch (type_Texture) {
	case Texture_Color:
		id_revol.insert(i, pos_texture);
		break;
	case Texture_Shiny:
		id_revol.insert(i + 1, pos_texture);
		break;
	case Texture_BoomMaping:
		id_revol.insert(i + 2, pos_texture);
		break;
	case Texture_Shadows:
		id_revol.insert(i + 3, pos_texture);
		break;
	}
}

void PAGRevolutionObject::addTextureTop(int pos_texture, int typeTexture)
{
	std::vector<int>::iterator i;
	i = id_revolTop.begin();

	switch (typeTexture) {
	case Texture_Color:
		id_revolTop.insert(i, pos_texture);
		break;
	case Texture_Shiny:
		id_revolTop.insert(i + 1, pos_texture);
		break;
	case Texture_BoomMaping:
		id_revolTop.insert(i + 2, pos_texture);
		break;
	case Texture_Shadows:
		id_revolTop.insert(i + 3, pos_texture);
		break;
	}
}

void PAGRevolutionObject::addTextureBot(int pos_texture, int typeTexture)
{
	std::vector<int>::iterator i;
	i = id_revolBot.begin();
	switch (typeTexture) {
	case Texture_Color:
		id_revolBot.insert(i, pos_texture);
		break;
	case Texture_Shiny:
		id_revolBot.insert(i + 1, pos_texture);
		break;
	case Texture_BoomMaping:
		id_revolBot.insert(i + 2, pos_texture);
		break;
	case Texture_Shadows:
		id_revolBot.insert(i + 3, pos_texture);
		break;
	}
}

void PAGRevolutionObject::setTexturesPack(PAGTexture * texturesPack)
{
	textures = texturesPack;
}

//Several gets to take all the data

glm::vec3 * PAGRevolutionObject::get_vertex()
{
	return vertex;
}

glm::vec3 * PAGRevolutionObject::get_normals()
{
	return normals;
}

glm::vec3 * PAGRevolutionObject::get_tangets()
{
	return tangents;
}

glm::vec2 * PAGRevolutionObject::get_texture()
{
	return texture;
}

glm::vec2 * PAGRevolutionObject::get_texture_down()
{
	return texture_down;
}

glm::vec2 * PAGRevolutionObject::get_texture_up()
{
	return texture_up;
}

int * PAGRevolutionObject::get_triangles()
{
	return triangles;
}

int * PAGRevolutionObject::get_triangles_down()
{
	return triangles_down;
}

int * PAGRevolutionObject::get_triangles_up()
{
	return triangles_up;
}

int PAGRevolutionObject::get_size_vertex()
{
	return size_vertex;
}

int PAGRevolutionObject::get_size_triangles()
{
	return size_triangles;
}

int PAGRevolutionObject::get_size_texture()
{
	return size_texture;
}
