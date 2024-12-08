//============================================================================
// Name           : CS-499 Milestone 2
// Author         : Ryan Hubbuck
// Created On     : 06/14/2023
// Last Modified  : 11/23/2024
// Description    : The purpose of this application is to allow users to 
//                  load an external file of courses and prerequisites. The
//                  courses are then sorted and users can search for a 
//                  specific course, add courses, or delete courses. For 
//                  proper functionality, the following files are required:
//                  - AVLtree.h
//                  - AVLNode.h
//                  - CourseLoader.h
//                  - functions.h
//============================================================================

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "CSVparser.hpp"
#include "functions.h"
#include "CourseLoader.h"
#include "AVLNode.h"
#include "AVLtree.h"

using namespace std;
typedef AVLNode* NodePtr;

int main(int argc, char* argv[]) {
    CourseLoader loader;
	AVLtree avl;
    string fname, userFile, cName, cNumber, pNumber, userCourse, courseToManage, courseToDelete;
    int menuChoice = 0;
    int subMenuChoice = 0;
    bool validCourse;
    bool validNewCourse = false;
    bool validPre = false;
    bool validNewPre = true;
    bool validDelete = false;
    bool preToDelete = false;


    while (menuChoice != 9) { 
        validCourse = false;
        vector<vector<string>> content;
        vector<string> row; 

        displayMenu();

        while (!(cin >> menuChoice)) { // validate user inputs type int
            std::cout << std::endl << "Error - enter a valid menu choice: ";
            cin.clear();
            cin.ignore(123, '\n');
        }

        switch (menuChoice) {

        case 1: // load in courses
            std::cout << std::endl << "Please enter the exact file name you wish to load. (case sensitive / include .{file extension})" << endl;
            cin >> fname;
			avl = loader.loadCourses(fname);
            break;

        case 2: // print courses
			std::cout << std::endl << "Sample Course Schedule:" << std::endl;
			std::cout << std::string(28, '_') << std::endl;
			avl.inorder();
			std::cout << std::endl;
            break;

        case 3: // print specific course details
            std::cout << std::endl << "What course do you want to know about? " << std::endl;
            cin >> userCourse; 
            std::transform(userCourse.begin(), userCourse.end(), userCourse.begin(), ::toupper);
			std::cout << std::endl << "Course: ";
			avl.printNode(userCourse);
            break;

        case 4: { // delte a course by key/number
            std::cout << std::endl << "Enter a course number you want to delete: " << std::endl;
            cin >> userCourse;
            std::transform(userCourse.begin(), userCourse.end(), userCourse.begin(), ::toupper);
			AVLNode* courseToDelete = avl.search(userCourse);

			if (courseToDelete == nullptr) {
				std::cout << std::endl << "That course was not found." << std::endl << std::endl;
			}
			else {
				avl.deleteNode(userCourse);
				std::cout << std::endl << userCourse << " was deleted." << std::endl << std::endl;
			}
			courseToDelete = nullptr;
            break;
		}
        case 5: // create a new course with number and title
            std::cout << std::endl << "Enter the new course's number (i.e. MATH101). " << std::endl;
            cin >> cNumber; 
            std::transform(cNumber.begin(), cNumber.end(), cNumber.begin(), ::toupper);
            std::cout << std::endl << "Enter the new course's title (i.e. Reverse Engineering). " << std::endl;
            cin.ignore();
            getline(cin, cName);
           
            if ((0 < cNumber.length() && cNumber.length() < 10) && (0 < cName.length() && cName.length() < 40)) {
                validNewCourse = true;
            }
            else {
                std::cout << "You have entered invalid information. Please try again. " << std::endl;
            }

            if (validNewCourse) {
				avl.insert(cNumber, cName);
				std::cout << cNumber << " has been added." << std::endl;
            }
            break;

        case 6: { // list, add to, or delete a course's prerequisites
            std::cout << std::endl << "Enter a course number to manage it's prerequisites. " << std::endl;
            cin >> userCourse;
			std::cout << std::endl;
            std::transform(userCourse.begin(), userCourse.end(), userCourse.begin(), ::toupper);
			AVLNode* courseToUpdate = avl.search(userCourse);
			if (courseToUpdate == nullptr) {
				std::cout << "That course was not found." << std::endl;
			}
			else {
				while (subMenuChoice != 3) {
					displaySubMenu();
					while (!(cin >> subMenuChoice)) {
						std::cout << "Error - enter a valid menu choice: ";
						cin.clear();
						cin.ignore(123, '\n');
					}

					switch (subMenuChoice) {
					case 1:
						std::cout << "Enter the prerequisite course number. " << std::endl;
						cin >> pNumber;
						std::cout << std::endl;
						std::transform(pNumber.begin(), pNumber.end(), pNumber.begin(), ::toupper);
						for (int j = 0; j < courseToUpdate->prerequisitesSize(); ++j) {
							if (courseToUpdate->getPrerequisite(j) == pNumber) {
								validNewPre = false;
							}
						}
						if ((0 < pNumber.length() && pNumber.length() < 10) && validNewPre) {
							courseToUpdate->addPrerequisite(pNumber);
						}
						break;
					case 2:
						if (courseToUpdate->prerequisitesSize() == 0) {
							std::cout << std::endl << "This course has no prerequisites. " << std::endl;
							break;
						}
						else {
							std::cout << "Prerequisites: ";
							for (int j = 0; j < courseToUpdate->prerequisitesSize(); ++j) {
								std::cout << courseToUpdate->getPrerequisite(j) << " ";
							}
						}
						std::cout << std::endl << "Enter a prerequisite to delete. " << std::endl;
						cin >> pNumber;
						std::transform(pNumber.begin(), pNumber.end(), pNumber.begin(), ::toupper);
						for (int l = 0; l < courseToUpdate->prerequisitesSize(); ++l) {
							if (courseToUpdate->getPrerequisite(l) == pNumber) {
								courseToUpdate->deletePrerequisite(l);
								validDelete = true;
							}
						}
						if (!validDelete) {
							std::cout << std::endl << "You entered an invalid prerequisite. Please try again. " << std::endl;
						}
						break;
					case 3:
						break;
					default:
						std::cout << std::endl << "Please enter a valid menu choice. " << std::endl;
					}
				}
			}
			subMenuChoice = 0;
			courseToUpdate = nullptr;
            break;
		}
        default: // invalid input
            std::cout << std::endl << "Please enter a valid menu choice." << std::endl << std::endl;
        }
    }
    std::cout << "Good bye." << std::endl;
    return 0;
}
