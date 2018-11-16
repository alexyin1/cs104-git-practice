//#ifndef ROTATEBST_H
#define ROTATEBST_H

#include "bst.h"

template <typename Key, typename Value>
class rotateBST :public BinarySearchTree<Key, Value>{
public:
    rotateBST(); //TODO
    virtual ~rotateBST(); //TODO
    bool sameKeys(const rotateBST& t2) const;
    void transform(rotateBST& t2) const;
    bool operator==(const rotateBST& t2) const;

protected:
    void leftRotate(Node<Key, Value>* r); 
    void rightRotate(Node<Key, Value>* r);
    void changeParentChild(Node<Key, Value>* r, Node<Key, Value>* replacement);
private:
    bool checkSame(Node<Key, Value>* n1, Node<Key, Value>*n2) const;
    void firstTransform(Node<Key, Value>* node);   //changes bst to sorted linkedlist with min val at root
    void secondTransform(Node<Key, Value>* t1node, Node<Key, Value>* t2node); // performs rotations to get to right val
};


template<typename Key, typename Value>
rotateBST<Key, Value>::rotateBST(){}

template<typename Key, typename Value>
rotateBST<Key, Value>::~rotateBST(){}

template<typename Key, typename Value>
void rotateBST<Key, Value>::changeParentChild(Node<Key, Value>* r, Node<Key, Value>* replacement){ //change rs parent to point to replacement
    if(r->getParent()!= NULL){
        if(r->getParent()->getLeft()!= NULL && r->getParent()->getLeft()->getKey()==r->getKey()){ //if r is parent left
            r->getParent()->setLeft(replacement);    
        }
        else if(r->getParent()->getRight()!= NULL && r->getParent()->getRight()->getKey()==r->getKey()){ //if r is parent right
            r->getParent()->setRight(replacement);
        }
    }
}

template<typename Key, typename Value>
bool rotateBST<Key, Value>::checkSame(Node<Key, Value>* n1, Node<Key, Value>*n2) const{
    bool ltrue; bool rtrue;
    if(n1== NULL && n2== NULL){
        return true;
    }
    if(n1==NULL && n2 != NULL || n1!=NULL && n2 == NULL ){
        return false;
    }
    if(n1->getKey()!= n2->getKey()){
        return false;
    }
    ltrue = checkSame(n1->getLeft(), n2->getLeft());
    if(ltrue == false){
        return false;
    }
    rtrue = checkSame(n1->getRight(), n2->getRight());
    if(rtrue == false){
        return false;
    }
    return ltrue&&rtrue;

}

template<typename Key, typename Value>
bool rotateBST<Key, Value>::operator==(const rotateBST& t2) const{
    if(this == &t2){      // Same object?
        return true;
    }
    return checkSame(this->mRoot, t2.mRoot);
}

template<typename Key, typename Value>
bool rotateBST<Key, Value>::sameKeys(const rotateBST& t2) const{
    typename BinarySearchTree<Key, Value>::iterator it = this->begin();
    typename BinarySearchTree<Key, Value>::iterator it2 = t2.begin();
    if(t2.end() != this->end()){
        return false;
    }
    while(it!= this->end()|| it2!= t2.end()){
        if(it->first != it2->first){//if different min keys not same set of keys  //iterator class does inorder traversal, so always min to max order
            return false;
        }
        ++it;
        ++it2;
    }
    if(it!= this->end() || it2!= t2.end()){
        return false; //if sizes are different, then must be different sets
    }
    return true;
}

template<typename Key, typename Value>
void rotateBST<Key, Value>::secondTransform(Node<Key, Value>* t1node, Node<Key, Value>* t2node){
    if(t1node == NULL){
        return;
    }
    if(t1node->getKey()== t2node->getKey()){
        secondTransform(t1node->getLeft(), t2node->getLeft());
        secondTransform(t1node->getRight(), t2node->getRight());
    }
    else if(t2node->getKey() < t1node->getKey()){
        leftRotate(t2node);
        secondTransform(t1node, t2node->getParent());
    }
    else if(t2node->getKey() > t1node->getKey()){
        rightRotate(t2node);
        secondTransform(t1node, t2node->getParent());
    }
    return;
}

template<typename Key, typename Value>
void rotateBST<Key, Value>::firstTransform(Node<Key, Value>* node){
// Perform right rotations on the root node of t2 until it has no left child.
    if(node==NULL){
        return;
    }
    while(node->getLeft()!=NULL){
        rightRotate(node);
        node = node->getParent();
    }
// // Recursively move to the right child and repeat the above operation.
    firstTransform(node->getRight());
// This should produce a tree which is effectively a linked list.
}

template<typename Key, typename Value>
void rotateBST<Key, Value>::transform(rotateBST& t2) const{
    if(this->sameKeys(t2)){
        t2.firstTransform(t2.mRoot);
        t2.secondTransform(this->mRoot, t2.mRoot);  //never change tree 1 relations        
    }
    return;
}

template<typename Key, typename Value>
void rotateBST<Key, Value>::leftRotate(Node<Key, Value>* r){
    if(r->getRight()==NULL){
        return;
    }
    Node<Key, Value>* replacement = r->getRight();
    r->setRight(replacement->getLeft());
    if(replacement->getLeft()!=NULL){
        replacement->getLeft()->setParent(r);
    }
    changeParentChild(r, replacement);
    replacement->setLeft(r);
    replacement->setParent(r->getParent());
    r->setParent(replacement);
    if(this->mRoot!= NULL && this->mRoot->getKey()==r->getKey()){ //update root if root changed
        this->mRoot = replacement;
    }
}

template<typename Key, typename Value>
void rotateBST<Key, Value>::rightRotate(Node<Key, Value>* r){
    if(r->getLeft()==NULL){
        return;
    }
    Node<Key, Value>* replacement = r->getLeft();
    r->setLeft(replacement->getRight());
    if(replacement->getRight()!=NULL){ 
        replacement->getRight()->setParent(r);
    }  
    changeParentChild(r, replacement);
    replacement->setParent(r->getParent());
    replacement->setRight(r);
    r->setParent(replacement);
    if(this->mRoot!= NULL && this->mRoot->getKey()==r->getKey()){ //update root if root changed
        this->mRoot = replacement;
    }
}