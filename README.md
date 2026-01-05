# Conway's Game of Life - Sprint 2

This is a C++ implementation of Conway's Game of Life. This project has been fully refactored into an Object-Oriented (OOP) structure based on the previous sprint, and implements the infinite grid functionality.

## Features

* **Object-Oriented Structure (OOP):** The code is clearly organized into three main classes: Grid (data storage), Simulation (core rules), and Workflow (user interaction).
* **Infinite Grid:** This is a dynamic system. When living cells reach the boundary of the grid, the map automatically expands in the corresponding direction, creating a theoretically boundless grid.
* **Flexible Initialization:**
    * **File Loading:** Supports reading the initial state from a `grid.txt` file.
    * **Random Generation:** Supports custom width and height with random cell distribution.
* **Interactive Control:** The user can specify the number of simulation steps and chooses to continue or exit after the simulation pauses.

## How to Compile

Please ensure you have a C++ compiler (such as g++) installed in your environment. Run the following command in the terminal:

```bash
g++ main.cpp -o game
How to Run
Windows:
.\game.exe
macOS / Linux:
./game
File Format
If you choose to load from a file, please ensure a grid.txt file exists in the directory. The format is as follows:

x or X or 1: Represents a living cell (Alive)

. or 0: Represents a dead cell (Dead)

Example (Glider):
.x.
..x
xxx