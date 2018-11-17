#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <cstdlib>
#include <string>
#include "rotateBST.h"

/**
* A special kind of node for an AVL tree, which adds the height as a data member, plus 
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
	// Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int getHeight() const;
    void setHeight(int height);

    // Getters for parent, left, and right. These need to be redefined since they 
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int mHeight;
};

/*
--------------------------------------------
Begin implementations for the AVLNode class.
--------------------------------------------
*/

/**
* Constructor for an AVLNode. Nodes are initialized with a height of 0.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent)
    : Node<Key, Value>(key, value, parent)
    , mHeight(0)
{

}

/**
* Destructor.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* Getter function for the height. 
*/
template<typename Key, typename Value>
int AVLNode<Key, Value>::getHeight() const
{
    return mHeight;
}

/**
* Setter function for the height. 
*/
template<typename Key, typename Value>
void AVLNode<Key, Value>::setHeight(int height)
{
    mHeight = height;
}

/**
* Getter function for the parent. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mParent);
}

/**
* Getter function for the left child. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mLeft);
}

/**
* Getter function for the right child. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mRight);
}

/*
------------------------------------------
End implementations for the AVLNode class.
------------------------------------------
*/

/**
* A templated balanced binary search tree implemented as an AVL tree.
*/
template <class Key, class Value>
class AVLTree : public rotateBST<Key, Value>
{
public:
	// Methods for inserting/removing elements from the tree. You must implement
	// both of these methods. 
    virtual void insert(const std::pair<Key, Value>& keyValuePair) override;
    void remove(const Key& key);
    bool isBalanced();

private:
	/* Helper functions are strongly encouraged to help separate the problem
	   into smaller pieces. You should not need additional data members. */
    AVLNode<Key, Value>* findImbalance(AVLNode<Key, Value>* source) const;
    void rebalance(AVLNode<Key, Value>* source);
    int isBalanced(Node<Key,Value>* node); //returns height or -1 if unbalanced
};

/*
--------------------------------------------
Begin implementations for the AVLTree class.
--------------------------------------------
*/

template<typename Key, typename Value>
bool AVLTree<Key,Value>::isBalanced(){
    if(isBalanced(this->mRoot)==-1){
        return false;
    }
    return true;
}

