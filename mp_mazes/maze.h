/* Your code here! */
#include <vector>
#include "cs225/PNG.h"
#pragma once
class SquareMaze{
private:
  int _width;
  int _height;
  std::vector<bool> rWall;
  std::vector<bool> dWall;
  int largestIdx;
  int dest;
public:
  cs225::PNG* drawCreativeMaze();
  void makeMaze (int width, int height);
	void setWall(int x,	int y, int dir,	bool exists);
  std::vector<int> solveMaze();
  cs225::PNG* drawMazeWithSolution();
  cs225::PNG* drawMaze() const;
  bool canTravel(int x, int y, int dir) const;
};
