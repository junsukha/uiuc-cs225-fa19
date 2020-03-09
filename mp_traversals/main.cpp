
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  // PNG png;      png.readFromFile("tests/pacman.png");
  //
  // FloodFilledImage image(png);
  // DFS dfs(png, Point(0, 0), 0.2);
  // HSLAPixel color(231, 1, 0.5);
  // SolidColorPicker solid(color);
  // image.addFloodFill( dfs, solid );
  //
  // Animation animation = image.animate(1000);


  PNG png;
  png.readFromFile("i.png");

  FloodFilledImage image(png);

  DFS dfs(png, Point(0, 0), 0.05);
  RainbowColorPicker rainbow(0.05);
  //HSLAPixel colorRed(231, 1, 0.5);//red
  //MyColorPicker my2(colorRed);
  image.addFloodFill( dfs, rainbow );

  //
  BFS bfs(png, Point(40, 40), 0.05);
  //HSLAPixel colorBlack(216, 1, 0.0);//black  luminance = 0
  //MyColorPicker my1(colorBlack);
  MyColorPicker my1;
  image.addFloodFill( bfs, my1 );

  Animation animation = image.animate(1000);
  //
   PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
   lastFrame.writeToFile("myFloodFill.png");
   animation.write("myFloodFill.gif");



  return 0;
}
