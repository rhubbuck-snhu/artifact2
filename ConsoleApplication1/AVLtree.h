#include "AVLNode.h"
#include <iostream>
#include <string>
#pragma once

typedef AVLNode* NodePtr;

class AVLtree
{
public:
	AVLtree();
	void inorder();
	void printNode(std::string k);
	NodePtr searchHelper(NodePtr node, std::string key);
	NodePtr search(std::string k);
	NodePtr minimum(NodePtr node);
	NodePtr maximum(NodePtr node);
	NodePtr successor(NodePtr x);
	NodePtr predecessor(NodePtr x);
	void leftRotate(NodePtr x);
	void rightRotate(NodePtr x);
	void insert(std::string key, std::string title);
	NodePtr deleteNode(std::string key);

private:
	NodePtr root;
	void initializeNode(NodePtr node, std::string key, std::string title);
	void inOrderHelper(NodePtr node);
	void printNodeHelper(NodePtr node, std::string key);
	NodePtr deleteNodeHelper(NodePtr node, std::string key);
	void updateBalance(NodePtr node);
	void rebalance(NodePtr node);
};
