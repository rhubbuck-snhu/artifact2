#include "AVLtree.h"
#include "AVLNode.h"
#include <iostream>
#include <string>

typedef AVLNode* NodePtr;

// initializes a node with a given course number (key) and title
void AVLtree::initializeNode(NodePtr node, std::string key, std::string title) {
	node->key = key;
	node->parent = nullptr;
	node->left = nullptr;
	node->right = nullptr;
	node->bf = 0;
	node->title = title;
}

// used to traverse tree and print all node details
void AVLtree::inOrderHelper(NodePtr node) {
	if (node != nullptr) {
		inOrderHelper(node->left);
		std::cout << node->key << " - " << node->title << " " << std::endl;
		inOrderHelper(node->right);
	}
}

// used to find a specific course and print it's details
void AVLtree::printNodeHelper(NodePtr node, std::string key) {
	if (node != nullptr && key == node->key) { //node == nullptr ||
		std::cout << node->title << std::endl;
		std::cout << "Prerequisites: ";
		for (int j = 0; j < node->prerequisitesSize(); ++j) {
			std::cout << node->getPrerequisite(j) << " ";
		}
		std::cout << std::endl << std::endl;
		return;
		//return node;
	}
	if (node == nullptr) {
		std::cout << "Course not found." << std::endl;
		//return node;
		return;
	}

	if (node != nullptr && key < node->key) {
		return printNodeHelper(node->left, key);
	}
	return printNodeHelper(node->right, key);
}

// used to find a node with a specific key and delete it
NodePtr AVLtree::deleteNodeHelper(NodePtr node, std::string key) {
	// search the key
	if (node == nullptr) return node;
	else if (key < node->key) node->left = deleteNodeHelper(node->left, key);
	else if (key > node->key) node->right = deleteNodeHelper(node->right, key);
	else {
		// the key has been found, now delete it

		// case 1: node is a leaf node
		if (node->left == nullptr && node->right == nullptr) {
			delete node;
			node = nullptr;
		}

		// case 2: node has only one child
		else if (node->left == nullptr) {
			NodePtr temp = node;
			node = node->right;
			delete temp;
		}

		else if (node->right == nullptr) {
			NodePtr temp = node;
			node = node->left;
			delete temp;
		}

		// case 3: has both children
		else {
			NodePtr temp = minimum(node->right);
			node->key = temp->key;
			node->right = deleteNodeHelper(node->right, temp->key);
		}

	}
	return node;
}

// update the balance factor the node
void AVLtree::updateBalance(NodePtr node) {
	if (node->bf < -1 || node->bf > 1) {
		rebalance(node);
		return;
	}

	if (node->parent != nullptr) {
		if (node == node->parent->left) {
			node->parent->bf -= 1;
		}

		if (node == node->parent->right) {
			node->parent->bf += 1;
		}

		if (node->parent->bf != 0) {
			updateBalance(node->parent);
		}
	}
}

// rebalance the tree
void AVLtree::rebalance(NodePtr node) {
	if (node->bf > 0) {
		if (node->right->bf < 0) {
			rightRotate(node->right);
			leftRotate(node);
		}
		else {
			leftRotate(node);
		}
	}
	else if (node->bf < 0) {
		if (node->left->bf > 0) {
			leftRotate(node->left);
			rightRotate(node);
		}
		else {
			rightRotate(node);
		}
	}
}

// constructor
AVLtree::AVLtree() {
	root = nullptr;
}

// in-order traversal to print all nodes
void AVLtree::inorder() {
	inOrderHelper(this->root);
	std::cout << std::endl;
}

// search the tree for a given key and print the node's information
void AVLtree::printNode(std::string k) {
	return printNodeHelper(this->root, k);
}

// used to help search for a specific node
NodePtr AVLtree::searchHelper(NodePtr node, std::string key) {
	if (node != nullptr && key == node->key) {
		return node;
	}
	if (node == nullptr) {
		return node;
	}

	if (node != nullptr && key < node->key) {
		return searchHelper(node->left, key);
	}
	return searchHelper(node->right, key);
}

// search the tree for a given key and return a pointer to that node
NodePtr AVLtree::search(std::string k) {
	return searchHelper(this->root, k);
}

// find the node with the minimum key
NodePtr AVLtree::minimum(NodePtr node) {
	while (node->left != nullptr) {
		node = node->left;
	}
	return node;
}

// find the node with the maximum key
NodePtr AVLtree::maximum(NodePtr node) {
	while (node->right != nullptr) {
		node = node->right;
	}
	return node;
}

// find the successor of a given node
NodePtr AVLtree::successor(NodePtr x) {
	if (x->right != nullptr) {
		return minimum(x->right);
	}

	NodePtr y = x->parent;
	while (y != nullptr && x == y->right) {
		x = y;
		y = y->parent;
	}
	return y;
}

// find the predecessor of a given node
NodePtr AVLtree::predecessor(NodePtr x) {
	if (x->left != nullptr) {
		return maximum(x->left);
	}

	NodePtr y = x->parent;
	while (y != nullptr && x == y->left) {
		x = y;
		y = y->parent;
	}
	return y;
}

// rotate left at a node
void AVLtree::leftRotate(NodePtr x) {
	NodePtr y = x->right;
	x->right = y->left;
	if (y->left != nullptr) {
		y->left->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == nullptr) {
		this->root = y;
	}
	else if (x == x->parent->left) {
		x->parent->left = y;
	}
	else {
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;

	// update the balance factor
	x->bf = x->bf - 1 - std::max(0, y->bf);
	y->bf = y->bf - 1 + std::min(0, x->bf);
}

// rotate right at a node
void AVLtree::rightRotate(NodePtr x) {
	NodePtr y = x->left;
	x->left = y->right;
	if (y->right != nullptr) {
		y->right->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == nullptr) {
		this->root = y;
	}
	else if (x == x->parent->right) {
		x->parent->right = y;
	}
	else {
		x->parent->left = y;
	}
	y->right = x;
	x->parent = y;

	// update the balance factor
	x->bf = x->bf + 1 - std::min(0, y->bf);
	y->bf = y->bf + 1 + std::max(0, x->bf);
}

// insert a node with user specified course number (key) and title
void AVLtree::insert(std::string key, std::string title) {
	NodePtr node = new AVLNode;
	node->parent = nullptr;
	node->left = nullptr;
	node->right = nullptr;
	node->key = key;
	node->bf = 0;
	node->title = title;
	NodePtr y = nullptr;
	NodePtr x = this->root;

	while (x != nullptr) {
		y = x;
		if (node->key < x->key) {
			x = x->left;
		}
		else {
			x = x->right;
		}
	}

	node->parent = y;
	if (y == nullptr) {
		root = node;
	}
	else if (node->key < y->key) {
		y->left = node;
	}
	else {
		y->right = node;
	}

	updateBalance(node);
}

// delete a node from the tree by key
NodePtr AVLtree::deleteNode(std::string key) {
	NodePtr deletedNode = deleteNodeHelper(this->root, key);
	return deletedNode;
}