#pragma once

#include <ostream>

class Node
{
public:
	int key;
	int height;
	Node* left;
	Node* right;

	Node();
	Node(int);
};

class AVLTree
{
public:
	AVLTree();
	~AVLTree();

	void insert(int key);
	void remove(int key);
	Node* find(int key);
	bool isAVL();
	void printPreorder();
	void printInorder();
	void printPostorder();
	void printLevelOrder();
	int countLess(int key);
	int countGreater(int key);
	int countLeaves();
	void clear();

private:
	Node* root;

	int getHeight(Node* root);
	int getBalance(Node* root);
	Node* rightRotate(Node* root);
	Node* leftRotate(Node* root);
	Node* minNode(Node* root);
	bool isBST(Node* root, Node* min, Node* max);
	bool isBalanced(Node* root);
	void printLevel(Node* root,int level);
	Node* insert(Node* root, int key);
	Node* remove(Node* root, int key);
	Node* find(Node* root, int key);
	bool isAVL(Node* root);
	void printPreorder(Node* root);
	void printInorder(Node* root);
	void printPostorder(Node* root);
	void printLevelOrder(Node* root);
	int countLess(Node* root, int key);
	int countGreater(Node* root, int key);
	int countLeaves(Node* root);
	void clear(Node*& root);
};

std::ostream& operator<<(std::ostream& os,const Node* node);