#include "AVLNode.h"
#include <iostream>

std::string AVLNode::getName() {
	return title;
}

void AVLNode::setName(std::string cName) {
	title = cName;
}

std::string AVLNode::getNumber() {
	return key;
}

void AVLNode::setNumber(std::string cNumber) {
	key = cNumber;
}

void AVLNode::addPrerequisite(std::string cPR) {
	if (prerequisites.size() < _maxSize) {
		prerequisites.push_back(cPR);
	}
	else {
		throw std::length_error("Maximum number of prerequisites met.");
	} 
}

void AVLNode::deletePrerequisite(int i) {
	prerequisites.erase(prerequisites.begin() + i);
}

int AVLNode::prerequisitesSize() {
	return prerequisites.size();
}

std::string AVLNode::getPrerequisite(int i) {
	return prerequisites[i];
}