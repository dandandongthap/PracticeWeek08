#include<iostream>
#include "AVLTree.h"

void testAVLTree();

void createTree(AVLTree& tree);

int main()
{
	testAVLTree();

	system("pause");
	return 0;
}

void testAVLTree()
{
	using std::cout;
	using std::endl;

	AVLTree tree;

	createTree(tree);

	tree.remove(27);

	cout << "Find: " << tree.find(88) << endl;
	cout << "AVL: " << tree.isAVL() << endl;

	cout << "Preorder: ";
	tree.printPreorder();
	cout << "\nInorder: ";
	tree.printInorder();
	cout << "\nPostorder: ";
	tree.printPostorder();
	cout << "\nLevel order:\n";
	tree.printLevelOrder();

	cout << "Less: " << tree.countLess(50) << endl;
	cout << "Greater: " << tree.countGreater(50) << endl;
	cout << "Leaves: " << tree.countLeaves() << endl;
}

void createTree(AVLTree& tree)
{
	int array[20] = { 23 ,96 ,23 ,39 ,35 ,51 ,88 ,91 ,37 ,32 ,41 ,7 ,93 ,44 ,62 ,82 ,72 ,62 ,56 ,70 };

	for (int i = 0; i < 20; i++)
	{
		tree.insert(array[i]);
	}
}
