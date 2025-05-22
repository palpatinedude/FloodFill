#ifndef MAZE_H
#define MAZE_H

#include "cell.h"             
#include <vector>    
#include "robot.h"            

class Robot;  

const int SIZE = 5;  // Maze size (5x5 grid)

class Maze {
private:
    std::array<std::array<Cell, SIZE>, SIZE> grid;  // Grid of maze cells
    Cell* start;   // Pointer to the start cell
    Cell* target;  // Pointer to the target (goal) cell
    Cell* robot;   // Pointer to the robot's current cell

public:
    Maze();  // Constructor: initializes maze structure

    void initMaze();  // Set up cells and link neighbors
    void setWall(int x, int y, Direction dir, bool exists);  // Add or remove a wall at (x, y) in a given direction
    bool isWall(int x, int y, Direction dir) const;  // Check if a wall exists at (x, y) in a given direction
    void setPerimeterWalls();  // Add surrounding outer walls
    void resetVisits();  // Clear visited flags on all cells
    void markGoalAsVisited();  // Mark the target cell as visited
    void setRobotPosition(Cell* newRobotPos);  // Update robot's position in the maze

    // ----------- Getters -----------
    Cell* getStart() const { return start; }  // Get the starting cell
    Cell* getTarget() const { return target; }  // Get the target (goal) cell
    Cell* getRobot() const { return robot; }  // Get the current robot cell
    int getSize() const { return SIZE; }  // Get the size of the maze (always 5)
    Cell* getCell(int x, int y) { return &grid[y][x]; }  // Get the cell at position (x, y)

    // ----------- Setters -----------
    void setStart(Cell* newStart) { start = newStart; }  // Set the starting cell
    void setTarget(Cell* newTarget) { target = newTarget; }  // Set the target (goal) cell

    void display() const;  // Print the maze grid to the terminal
};

#endif  // MAZE_H
