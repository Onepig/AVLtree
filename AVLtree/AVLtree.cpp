#include <iostream>
//#include <algorithm>
using namespace std;

template <class T>
class avlTreeNode
{
public:
	avlTreeNode() :key(T()), left(NULL), right(NULL), height(-1) {}
	T key;
	avlTreeNode<T>* left;
	avlTreeNode<T>* right;
	int height;
};

template <class T>
class avlTree
{
public:
	avlTree();
	int search_key(const T& k) const;
	int get_minmum(T& bitmin) const;
	int get_maxmum(T& bitmax) const;
	//int get_successor(const T& k, T& bit) const;
	//int get_predecessor(const T& k, T& bit) const;
	int insert_key(const T& k);
	int delete_key(const T& k);
	void inorder_tree_walk() const;//中序遍历
	avlTreeNode<T>* get_root() const;

	~avlTree();
private:
	avlTreeNode<T>* root;
	static  avlTreeNode<T>* NIL;
	avlTreeNode<T>* get_left(avlTreeNode<T>* pnode) const;
	avlTreeNode<T>* get_right(avlTreeNode<T>* pnode) const;
	T get_key(avlTreeNode<T>* pnode) const;
	avlTreeNode<T>* get_maxmum(avlTreeNode<T> *subtree) const;
	avlTreeNode<T>* get_minmum(avlTreeNode<T> *subtree) const;
	//avlTreeNode<T>* get_successor(avlTreeNode<T> *pnode) const;
	//avlTreeNode<T>* get_predecessor(avlTreeNode<T> *pnode) const;
	avlTreeNode<T>* search_tree_node(const T& k)const;
	avlTreeNode<T>* insert_key(avlTreeNode<T>* newnode, avlTreeNode<T>* tree);
	void inorder_tree_walk(avlTreeNode<T> * tree)const;
	void make_empty(avlTreeNode<T>* root);
	avlTreeNode<T>* SingleRotateLeft(avlTreeNode<T>* tree);
	avlTreeNode<T>* DoubleRotateLeft(avlTreeNode<T>* tree);
	avlTreeNode<T>* SingleRotateRight(avlTreeNode<T>* tree);
	avlTreeNode<T>* DoubleRotateRight(avlTreeNode<T>* tree);
	int  max(int x, int y) { return x>y ? x : y; }
};

template <class T>
avlTreeNode<T>* avlTree<T>::NIL = new avlTreeNode<T>;

template <class T>
avlTree<T>::avlTree()
{
	root = NULL;
}

template <class T>
int avlTree<T>::search_key(const T& k) const
{
	return (NIL != search_tree_node(k));
}

template <class T>
avlTreeNode<T>* avlTree<T>::get_root() const
{
	return root;
}


template < class T>
avlTreeNode<T>* avlTree<T>::get_left(avlTreeNode<T>* pnode) const
{
	return pnode->left;
}

template < class T>
avlTreeNode<T>* avlTree<T>::get_right(avlTreeNode<T>* pnode) const
{
	return pnode->right;
}

template <class T>
T avlTree<T>::get_key(avlTreeNode<T>* pnode) const
{
	return pnode->key;
}

template <class T>
void avlTree<T>::make_empty(avlTreeNode<T>* avltree)
{
	if (avltree)
	{
		avlTreeNode<T> *pleft = avltree->left;
		avlTreeNode<T>* pright = avltree->right;
		delete avltree;
		if (pleft != NIL)
			make_empty(pleft);
		if (pright != NIL)
			make_empty(pright);
	}
}


template <class T>
avlTreeNode<T>* avlTree<T>::search_tree_node(const T & k) const
{
	avlTreeNode<T>* pnode = root;
	while (pnode != NULL)
	{
		if (pnode->key < k)
			pnode = pnode->right;
		else if (pnode->key > k)
			pnode = pnode->left;
		else
			break;
	}
	return pnode;
}

template <class T>
avlTree<T>::~avlTree()
{
	make_empty(root);
}

template<class T>
void avlTree<T>::inorder_tree_walk() const
{
	if (root != NULL)
		inorder_tree_walk(root);
	else
		cout << "The binary is empty." << endl;
}

template <class T>
void avlTree<T>::inorder_tree_walk(avlTreeNode<T>* tree) const
{
	if (tree != NIL)
	{
		inorder_tree_walk(tree->left);
		cout << tree->key << endl;
		inorder_tree_walk(tree->right);
	}
}

template <class T>
int avlTree<T>::get_minmum(T& bitmin) const
{
	if (root)
	{
		bitmin = get_minmum(root)->key;
		return 0;
	}
	return -1;
}

template <class T>
avlTreeNode<T>* avlTree<T>::get_minmum(avlTreeNode<T>* tree) const
{
	avlTreeNode<T>* pnode = tree;
	while (pnode->left != NIL)
	{
		pnode = pnode->left;
	}
	return pnode;
}

template <class T>
int avlTree<T>::get_maxmum(T& bitmax) const
{
	if (root)
	{
		bitmax = get_maxmum(root)->key;
		return 0;
	}
	return -1;
}

