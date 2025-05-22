// This file implements the Floodfill class methods used for maze navigation.
// It calculates distances from the target using flood-fill logic and guides the robot step-by-step.
// Also allows dynamic wall addition during runtime for debugging or simulation.

#include "floodfill.h"
#include "../cell.h"
#include "../robot.h"
#include <climits>
#include <thread>
#include <iostream>
#include <algorithm>

// Direction array used in traversal
const Direction Floodfill::directions[4] = { UP, RIGHT, DOWN, LEFT };

// Constructor: Initialize Floodfill with reference to the maze
Floodfill::Floodfill(Maze& maze) : maze(maze) {
    updateFloodValues(); // Start with flood values from goal
}

// Reset all cells' distances and paths to initial state
void Floodfill::resetFloodValues() {
    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            maze.getCell(x, y)->distance = INT_MAX;  // Reset distance
            maze.getCell(x, y)->previous = nullptr;  // Reset previous pointer
        }
    }
}

// Recalculate flood values from current robot position
void Floodfill::reflood(Cell* robot) {
    updateFloodValues(); // Use standard flood update
}

// Check if robot is trapped (no accessible neighbors)
bool Floodfill::isTrapped(Cell* current) {
    for (Direction dir : directions) {
        if (!current->isWall(dir)) { // Check if wall blocks the way
            Cell* neighbor = current->neighbors[dir];
            if (neighbor != nullptr && neighbor->distance < INT_MAX) {
                return false; // At least one path exists
            }
        }
    }
    return true; // All paths blocked or unreachable
}

// Update all cell distances starting from the goal (flood-fill)
void Floodfill::updateFloodValues() {
    resetFloodValues(); // Reset all distances
    Cell* goal = maze.getTarget();
    goal->distance = 0; // Goal has zero distance

    std::queue<Cell*> floodQueue;
    floodQueue.push(goal); // Start from the goal

    while (!floodQueue.empty()) {
        Cell* current = floodQueue.front(); floodQueue.pop();

        for (Direction dir : directions) {
            int dx = 0, dy = 0;
            switch (dir) {
                case UP:    dy = -1; break;
                case DOWN:  dy = 1;  break;
                case LEFT:  dx = -1; break;
                case RIGHT: dx = 1;  break;
                default: continue;
            }

            int nx = current->pos[0] + dx;
            int ny = current->pos[1] + dy;

            if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE) {
                if (!current->isWall(dir)) {
                    Cell* neighbor = maze.getCell(nx, ny);
                    if (neighbor->distance > current->distance + 1) {
                        neighbor->distance = current->distance + 1;
                        neighbor->previous = current;
                        floodQueue.push(neighbor);
                    }
                }
            }
        }
    }
}

// Determine best next cell to move to (lowest flood value)
Cell* Floodfill::getBestMove(Cell* current) {
    Cell* nextCell = nullptr;
    int minDistance = current->distance;

    for (Direction dir : directions) {
        if (!current->isWall(dir)) {
            Cell* neighbor = current->neighbors[dir];
            if (neighbor != nullptr && neighbor->distance < minDistance) {
                minDistance = neighbor->distance;
                nextCell = neighbor;
            }
        }
    }

    return nextCell;
}

// Generate a full path for the robot using flood values
bool Floodfill::computePath(Robot& robot, Cell* current) {
    while (current != maze.getTarget()) {
        path[pathIndex++] = current;
        Cell* nextCell = getBestMove(current);

        if (!nextCell) {
            if (isTrapped(current)) {
                return false; // No way out
            }

            reflood(current); // Update distances based on current state
            nextCell = getBestMove(current);
            if (!nextCell) return false;
        }

        robot.move(nextCell);        // Move robot
        current = robot.getPosition();
        std::this_thread::sleep_for(std::chrono::milliseconds(1500)); // Pause for visibility
        handleUserInput(current);   // Optional wall updates
        maze.display();
    }

    path[pathIndex++] = current; // Add target to path
    return true;
}

