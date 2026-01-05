# Conway's Game of Life - Sprint 2

This is the second iteration (Sprint 2) of the Conway's Game of Life project. This version introduces a major architectural refactoring from procedural programming to Object-Oriented Programming (OOP) and implements a dynamic, infinite grid system.

## Project Overview

The primary goal of Sprint 2 was to enhance the maintainability and scalability of the simulation. The code has been restructured into distinct classes to separate concerns: data management, simulation logic, and user interaction. Additionally, the simulation now supports an "infinite" grid, where the simulation area automatically expands as living cells reach the boundaries.

## Architecture and OOP Design

The project is structured around three core classes:

### 1. Grid Class
* **Responsibility:** Manages the data structure (2D boolean vector) representing the cellular automaton.
* **Key Capabilities:**
    * **Data Storage:** Encapsulates the `vector<vector<bool>>` cells.
    * **File I/O:** Parses input files (`grid.txt`) to initialize the state.
    * **Randomization:** Generates random grid states based on user-defined dimensions.
    * **Infinite Expansion:** Implements the `expandIfNeeded()` method. This checks the four boundaries (top, bottom, left, right) before every simulation step. If a living cell is detected on an edge, the grid dimensions are automatically increased by inserting new empty rows or columns.

### 2. Simulation Class
* **Responsibility:** Encapsulates the core rules and logic of Conway's Game of Life.
* **Key Capabilities:**
    * **Rule Implementation:** Applies the standard rules (Survival, Death by Isolation/Overpopulation, Reproduction).
    * **State Management:** Maintains the current state and computes the next generation using a double-buffering approach (creating a temporary grid) to ensure simultaneous updates.
    * **Neighbor Counting:** Calculates active neighbors for any given coordinate.

### 3. Workflow Class
* **Responsibility:** Handles user interaction and the main execution loop.
* **Key Capabilities:**
    * **Menu System:** Provides a command-line interface for the user to choose between file loading or random generation.
    * **Simulation Loop:** Manages the flow of time steps and allows the user to pause, continue, or exit the simulation.
    * **Visualization:** Handles the console output and screen clearing for animation effects.

## New Features in Sprint 2

* **Infinite Grid:** Unlike Sprint 1, which had fixed boundaries, this version allows patterns (such as Gliders) to travel indefinitely. The grid dynamically resizes in memory to accommodate the expanding population.
* **Random Initialization:** Users can now generate a random starting state by specifying the width and height. The system initializes cells with a 50% probability of being alive.
* **Interactive Control:** The simulation runs in batches of iterations defined by the user. After a batch completes, the system pauses and awaits further instructions, preventing the program from terminating prematurely.

## Compilation and Execution

### Prerequisites
* A C++ compiler (GCC/g++ recommended).
* Standard C++ libraries.

### Compilation
To compile the project, open your terminal or command prompt in the project directory and run:

```bash
g++ main.cpp -o game
Running the Application
Windows:
.\game.exe
macOS / Linux:
./game
Usage Guide
Upon launching the application, you will be presented with a menu:

Select Initialization Method:

Enter 1 to load from a file (grid.txt).

Enter 2 to generate a random grid.

Configuration:

If File Loading: Enter the filename (e.g., grid.txt).

If Random: Enter the desired Width and Height (e.g., 20 20).

Simulation Control:

The program will ask: How many iterations to run?.

Enter a number (e.g., 50) to watch the simulation.

When the iterations finish, the simulation pauses. You can enter another number to continue or 0 to exit.

File Format Specification
If loading from a file, the system expects a text file (e.g., grid.txt) with the following format:

Alive Cell: Represented by x, X, or 1.

Dead Cell: Represented by ., 0, or any other character.

Constraint: All rows must have the same length.

Example Input:


.x.
..x
xxx
Authors
Group 55