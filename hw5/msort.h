#include <vector>
#include <queue>
#include <utility>
#include <functional>
#include <iostream>
#include <algorithm>
#include <iterator>

void mergeHalfs(std::vector<int>& myArray, const int startleft, const int startright, const int endright){
    std::queue<int> holder;
    int leftiter = startleft;
    int rightiter = startright;
    while(leftiter<=startright-1 || rightiter<=endright){
        if(leftiter<=startright-1 &&(rightiter > endright || myArray[leftiter] < myArray[rightiter])){
            holder.push(myArray[leftiter++]);
        }
        else{
            holder.push(myArray[rightiter++]);
        }
    }
    leftiter = startleft;
    while(holder.size()>0){
        myArray[leftiter++]=holder.front();
        holder.pop();
    }
}

bool elementsRemain(int *&sindexes, int *& endindexes, int k){
    for(int i=0; i<k; i++){
        if(sindexes[i]<=endindexes[i]){
            return 1;
        }
    }
    return 0;
    //return std::equal(begin(sindexes), end(sindexes), begin(endindexes));
    // while(i< (2*k)-1){
    //     if(indexes[i-1]<=indexes[i]){
    //       return 0;
    //     }    
    //     i+=2;
    // }
    // return 1; 
}

int findMin(std::vector<int>& myArray,int *& sindexes, int *& endindexes, int k){  //add all possible to an array then iter through that
    std::vector<int> legalindexes; int min;
    for(int i=0; i<k; i++){ //first k-1 elements are all size = partsize  
        if(sindexes[i]<=endindexes[i]){
            legalindexes.push_back(i);
        }
        min = legalindexes[0];
        for(size_t i=0; i<legalindexes.size(); i++){
            if (myArray[sindexes[legalindexes[i]]] < myArray[sindexes[min]]){
                min = i;
            }
        }
    }  
    sindexes[min] = sindexes[min]+1; //update indexes
    // std::cout<< myArray[sindexes[min]-1] << std::endl;
    return myArray[sindexes[min]-1];  //issue: ++
}

void mergeKparts(std::vector<int>& myArray, int *&sindexes, int *&endindexes, int k){ 
    int startleft = sindexes[0]; int endright= endindexes[k-1];
    std::queue<int> holder; int count = 0;// should equal 
    std::cout<< "before merge: ";
    for(int i=startleft; i<= endright; i++){
        std::cout << myArray[i] << " ";
    }
    std::cout<<std::endl;
    std::cout<< "Startindexes: ";
    for(int i=0; i< k; i++){
        std::cout << sindexes[i] << " "<< endindexes[i] << ", ";
    }
    std::cout<<std::endl;
    std::cout<< "Correct count: " << endright-startleft << std::endl;
    std::cout << std::endl;
    while(elementsRemain(sindexes, endindexes, k)){
        holder.push(findMin(myArray, sindexes, endindexes, k));
        std::cout<< "indexes: ";
        for(int i=0; i< k; i++){
            std::cout << sindexes[i] << " " << endindexes[i] << ", ";
        }
        std::cout<<std::endl;
        count++;
    }
    for(int i= startleft; i<=endright;i++){
        myArray[i]= holder.front();
        holder.pop();
    }
    std::cout<< "after merge: ";
    for(int i=sindexes[0]; i<= endindexes[k-1]; i++){
        std::cout << myArray[i] << " ";
    }
     std::cout<< "Actual count: " << count << std::endl;
    std::cout << std::endl;
    //deallocate indexes
}


void mergetwoSort(std::vector<int>& myArray, const int startleft,const int endright){
    if(startleft>=endright){
        return;
    }
    int middle = (endright+startleft)/2;
    mergetwoSort(myArray, startleft, middle);
    mergetwoSort(myArray, middle+1, endright);
    mergeHalfs(myArray, startleft, middle+1, endright);
}

void mergeSort(std::vector<int>& myArray, int startleft, int endright, int k){
    if(startleft>=endright){
        return;
    }
    int partsize = (endright+1-startleft)/k; //want the size/k,t the indexes so +1
    if (partsize<=1){ //if k > endright-startleft+1
        mergetwoSort(myArray, startleft, endright);
        return;
    }
    int* sindexes = new int[k];
    int* endindexes = new int[k]; // there are k starting and k ending points 
    std::cout<<"starting: ";
    for(int i=0; i<k-1; i++){ //first k-1 elements are all size = partsize
        sindexes[i] = startleft + (i*partsize); //start     
        endindexes[i] = sindexes[i]+ partsize;  //end    
        std::cout << sindexes[i] << ", " << endindexes[i]<<" ,";     
    }  
    sindexes[k-1] = startleft+(k-1)*partsize-1;
    endindexes[k-1] = endright;
    std::cout <<sindexes[k-1] << ", " << endindexes[k-1]<<std::endl; 
    for(int j=0; j<k; j++){
        mergeSort(myArray, sindexes[j], endindexes[j], k);
    }
    mergeKparts(myArray, sindexes, endindexes, k); 
    delete [] sindexes;
    delete [] endindexes;   
}

void mergeSort(std::vector<int>& myArray, int k){
    //do k way mergeSort, and then on the k sorted arrays do k merge 
    if(myArray.size()==0){
        return;
    }
    if(k == 2){
        mergetwoSort(myArray, 0, myArray.size()-1);
        return;
    }
    int* sindexes = new int[k];
    int* endindexes = new int[k]; // there are k starting and k ending points 
    int partsize = (myArray.size())/k; //want the size/k,t the indexes so +1
    //     std::cout<<"starting: ";
    for(int i=0; i<k-1; i++){ //first k-1 elements are all size = partsize
        sindexes[i] = (i*partsize); //start     
        endindexes[i] = sindexes[i]+ partsize-1;  //end    
    //    std::cout << sindexes[i] << ", " << endindexes[i]<<" ,";     
    }  
    sindexes[k-1] = (k-1)*partsize;
    endindexes[k-1] = myArray.size()-1;
    //std::cout <<sindexes[k-1] << ", " << endindexes[k-1]<<std::endl; 
    for(int j=0; j<k; j++){
        mergeSort(myArray, sindexes[j], endindexes[j], k);
    }
    std::cout<<"starting: ";
    for(int i=0; i<k; i++){ //first k-1 elements are all size = partsize
        std::cout << sindexes[i] << ", " << endindexes[i]<<" ,";     
    }  
    mergeKparts(myArray, sindexes, endindexes, k); 
    delete [] sindexes;
    delete [] endindexes;
}

		//dont want vectors as private variables, because each mergeSort call requires maniupulating the vectors



