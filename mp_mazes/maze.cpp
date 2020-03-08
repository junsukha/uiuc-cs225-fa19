/* Your code here! */
#include "maze.h"
#include "dsets.h"
#include <stdlib.h>
#include <queue>
#include <vector>
#include <iostream>

#include <map>
#include <cstdlib>
#include <algorithm>
using namespace std;

void SquareMaze::makeMaze(int width, int height) {
  _width = width;
  _height = height;
  for (int i = 0; i < _width * _height; i++) {
    dWall.push_back(true);
    rWall.push_back(true);
  }

  DisjointSets dsets;
  dsets.addelements(height * width);


  int bound = 0;

  while (bound < width * height - 1) {
    int randX = rand() % width;
    int randY = rand() % height;
    bool randR = rand() % 2;
    int currIdx = randX + randY * width;
    int currIdxRight = randX + 1 + randY * width;
    int currIdxDown =randX + (randY + 1) * width;

    if (randR) {
      if (randX < width - 1 && rWall[randX + randY * width] &&
        dsets.find(currIdx) != dsets.find(currIdxRight)) {
          rWall[randX + randY * width] = false;
          dsets.setunion(dsets.find(currIdx), dsets.find(currIdxRight));
          bound++;
        }
      } else {
        //break down wall
        if (randY < height - 1 && dWall[randX + randY * width] &&
          dsets.find(currIdx) != dsets.find(currIdxDown)) {
            dWall[randX + randY * width] = false;
            dsets.setunion(dsets.find(currIdx), dsets.find(currIdxDown));
            bound++;
          }
        }
      }
    }



//
// dir = 0 represents a rightward step (+1 to the x coordinate)
// dir = 1 represents a downward step (+1 to the y coordinate)
// dir = 2 represents a leftward step (-1 to the x coordinate)
// dir = 3 represents an upward step (-1 to the y coordinate)