template <class T>
avlTreeNode<T>* avlTree<T>::get_maxmum(avlTreeNode<T>* tree) const
{
	avlTreeNode<T>* pnode = tree;
	while (pnode->right != NIL)
	{
		pnode = pnode->right;
	}
	return pnode;
}
/*
template < class T>
int avlTree<T>::get_successor(const T& k, T& bit) const
{
	if (root)
	{
		avlTreeNode<T>* pnode = search_tree_node(k);
		if (pnode != NIL)
		{
			pnode = get_successor(pnode);
			if (pnode != NIL)
			{
				bit = pnode->key;
				return 0;
			}
			return -1;
		}
		return -1;
	}
	return -1;
}

template <class T>
avlTreeNode<T>*  avlTree<T>::get_successor(avlTreeNode<T>* subtree) const
{
	if (subtree->right != NIL)
	{
		return get_minmum(subtree->right);
	}
	avlTreeNode<T>* parentnode = get_parent(subtree);
	while (parentnode != NIL && subtree == parentnode->right)
	{
		subtree = parentnode;
		parentnode = get_parent(parentnode);
	}
	return parentnode;
}

template < class T>
int avlTree<T>::get_predecessor(const T& k, T& bit) const
{
	if (root)
	{
		avlTreeNode<T>* pnode = search_tree_node(k);
		if (pnode != NIL)
		{
			pnode = get_predecessor(pnode);
			if (pnode != NIL)
			{
				bit = pnode->key;
				return 0;
			}
			return -1;
		}
		return -1;
	}
	return -1;
}

template <class T>
avlTreeNode<T>*  avlTree<T>::get_predecessor(avlTreeNode<T>* subtree) const
{
	if (subtree->left != NIL)
		return get_minmum(subtree->left);
	avlTreeNode<T>* parentnode = get_parent(subtree);
	while (parentnode != NIL && subtree == parentnode->left)
	{
		subtree = parentnode;
		parentnode = get_parent(parentnode);
	}
	return parentnode;
}
*/


template <class T>
int avlTree<T>::delete_key(const T& k)
{
	avlTreeNode<T>* pnode = search_tree_node(k); //z

	if (NIL != pnode)
	{
		if (pnode->left == NIL)
			transplant(pnode, get_right(pnode));
		else if (pnode->right == NIL)
			transplant(pnode, get_left(pnode));
		else
		{
			avlTreeNode<T>* qnode = get_minmum(pnode->right);//y
			cout << qnode->key << endl;
			if (qnode->parent != pnode)
			{
				transplant(qnode, qnode->right);
				qnode->right = pnode->right;
				pnode->right->parent = qnode;
			}
			transplant(pnode, qnode);
			qnode->left = pnode->left;
			qnode->left->parent = qnode;
		}
		delete pnode;
		return 0;
	}
	return -1;
}

template < class T>
int avlTree<T>::insert_key(const T& k)
{
	avlTreeNode<T>* newnode = new avlTreeNode<T>;
	newnode->key = k;
	newnode->left = NIL;
	newnode->right = NIL;
	newnode->height = -1;

	root=insert_key(newnode, root);
	return 0;
}

template <class T>
avlTreeNode<T>* avlTree<T>::insert_key(avlTreeNode<T>* newnode, avlTreeNode<T>* tree)
{
	if (tree == NULL || tree== NIL)
		tree = newnode;
	else if (tree->key > newnode->key)//插入在左边
	{
		tree->left=insert_key(newnode, tree->left);
		if ( (tree->left->height) - (tree->right->height) == 2)
		{
			if (newnode->key < tree->left->key)
				tree = SingleRotateLeft(tree);
			else
				tree = DoubleRotateLeft(tree);
		}
	}
	else if(tree->key < newnode->key)
	{
		tree->right = insert_key(newnode, tree->right);
		if ((tree->right->height) - (tree->left->height) == 2 )
		{
			if (newnode->key > tree->right->key)
				tree = SingleRotateRight(tree);
			else
				tree = DoubleRotateRight(tree);
		}
	}
	tree->height = max((tree->right->height), (tree->left->height) ) + 1;
	return tree;
}

template<class T>
avlTreeNode<T>* avlTree<T>::SingleRotateLeft(avlTreeNode<T>* tree)
{
	cout << "single rotate left" << endl;
	avlTreeNode<T>* qnode;

	qnode = tree->left;
	tree->left = qnode->right;
	qnode->right = tree;
	tree->height = max((tree->left->height), (tree->right->height)) + 1;
	//qnode->height = max((qnode->left->height), (tree->height)) + 1;
	//root = qnode;
	return qnode;
}

template<class T>
avlTreeNode<T>* avlTree<T>::DoubleRotateLeft(avlTreeNode<T>* tree)
{
	cout << "double rotate left" << endl;
	tree->left = SingleRotateRight(tree->left);

	//root = SingleRotateLeft(tree);
	return SingleRotateLeft(tree);
}

