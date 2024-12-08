#pragma once
#include <vector>
#include "AVLNode.h"
#include "AVLtree.h"

class CourseLoader {
public:
	CourseLoader();
	AVLtree loadCourses(std::string fName);
};