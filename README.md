# 🧠 Maze-Solving Robot Simulation using Flood-Fill Algorithm

This project simulates a robot navigating through a maze using the **Flood-Fill pathfinding algorithm**. It mimics the logic used in micromouse maze-solving competitions. The system is composed of modular components including a maze, cells, a robot, a flood-fill algorithm, and a custom queue.

---

## 📁 File Structure

├── cell.cpp  
├── cell.h  
├── floodfill  
│   ├── floodfill.cpp  
│   ├── floodfill.h  
│   ├── queue.cpp  
│   └── queue.h  
├── main  
├── main.cpp  
├── maze.cpp  
├── maze.h  
├── robot.cpp  
└── robot.h  

---

## 🔧 Component Overview

### 🔹 `cell.h / cell.cpp`

Defines the individual **cells** that make up the maze grid.  
Each `Cell` contains:

- Position `(x, y)`
- Wall presence (up, right, down, left)
- Neighbor references
- Flood-fill distance
- Visited state and type (e.g., START, TARGET)

**Key Features**:
- `setWall()` and `isWall()` for wall logic
- `markVisited()` and `reset()` for algorithm state
- `printNeighbors()` for debugging

---

### 🔹 `maze.h / maze.cpp`

Defines the **Maze**, a 2D grid of `Cell` objects.

**Responsibilities**:
- Initialize the maze and manage cell connections
- Track the start, goal, and robot position
- Provide functions like `getCell()`, `setWall()`, and `display()`

---

### 🔹 `robot.h / robot.cpp`

Encapsulates the logic of the **robot** navigating the maze.

- Keeps track of the robot's current `Cell`
- Exposes `move()` and `getPosition()` methods
- Defines `solveMaze(Floodfill&)` which triggers maze-solving using flood-fill

---

### 🔹 `floodfill/floodfill.h / floodfill.cpp`

Implements the **Flood-Fill** algorithm used by the robot to find a path.

**Key Logic**:
- `updateFloodValues()` — Propagates distances from the goal using BFS
- `getBestMove()` — Chooses next move based on lowest distance
- `computePath()` — Walks the robot to the goal, updating position
- `reflood()` — Re-floods maze if new walls are discovered
- `isTrapped()` — Detects if robot is stuck
- `handleUserInput()` — Allows wall insertion during simulation
- `displayPath()` — Debug view of the chosen path

---

### 🔹 `floodfill/queue.h / queue.cpp`

Implements a simple **FIFO Queue** used during the BFS traversal of the flood-fill algorithm.

---

## 🚀 How It Works

1. **Setup**: The maze is initialized with cells, a starting cell, and a goal cell.
2. **Flood-Fill**: Distances from the goal to all other cells are calculated.
3. **Navigation**: The robot chooses neighboring cells with decreasing distance values.
4. **Dynamic Walls**: Users can insert walls while the robot is solving the maze.
5. **Visualization**: The maze and robot's path are displayed in the console.

---

## ▶️ `main.cpp` Entry Point

