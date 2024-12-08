#include "CourseLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "CSVparser.hpp"

// Defines the primary method used to read in an external file and populate a vector with individual Course objects
// CSVparser is required for proper functionality
AVLtree CourseLoader::loadCourses(std::string fname) {
    AVLtree avl;

    try {
        std::vector<std::vector<std::string>> content;
        std::vector<std::string> row;
        std::string line, word;

        std::fstream file(fname, std::ios::in);
        if (file.is_open()) 
        {
            while (getline(file, line)) 
            {
                row.clear();

                std::stringstream str(line); 

                while (getline(str, word, ',')) {
                    row.push_back(word);
                }
                content.push_back(row); 
            }
        }
        else 
            std::cout << std::endl << "Could not open the file" << std::endl << std::endl;

        for (int i = 0; i < content.size(); i++)
        {
            avl.insert(content[i][0], content[i][1]);
            AVLNode* currentCourse = avl.search(content[i][0]);
            for (int j = 0; j < content[i].size(); j++)
            {
                if (j > 1 && j < content[i].size()) {
                    if (content[i][j] != "") {
                        currentCourse->addPrerequisite(content[i][j]);
                    }
                }
            }
        }

    }
    catch (csv::Error& e) { // catch any errors resulting from opening or reading the file
        std::cerr << e.what() << std::endl;
    }
    std::cout << std::endl << "Courses successfully loaded in." << std::endl << std::endl;
    return avl; 
}

CourseLoader::CourseLoader() {
}
