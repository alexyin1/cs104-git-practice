#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
#include <cmath>

/**
* A templated class for a Node in a search tree. The getters for parent/left/right are virtual so that they
* can be overridden for future kinds of search trees, such as Red Black trees, Splay trees, and AVL trees.
*/
template <typename Key, typename Value>
class Node
{
public:
	Node(const Key& key, const Value& value, Node<Key, Value>* parent);
	virtual ~Node();

	const std::pair<Key, Value>& getItem() const;
	std::pair<Key, Value>& getItem();
	const Key& getKey() const;
	const Value& getValue() const;
	Key& getKey();
	Value& getValue();

	virtual Node<Key, Value>* getParent() const;
	virtual Node<Key, Value>* getLeft() const;
	virtual Node<Key, Value>* getRight() const;

	void setParent(Node<Key, Value>* parent);
	void setLeft(Node<Key, Value>* left);
	void setRight(Node<Key, Value>* right);
	void setValue(const Value &value);

protected:
	std::pair<Key, Value> mItem;
	Node<Key, Value>* mParent;
	Node<Key, Value>* mLeft;
	Node<Key, Value>* mRight;

};

/*
	-----------------------------------------
	Begin implementations for the Node class.
	-----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent)
	: mItem(key, value)
	, mParent(parent)
	, mLeft(NULL)
	, mRight(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed within the deleteAll() helper method in the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{
}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<Key, Value>& Node<Key, Value>::getItem() const
{
	return mItem;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<Key, Value>& Node<Key, Value>::getItem()
{
	return mItem;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
	return mItem.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
	return mItem.second;
}

/**
* A non-const getter for the key.
*/
template<typename Key, typename Value>
Key& Node<Key, Value>::getKey()
{
	return mItem.first;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
	return mItem.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
	return mParent;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
	return mLeft;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
	return mRight;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
	mParent = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
	mLeft = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
	mRight = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
	mItem.second = value;
}

/*
	---------------------------------------
	End implementations for the Node class.
	---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
	public:
		BinarySearchTree(); //TODO
		virtual ~BinarySearchTree(); //TODO
  		virtual void insert(const std::pair<Key, Value>& keyValuePair); //TODO
        virtual void remove(const Key& key); //TODO
  		void clear(); //TODO
  		void print() const;
  		bool isBalanced() const; //TODO

	public:
		/**
		* An internal iterator class for traversing the contents of the BST.
		*/
		class iterator
		{
			public:
				iterator(Node<Key,Value>* ptr);
				iterator();

				std::pair<Key,Value>& operator*() const;
				std::pair<Key,Value>* operator->() const;

				bool operator==(const iterator& rhs) const;
				bool operator!=(const iterator& rhs) const;
				iterator& operator=(const iterator& rhs);

				iterator& operator++();

			protected:
				Node<Key, Value>* mCurrent;
				friend class BinarySearchTree<Key, Value>;
		};

	public:
		iterator begin() const;
		iterator end() const;
		iterator find(const Key& key) const;

	protected:
		Node<Key, Value>* internalFind(const Key& key) const; //TODO
		Node<Key, Value>* getSmallestNode() const; //TODO
        Node<Key, Value>* getSmallestNode(Node<Key, Value>* startnode) const;
        Node<Key, Value>* getLargestNode(Node<Key, Value>* startnode) const;
        void printRoot (Node<Key, Value>* root) const;

	protected:
		Node<Key, Value>* mRoot;//temp

	public:
		void print() {this->printRoot(this->mRoot);}

    private:
        void clear(Node<Key, Value>* node);
        void changeParentChild(Node<Key, Value>* keynode, Node<Key, Value>* replacement); //change keynodes parent to point to replacement
        int isBalanced(Node<Key,Value>* node) const; //returns height or -1 if unbalanced

};