bool SquareMaze::canTravel(int x, int y, int dir) const{

  switch(dir){
    case 0: //right
      return rWall[y * _width + x] == false;
    case 1: //down
      return dWall[y * _width + x] == false;
    case 2: //left
      return (x != 0) && (rWall[y * _width + x - 1] == false);
    case 3: //up
      return (y != 0) && (dWall[y * _width + x - _width] == false);
  }
  return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {
   // if (x < 0 || x >= width || y < 0 || y >= height ) return;
   if (dir == 0) {
     rWall[x + y * _width] = exists;
   } else if (dir == 1) {
     dWall[x + y * _width] = exists;
   }
 }

std::vector<int> SquareMaze::solveMaze() {
  std::vector<int> result;
  std::vector<int> path;
  std::vector<int> dist;
  path.push_back(0);
  //for(int i = 1; i < _width * _height; i++)
  for(int i = 1; i < _width * _height; i++){
    path.push_back(-1);
    dist.push_back(0);
  }
  int x;
  int y;

  std::queue<int> q;
  int curr;
  q.push(0);

  while(!q.empty()){
    //std::cout << "check" << std::endl;
    curr = q.front();
    q.pop();
    x = curr % _width;
    y = curr / _width;
    if(canTravel(x, y, 0)){//right
      //curr = q.front();
      //q.pop();
      if(path[curr+1] == -1){
        q.push(curr+1);
        path[curr+1] = curr;
        dist[curr+1] = dist[curr] + 1;
      }
    }
    if(canTravel(x, y, 1)){//down
      if(path[curr + _width] == -1){
        q.push(curr + _width);
        path[curr + _width] = curr;
        dist[curr+_width] = dist[curr] + 1;
      }
    }
    if(canTravel(x, y, 2)){//left
      if(path[curr - 1] == -1){
        q.push(curr-1);
        path[curr-1] = curr;
        dist[curr-1] = dist[curr] + 1;
      }
    }
    if(canTravel(x, y, 3)){//up
      if(path[curr - _width] == -1){
        q.push(curr - _width);
        path[curr - _width] = curr;
        dist[curr - _width] = dist[curr] + 1;
      }
    }
  }//while
  //setting the largest path
  largestIdx = _width * (_height-1);
  for(int k = 0; k < _width; k++){
    if(dist[_width * (_height - 1) + k] > dist[largestIdx]){
      largestIdx = _width * (_height - 1) + k;
    }
  }
  dest = largestIdx;
  curr = dest;
  while(curr != 0){

    if(path[curr] == curr - 1){//the previous idx is left, i.e., moved to right
      result.push_back(0);
    }
    if(path[curr] == curr - _width){//moved to down
      result.push_back(1);
    }
    if(path[curr] == curr + 1){//moved to left
      result.push_back(2);
    }
    if(path[curr] == curr + _width){
      result.push_back(3);
    }
    curr = path[curr];
  }
  std::reverse(result.begin(), result.end());

  return result;


}


cs225::PNG * SquareMaze::drawMaze() const {
   int pH = _height * 10 + 1;
   int pW = _width * 10 + 1;
   cs225::PNG* unsolved = new cs225::PNG(pW, pH);
   for (int i = 0; i < pH; i++) {
     cs225::HSLAPixel& pixel = unsolved->getPixel(0, i);
     // pixel->h = 0.0;
     pixel.l = 0.0;
     // pixel->s = 0.0;
     // pixel->a = 1.0;
   }
   for (int i = 10; i < pW; i++) {
     cs225::HSLAPixel& pixel = unsolved->getPixel(i, 0);
     pixel.l = 0.0;
   }
   for (int x = 0; x < _width; x++) {
     for (int y = 0; y < _height; y++) {
       if (rWall[x + y * _width]) {
         for (int i = 0; i < 11; i++) {
           cs225::HSLAPixel& pixel = unsolved->getPixel(10 * x + 10, 10 * y + i);
           pixel.l = 0.0;
         }
       }
       if (dWall[x + y * _width]) {
         for (int i = 0; i < 11; i++) {
           cs225::HSLAPixel& pixel = unsolved->getPixel(10 * x + i, 10 * y + 10);
           pixel.l = 0.0;
         }
       }
     }
   }
   return unsolved;
 }


cs225::PNG * SquareMaze::drawMazeWithSolution() {
   cs225::PNG* unsolved = drawMaze();
   std::vector<int> dirs = solveMaze();
   int x = 5;
   int y = 5;
   for (unsigned i = 0; i < dirs.size(); i++) {
     if (dirs[i] == 0) {
       for (int i = 0; i < 10; i++) {
         cs225::HSLAPixel& pixel = unsolved->getPixel(x, y);
         pixel.h = 0;
         pixel.s = 1;
         pixel.l = 0.5;
         x += 1;
       }
     } else if (dirs[i] == 1) {
       for (int i = 0; i < 10; i++) {
         cs225::HSLAPixel& pixel = unsolved->getPixel(x, y);
         pixel.h = 0;
         pixel.s = 1;
         pixel.l = 0.5;
         y += 1;
       }
     } else if (dirs[i] == 2) {
       for (int i = 0; i < 10; i++) {
         cs225::HSLAPixel& pixel = unsolved->getPixel(x, y);
         pixel.h = 0;
         pixel.s = 1;
         pixel.l = 0.5;
         x -= 1;
       }
     } else if (dirs[i] == 3) {
       for (int i = 0; i < 10; i++) {
         cs225::HSLAPixel& pixel = unsolved->getPixel(x, y);
         pixel.h = 0;
         pixel.s = 1;
         pixel.l = 0.5;
         y -= 1;
       }
     }
   }
   cs225::HSLAPixel& p = unsolved->getPixel(x, y);
   p.h = 0.0;
   p.s = 1.0;
   p.l = 0.5;
   p.a = 1.0;
   x -= 4;
   y += 5;
   for (int i = 0; i < 9; i++) {
     cs225::HSLAPixel& pixel = unsolved->getPixel(x, y);
     // pixel->h = 0.0;
     // pixel->s = 0.0;
     pixel.l = 1.0;
     pixel.a = 1.0;
     x += 1;
   }
   return unsolved;
 }
cs225::PNG* SquareMaze::drawCreativeMaze(){
   cs225::PNG* unsolved = drawMaze();
   std::vector<int> dirs = solveMaze();
   int x = 5;
   int y = 5;
   for (unsigned i = 0; i < dirs.size(); i++) {
     if (dirs[i] == 0) {
       for (int i = 0; i < 10; i++) {
         cs225::HSLAPixel& pixel = unsolved->getPixel(x, y);
         pixel.h = 216;
         pixel.s = 1;
         pixel.l = 0.5;
         x += 1;
       }
     } else if (dirs[i] == 1) {
       for (int i = 0; i < 10; i++) {
         cs225::HSLAPixel& pixel = unsolved->getPixel(x, y);
         pixel.h = 100;
         pixel.s = 1;
         pixel.l = 0.5;
         y += 1;
       }
     } else if (dirs[i] == 2) {
       for (int i = 0; i < 10; i++) {
         cs225::HSLAPixel& pixel = unsolved->getPixel(x, y);
         pixel.h = 11;
         pixel.s = 1;
         pixel.l = 0.5;
         x -= 1;
       }
     } else if (dirs[i] == 3) {
       for (int i = 0; i < 10; i++) {
         cs225::HSLAPixel& pixel = unsolved->getPixel(x, y);
         pixel.h = 1;
         pixel.s = 1;
         pixel.l = 0.5;
         y -= 1;
       }
     }
   }
   cs225::HSLAPixel& p = unsolved->getPixel(x, y);
   p.h = 0.0;
   p.s = 1.0;
   p.l = 0.5;
   p.a = 1.0;
   x -= 4;
   y += 5;
   for (int i = 0; i < 9; i++) {
     cs225::HSLAPixel& pixel = unsolved->getPixel(x, y);
     // pixel->h = 0.0;
     // pixel->s = 0.0;
     pixel.l = 1.0;
     pixel.a = 1.0;
     x += 1;
   }
   return unsolved;
 }