template<class T>
avlTreeNode<T>* avlTree<T>::SingleRotateRight(avlTreeNode<T>* tree)
{
	cout << "single rotate right" << endl;
	avlTreeNode<T>* qnode;

	qnode = tree->right;
	tree->right = qnode->left;
	qnode->left = tree;
	tree->height = max((tree->left->height), (tree->right->height)) + 1;
	//qnode->height = max((qnode->right->height), (tree->height)) + 1;
	//root = qnode;
	return qnode;
}

template<class T>
avlTreeNode<T>* avlTree<T>::DoubleRotateRight(avlTreeNode<T>* tree)
{
	cout << "double rotate right" << endl;
	tree->right = SingleRotateLeft(tree->right);

	//root = SingleRotateRight(tree);
	return SingleRotateRight(tree);
}


int main()
{
	avlTree<int> avltree;
	//int value;
	avltree.insert_key(66);
	cout << "root is: " << avltree.get_root()->key << endl;
	cout << "Inorder walk avl tree:" << endl;
	avltree.inorder_tree_walk();

	avltree.insert_key(15);
	cout << "root is: " << avltree.get_root()->key << endl;
	cout << "Inorder walk avl tree:" << endl;
	avltree.inorder_tree_walk();

	avltree.insert_key(5);
	cout << "root is: " << avltree.get_root()->key << endl;
	cout << "Inorder walk avl tree:" << endl;
	avltree.inorder_tree_walk();

	avltree.insert_key(70);
	cout << "root is: " << avltree.get_root()->key << endl;
	cout << "Inorder walk avl tree:" << endl;
	avltree.inorder_tree_walk();
	avltree.insert_key(20);
	cout << "root is: " << avltree.get_root()->key << endl;
	cout << "Inorder walk avl tree:" << endl;
	avltree.inorder_tree_walk();
	avltree.insert_key(7);
	cout << "root is: " << avltree.get_root()->key << endl;
	cout << "Inorder walk avl tree:" << endl;
	avltree.inorder_tree_walk();
	avltree.insert_key(75);
	cout << "root is: " << avltree.get_root()->key << endl;
	cout << "Inorder walk avl tree:" << endl;
	avltree.inorder_tree_walk();
	avltree.insert_key(78);
	cout << "root is: " << avltree.get_root()->key << endl;
	cout << "Inorder walk avl tree:" << endl;
	avltree.inorder_tree_walk();
	avltree.insert_key(60);
	cout << "root is: " << avltree.get_root()->key << endl;
	cout << "Inorder walk avl tree:" << endl;
	avltree.inorder_tree_walk();
	
	avltree.insert_key(30);
	cout << "root is: " << avltree.get_root()->key << endl;
	cout << "Inorder walk avl tree:" << endl;
	avltree.inorder_tree_walk();
	avltree.insert_key(50);
	cout << "root is: " << avltree.get_root()->key << endl;
	cout << "Inorder walk avl tree:" << endl;
	avltree.inorder_tree_walk();
	avltree.insert_key(65);
	cout << "root is: " << avltree.get_root()->key << endl;
	cout << "Inorder walk avl tree:" << endl;
	avltree.inorder_tree_walk();
	avltree.insert_key(25);
	cout << "root is: " << avltree.get_root()->key << endl;
	cout << "Inorder walk avl tree:" << endl;
	avltree.inorder_tree_walk();
	avltree.insert_key(90);
	cout << "root is: " << avltree.get_root()->key << endl;
	cout << "Inorder walk avl tree:" << endl;
	avltree.inorder_tree_walk();
	avltree.insert_key(40);
	cout << "root is: " << avltree.get_root()->key << endl;
	cout << "Inorder walk avl tree:" << endl;
	avltree.inorder_tree_walk();
	avltree.insert_key(55);
	cout << "root is: " << avltree.get_root()->key << endl;
	cout << "Inorder walk avl tree:" << endl;
	avltree.inorder_tree_walk();
	
	/*	
	
	if (avltree.get_minmum(value) == 0)
		cout << "minmum is: " << value << endl;

	if (avltree.get_maxmum(value) == 0)
		cout << "maxmum is: " << value << endl;

	int val(66);

	if (avltree.search_key(val) != 0)
		cout << val << "is found." << endl;

	if (avltree.get_successor(val, value) == 0)
		cout << val << "'s successor is: " << value << endl;

	if (avltree.get_predecessor(val, value) == 0)
		cout << val << "'s predecessor is: " << value << endl;

	if (avltree.delete_key(val) == 0)
		cout << "delete " << val << " successfully" << endl;

	if (avltree.delete_key(65) == 0)
		cout << "delete 65 successfully" << endl;

	cout << "root is: " << avltree.get_root()->key << endl;
	cout << "Inorder walk red black tree:" << endl;
	avltree.inorder_tree_walk();

	if (avltree.delete_key(60) == 0)
		cout << "delete 60 successfully" << endl;
	avltree.search_key(20);

	cout << "root is: " << avltree.get_root()->key << endl;
	cout << "Inorder walk red black tree:" << endl;
	avltree.inorder_tree_walk();
	*/
	return 0;
}
