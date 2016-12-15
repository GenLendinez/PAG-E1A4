#include "PAGFileManager.h"

/*
* Constructor with parameter PAGFileManager
* @param new_name_file Just the name if the file is inside the project, otherwise it has to be the absolute file path
*/

PAGFileManager::PAGFileManager(std::string new_name_file)
{
	name_file = new_name_file;
	closed_y_first = false;
	closed_y_last = false;
}

/*
* Default constructor PAGFileManager
* name_file will be "null" and size_points will be zero
*/

PAGFileManager::PAGFileManager()
{
	name_file = "null";
	size_points = 0;
}
/*
* Destructor PAGFileManager
* It releases resources
*/
PAGFileManager::~PAGFileManager()
{
	delete[] points_file;
}
/*
* loadFile PAGFile Manager
* It will load the file with the name given in the constructor with parameters, it will save the data in points_file which is a 
* vector of structs point3D
* Conditions: Number of subdivisions has to be 0 or greater
*			  Number of points has to be 2 or greater
*			  It allows points closed in the y axe in the begin and in the end but not in the middle
*			  Points has to be equal or greater than zero, otherwise they will be dismissed
*			  It takes the file from your desktop by passing just the file's name but not the absolute path
*/
void PAGFileManager::loadFile()
{
	char *dir = getenv("userprofile");
	std::string path = dir;
	path += "/Desktop/";
	path += name_file;
	std::ifstream myfile(path, std::ios::in);
	myfile >> size_points;
	myfile >> nSubdivision;
	points_file = new glm::vec3[size_points];
	if (!myfile.good()) {
		return;
	}
	float x_aux, y_aux;
	for (int i = 0; i < size_points; i++) {
		myfile >> x_aux;
		myfile >> y_aux;
		if (i == 0 && x_aux == 0) closed_y_first = true;
		if (i == (size_points - 1) && x_aux == 0) closed_y_last = true;
		if (y_aux >= 0 && x_aux >= 0) {
			points_file[i].x = x_aux;
			points_file[i].y = y_aux;
			points_file[i].z = 0.0;
		}
		else {
			size_points--;
		}
	}
}

/*
* saveData PAGFileManager
* Save in several files (txt) all the data obtained from revolutionazing the given profile
* Data will be saved in desktop (just in windows, i do not guarantee same results in linux or another SO)
* @param slices integer which represents how many slices is going have your object (around y axe)
*/

void PAGFileManager::saveData(int slices)
{
	//First the object is revolutionazied
	if (size_points < 2) return;
	PAGRevolutionObject object_revolution(points_file, size_points, closed_y_first, closed_y_last, false);
	object_revolution.Subdivide_Profile(nSubdivision);
	object_revolution.Revolutionize(slices);

	//Then its taken vertex, normals and tangets and put them in the same file

	glm::vec3 *vertex, *normals, *tangents;
	vertex = object_revolution.get_vertex();
	normals = object_revolution.get_normals();
	tangents = object_revolution.get_tangets();
	int size_vertex = object_revolution.get_size_vertex();
	int size_texture = object_revolution.get_size_texture();
	char *dir = getenv("userprofile");
	std::string path = dir;
	path += "/Desktop/Geometry-LendinezSanchez_Juan-out.txt";
	std::ofstream file_save(path);
	file_save << size_vertex << std::endl;
	for (int i = 0; i < size_vertex; i++) {
		file_save << vertex[i].x << " " << vertex[i].y << " " << vertex[i].z << " + " <<
			normals[i].x << " " << normals[i].y << " " << normals[i].z << " + " <<
			tangents[i].x << " " << tangents[i].y << " " << tangents[i].z << std::endl;
	}

	//Now its taken texture coordenates and in case it exist tape down or up its created a file for each one

	glm::vec2 *texture, *texture_up, *texture_down;
	texture = object_revolution.get_texture();
	texture_up = object_revolution.get_texture_up();
	texture_down = object_revolution.get_texture_down();
	if (texture_up != nullptr) {
		path = dir;
		path+= "/Desktop/Texture_UP-LendinezSanchez_Juan-out.txt";
		std::ofstream file_save_tup(path);
		file_save_tup << slices + 2 << std::endl;
		for (int i = 0; i < (slices + 2); i++)
			file_save_tup << texture_up[i].s << " " << texture_up[i].t << std::endl;
	}
	if (texture_down != nullptr) {
		path = dir;
		path += "/Desktop/Texture_DOWN-LendinezSanchez_Juan-out.txt";
		std::ofstream file_save_tdo(path);
		file_save_tdo << (slices + 2) << std::endl;
		for (int i = 0; i < (slices + 2); i++)
			file_save_tdo << texture_down[i].s << " " << texture_down[i].t << std::endl;
	}

	path = dir;
	path += "/Desktop/Texture-LendinezSanchez_Juan-out.txt";
	std::ofstream file_save_t(path);
	file_save_t << size_texture << std::endl;
	for (int i = 0; i < size_texture; i++) {
		file_save_t << texture[i].s << " " << texture[i].t << std::endl;
	}

	//Finally its taken triangles from the object and put them in a file
	//same procedure as before if it exist tape its created another file

	int *triangles, *triangles_up, *triangles_down;
	triangles_up = object_revolution.get_triangles_up();
	triangles_down = object_revolution.get_triangles_down();
	if (triangles_up != nullptr) {
		path = dir;
		path += "/Desktop/Index_Up-LendinezSanchez_Juan-out.txt";
		std::ofstream file_save_iup(path);
		file_save_iup << (slices + 2) << std::endl;
		for (int i = 0; i < (slices + 2); i++)
			file_save_iup << triangles_up[i] << std::endl;
	}
	if (triangles_down != nullptr) {
		path = dir;
		path += "/Desktop/Index_Down-LendinezSanchez_Juan-out.txt";
		std::ofstream file_save_ido(path);
		file_save_ido << (slices + 2) << std::endl;
		for (int i = 0; i < (slices + 2); i++)
			file_save_ido << triangles_down[i] << std::endl;
	}
	int size_triangles;
	triangles = object_revolution.get_triangles();
	size_triangles = object_revolution.get_size_triangles();
	path = dir;
	path += "/Desktop/Index-LendinezSanchez_Juan-out.txt";
	std::ofstream file_save_i(path);
	file_save_i << size_triangles << std::endl;
	for (int i = 0; i < size_triangles; i++) {
		file_save_i << triangles[i] << std::endl;
	}

}

/*
* get_points_file PAGFileManager
* @return a pointer pointing a vector of point3D
*/

glm::vec3 * PAGFileManager::get_points_file()
{
	if (size_points == 0)
		return nullptr;
	return points_file;
}
bool PAGFileManager::get_closed_y_first()
{
	return closed_y_first;
}
bool PAGFileManager::get_closed_y_last()
{
	return closed_y_last;
}
int PAGFileManager::get_nSubdivision()
{
	return nSubdivision;
}
/*
* get_size_points PAGFileManager
* @return size_points integer which is the size of points_file
*/
int PAGFileManager::get_size_points()
{
	return size_points;
}
