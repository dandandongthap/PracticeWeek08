#include "AVLTree.h"
#include <iostream>
#include <cmath>

Node::Node()
{
	this->key = 0;
	this->height = 1;
	this->left = nullptr;
	this->right = nullptr;
}

Node::Node(int key)
{
	this->key = key;
	this->height = 1;
	this->left = nullptr;
	this->right = nullptr;
}

AVLTree::AVLTree()
{
	this->root = nullptr;
}

AVLTree::~AVLTree()
{
	clear();
}

void AVLTree::insert(int key)
{
	this->root = insert(this->root, key);
}

void AVLTree::remove(int key)
{
	this->root = remove(this->root, key);
}

Node* AVLTree::find(int key)
{
	return find(this->root, key);
}

bool AVLTree::isAVL()
{
	return isAVL(this->root);
}

void AVLTree::printPreorder()
{
	printPreorder(this->root);
}

void AVLTree::printInorder()
{
	printInorder(this->root);
}

void AVLTree::printPostorder()
{
	printPostorder(this->root);
}

void AVLTree::printLevelOrder()
{
	printLevelOrder(this->root);
}

int AVLTree::countLess(int key)
{
	return countLess(this->root, key);
}

int AVLTree::countGreater(int key)
{
	return countGreater(this->root, key);
}

int AVLTree::countLeaves()
{
	return countLeaves(this->root);
}

void AVLTree::clear()
{
	clear(this->root);
}

int AVLTree::getHeight(Node* root)
{
	return root ? root->height : 0;
}

int AVLTree::getBalance(Node* root)
{
	return root ? getHeight(root->left) - getHeight(root->right) : 0;
}

Node* AVLTree::rightRotate(Node* root)
{
	Node* leftChild = root->left;

	root->left = leftChild->right;
	leftChild->right = root;

	root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));
	leftChild->height = 1 + std::max(getHeight(leftChild->left), root->height);

	return leftChild;
}

Node* AVLTree::leftRotate(Node* root)
{
	Node* rightChild = root->right;

	root->right = rightChild->left;
	rightChild->left = root;

	root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));
	rightChild->height = 1 + std::max(getHeight(rightChild->left), root->height);

	return rightChild;
}

Node* AVLTree::minNode(Node* root)
{
	if (!root) return nullptr;
	return (root->left) ? minNode(root->left) : root;
}

bool AVLTree::isBST(Node* root, Node* min, Node* max)
{
	if (!root) return true;

	if (min && root->key <= min->key) return false;
	if (max && root->key >= max->key) return false;
	return isBST(root->left, min, root) && isBST(root->right, root, max);
}

bool AVLTree::isBalanced(Node* root)
{
	if (!root) return true;

	if (isBalanced(root->left) && isBalanced(root->right) && std::abs(getBalance(root)) < 2) return true;

	return false;
}

void AVLTree::printLevel(Node* root, int level)
{
	if (!root) return;

	if (level == 1)
	{
		std::cout << root << "    ";
	}
	else if (level > 1)
	{
		printLevel(root->left, level - 1);
		printLevel(root->right, level - 1);
	}
}

Node* AVLTree::insert(Node* root, int key)
{
	if (!root) return new Node(key);

	if (key < root->key)
	{
		root->left = insert(root->left, key);
	}
	else if (key > root->key)
	{
		root->right = insert(root->right, key);
	}
	else
	{
		std::cerr << root->key << " already exists!\n";
		return root;
	}
	root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));

	int balance = getBalance(root);

	if (balance > 1)
	{
		if (key > root->left->key)
		{
			root->left = leftRotate(root->left);
		}
		return rightRotate(root);
	}
	if (balance < -1)
	{
		if (key < root->right->key)
		{
			root->right = rightRotate(root->right);
		}
		return leftRotate(root);
	}
	return root;
}

Node* AVLTree::remove(Node* root, int key)
{
	if (!root)
	{
		std::cerr << key << " does not exists!\n";
		return nullptr;
	}

	if (key < root->key)
	{
		root->left = remove(root->left, key);
	}
	else if (key > root->key)
	{
		root->right = remove(root->right, key);
	}
	else if (!root->left)
	{
		Node* temp = root->right;

		delete root;
		root = nullptr;
		return temp;
	}
	else if (!root->right)
	{
		Node* temp = root->left;

		delete root;
		root = nullptr;
		return temp;
	}
	else
	{
		Node* min = minNode(root->right);

		root->key = min->key;
		root->right = remove(root->right, min->key);
	}

	root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));

	int balance = getBalance(root);

	if (balance > 1)
	{
		if (getBalance(root->left) < 0)
		{
			root->left = leftRotate(root->left);
		}
		return rightRotate(root);
	}
	if (balance < -1)
	{
		if (getBalance(root->right) > 0)
		{
			root->right = rightRotate(root->right);
		}
		return leftRotate(root);
	}
	return root;
}

Node* AVLTree::find(Node* root, int key)
{
	if (!root) return nullptr;

	if (key < root->key) return find(root->left, key);
	if (key > root->key) return find(root->right, key);
	return root;
}

bool AVLTree::isAVL(Node* root)
{
	return isBST(root, nullptr, nullptr) && isBalanced(root);
}

void AVLTree::printPreorder(Node* root)
{
	if (!root) return;

	std::cout << root << "    ";
	printPreorder(root->left);
	printPreorder(root->right);
}

void AVLTree::printInorder(Node* root)
{
	if (!root) return;

	printInorder(root->left);
	std::cout << root << "    ";
	printInorder(root->right);
}

void AVLTree::printPostorder(Node* root)
{
	if (!root) return;

	printPostorder(root->left);
	printPostorder(root->right);
	std::cout << root << "    ";

}

void AVLTree::printLevelOrder(Node* root)
{
	int height = getHeight(root);

	for (int i = 1; i <= height; i++)
	{
		printLevel(root, i);
		std::cout << std::endl;
	}
}

int AVLTree::countLess(Node* root, int key)
{
	if (!root) return 0;

	if (root->key < key)
		return 1 + countLess(root->left, key) + countLess(root->right, key);

	return countLess(root->left,key);
}

int AVLTree::countGreater(Node* root, int key)
{
	if (!root) return 0;

	if (root->key > key)
		return 1 + countGreater(root->left, key) + countGreater(root->right, key);

	return countGreater(root->right, key);
}

int AVLTree::countLeaves(Node* root)
{
	if (!root) return 0;

	return (getHeight(root) == 1) ? 1 : (countLeaves(root->left) + countLeaves(root->right));
}

void AVLTree::clear(Node*& root)
{
	if (!root) return;

	clear(root->left);
	clear(root->right);
	delete root;
	root = nullptr;
}

std::ostream& operator<<(std::ostream& os, const Node* node)
{
	if (!node)
	{
		os << "(-1, -1)";
	}
	else
	{
		os << "(" << node->key << ", " << node->height << ")";
	}
	return os;
}
