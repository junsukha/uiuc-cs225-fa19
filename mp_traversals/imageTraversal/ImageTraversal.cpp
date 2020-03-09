#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  traversal = nullptr;
  endCheck = true;
  //cs225::PNG png;
  //Point start;
  //double tolerance;
  //std::vector<Point> v;
  //std::vector<vector<bool>> visited;
  //Point(-1,-1) is acting as a null so that when use .end(); will return this point
  //point = Point(-1, -1);
}
//check the parameters that iterator need to use
//custom constructor
ImageTraversal::Iterator::Iterator(PNG png, Point start, double tolerance, ImageTraversal* traversal){
  this->png = png;
  this->start = start;
  this->tolerance = tolerance;
  this->traversal = traversal;
  point = start;//????
  //std::cout<<"test"<<std::endl;
  //check Big O
  for(unsigned i = 0; i < png.width() * png.height(); i++){
      visited.push_back(false);
    }
  endCheck = false;
  //std::cout << "yaya" << std::endl;
  //add a start point if it meets requirements
  if(checkValid(start)){
    traversal->add(start);
    visited[start.x + start.y * png.width()] = true;

    //v.push_back(start);
  }
  else endCheck = true;
}
/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  //
  Point toRight = Point(point.x + 1, point.y);
  Point toBelow = Point(point.x, point.y + 1);
  Point toLeft = Point(point.x-1, point.y );
  Point toAbove = Point(point.x, point.y-1);
  // HSLAPixel startPixel = png.getPixel(start.x, start.y);
  // HSLAPixel toRight = png.getPixel(start.x + 1, start.y);
  // HSLAPixel toBelow = png.getPixel(start.x, start.y + 1);
  // HSLAPixel toLeft = png.getPixel(start.x - 1, start.y);
  // HSLAPixel toAbove = png.getPixel(start.x - 1, start.y);

  //only add the points there arn't visited, satisfy tolerance, etc
  if(checkValid(toRight))
    traversal->add(toRight);
  if(checkValid(toBelow))
  //point.x < png.width() && point.y < png.height()
    traversal->add(toBelow);
  if(checkValid(toLeft))
    traversal->add(toLeft);
  if(checkValid(toAbove))
    traversal->add(toAbove);

  if(traversal->empty()){
    endCheck = true;
    return *this;


  }

  //next point traversal going to visit
  point = traversal->pop();
  while(visited[point.x + point.y * png.width()]){
    if(traversal->empty()){
      endCheck = true;
      return *this;
    }
    point = traversal->pop();
  }

  //
  // if(visited[point.x + point.y * png.width()])
  //   point = traversal->pop();
  //
  // while(visited[point.x + point.y * png.width()]){
  //
  //     point = traversal->pop();
  //     //temp = traversal->peek();
  //
  //
  //   //temp = traversal->peek();
  // }

  //traversal->add()//already added
  visited[point.x + point.y * png.width()] = true;


  return *this;//iterator?
}

  //Point point =
  //vector
  // if ((tolerance >= calculateDelta(png.getPixel(start.x, start.y), png.getPixel(wantToVisit.x, wantToVisit.y)) && !visited[point] && png >=0 && point.x <= width && point.y >=0 && point.y <=height){
  //   add(point);
  //   point.x += 1;
  // }
  //
  // else if ((tolerance >= calculateDelta(point.x + 1 , point.y)) && !visited[point.x + 1][point.y] && point.x >=0 && point.x <= width && point.y >=0 && point.y <=height){
  //   add(point);
  //point.x < png.width() && point.y < png.height()
  // }
  // else if ((tolerance >= calculateDelta(point.x - 1 , point.y)) && !visited[point.x - 1][point.y] && point.x >=0 && point.x <= width && point.y >=0 && point.y <=height){
  //   add(point);
  //   point.x -= 1;
  // }
  // else if ((tolerance >= calculateDelta(point.x + 1 , point.y)) && !visited[point.x + 1][point.y] && point.x >=0 && point.x <= width && point.y >=0 && point.y <=height){
  //   add(point);
  // }





bool ImageTraversal::Iterator::checkValid(Point& point){
  //start = Point(start.x, start.y);
  if(point.x >= png.width())/// -1 is bigger than png.wideth
    return false;
  if(point.y >= png.height())
    return false;


  HSLAPixel startPixel = png.getPixel(start.x, start.y);
  HSLAPixel visitPixel = png.getPixel(point.x, point.y);
  // Point toRight = Point(start.x + 1, start.y);
  // Point toBelow = Point(start.x, start.y + 1);
  // Point toLeft = Point(start.x, start.y - 1);
  // Point toAbove = Point(start.x - 1, start.y);

  //checking if the point is already in v queue or stack
  // for(unsigned i = 0; i < v.size(); ++i){
  //   if(v[i] == point)
  //     return false;
  // }

  if((calculateDelta(startPixel, visitPixel) <= tolerance))// && (!visited[point.x + point.y * png.width()]))
    return true;

  return false;
}

// check visited
// if ((tolerance >= calculateDelta(point.x , point.y)) && !visited[point.x][point.y] && point.x >=0 && point.x <= width && point.y >=0 && point.y <=height){
// v.push_back(point);
//   visited[point.x][point.y] = true;
// }


/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 // */  //bool thisEmpty = false;
 //  bool otherEmpty = false;
 //
 //  if (traversal == NULL) { thisEmpty = true; }
 //  if (other.traversal == NULL) { otherEmpty = true; }
 //
 //  if (!thisEmpty)  { thisEmpty = traversal->empty(); }
 //  if (!otherEmpty) { otherEmpty = other.traversal->empty(); }
 //
 //  if (thisEmpty && otherEmpty) return false; // both empty then the traversals are equal, return true
 //  else if ((!thisEmpty)&&(!otherEmpty)) return (traversal != other.traversal); //both not empty then compare the traversals
 //  else return true;
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */

  return point;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */

  return endCheck != other.endCheck;
  // bool thisEmpty = false;
  // bool otherEmpty = false;
  //
  // if (traversal == NULL) { thisEmpty = true; }
  // if (other.traversal == NULL) { otherEmpty = true; }
  //
  // if (!thisEmpty)  { thisEmpty = traversal->empty(); }
  // if (!otherEmpty) { otherEmpty = other.traversal->empty(); }
  //
  // if (thisEmpty && otherEmpty) return false; // both empty then the traversals are equal, return true
  // else if ((!thisEmpty)&&(!otherEmpty)) return (traversal != other.traversal); //both not empty then compare the traversals
  // else return true; // one is empty while the other is not, return true



  // Point temp = other.point;
  // unsigned thisX = this->point.x;
  //
  // return (this->point.x != temp.x) && (this->point.y != temp.y);
  //this->point != temp;
}
