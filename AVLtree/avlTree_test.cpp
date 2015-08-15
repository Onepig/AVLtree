
#include <iostream>
#include "AVLtree.h"
using namespace std;
//, 88, 33, 99, 44, 22, 77, 55, 100
static int input[] = { 1,66,11, 88, 33, 99, 44, 22, 77, 55, 100 };
#define Length_input(a) (sizeof(a)/sizeof(a[0]))


int main()
{
	avlTree<int> avltree;
	//int value;
	int Len = Length_input(input);
	for (int i = 0; i < Len; i++)
	{
		avltree.insert_key(input[i]);
		cout << "root is: " << avltree.get_root()->key << endl;
		cout << "Inorder walk avl tree:" << endl;
		avltree.inorder_tree_walk();
		cout << endl;
	}
	
	int value(44);
	if (avltree.get_minmum(value) == 0)
		cout << "minmum is: " << value << endl;

	if (avltree.get_maxmum(value) == 0)
		cout << "maxmum is: " << value << endl;


	int val(66);
	if (avltree.search_key(val) != 0)
		cout << val << " is found." << endl;
	
	
	cout << "1" << endl;

	if (avltree.search_key(val) != 0)
		cout << val << "is found." << endl;
	if (avltree.remove(val) == 0)
	{
		cout << "root is: " << avltree.get_root()->key << endl;
		cout << "Inorder walk avl tree:" << endl;
		avltree.inorder_tree_walk();
		cout << endl;
	}

	int val2(55);
	if (avltree.remove(val2) == 0)
	{
		cout << "root is: " << avltree.get_root()->key << endl;
		cout << "Inorder walk avl tree:" << endl;
		avltree.inorder_tree_walk();
		cout << endl;
	}

	return 0;
}