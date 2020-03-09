#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"


/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 *
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) {
  /** @todo [Part 1] */
  this->start = start;
  this->png = png;
  this->tolerance = tolerance;
  this->add(start);
  //std::cout<<"DFS ctor"<<std::endl;
  // for(unsigned i = 0; i < png.width() * png.height(); i++){
  //     visited.push_back(false);
  //   }
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  //DFS(const PNG & png, const Point & start, double tolerance);
  //ImageTraversal::Iterator::Iterator(Png png, Point start, double tolerance, ImageTraversal* traversal)
  //std::cout<<"DFS begin"<<std::endl;
  return ImageTraversal::Iterator(png, start, tolerance, this);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  //std::cout<<"DFS end"<<std::endl;
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
  //check visited
  //if ((tolerance >= calculateDelta(point.x , point.y)) && !visited[point.x][point.y] && point.x >=0 && point.x <= width && point.y >=0 && point.y <=height){
  v.push_back(point);
  //std::cout<<"DFS add"<<std::endl;
    //visited[point.x][point.y] = true;
  //}


}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
  //std::cout<<"DFS pop"<<std::endl;
  Point temp = v.back();
  v.pop_back();
  return temp;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  return v.back();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  return v.empty();
}
