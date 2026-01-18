#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <thread>
#include <chrono>
#include <ctime> 

using namespace std;

class Grid {
private:
    vector<vector<bool>> cells;
    int width;
    int height;

public:
    Grid() : width(0), height(0) {}

    int getHeight() const { return cells.size(); }
    
    int getWidth() const { return cells.empty() ? 0 : cells[0].size(); }

    bool getCell(int r, int c) const {
        if (r < 0 || r >= getHeight() || c < 0 || c >= getWidth()) return false;
        return cells[r][c];
    }

    void setCell(int r, int c, bool alive) {
        if (r >= 0 && r < getHeight() && c >= 0 && c < getWidth()) {
            cells[r][c] = alive;
        }
    }

    bool loadFromFile(string filename) {
        ifstream myfile(filename);
        if (!myfile.is_open()) return false;

        cells.clear();
        string line;
        int expectedWidth = -1;

        while (getline(myfile, line)) {
            if (line.empty()) continue; // Skip empty rows

            vector<bool> row;
            for (char c : line) {
                // Only process valid characters, ignore hidden \r or spaces
                if (c == 'x' || c == 'X' || c == '1' || c == '.') {
                    row.push_back(c == 'x' || c == 'X' || c == '1'); 
                }
            }

            // Check if grid has consistent row size
            if (expectedWidth == -1) {
                expectedWidth = row.size(); // Set the standard width from the first row
            } 
            else if (row.size() != expectedWidth) {
                cerr << "Error: Grid is uneven! Row " << cells.size() + 1 
                    << " has " << row.size() << " cells, expected " << expectedWidth << "." << endl;
                return false; 
            }

            cells.push_back(row); // Add the validated row to our cells vector
        }

        myfile.close();

        // Final check to update class members if loading was successful
        if (!cells.empty()) {
            height = cells.size();
            width = expectedWidth;
        }
        
        return true;
    }

    void generateRandom(int w, int h) {
        cells.clear();
        width = w;
        height = h;
        srand(time(0));

        for (int i = 0; i < height; i++) {
            vector<bool> row;
            for (int j = 0; j < width; j++) {
                bool alive = (rand() % 2) == 1; 
                row.push_back(alive);
            }
            cells.push_back(row);
        }
    }

    void print() const {
        for (const auto& row : cells) {
            for (bool cell : row) {
                cout << (cell ? "X" : ".");
            }
            cout << endl;
        }
        cout << "-----------------" << endl;
    }

    void expandIfNeeded() {
        if (cells.empty()) return;

        bool topNeedsSpace = false;
        for (bool c : cells[0]) if (c) topNeedsSpace = true;
        if (topNeedsSpace) {
            cells.insert(cells.begin(), vector<bool>(width, false));
            height++;
        }

        bool bottomNeedsSpace = false;
        for (bool c : cells.back()) if (c) bottomNeedsSpace = true;
        if (bottomNeedsSpace) {
            cells.push_back(vector<bool>(width, false));
            height++;
        }

        bool leftNeedsSpace = false;
        for (int i = 0; i < height; i++) if (cells[i][0]) leftNeedsSpace = true;
        if (leftNeedsSpace) {
            for (int i = 0; i < height; i++) cells[i].insert(cells[i].begin(), false);
            width++;
        }

        bool rightNeedsSpace = false;
        for (int i = 0; i < height; i++) if (cells[i].back()) rightNeedsSpace = true;
        if (rightNeedsSpace) {
            for (int i = 0; i < height; i++) cells[i].push_back(false);
            width++;
        }
    }

    friend class Simulation;
};

class Simulation {
private:
    Grid grid;

    int countNeighbors(int r, int c) {
        int count = 0;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i == 0 && j == 0) continue;
                if (grid.getCell(r + i, c + j)) count++;
            }
        }
        return count;
    }

public:
    void setGrid(Grid g) { grid = g; }
    
    Grid getGrid() const { return grid; }

    void update() {
        grid.expandIfNeeded();

        Grid nextGrid = grid; 
        
        for (int i = 0; i < grid.getHeight(); i++) {
            for (int j = 0; j < grid.getWidth(); j++) {
                int neighbors = countNeighbors(i, j);
                bool isAlive = grid.getCell(i, j);

                if (isAlive) {
                    if (neighbors < 2 || neighbors > 3) {
                        nextGrid.setCell(i, j, false);
                    }
                } else {
                    if (neighbors == 3) {
                        nextGrid.setCell(i, j, true);
                    }
                }
            }
        }
        grid = nextGrid;
    }
};


class Workflow {
private:
    Simulation sim;

public:
    void run() {
        Grid myGrid;
        int choice;
        cout << "Welcome to Game of Life (Sprint 2)" << endl;
        while(true){
            cout << "1. Load from file (grid.txt)" << endl;
            cout << "2. Generate random grid" << endl;
            cout << "Enter choice: ";
            if (cin >> choice && (choice == 1 || choice == 2)) {
                break; //break out of loop if inputs are correct
            }

            else {
                cout << "Invalid input. Please enter 1 or 2." << endl;
                cin.clear(); // Reset error flags
                cin.ignore(1000, '\n'); // Clear the buffer
            }   
        }

        if (choice == 1) {
            string filename;
            cout << "Enter filename (e.g. grid.txt): ";
            cin >> filename;
            if (!myGrid.loadFromFile(filename)) {
                cerr << "Error loading file!" << endl;
                return;
            }
        } else {
            int w, h;
            while(true){
                cout << "Enter width AND height: ";
                if (cin >> w >> h && w > 0 && h > 0) {
                    break;
                }
                else {
                    cerr << "Error: Dimensions must be positive integers!" << endl;
                    cin.clear(); 
                    cin.ignore(1000, '\n');
                }
            }
            myGrid.generateRandom(w, h);
        }

        sim.setGrid(myGrid);
        sim.getGrid().print();

        while (true) {
            int steps;
            cout << "How many iterations to run? (0 to exit): ";
            cin >> steps;

            if (steps <= 0) break;

            for (int t = 0; t < steps; t++) {
                
                cout << "\033[2J\033[1;1H"; 
                
                sim.update(); 
                
                cout << "Iteration: " << t + 1 << endl;
                sim.getGrid().print(); 
                
                this_thread::sleep_for(chrono::milliseconds(1000));
            }
            
            cout << "Paused. Continue?" << endl;
        }
        cout << "Simulation finished." << endl;
    }
};

int main() {
    Workflow app;
    app.run();
    return 0;
}