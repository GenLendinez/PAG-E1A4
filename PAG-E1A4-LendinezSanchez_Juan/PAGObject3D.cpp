#include "PAGObject3D.h"

/*
* Default constructor PAGObject3D
* Default and only constructor of this class, it will just give shader_choosen -1 to represent that
* there is no shader active.
*/

PAGObject3D::PAGObject3D()
{
	this->setModelMatrix(glm::mat4(1.0f));
}

/*
* Destructor PAGObject3D
*/

PAGObject3D::~PAGObject3D()
{
}



void PAGObject3D::drawPeon()
{
	/*
	* Peon de Ajedrez
	*/

	//Cuerpo estructural del peon

	glm::vec3* body = new glm::vec3[6];
	body[0] = glm::vec3(0, 1, 0);
	body[1] = glm::vec3(1, 1, 0);
	body[2] = glm::vec3(1, 1.5, 0);
	body[3] = glm::vec3(0.2, 1.5, 0);
	body[4] = glm::vec3(0.1, 2.5, 0);
	body[5] = glm::vec3(0.1, 3, 0);

	PAGRevolutionObject test(body, 6, true, false, false);
	test.Subdivide_Profile(2);
	test.Revolutionize(100);

	//Disco del peon

	glm::vec3* disc = new glm::vec3[3];
	disc[0] = glm::vec3(0, 1, 0);
	disc[1] = glm::vec3(1.5, 1.2, 0);
	disc[2] = glm::vec3(0, 1.4, 0);

	PAGRevolutionObject test2(disc, 3, true, true, false);
	test2.Subdivide_Profile(2);
	test2.Revolutionize(100);
	test2.setModelMatrix(glm::translate(test2.getModelMatrix(), glm::vec3(0, 1.4, 0)));

	//Bola de arriba del peon

	glm::vec3* ball = new glm::vec3[9];
	ball[0] = glm::vec3(0, 1, 0);
	ball[1] = glm::vec3(0.3, 1, 0);
	ball[2] = glm::vec3(0.6, 1.2, 0);
	ball[3] = glm::vec3(0.8, 1.4, 0);
	ball[4] = glm::vec3(0.8, 1.6, 0);
	ball[5] = glm::vec3(0.8, 1.8, 0);
	ball[6] = glm::vec3(0.6, 2, 0);
	ball[7] = glm::vec3(0.3, 2.2, 0);
	ball[8] = glm::vec3(0, 2.2, 0);

	PAGRevolutionObject ball_up(ball, 9, true, true, false);
	ball_up.Subdivide_Profile(5);
	ball_up.Revolutionize(100);
	ball_up.setModelMatrix(glm::translate(ball_up.getModelMatrix(), glm::vec3(0, 1.9, 0)));

	revolutione_objects.push_back(ball_up);
	revolutione_objects.push_back(test);
	revolutione_objects.push_back(test2);

	delete[] body;
	delete[] disc;
	delete[] ball;
}

