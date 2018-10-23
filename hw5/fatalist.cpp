#include <algorithm>
#include <vector>
#include <iostream> 
#include <utility> 



bool secondCompare(const std::pair<int, int>& firstElem, const std::pair<int, int>& secondElem) {
  return firstElem.second < secondElem.second ||
        (firstElem.first < secondElem.first && firstElem.second == secondElem.second); //tie breaker is .first values
}


bool FatalistHypothesis(std::vector<std::pair<int,int> > grades){
    if(grades.empty()){
        return 0;
    }
    std::vector<std::pair<int,int> > discreetsorted;
    discreetsorted = grades;
    std::sort(grades.begin(), grades.end());
    std::sort(discreetsorted.begin(), discreetsorted.end(), secondCompare);
    return (grades == discreetsorted);
}
