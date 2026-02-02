#ifndef GRID_H
#define GRID_H

#include <set>
#include <vector>
#include <string>
#include <utility>
#include <fstream>
#include <iostream>
#include <climits> // Needed for INT_MAX and INT_MIN

// pair<x,y> shows coordinate
using Coordinate = std::pair<int, int>;

class Grid {
private:
    // list that only holds the coordinates of living cells.
    std::set<Coordinate> liveCells;

    // NEW: Persistent boundaries that only expand, never shrink
    int boundMinX = INT_MAX;
    int boundMaxX = INT_MIN;
    int boundMinY = INT_MAX;
    int boundMaxY = INT_MIN;

    // Helper to update these bounds
    void expandBounds(int x, int y) {
        if (x < boundMinX) boundMinX = x;
        if (x > boundMaxX) boundMaxX = x;
        if (y < boundMinY) boundMinY = y;
        if (y > boundMaxY) boundMaxY = y;
    }
public:
    Grid();
    
    //function to manually add new cells
    void addCell(int x, int y);
    
    // function to proceed to next iteration
    void step();
    
    // returns the current number of living cells
    size_t getPopulation() const;

    // save as PBM
    void saveToPBM(const std::string& filename) const;

    // load files
    void loadFromFile(const std::string& filename);
};

#endif