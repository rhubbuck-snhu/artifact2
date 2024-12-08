#pragma once
#include <string>
#include <vector>

class AVLNode
{
public:
	std::string key; // holds the key
	AVLNode* parent; // pointer to the parent
	AVLNode* left; // pointer to left child
	AVLNode* right; // pointer to right child
	int bf; // balance factor of the node
	std::string title;
	std::vector<std::string> prerequisites;
	std::string getNumber();
    std::string getName();
    void setName(std::string cName);
    void setNumber(std::string cNumber);

	void addPrerequisite(std::string cPR);
	void deletePrerequisite(int i);
	int prerequisitesSize();
	std::string getPrerequisite(int i);

private:
	int _maxSize = 10;
};