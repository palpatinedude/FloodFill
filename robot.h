// This header file defines the Robot class used to navigate through a maze.
// The Robot interacts with a Maze and uses a Floodfill algorithm to find target cell.
// It keeps track of its position and can move, solve the maze, and return to the start.

#ifndef ROBOT_H  
#define ROBOT_H

#include "maze.h"  
#include "cell.h"  
#include <iostream>  

class Floodfill;  
class Maze;       

class Robot {
private:
    Maze& maze;           // Reference to the maze the robot will navigate
    Cell* currentCell;    // Pointer to the robot's current cell in the maze
    Cell* position;       // Another pointer to the robot's current position (possibly used differently)

public:
    // Constructor: takes a reference to a Maze object to initialize the robot
    Robot(Maze& maze);

    // Uses the Floodfill algorithm to solve the maze
    void solveMaze(Floodfill& floodfill);

    // Uses Floodfill to return the robot to the starting cell
    void returnToStart(Floodfill& floodfill);

    // Moves the robot to the specified next cell
    void move(Cell* nextCell);

    // Returns the current position of the robot
    Cell* getPosition() const;

    // Sets the robot’s position to a new cell
    void setPosition(Cell* newPos);
};

#endif // ROBOT_H  
