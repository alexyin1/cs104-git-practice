#include <cstddef>
#include <vector>
#include <exception>
template <class T>

class MinHeap {
    struct Node{
        T item;
        int priority;
        Node() = default;
        //Node(Node const & other) = default;
        Node(T it, int prio): item(it), priority(prio){}

        Node& operator = (const Node &node){ 
        // Check for self assignment 
            if(&node == this)
            return *this;

            if(this != &node) {
                this->item = node.item; 
                this->priority = node.priority;
            }
            return *this; 
        } 
    };
    public:
    /* Constructor that builds a d-ary Min Heap
    This should work for any d >= 2,
    but doesn't have to do anything for smaller d.*/
    MinHeap (int d){
        n = d;
        if(d<2){
            n = 2;
        }
        size = 0;
    }


    ~MinHeap (){
        for(size_t i=0; i< size; i++){
            delete nodes[i];
        }
    }

    /* adds the item to the heap, with the given priority. */
    void add (T item, int priority){
        if(size >= nodes.size()){
            nodes.push_back(new Node(item, priority));
        }
        else{
            nodes[size] = new Node(item, priority);
        }
        bubbleUp(size);
        size++;
    }

    const T & peek () const{
        if(size<=0){
            throw std::exception();
        }
        return nodes[0]->item;
    }
    /* returns the element with smallest priority.  
    Break ties however you wish.  
    Throws an exception if the heap is empty. */

    void remove (){
        //add exception for when size == 0;
        if(size<=0){
            throw std::exception();
        }
        size--;
        *nodes[0]= *nodes[size];
        delete nodes[size];
        nodes[size] = nullptr;
        if(size>0){
            sieveDown(0);
        }
    }

    //make that index nullptr
    /* removes the element with smallest priority.
    Break ties however you wish.
    Throws an exception if the heap is empty. */

    bool isEmpty (){
        return size <= 0;
        /* returns true iff there are no elements on the heap. */
    }

private:
    size_t n;  
    size_t size;
    std::vector<Node*> nodes;
    Node temp;

    void swap(size_t index1, size_t index2){
        temp = *nodes[index1];
        *nodes[index1] = *nodes[index2];
        *nodes[index2] = temp;
    }

    void bubbleUp(size_t cindex){
        if(cindex == 0){
            return;
        }
        size_t pindex = (cindex-1)/n;
        if(nodes[pindex]->priority > nodes[cindex]->priority){  //while parent priority > child priority
            swap(pindex, cindex);
            bubbleUp(pindex);
        }
    }

    void sieveDown(size_t pindex){
        if(nodes[pindex]==nullptr || (pindex*n+1) >= size){
            return;
        }
        size_t startcindex = (n*pindex) +1;
        size_t mincindex = (n*pindex) +1;
        for(size_t i=0; i<n; i++){
            if(startcindex+i < size && nodes[startcindex+i]!=nullptr){
                if(nodes[mincindex]== nullptr){
                    mincindex = startcindex+i;
                }
                else if(nodes[startcindex+i]->priority < nodes[mincindex]->priority){ //if child priority < minchild priority
                    mincindex = startcindex + i;
                }
            }
        }
        if(nodes[mincindex] != nullptr){
            if(nodes[mincindex]->priority < nodes[pindex]->priority){  //while child priority < pindex
                swap(mincindex, pindex);
                sieveDown(mincindex);
            }
        }
    }
};
//in 2-ary tree
//for any node i, parent = i/2 leftchild = 2i rightchild = 2i+1

//in n-ary tree
//for any node i, parent = i/n, kth child of i, 0<=k<n 