void PAGObject3D::drawLegs(PAGTexture *textures)
{

	glm::vec3* leg = new glm::vec3[4];
	leg[0] = glm::vec3(0, 0.4, 0);
	leg[1] = glm::vec3(0.1, 0.4, 0);
	leg[2] = glm::vec3(0.1, 1.8, 0);
	leg[3] = glm::vec3(0, 1.8, 0);

	PAGRevolutionObject leg_(leg, 4, true, true, false);
	leg_.Revolutionize(10);
	glm::mat4 model;
	model = glm::translate(leg_.getModelMatrix(), glm::vec3(0, 2, 1.2));
	leg_.setModelMatrix(model);
	model = glm::rotate(leg_.getModelMatrix(), 45.0f, glm::vec3(1, 0, 0));
	leg_.setModelMatrix(model);
	leg_.setModel_m(model);
	leg_.addTexture(3, Texture_Color);
	leg_.setTexturesPack(textures);

	PAGRevolutionObject leg_2(leg, 4, true, true, false);
	leg_2.Revolutionize(10);

	model = glm::translate(leg_2.getModelMatrix(), glm::vec3(0, 2, 4.15));
	leg_2.setModelMatrix(model);
	model = glm::rotate(leg_2.getModelMatrix(), -45.0f, glm::vec3(1, 0, 0));
	leg_2.setModelMatrix(model);
	leg_2.setModel_m(model);
	leg_2.addTexture(3,Texture_Color);
	leg_2.setTexturesPack(textures);

	PAGRevolutionObject leg_3(leg, 4, true, true, false);
	leg_3.Revolutionize(10);

	model = glm::translate(leg_3.getModelMatrix(), glm::vec3(0, 2, -1.2));
	leg_3.setModelMatrix(model);
	model = glm::rotate(leg_3.getModelMatrix(), -45.0f, glm::vec3(1, 0, 0));
	leg_3.setModelMatrix(model);
	leg_3.setModel_m(model);
	leg_3.addTexture(3, Texture_Color);
	leg_3.setTexturesPack(textures);

	PAGRevolutionObject leg_4(leg, 4, true, true, false);
	leg_4.Revolutionize(10);

	model = glm::translate(leg_4.getModelMatrix(), glm::vec3(0, 2, -4.15));
	leg_4.setModelMatrix(model);
	model = glm::rotate(leg_4.getModelMatrix(), 45.0f, glm::vec3(1, 0, 0));
	leg_4.setModelMatrix(model);
	leg_4.setModel_m(model);
	leg_4.addTexture(3, Texture_Color);
	leg_4.setTexturesPack(textures);


	//Legs 2 

	PAGRevolutionObject leg__(leg, 4, true, true, false);
	leg__.Revolutionize(10);

	leg__.setModelMatrix(glm::translate(leg__.getModelMatrix(), glm::vec3(2.4, 2, 0.5)));
	model = glm::rotate(leg__.getModelMatrix(), 45.0f, glm::vec3(1, 0, 0));
	leg__.setModelMatrix(model);
	leg__.setModel_m(model);
	leg__.addTexture(3, Texture_Color);
	leg__.setTexturesPack(textures);

	PAGRevolutionObject leg_2_(leg, 4, true, true, false);
	leg_2_.Revolutionize(10);

	leg_2_.setModelMatrix(glm::translate(leg_2_.getModelMatrix(), glm::vec3(2.4, 2, 3.45)));
	model = glm::rotate(leg_2_.getModelMatrix(), -45.0f, glm::vec3(1, 0, 0));
	leg_2_.setModelMatrix(model);
	leg_2_.setModel_m(model);
	leg_2_.addTexture(3, Texture_Color);
	leg_2_.setTexturesPack(textures);

	PAGRevolutionObject leg_3_(leg, 4, true, true, false);
	leg_3_.Revolutionize(10);

	leg_3_.setModelMatrix(glm::translate(leg_3_.getModelMatrix(), glm::vec3(2.4, 2, -0.5)));
	model = glm::rotate(leg_3_.getModelMatrix(), -45.0f, glm::vec3(1, 0, 0));
	leg_3_.setModelMatrix(model);
	leg_3_.setModel_m(model);
	leg_3_.addTexture(3, Texture_Color);
	leg_3_.setTexturesPack(textures);

	PAGRevolutionObject leg_4_(leg, 4, true, true, false);
	leg_4_.Revolutionize(10);

	leg_4_.setModelMatrix(glm::translate(leg_4_.getModelMatrix(), glm::vec3(2.4, 2, -3.45)));
	model = glm::rotate(leg_4_.getModelMatrix(), 45.0f, glm::vec3(1, 0, 0));
	leg_4_.setModelMatrix(model);
	leg_4_.setModel_m(model);
	leg_4_.addTexture(3, Texture_Color);
	leg_4_.setTexturesPack(textures);

	revolutione_objects.push_back(leg_);
	revolutione_objects.push_back(leg_2);
	revolutione_objects.push_back(leg_3);
	revolutione_objects.push_back(leg_4);
	revolutione_objects.push_back(leg__);
	revolutione_objects.push_back(leg_2_);
	revolutione_objects.push_back(leg_3_);
	revolutione_objects.push_back(leg_4_);

	delete[] leg;
}

