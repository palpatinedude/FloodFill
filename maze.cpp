//  This file defines how the Maze class works. 
//  The maze is  a grid of cells , where a robot moves from a start position to a target using floodfill logic. 
//  The maze handles initialization, walls, robot tracking, and display.

#include <iostream>
#include "maze.h"

// Constructor: Initialize maze pointers and setup grid
Maze::Maze() : start(nullptr), target(nullptr), robot(nullptr) {
    initMaze();
}

// Set the robot's position in the maze and mark the cell as visited
void Maze::setRobotPosition(Cell* newRobotPos) {
    robot = newRobotPos;
    robot->markVisited();
}

// Add perimeter walls and remove neighbors beyond the edges
void Maze::setPerimeterWalls() {
    for (int y = 0; y < SIZE; ++y) {
        for (int x = 0; x < SIZE; ++x) {
            if (y == 0) {
                grid[y][x].setWall(UP, true);
                grid[y][x].neighbors[UP] = nullptr;  // No neighbor above
            }
            if (y == SIZE - 1) {
                grid[y][x].setWall(DOWN, true);
                grid[y][x].neighbors[DOWN] = nullptr;  // No neighbor below
            }
            if (x == 0) {
                grid[y][x].setWall(LEFT, true);
                grid[y][x].neighbors[LEFT] = nullptr;  // No neighbor left
            }
            if (x == SIZE - 1) {
                grid[y][x].setWall(RIGHT, true);
                grid[y][x].neighbors[RIGHT] = nullptr;  // No neighbor right
            }
        }
    }
}

// Initialize cells, link neighbors, set start and target positions
void Maze::initMaze() {
    int startPosX = 0, startPosY = 0;
    int centerX = SIZE / 2, centerY = SIZE / 2;

    for (int y = 0; y < SIZE; ++y) {
        for (int x = 0; x < SIZE; ++x) {
            if (x == startPosX && y == startPosY) {
                grid[y][x] = Cell(x, y, START);  // Mark cell as START
                start = &grid[y][x];
            } else if (x == centerX && y == centerY) {
                grid[y][x] = Cell(x, y, TARGET);  // Mark cell as TARGET
                target = &grid[y][x];
            } else {
                grid[y][x] = Cell(x, y, UNEXPLORED);  // Default unexplored
            }

            // Set Manhattan distance to the target
            grid[y][x].distance = std::abs(x - centerX) + std::abs(y - centerY);

            // Assign neighbors if within bounds
            if (y > 0) grid[y][x].neighbors[UP] = &grid[y - 1][x];
            if (x < SIZE - 1) grid[y][x].neighbors[RIGHT] = &grid[y][x + 1];
            if (y < SIZE - 1) grid[y][x].neighbors[DOWN] = &grid[y + 1][x];
            if (x > 0) grid[y][x].neighbors[LEFT] = &grid[y][x - 1];
        }
    }

    setPerimeterWalls();  // Add boundary walls
}

// Add or remove a wall at a given cell and direction, sync with neighbor
void Maze::setWall(int x, int y, Direction dir, bool exists) {
    getCell(x, y)->setWall(dir, exists);  // Set wall for this cell

    Cell* neighbor = getCell(x, y)->neighbors[dir];

    if (neighbor) {
        Direction oppositeDir = static_cast<Direction>((dir + 2) % 4);  // Get opposite direction
        neighbor->setWall(oppositeDir, exists);  // Sync neighbor wall

        if (exists) {
            // Break neighbor connections if wall is added
            std::cout << "Breaking connection between (" << x << ", " << y << ") and its neighbor in direction " << dir << "\n";
            getCell(x, y)->neighbors[dir] = nullptr;
            neighbor->neighbors[oppositeDir] = nullptr;
        } else {
            // Restore connection if wall removed
            getCell(x, y)->neighbors[dir] = neighbor;
            neighbor->neighbors[oppositeDir] = getCell(x, y);
        }
    }
}

// Check if there's a wall at (x, y) in the given direction
bool Maze::isWall(int x, int y, Direction dir) const {
    return grid[y][x].isWall(dir);
}

// Reset all cells to unvisited
void Maze::resetVisits() {
    for (int y = 0; y < SIZE; ++y)
        for (int x = 0; x < SIZE; ++x)
            grid[y][x].visited = false;
}

// Mark the target cell as visited
void Maze::markGoalAsVisited() {
    target->type = TARGET;
    target->visited = true;
}

// Display the maze in the terminal with walls, robot, start, target
void Maze::display() const {
    // Top border
    for (int x = 0; x < SIZE; ++x)
        std::cout << "+---";
    std::cout << "+" << std::endl;

    for (int y = 0; y < SIZE; ++y) {
        std::cout << "|";  // Left border

        for (int x = 0; x < SIZE; ++x) {
            // Print content based on role
            if (&grid[y][x] == robot) std::cout << " R ";
            else if (&grid[y][x] == start) std::cout << " S ";
            else if (&grid[y][x] == target) std::cout << " T ";
            else if (grid[y][x].distance != 2147483647) std::cout << " " << grid[y][x].distance << " ";
            else std::cout << "   ";

            // Right wall
            if (x < SIZE - 1 && grid[y][x].isWall(RIGHT))
                std::cout << "|";
            else
                std::cout << " ";
        }

        std::cout << "|" << std::endl;  // Right border

        // Horizontal walls (down)
        if (y < SIZE - 1) {
            for (int x = 0; x < SIZE; ++x) {
                if (grid[y][x].isWall(DOWN))
                    std::cout << "+---";
                else
                    std::cout << "+   ";
            }
            std::cout << "+" << std::endl;
        }
    }

    // Bottom border
    std::cout << "+";
    for (int x = 0; x < SIZE; ++x)
        std::cout << "---+";
    std::cout << std::endl;
}