// This file defines the Cell class used to represent a  single square in a maze grid. 
// Each Cell keeps track of: its position (x, y), wall presence in each direction ,neighboring cells ,type (start, target, path, etc) ,pathfinding information like visited state and distance
// This class is essential for robot navigation and maze solving.

#ifndef CELL_H
#define CELL_H

#include <array>     
#include <cstdint>   

enum CELL_TYPE {
    PATH,         // A standard path cell
    CORNER,       // A corner cell
    JUNCTION3,    // 3-way junction
    JUNCTION4,    // 4-way junction
    DEAD_END,     // Dead end cell
    START,        // Starting cell
    TARGET,       // Target/goal cell
    UNEXPLORED,   // Not yet explored
    EXPLORED      // Already visited/explored
};


enum Direction {
    UP = 0,       // North
    RIGHT,        // East
    DOWN,         // South
    LEFT          // West
};


class Cell {
public:
    // Constructor
    Cell(int posX = 0, int posY = 0, CELL_TYPE type = UNEXPLORED); // Create cell at (posX, posY) with a given type
    int pos[2];                                // (x, y) coordinates of the cell
    CELL_TYPE type;                            // Type of cell (START, TARGET, etc.)

    // Maze Navigation
    std::array<bool, 4> walls;                 // Wall status in 4 directions [UP, RIGHT, DOWN, LEFT]
    std::array<Cell*, 4> neighbors;            // Pointers to neighboring cells in each direction
    int distance;                              // Distance from the goal (used in flood fill or pathfinding)
    bool visited;                              // True if the cell has been visited
    bool inPerimeter;                          // True if this cell is part of the perimeter
    Cell* previous;                            // Pointer to the previous cell in a path

    // Wall and Movement Methods 
    void setWall(Direction dir, bool exists);         // Add or remove a wall in a given direction
    bool isWall(Direction dir) const;                 // Check if there's a wall in a specific direction
    bool isBoundaryWall(Direction dir) const;         // Check if wall is on maze perimeter
    Direction oppositeDir(Direction dir) const;       // Get opposite direction (e.g., UP <-> DOWN)

    void reset();                                     // Reset cell to default values
    bool canMove(Direction dir) const;                // Check if robot can move in a direction (no wall and neighbor exists)
    void markVisited();                               // Mark the cell as visited
    void printNeighbors() const;                      // Print information about neighboring cells
};

#endif // CELL_H
