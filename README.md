# Conway's Game of Life - Sprint 3

This is the third iteration (Sprint 3) of the Conway's Game of Life project. This version focuses on **performance optimization**, **memory efficiency**, and **professional build management**.

## Key Improvements in Sprint 3

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

## Project Structure

```text
.
├── CMakeLists.txt       # Build configuration
├── README.md            # Documentation
└── src/
    ├── main.cpp         # Main execution loop
    ├── Grid.h           # Grid class definition (Sparse implementation)
    └── Grid.cpp         # Grid class implementation
Authors
Group 55