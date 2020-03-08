/* Your code here! */
#include "dsets.h"
#include <cmath>
void DisjointSets::addelements(int num){
  for(int i = 0; i < num; i++){
    v.push_back(-1);
  }
}

int DisjointSets::find(int elem){
  if(v[elem] < 0)
    return elem;
  else
    return find(v[elem]);
}

void DisjointSets::setunion(int a, int b){
  if(abs(v[find(a)]) > abs(v[find(b)])){
    v[find(a)] += v[find(b)];
    v[find(b)] = find(a);
  }
  else{
    v[find(b)] += v[find(a)];
    v[find(a)] = find(b);
  }
}
int DisjointSets::size(int elem){
  return abs(v[find(elem)]);
}
