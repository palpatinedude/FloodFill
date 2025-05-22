// This file implements the Robot class functions declared in robot.h.
// The Robot can solve a maze using a Floodfill algorithm and return to the start.
// It interacts with the Maze and Floodfill classes to navigate between cells.

#include "robot.h"
#include "floodfill/floodfill.h"
#include <iostream>
#include <algorithm>  

// Constructor: Initializes the robot with the given maze
Robot::Robot(Maze& maze) : maze(maze), position(nullptr) {
    position = maze.getStart();  // Set the initial position to the maze's start cell
    maze.setRobotPosition(position);  // Update the maze with the robot's initial position

    std::cout << "Robot initialized at (" 
              << position->pos[0] << ", " << position->pos[1] << ")\n";
}

// Move the robot to a specified cell
void Robot::move(Cell* nextCell) {
    if (!nextCell) {
        std::cout << "Invalid move: No next cell available." << std::endl;
        return;
    }

    position = nextCell;  // Update the robot's current position
    maze.setRobotPosition(nextCell);  // Update the maze's view of the robot
    std::cout << "Robot moved to (" 
              << position->pos[0] << ", " << position->pos[1] << ")\n";

    maze.display();  // Show the updated maze
}

// Return the current position of the robot
Cell* Robot::getPosition() const {
    return position;
}

// Set a new position for the robot
void Robot::setPosition(Cell* newPos) {
    if (newPos) {
        position = newPos;  // Update robot's internal position
        maze.setRobotPosition(newPos);  // Reflect this in the maze
    } else {
        std::cout << "Invalid position: Cell is null." << std::endl;
    }
}

// Solve the maze using the Floodfill algorithm
void Robot::solveMaze(Floodfill& floodfill) {
    auto path = floodfill.getPath();  // Retrieve the path from floodfill
    std::fill(path.begin(), path.end(), nullptr);  // Clear old path values
    floodfill.setPath(path);  // Update with cleared path

    Cell* current = getPosition();  // Get current cell

    std::cout << "Current Robot position: (" 
              << current->pos[0] << ", " << current->pos[1] << ")\n";

    // Try to compute a path to the goal
    if (!floodfill.computePath(*this, current)) {
        std::cout << "Navigation failed: Robot is trapped or no valid path found.\n";
        return;  // Stop if no valid path found
    }

    maze.markGoalAsVisited();  // Indicate goal was reached in the maze
    std::cout << "Goal reached!\n";

    returnToStart(floodfill);  // Return to the start after reaching the goal
}

// Move the robot back to the start following the reverse path
void Robot::returnToStart(Floodfill& floodfill) {
    std::cout << "Returning to start...\n";

    auto path = floodfill.getPath();  // Get the existing path to goal
    std::reverse(path.begin(), path.end());  // Reverse it to return to start

    for (auto cell : path) {
        move(cell);  // Move to each cell in the path

        if (cell == maze.getStart()) {  // Check if we’ve reached the start
            std::cout << "Robot returned back to the start cell" << std::endl;
            break;
        }
    }

    floodfill.displayPath();  // Show the path taken
}