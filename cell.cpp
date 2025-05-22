//  This file implements the Cell class defined in cell.h.
//  Each cell represents a unit in the maze, storing: its type (e.g., START, TARGET),wall presence ,neighbor references ,state data for algorithms (visited, distance, etc.)
//  Functions here support maze setup, traversal, and debugging.


#include "cell.h"
#include <iostream>


const int SIZE = 5;

// Constructor: Initialize a cell at given (x, y) with a type
Cell::Cell(int posX, int posY, CELL_TYPE type)
    : distance(0), visited(false) {
    pos[0] = posX;                  // Set x position
    pos[1] = posY;                  // Set y position
    this->type = type;             // Set the cell type
    neighbors.fill(nullptr);       // Initialize all neighbor pointers to null
    walls.fill(false);             // No walls by default
}

// Reset the cell's state unless it's START or TARGET
void Cell::reset() {
    if (type != START && type != TARGET) {
        type = UNEXPLORED;         // Reset type unless it's START or TARGET
    }
    distance = 0;                  // Reset distance
    visited = false;              // Mark as unvisited
    previous = nullptr;           // Clear path pointer

    if (!inPerimeter) {
        walls.fill(false);        // Remove all walls if not a perimeter cell
    } else {
        // Only reset non-boundary walls
        for (Direction dir : {UP, RIGHT, DOWN, LEFT}) {
            if (!isBoundaryWall(dir)) {
                walls[dir] = false;
            }
        }
    }
}


// Set or remove a wall in a given direction
void Cell::setWall(Direction dir, bool exists) {
    walls[dir] = exists;
}


// Check if there is a wall in a specific direction
bool Cell::isWall(Direction dir) const {
    return walls[dir];
}


// Determine if a wall is part of the maze's outer boundary
bool Cell::isBoundaryWall(Direction dir) const {
    if (dir == UP    && pos[1] == 0)         return true; // Top edge
    if (dir == DOWN  && pos[1] == SIZE - 1)  return true; // Bottom edge
    if (dir == LEFT  && pos[0] == 0)         return true; // Left edge
    if (dir == RIGHT && pos[0] == SIZE - 1)  return true; // Right edge

    return false; // Not a boundary wall
}


// Mark the cell as visited and change type to EXPLORED if applicable
void Cell::markVisited() {
    if (type == UNEXPLORED) {
        type = EXPLORED;
        visited = true;
    }
}


// Return the opposite direction (used when managing neighbor connections)
Direction Cell::oppositeDir(Direction dir) const {
    switch (dir) {
        case UP:    return DOWN;
        case DOWN:  return UP;
        case RIGHT: return LEFT;
        case LEFT:  return RIGHT;
        default:    return UP; // Default fallback
    }
}


// Print information about neighboring cells (for debugging)
void Cell::printNeighbors() const {
    static const char* directionNames[4] = { "UP", "RIGHT", "DOWN", "LEFT" };

    std::cout << "Neighbors of cell (" << pos[0] << ", " << pos[1] << "):\n";

    for (int i = 0; i < 4; ++i) {
        Direction dir = static_cast<Direction>(i);
        Cell* neighbor = neighbors[dir];

        std::cout << "Direction " << directionNames[i] << ": ";

        if (neighbor) {
            std::cout << "Neighbor at (" << neighbor->pos[0] << ", " << neighbor->pos[1] << ")";
        } else {
            std::cout << "No neighbor";
        }

        std::cout << (isWall(dir) ? " [WALL PRESENT]" : " [NO WALL]") << "\n";
    }
}


// Check if the robot can move in a given direction:
bool Cell::canMove(Direction dir) const {
    if (neighbors[dir] == nullptr) return false; // No neighbor
    return !isWall(dir);                         // True if no wall in that direction
}