void PAGObject3D::drawLowerBodySpiderAndHead(PAGTexture *textures)
{
	glm::vec3* ball = new glm::vec3[5];
	ball[0] = glm::vec3(0, 1, 0);
	ball[1] = glm::vec3(1, 1, 0);
	ball[2] = glm::vec3(2, 2, 0);
	ball[3] = glm::vec3(1, 3, 0);
	ball[4] = glm::vec3(0, 3, 0);

	PAGRevolutionObject ball_up(ball, 5, true, true, false);
	ball_up.Subdivide_Profile(5);
	ball_up.addTexture(1, Texture_Color);
	ball_up.addTextureBot(3, Texture_Color);
	ball_up.addTextureTop(3, Texture_Color);
	ball_up.setTexturesPack(textures);
	ball_up.Revolutionize(100);

	glm::vec3* ball2 = new glm::vec3[4];
	ball2[0] = glm::vec3(0, 1, 0);
	ball2[1] = glm::vec3(1, 1, 0);
	ball2[2] = glm::vec3(1, 2, 0);
	ball2[3] = glm::vec3(0, 2, 0);

	PAGRevolutionObject ball_up2(ball2, 4, true, true, false);
	ball_up2.Subdivide_Profile(5);
	ball_up2.setTexturesPack(textures);
	ball_up2.addTexture(5, Texture_Color);
	ball_up2.addTextureBot(3, Texture_Color);
	ball_up2.addTextureTop(3, Texture_Color);
	ball_up2.Revolutionize(100);
	glm::mat4 model;
	model = glm::translate(ball_up2.getModelMatrix(), glm::vec3(2.4, 0.5, 0));
	ball_up2.setModelMatrix(model);
	ball_up2.setModel_m(model);
	

	glm::vec3* head = new glm::vec3[4];
	head[0] = glm::vec3(0, 0.5, 0);
	head[1] = glm::vec3(0.5, 0.5, 0);
	head[2] = glm::vec3(0.5, 1, 0);
	head[3] = glm::vec3(0, 1, 0);

	PAGRevolutionObject head_(head, 4, true, true, false);
	head_.Subdivide_Profile(3);
	head_.Revolutionize(40);

	model = glm::translate(head_.getModelMatrix(), glm::vec3(3.5, 1.3, 0));
	head_.setModelMatrix(model);
	head_.setModel_m(model);
	head_.setTexturesPack(textures);
	head_.addTexture(4, Texture_Color);
	head_.addTextureBot(3, Texture_Color);
	head_.addTextureTop(3, Texture_Color);

	revolutione_objects.push_back(ball_up2);
	revolutione_objects.push_back(ball_up);
	revolutione_objects.push_back(head_);

	delete[] ball2;
	delete[] head;
	delete[] ball;
}

/*
* prepareToDraw PAGObject3D
* This function will call "prepareToDraw" from all the object revolution in order to
* prepare data buffer, vbo, ibo, vao etc....
* @param drawing_type It will say to the function how is going to be draw the data
* (GL_POINTS,GL_TRIANGLES,GL_TRIANGLE_STRIP)
* IMPORTANT : This function must be call before "draw" or it will end in an exception
*/

void PAGObject3D::prepareToDraw(GLenum drawing_type)
{
	for (int i = 0; i < revolutione_objects.size(); i++)
		revolutione_objects.at(i).prepareToDraw(drawing_type);
}

/*
* add_revolution_object PAGObject3D
* This function will ad a new revolution object to the vector, by using PAGFileManager
* @param name_file file's name of the txt located in /Users/----/Desktop
* name_file param example : "vertex.txt" It will take vertex.txt from desktop
* @param slices number greater than 0, number of division in revolution object
*/

void PAGObject3D::add_revolution_object(std::string name_file, int slices)
{
	PAGFileManager file = PAGFileManager(name_file);
	file.loadFile();
	int size = file.get_size_points();
	glm::vec3 *aux_points = new glm::vec3[size];
	for (int i = 0; i < size; i++) {
		aux_points[i] = file.get_points_file()[i];
	}
	PAGRevolutionObject object(aux_points, file.get_size_points(), file.get_closed_y_first(), file.get_closed_y_last(), false);
	object.Subdivide_Profile(file.get_nSubdivision());
	object.Revolutionize(slices);
	revolutione_objects.push_back(object);
}

/*
* add_revolution_object PAGObject3D
* This function will ad a new revolution object to the vector, by using a copy of an object
* @param new_object PAGRevolutionObject as parameter, easy paisy
*/

void PAGObject3D::add_revolution_object(PAGRevolutionObject new_object)
{
	revolutione_objects.push_back(new_object);
}

void PAGObject3D::setShininess(GLfloat new_shin)
{
	shininess = new_shin;
}

int PAGObject3D::getSize()
{
	return revolutione_objects.size();
}

/*
* draw PAGObject3D
* This function will call the function draw from every revolution object contains in the vector
* IMPORTANT : This functions must be call after prepareToDraw
*/

void PAGObject3D::draw(PagShaderProgram *shader_used, glm::mat4 model_up, PAGCamera *camera_used, GLuint text)
{
	model_up = model_up * this->getModelMatrix();
	for (int i = 0; i < revolutione_objects.size(); i++) {
		revolutione_objects.at(i).draw(shader_used, model_up,camera_used,text);
	}
}
