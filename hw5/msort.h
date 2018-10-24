#include <vector>
#include <queue>
#include <utility>
#include <functional>
#include <iostream>
#include <algorithm>
#include <iterator>

template <class T, class Comparator>
void mergeHalfs(std::vector<T>& myArray, const int startleft, const int startright, const int endright, Comparator comp){
    T*holder = new T[endright-startleft+1];
    int leftiter = startleft;
    int rightiter = startright;
    int i = 0;
    while(leftiter<=startright-1 || rightiter<=endright){
        if(leftiter<=startright-1 &&(rightiter > endright || comp(myArray[leftiter], myArray[rightiter])==true) ){
            holder[i] = myArray[leftiter++];
        }
        else{
            holder[i]= myArray[rightiter++];
        }
        i++;
    }
    leftiter = startleft;
    i=0;
    while(leftiter <= endright){
        myArray[leftiter++] = holder[i++];
    }
}

bool elementsRemain(int *&sindexes, int *& endindexes, int k){
    for(int i=0; i<k; i++){
        if(sindexes[i]<=endindexes[i]){
            return 1;
        }
    }
    return 0;
}

template <class T, class Comparator>
T findMin(std::vector<T>& myArray,int *& sindexes, int *& endindexes, int k,  Comparator comp){  //add all possible to an array then iter through that
    int min = -1;
    for(int i=0; i<k; i++){ /
        if(sindexes[i]<=endindexes[i]){
            if(min ==-1){
                min = i;
            }  
            else if(comp(myArray[ sindexes[i]], myArray[ sindexes[min]]) == true){
                min = i;
            }
        }
    }
    return myArray[sindexes[min]++];  
}

template <class T, class Comparator>
void mergeKparts(std::vector<T>& myArray, int *&sindexes, int *&endindexes, int k,  Comparator comp){ 
    int startleft = sindexes[0]; int endright= endindexes[k-1];
    T* holder = new T[endright-startleft+1]; 
    int count = 0;// should equal 
    while(startleft + count <= endright){
        holder[count++] = findMin(myArray, sindexes, endindexes, k, comp);
    }
    count = 0;
    while(startleft <= endright){
        myArray[startleft++] = holder[count++];
    }
}

template <class T, class Comparator>
void mergetwoSort(std::vector<T>& myArray, const int startleft,const int endright, Comparator comp){
    if(startleft>=endright){
        return;
    }
    int middle = (endright+startleft)/2;
    mergetwoSort(myArray, startleft, middle, comp);
    mergetwoSort(myArray, middle+1, endright, comp);
    mergeHalfs(myArray, startleft, middle+1, endright, comp);
}

template <class T, class Comparator>
void mergeSort(std::vector<T>& myArray, int startleft, int endright, int k,  Comparator comp){
    if(startleft>=endright){
        return;
    }
    int partsize = (endright+1-startleft)/k; //want the size/k so +1
    if(partsize<1){ 
        mergetwoSort(myArray, startleft, endright, comp);
        return;
    }
    int* sindexes = new int[k];
    int* endindexes = new int[k]; // there are k starting and k ending points 
    for(int i=0; i<k-1; i++){ //first k-1 elements are all size = partsize
        sindexes[i] = startleft + (i*partsize); //start     
        endindexes[i] = sindexes[i]+ partsize -1;  //end 
        mergeSort(myArray, sindexes[i], endindexes[i], k, comp);   
    }  
    sindexes[k-1] = startleft+(k-1)*partsize;
    endindexes[k-1] = endright;
    mergeSort(myArray, sindexes[k-1], endindexes[k-1], k, comp);
    mergeKparts(myArray, sindexes, endindexes, k, comp); 
    delete [] sindexes;
    delete [] endindexes;   
}

template <class T, class Comparator>
void mergeSort(std::vector<T>& myArray, int k,  Comparator comp){
    //do k way mergeSort, and then on the k sorted arrays do k merge 
    if(myArray.size()==0){
        return;
    }
    if(k == 2){
        mergetwoSort(myArray, 0, myArray.size()-1, comp);
        return;
    }
    mergeSort(myArray, 0, myArray.size()-1, k, comp); 
}

		//dont want vectors as private variables, because each mergeSort call requires maniupulating the vectors