// Print all cells in the computed path
void Floodfill::displayPath() const {
    std::cout << "Path from start to goal:\n";
    for (int i = 0; i < pathIndex; ++i) {
        if (path[i] != nullptr) {
            std::cout << "(" << path[i]->pos[0] << ", " << path[i]->pos[1] << ") ";
        }
    }
    std::cout << std::endl;
}

// Return stored path (getter)
const std::array<Cell*, 256>& Floodfill::getPath() const {
    return path;
}

// Replace stored path with a new one (setter)
void Floodfill::setPath(const std::array<Cell*, 256>& newPath) {
    path = newPath;
}

// Handle user input to add walls manually during runtime
void Floodfill::handleUserInput(Cell* current) {
    char userInput;
    std::cout << "Press 'l' to continue or 'w' to add walls: ";
    std::cin >> std::ws;
    userInput = std::cin.get();

    if (userInput == 'w') {
        int numWalls;
        std::cout << "How many walls do you want to add? (1–4): ";
        std::cin >> numWalls;

        if (numWalls < 1 || numWalls > 4) {
            std::cout << "Invalid number of walls. Please enter a number between 1 and 4.\n";
            return;
        }

        for (int i = 0; i < numWalls; ++i) {
            int x, y;
            char dir;
            std::cout << "\nWall #" << (i + 1) << ":\n";
            std::cout << "Enter x coordinate: ";
            std::cin >> x;
            std::cout << "Enter y coordinate: ";
            std::cin >> y;
            std::cout << "Enter direction (U/D/L/R): ";
            std::cin >> dir;

            if (dir != 'U' && dir != 'D' && dir != 'L' && dir != 'R') {
                std::cout << "Invalid direction! Skipping this wall.\n";
                continue;
            }

            Direction wallDir = (dir == 'U' ? UP : dir == 'D' ? DOWN : dir == 'L' ? LEFT : RIGHT);
            maze.setWall(x, y, wallDir, true); // Add wall to maze
            std::cout << "Wall added at (" << x << ", " << y << ") in direction " << dir << "\n";

            Cell* wallCell = maze.getCell(x, y);
            if (wallCell) {
                wallCell->printNeighbors();
            } else {
                std::cout << "Error: Invalid cell coordinates.\n";
            }
        }

        reflood(maze.getRobot()); // Recalculate flood values
        std::cout << "After reflooding, distances updated.\n";

    } else if (userInput != 'l') {
        std::cout << "Invalid input. Press 'l' to continue or 'w' to add walls.\n";
    }
}

/*
ONE WALL AT TIME
void Floodfill::handleUserInput(Cell* current) {
    char userInput;
    std::cout << "Press 'l' to continue or 'w' to add a wall: ";
    std::cin >> std::ws;
    userInput = std::cin.get();

    if (userInput == 'w') {
        int x, y;
        char dir;
        std::cout << "Enter the x coordinate of the wall: ";
        std::cin >> x;
        std::cout << "Enter the y coordinate of the wall: ";
        std::cin >> y;
        std::cout << "Enter the direction to add the wall (U/D/L/R): ";
        std::cin >> dir;

        if (dir != 'U' && dir != 'D' && dir != 'L' && dir != 'R') {
            std::cout << "Invalid direction! Please enter U, D, L, or R.\n";
            return;
        }

        Direction wallDir = (dir == 'U' ? UP : dir == 'D' ? DOWN : dir == 'L' ? LEFT : RIGHT);
        maze.setWall(x, y, wallDir, true); // Add wall to maze
        std::cout << "Wall added at (" << x << ", " << y << ") in direction " << dir << "\n";

        Cell* wallCell = maze.getCell(x, y);
        if (wallCell) {
            wallCell->printNeighbors(); // Display updated neighbors
        } else {
            std::cout << "Error: Invalid cell coordinates.\n";
        }

        reflood(maze.getRobot()); // Recalculate flood values
        std::cout << "After reflooding, distances updated.\n";
    } else if (userInput != 'l') {
        std::cout << "Invalid input. Press 'l' to continue or 'w' to add a wall.\n";
    }
}
*/