/*
	---------------------------------------------------------------
	Begin implementations for the BinarySearchTree::iterator class.
	---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value>* ptr)
	: mCurrent(ptr)
{

}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator()
	: mCurrent(NULL)
{

}

/**
* Provides access to the item.
*/
template<typename Key, typename Value>
std::pair<Key, Value>& BinarySearchTree<Key, Value>::iterator::operator*() const
{
	return mCurrent->getItem();
}

/**
* Provides access to the address of the item.
*/
template<typename Key, typename Value>
std::pair<Key, Value>* BinarySearchTree<Key, Value>::iterator::operator->() const
{
	return &(mCurrent->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator==(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return this->mCurrent == rhs.mCurrent;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator!=(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return this->mCurrent != rhs.mCurrent;
}

/**
* Sets one iterator equal to another iterator.
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator &BinarySearchTree<Key, Value>::iterator::operator=(const BinarySearchTree<Key, Value>::iterator& rhs)
{
	this->mCurrent = rhs.mCurrent;
	return *this;
}

/**
* Advances the iterator's location using an in-order traversal.
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator& BinarySearchTree<Key, Value>::iterator::operator++()
{
	if(mCurrent->getRight() != NULL)
	{
		mCurrent = mCurrent->getRight();
		while(mCurrent->getLeft() != NULL)
		{
			mCurrent = mCurrent->getLeft();
		}
	}
	else if(mCurrent->getRight() == NULL)
	{
		Node<Key, Value>* parent = mCurrent->getParent();
		while(parent != NULL && mCurrent == parent->getRight())
		{
			mCurrent = parent;
			parent = parent->getParent();
		}
		mCurrent = parent;
	}
	return *this;
}

/*
	-------------------------------------------------------------
	End implementations for the BinarySearchTree::iterator class.
	-------------------------------------------------------------
*/

/*
	-----------------------------------------------------
	Begin implementations for the BinarySearchTree class.
	-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::BinarySearchTree()
{
	// TODO DONE
    mRoot = NULL;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
	// TODO DONE
    clear();
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
	printRoot(mRoot);
	std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::begin() const
{
	BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
	return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::end() const
{
	BinarySearchTree<Key, Value>::iterator end(NULL);
	return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::find(const Key& key) const
{
	Node<Key, Value>* curr = internalFind(key);
	BinarySearchTree<Key, Value>::iterator it(curr);
	return it;
}

/**
* An insert method to insert into a Binary Search Tree. The tree will not remain balanced when
* inserting.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<Key, Value>& keyValuePair)
{
	// TODO DONE
    if(mRoot==NULL){
        mRoot = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
        return;
    }
    Node<Key, Value>* node = mRoot;
    while(1){
        if(node->getKey() == keyValuePair.first){ //if key exists already
            node->setValue(keyValuePair.second);    
            return;
        }
        else if(keyValuePair.first <= node->getKey()){
            if(node->getLeft() == NULL){   //insert new node into left child of current node
                Node<Key, Value>* child = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, node);
                node->setLeft(child);
                return;
            }
            else{
                node = node->getLeft();
            }
        }
        else if(keyValuePair.first >= node->getKey()){
            if(node->getRight() == NULL){   //insert new node into right child of current node
                Node<Key, Value>* child = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, node);
                node->setRight(child);
                return;
            }
            else{
                node = node->getRight();
            }
        }
    }
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::changeParentChild(Node<Key, Value>* keynode, Node<Key, Value>* replacement){ //change keynodes parent to point to replacement
    if(keynode->getParent()!= NULL){
        if(keynode->getParent()->getLeft()!= NULL && keynode->getParent()->getLeft()->getKey()==keynode->getKey()){ //if keynode is parent left
            keynode->getParent()->setLeft(replacement);    
        }
        else if(keynode->getParent()->getRight()!= NULL && keynode->getParent()->getRight()->getKey()==keynode->getKey()){ //if keynode is parent right
            keynode->getParent()->setRight(replacement);
        }
    }
}

/**
* An remove method to remove a specific key from a Binary Search Tree. The tree may not remain balanced after
* removal.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
	// TODO DONE
    //find key 
    Node<Key, Value>* keynode = internalFind(key);
    Node<Key, Value>* replacement = NULL;
    if(keynode == NULL){
        return;
    }
    // no children
    if(keynode->getLeft()==NULL && keynode->getRight()==NULL){
    }
    //only right child
    else if(keynode->getRight()!=NULL && keynode->getLeft()==NULL){
        replacement= keynode->getRight();
        replacement->setParent(keynode->getParent());
    }
    else{ //get smallestnode of right subtree
        replacement = getLargestNode(keynode->getLeft());
        if(replacement->getKey()!=keynode->getLeft()->getKey()){
            replacement->getParent()->setRight(replacement->getLeft());
            if(replacement->getLeft()!=NULL){ //replacement must have parent for earlier conditional to be true
                replacement->getLeft()->setParent(replacement->getParent());
            }
            replacement->setLeft(keynode->getLeft());
            keynode->getLeft()->setParent(replacement);
        }
        replacement->setRight(keynode->getRight());
        replacement->setParent(keynode->getParent());
        if(keynode->getRight()!= NULL){
            keynode->getRight()->setParent(replacement);
        }
    }
    changeParentChild(keynode, replacement);
    if(mRoot!= NULL && mRoot->getKey()==key){ //update root if root changed
        mRoot = replacement;
    }
    delete keynode;
    keynode=NULL;
    return;
}

/**
* A method to remove all contents of the tree and reset the values in the tree
* for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear(Node<Key, Value>* node)
{
    if(node == NULL){
        return;
    }
    clear(node->getLeft());
    clear(node->getRight());
    delete node;
    node = NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
	// TODO DONE
    if(mRoot!=NULL){
        clear(mRoot);
        mRoot=NULL;
    }
}

/**
* A helper function to find the smallest node in the tree.
*/

template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::getLargestNode(Node<Key, Value>* startnode) const{
    if(startnode == NULL){
        return NULL;
    }
    Node<Key,Value>* largest = startnode;
    while(largest->getRight()!= NULL){
        largest = largest->getRight();
    }
    return largest;
}

template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::getSmallestNode(Node<Key, Value>* startnode) const //find smallest given a starting node
{
    if(startnode == NULL){
        return NULL;
    }
    Node<Key,Value>* smallest = startnode;
    while(smallest->getLeft()!= NULL){
        smallest=smallest->getLeft();
    }
    return smallest;
}

template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::getSmallestNode() const
{
    return getSmallestNode(mRoot);
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
	// TODO DONE
    Node<Key,Value>* node = mRoot;
    while(1){
        if(node == NULL){
            return NULL;
        }
        if(node->getKey() == key){
            return node;
        }
        else if(key < node->getKey()){
            node = node->getLeft();
        }
        else if(key > node->getKey()){
            node = node ->getRight();
        }
    }
    return NULL;
}

/**
 * Return true iff the BST is an AVL Tree.
 */
template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::isBalanced(Node<Key,Value>* node) const{ //returns height or -1 if unbalanced
    int lh; int rh;
    if(node==NULL){
        return 0;
    }        
    lh = isBalanced(node->getLeft());
    if(lh == -1){
        return -1;
    }
    rh = isBalanced(node->getRight());
    if(rh == -1){
        return -1;
    }
    if(abs(lh-rh)>1){
        return -1;
    }
    else{
        return std::max(lh, rh) +1;
    }
}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
	// 
    if(isBalanced(this->mRoot)== -1){
        return false;
    }
    return true;
}


/**
 * Lastly, we are providing you with a print function, BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->mRoot)

   It will print up to 5 levels of the tree rooted at the passed node, in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
	---------------------------------------------------
	End implementations for the BinarySearchTree class.
	---------------------------------------------------
*/

#endif
