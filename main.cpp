#include <iostream>
#include <string>
#include "floodfill/floodfill.h"
#include "floodfill/queue.h"
#include "maze.h"
#include "robot.h"

int main() {
    Maze maze;
    Robot robot(maze); 
    maze.display(); 
    Floodfill floodfill(maze); 
    robot.solveMaze(floodfill);
    
    return 0;
}

