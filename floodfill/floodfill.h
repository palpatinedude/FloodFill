//  This file defines the Floodfill class used for pathfinding in a maze.
//  It provides methods for calculating flood values, computing paths,
//  and guiding a robot from a start to a goal cell using flood-fill logic.

#ifndef FLOODFILL_H
#define FLOODFILL_H

#include "../maze.h"
#include "queue.h"
#include <climits>  
#include "../robot.h"

class Robot; 

class Floodfill {
public:
    Floodfill(Maze& maze);       // Constructor: Initializes the floodfill system with a maze reference
    void reflood(Cell* start);       // Recalculate flood values from a given start cell when walls are discovered
    Cell* getBestMove(Cell* current);  // Determine the best move based on current flood values
    void updateFloodValues();          // Propagate updated flood values from the goal cell across the maze
    void resetFloodValues();           // Set all cell flood values (distances) to infinity
    bool computePath(Robot& robot, Cell* current);    // Compute a valid path for the robot from current to goal
    bool isTrapped(Cell* current);                    // Check if the robot is trapped (no unblocked neighbors)
    const std::array<Cell*, 256>& getPath() const;    // Return the currently stored path
    void setPath(const std::array<Cell*, 256>& newPath);   // Overwrite the current path with a new one
    void displayPath() const;                              // Print the stored path for debugging
    int getPathIndex() const { return pathIndex; }         // Get the current index in the path array
    void handleUserInput(Cell* current);                   // Allow manual wall input during runtime (for testing)

private:
    Maze& maze;  // Reference to the maze object
    Queue floodQueue;  // Queue used for flood-fill traversal (BFS)
    std::array<Cell*, 256> path;  // Array holding the computed path cells
    int pathIndex = 0;            // Current index in the path
    static const Direction directions[4];   // Cardinal directions (UP, RIGHT, DOWN, LEFT)
};

#endif  // FLOODFILL_H