template<typename Key, typename Value>
int AVLTree<Key, Value>::isBalanced(Node<Key,Value>* node){ //updates height and returns -1 if unbalanced
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
    //set height
    int height = std::max(lh, rh) +1;
    dynamic_cast<AVLNode<Key, Value>*>(node)->setHeight(height);
    if(abs(lh-rh)>1){
        return -1;
    }
    else{
        return height;
    }
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::rebalance(AVLNode<Key, Value>* source){
if(source == NULL){
    return;
}

if(source->getLeft()==NULL && source->getRight()==NULL){
    return;
}

if(source->getLeft()!=NULL){
    if(source->getRight()==NULL){
        //left left case1
        if(source->getLeft()->getRight()==NULL){
            this->rightRotate(source);
            return;
        }
        //left right case2
        else if(source->getLeft()->getLeft()==NULL){
            this->leftRotate(source->getLeft());
            this->rightRotate(source);
            return;
        }
        //left right case1
        else if(source->getLeft()->getRight()->getHeight() > source->getLeft()->getLeft()->getHeight()){
            this->leftRotate(source->getLeft());
            this->rightRotate(source);
            return;
        }
        //left left case2
        else if(source->getLeft()->getLeft()->getHeight() >= source->getLeft()->getRight()->getHeight()){
            this->rightRotate(source);
            return;
        }
        
    }
    else if(source->getLeft()->getHeight() > source->getRight()->getHeight()){
        // left left case3
        if(source->getLeft()->getRight()==NULL){
            this->rightRotate(source);
            return;
        }
         //left right case4
        else if(source->getLeft()->getLeft()==NULL){
            this->leftRotate(source->getLeft());
            this->rightRotate(source);
            return;
        }
        //left right case3
        else if(source->getLeft()->getRight()->getHeight() > source->getLeft()->getLeft()->getHeight()){
            this->leftRotate(source->getLeft());
            this->rightRotate(source);
            return;
        }
        //left left case4
        else if(source->getLeft()->getLeft()->getHeight() >= source->getLeft()->getRight()->getHeight()){
            this->rightRotate(source);
            return;
        }
    }
}

if(source->getRight()!=NULL){
    if(source->getLeft()==NULL){
        // right right case1
        if(source->getRight()->getLeft()==NULL){
            this->leftRotate(source);
            return;
        }
         //right left case2
        else if(source->getRight()->getRight()==NULL){
            this->rightRotate(source->getRight());
            this->leftRotate(source);
            return;
        }
        //right left case1
        else if(source->getRight()->getLeft()->getHeight() >= source->getRight()->getRight()->getHeight()){
            this->rightRotate(source->getRight());
            this->leftRotate(source);
            return;
        }
        //right right case2
        else if(source->getRight()->getRight()->getHeight() > source->getRight()->getLeft()->getHeight()){
            this->leftRotate(source);
            return;
        }
        
    }
    else if(source->getRight()->getHeight() > source->getLeft()->getHeight()){
        // right right case3
        if(source->getRight()->getLeft()==NULL){
            this->leftRotate(source);
            return;
        }
         //right left case4
        else if(source->getRight()->getRight()==NULL){
            this->rightRotate(source->getRight());
            this->leftRotate(source);
            return;
        }
        //right left case3
        else if(source->getRight()->getLeft()->getHeight() >= source->getRight()->getRight()->getHeight()){
            this->rightRotate(source->getRight());
            this->leftRotate(source);
            return;
        }
        //right right case4
        else if(source->getRight()->getRight()->getHeight() > source->getRight()->getLeft()->getHeight()){
            this->leftRotate(source);
            return;
        }
        
    }
}

return;
}

template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::findImbalance(AVLNode<Key, Value>* node) const{
    int lh; int rh;
    if(node==NULL){
        return NULL;
    }   
    if(node->getLeft()==NULL){
        lh = 0;
    }     
    else{
        lh = node->getLeft()->getHeight();
    }
    
    if(node->getRight()==NULL){
        rh = 0;
    }     
    else{
        rh = node->getRight()->getHeight();
    }

    if(abs(lh-rh)>1){
        return node;
    }
    return findImbalance(node->getParent());
}
/**
* Insert function for a key value pair. Finds location to insert the node and then balances the tree. 
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::insert(const std::pair<Key, Value>& keyValuePair)
{
    // TODO 
    if(this->mRoot==NULL){
        this->mRoot = new AVLNode<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
        return;
    }
    Node<Key, Value>* node= this->internalFind(keyValuePair.first);
    if(node==NULL){
        node = this->mRoot;
    }
    else{
        node->setValue(keyValuePair.second);    
        return;
    }   
    while(1){
        if(keyValuePair.first <= node->getKey()){
            if(node->getLeft() == NULL){   //insert new node into left child of current node
                AVLNode<Key, Value>* child = new AVLNode<Key, Value>(keyValuePair.first, keyValuePair.second, dynamic_cast<AVLNode<Key,Value>*>(node));
                node->setLeft(child);
                if(this->isBalanced(this->mRoot)==-1){
                    rebalance(findImbalance(child));
                }
                return;
            }
            else{
                node = node->getLeft();                
            }
        }
        else if(keyValuePair.first >= node->getKey()){
            if(node->getRight() == NULL){   //insert new node into right child of current node
                AVLNode<Key, Value>* child = new AVLNode<Key, Value>(keyValuePair.first, keyValuePair.second, dynamic_cast<AVLNode<Key,Value>*>(node));
                node->setRight(child);
                if(this->isBalanced(this->mRoot)==-1){
                    rebalance(findImbalance(child));
                }
                return;
            }
            else{
                node = node->getRight();
                
            }
        }
    }
}

/**
* Remove function for a given key. Finds the node, reattaches pointers, and then balances when finished. 
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
    // TODO
    Node<Key, Value>* keynode = this->internalFind(key);
    Node<Key, Value>*imbalancedNode = NULL;
    if(keynode->getParent()!=NULL){
        imbalancedNode = keynode->getParent();
    }
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
        replacement = this->getLargestNode(keynode->getLeft());
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
    this->changeParentChild(keynode, replacement);
    if(this->mRoot!= NULL && this->mRoot->getKey()==key){ //update root if root changed
        this->mRoot = replacement;
    }
    delete keynode;
    keynode=NULL;
    if(this->isBalanced(this->mRoot)==-1){
        if(replacement!=NULL){
            rebalance(findImbalance(dynamic_cast<AVLNode<Key, Value>*>(replacement)));
        }
        else if(imbalancedNode!=NULL){
            rebalance(findImbalance(dynamic_cast<AVLNode<Key, Value>*>(imbalancedNode)));
        }
        else{
            rebalance(findImbalance(dynamic_cast<AVLNode<Key, Value>*>(this->getSmallestNode(this->mRoot))));
        }
    }
    return;
}

/*
------------------------------------------
End implementations for the AVLTree class.
------------------------------------------
*/

#endif
