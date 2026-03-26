<h1 align="center">
  Conway's Game of Life - Sprint 3 (Final)
  <br>
</h1>

<div align="center">
  <img src="./simulation.gif" alt="Game of Life Simulation" />
  <br>
  Game of Life Simulation
</div> 

# Table of Contents
* [Introduction](#introduction)
* [Background](#background)
* [Improvements](#improvements-in-sprint-3)
* [Build Instructions](#build--run-instructions)
* [Project Structure](#project-structure)

## Introduction
This is the third iteration (Sprint 3) of the Conway's Game of Life project. This version focuses on **performance optimization**, **memory efficiency**, and **professional build management**.

## Background
We consider an arbitrary grid of squares. Each component of the grid is called a (biological) cell. At the beginning (`t=0`), all
cells are either "dead" or "alive".
Now we are going to add dynamics to the scene by applying the following rules at any time step `t = t + 1`:    

A living cell   

* stays alive, if it hast exact 2 or 3 neighbors
* dies due to loneliness if it has fewer neighbors
* dies du to overpopulation if it has more neighbors

A dead cell  

* will be reborn if it has exactly 3 neighbors
* remains dead otherwise

## Improvements in Sprint 3

### 1. Sparse Representation (Infinite Grid)
- **Problem in Sprint 2:** The previous version used a 2D vector (`vector<vector<bool>>`). This required resizing the entire grid in memory whenever a cell moved out of bounds, which was inefficient for large, empty spaces.
- **Solution in Sprint 3:** We implemented a **Sparse Grid** using `std::set<std::pair<int, int>>`.
- **Benefit:**
    - Only **live cells** are stored in memory.
    - Dead cells consume zero memory.
    - The grid is effectively infinite without the need for manual resizing or reallocation.
    - Performance is now proportional to the number of *live cells*, not the grid size.

### 2. PBM Image Output
- Instead of printing text to the console, the simulation now exports each time step as a **PBM (Portable Bitmap)** image file.
- Files are automatically saved to an `output/` directory (e.g., `grid_0.pbm`, `grid_1.pbm`).
- These files can be viewed with standard image viewers or converted to other formats.

### 3. CMake Build System
- The project has been migrated to use **CMake**, a standard industry tool for C++ build automation.
- Source code is organized into a clean structure (`src/` folder).

## Build & Run Instructions

### 1. Create and enter a build directory
`mkdir build && cd build`

### 2. Configure and build the project
`cmake ..`  
`make`

### 3. Go back to the project root
`cd ..`

### 4. Run the simulation from the root
`./build/game_of_life`

### 4.1 Load some .txt files from the samples folder to see some common simulation 

### 5. Run the included python script to create a gif for cisualization
Note: Requires PIL library (`pip install Pillow`)  
`python3 visualizer.py`

### 6. (Optional) Open the GIF directly from WSL in Windows
`explorer.exe simulation.gif`

## Project Structure

```text
.
├── CMakeLists.txt       # Build configuration
├── README.md            # Documentation
└── src/
    ├── main.cpp         # Main execution loop
    ├── Grid.h           # Grid class definition 
    ├── Grid.cpp         # Grid class implementation
    ├── Workflow.h       # Workflow class definition
    └── Workflow.cpp     # Workflow class implementation
```

Authors: Group 55