#ifndef _AVL_Tree_HPP_
#define _AVL_Tree_HPP_

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
	int remove(const T& k);
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
	avlTreeNode<T>* detele_key(avlTreeNode<T>* newnode, avlTreeNode<T>*& tree);
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
		cout << tree->key <<"\t"<<tree->height<< endl;
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
	cout << "tree->key3=" << tree->key << endl;
	cout << "tree->left->key3=" << tree->left->key << endl;
	cout << "tree->left->left->key3=" << tree->left->key << endl;
	qnode = tree->left;
	tree->left = qnode->right;
	qnode->right = tree;
	tree->height = max((tree->left->height), (tree->right->height)) + 1;
	//qnode->height = max((qnode->left->height), (tree->height)) + 1;
	//root = qnode;
	cout << "qnode->key3=" << qnode->key << endl;
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
	cout << "tree->left->key=" << tree->left->key << endl;
	tree->height = max((tree->left->height), (tree->right->height)) + 1;

	//qnode->height = max((qnode->right->height), (tree->height)) + 1;
	//root = qnode;
	cout << "qnode->left->key=" << qnode->left->key << endl;
	cout << "qnode->key=" << qnode->key << endl;
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


template <class T>
int avlTree<T>::remove(const T& k)
{
	avlTreeNode<T>* pnode = search_tree_node(k); //z
	if(pnode != NIL)
	{
		root=detele_key(pnode, root);
		cout << "Delete "<<k<<" successfully!" << endl;
		return 0;
	}
	else
		return -1;
}

template<class T>
avlTreeNode<T>* avlTree<T>::detele_key(avlTreeNode<T>* delnode, avlTreeNode<T>*& tree)
{
	if (tree->key > delnode->key)//待删除节点在左边
	{
		tree->left = detele_key(delnode, tree->left);
		if ((tree->right->height) - (tree->left->height) == 2)
		{
			avlTreeNode<T>* rtree = tree->right;
			if (rtree->right->height < rtree->left->height)
				tree = SingleRotateRight(tree);
			else
				tree = DoubleRotateRight(tree);
		}
	}

	else if (tree->key < delnode->key) //待删除节点在右边
	{
		tree->right = detele_key(delnode, tree->right);
		if ((tree->left->height) - (tree->right->height) == 2)
		{
			avlTreeNode<T>* ltree = tree->left;
			if (ltree->left->height > ltree->right->height)
				tree = SingleRotateLeft(tree);
			else
				cout << "tree->key before=" << tree->key << endl;
				tree = DoubleRotateLeft(tree);
				cout << "tree->key after=" << tree->key << endl;
		}
	}

	else //tree就是待删除的节点delnode
	{
		if( (tree->left!= NIL) && (tree->right!=NIL) )//左右几点均不为 NIL
		{
			if ( (tree->right->height) > (tree->left->height)) //右树高大于左树高
			{
				avlTreeNode<T>* min = get_minmum(tree->right);
				tree->key = min->key;
				tree->right = detele_key(min, tree->right);
			}
			else//左树高大于、或等于右树高
			{
				avlTreeNode<T>* max = get_maxmum(tree->left);
				tree->key = max->key;
				tree->left = detele_key(max, tree->left);
			}
		}
		else//有一子树为NIL，那么另一子树高至多为 0
		{
			avlTreeNode<T>* tmp = tree;
			if (tree->left != NIL)
				tree = tree->left;
			else
				tree = tree->right;
			delete tmp;
		}
	}

	//tree->height = max((tree->right->height), (tree->left->height)) + 1;
	cout << tree->key <<"\t"<< tree->height<< endl;
	return tree;
}

#endif