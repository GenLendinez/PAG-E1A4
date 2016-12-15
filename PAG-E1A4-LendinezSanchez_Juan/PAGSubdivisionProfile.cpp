#include "PAGSubdivisionProfile.h"

/*
* Constructor with parameters PAGSubdivisionProfile
* @param points_new vector that contains the new profile
* @param points_size_new size of points_new param
*/

PAGSubdivisionProfile::PAGSubdivisionProfile(glm::vec3 *points_new, int points_size_new)
{
	points_size_original = points_size_new;
	points = new glm::vec3[points_size_original];
	for (int i = 0; i < points_size_new; i++)
		points[i] = points_new[i];
}
/*
* Default constructor PAGSubdivisionProfile
*/

PAGSubdivisionProfile::PAGSubdivisionProfile()
{
	points_size_original = 0;
	points = nullptr;
}
PAGSubdivisionProfile::PAGSubdivisionProfile(PAGSubdivisionProfile const& copy)
{
	points_size_original = copy.points_size_original;
	points = new glm::vec3[points_size_original];
	for (int i = 0; i < points_size_original; i++)
		points[i] = copy.points[i];
}
PAGSubdivisionProfile PAGSubdivisionProfile::operator=(PAGSubdivisionProfile const & cope)
{
	return PAGSubdivisionProfile(cope.points,cope.points_size_original);
}
/*
* Destructor PAGSubdivisionProfile
* It releases the memory
*/
PAGSubdivisionProfile::~PAGSubdivisionProfile()
{
	if (points != nullptr) {
		delete[] points;
	}
}

/*
* subdivision_points PAGSubdivisionProfile
* This function divides the given profile (if there is not, it will just exit)
* it will divide as many times as the parameter "division_number"
* @param division_number integer that gives information about how many times
* the profile is going to be divided, it can be zero but not negative
*/

void PAGSubdivisionProfile::subdivision_points(int division_number)
{
	if (points_size_original == 0 || division_number<=0)
		return;
	int index_divpoints = 2;
	int points_size = (2 * points_size_original) - 1 ;
	glm::vec3 *divided_points = new glm::vec3[points_size];
	for (int div=1;div<=division_number;div++){
		divided_points[0] = points[0];
		divided_points[points_size - 1] = points[points_size_original - 1];
		divided_points[1].x = (divided_points[0].x + points[1].x) / 2;
		divided_points[1].y = (divided_points[0].y + points[1].y) / 2;
		for (int i = 1; i < points_size_original - 1; i++) {
			divided_points[index_divpoints + 1].x = (points[i].x + points[i + 1].x) / 2;
			divided_points[index_divpoints + 1].y = (points[i].y + points[i + 1].y) / 2;
			divided_points[index_divpoints].x = ((3 * points[i].x) / 4) + (points[i - 1].x / 8) + (points[i + 1].x / 8);
			divided_points[index_divpoints].y = ((3 * points[i].y) / 4) + (points[i - 1].y / 8) + (points[i + 1].y / 8);
			index_divpoints += 2;
		}
		index_divpoints = 2;
		delete[] points;
		points = divided_points;
		points_size_original = points_size;
		points_size = (2 * points_size) - 1;
		divided_points = NULL;
		divided_points = new glm::vec3[points_size];
	}
	delete[] divided_points;
}
/*
* get_size_points PAGSubdivisionProfile
* This function returns the size of the current profile
*/
int PAGSubdivisionProfile::get_size_points()
{
	return points_size_original;
}
/*
* get_points PAGSubdivisionProfile
* This function returns a pointer pointing the profile vector, if there is not
* it returns null
*/
glm::vec3 * PAGSubdivisionProfile::get_points()
{
	if (points_size_original == 0) return nullptr;
	return points;
}
