#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main() {
    SquareMaze maze;
    maze.makeMaze(100, 100);
    cs225::PNG * result = maze.drawCreativeMaze();
    result->writeToFile("creative.png");

    delete result;
    return 0;
}
