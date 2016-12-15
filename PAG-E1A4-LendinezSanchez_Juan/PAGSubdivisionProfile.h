#pragma once
#include <iostream>
#include "glm\vec3.hpp"
#include "glm\vec2.hpp"

/*
* Class PAGSubdivisionProfile
* This class will subdivide a given profile generating more points in order to
* make a curve smoother
*/

class PAGSubdivisionProfile {
private:
	int points_size_original; /* Size of vector points, it will change once the profile is subdivided */
	glm::vec3 *points; /*Vector glm::vec3, this struct has three float variables : "x","y" and "z"  */
public:
	PAGSubdivisionProfile(glm::vec3 *points_new, int points_size_new);
	PAGSubdivisionProfile(PAGSubdivisionProfile const& copy);
	PAGSubdivisionProfile operator=(PAGSubdivisionProfile const& cope);
	PAGSubdivisionProfile();
	~PAGSubdivisionProfile();
	void subdivision_points(int division_number);
	int get_size_points();
	glm::vec3 *get_points();
 };
