#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include "PAGRevolutionObject.h"
#include "glm\vec3.hpp"
#include "glm\vec2.hpp"

/*
* Class PAGFileManager
* This class will open and save files related with profile and it will be the one
* who has to call to PAGRevolutionObject
*/

class PAGFileManager {
private:
	std::string name_file;
	int nSubdivision, size_points;
	bool closed_y_first,closed_y_last;
	glm::vec3 *points_file;
public:
	PAGFileManager(std::string new_name_file);
	PAGFileManager();
	~PAGFileManager();
	void loadFile();
	void saveData(int slices);
	glm::vec3 *get_points_file();
	bool get_closed_y_first();
	bool get_closed_y_last();
	int get_nSubdivision();
	int get_size_points();
};
