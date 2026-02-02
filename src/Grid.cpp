// src/Grid.cpp
#include "Grid.h"
#include <fstream>
#include <iostream>
#include <map>
#include <algorithm>

Grid::Grid() {}

void Grid::addCell(int x, int y) {
    liveCells.insert({x, y});
    expandBounds(x, y);
}

size_t Grid::getPopulation() const {
    return liveCells.size();
}


void Grid::step() {
    std::map<Coordinate, int> neighborCounts;

    // loop through existing cells
    for (const auto& cell : liveCells) {
        int x = cell.first;
        int y = cell.second;

        // Loop through the 3x3 area around the current cell
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (dx == 0 && dy == 0) continue;
                //+1 to all 8 cells around existing cells
                // neighborCounts is a map of coordinates and how many + they got
                neighborCounts[{x + dx, y + dy}]++;
            }
        }
    }

    std::set<Coordinate> nextGeneration;


    for (const auto& entry : neighborCounts) {
        Coordinate pos = entry.first;
        int count = entry.second;
        // check which of the coordinates in the neightborCount map is already alive in the original Grid
        bool isAlive = liveCells.count(pos);

        //for any alive cell with count == 2 or 3, it survives
        if (isAlive && (count == 2 || count == 3)) {
            nextGeneration.insert(pos);
        
        //for any dead cell with count ==3, it is born
        } else if (!isAlive && count == 3) {
            nextGeneration.insert(pos);
        }
        // implicitly, the rest is dead, so is not insert into the nextGen grid
    }

    liveCells = nextGeneration;

    for (const auto& cell : liveCells) {
        expandBounds(cell.first, cell.second);
    }
}


void Grid::saveToPBM(const std::string& filename) const {
    if (boundMinX == INT_MAX) {
        std::ofstream file(filename);
        file << "P1\n1 1\n0\n";
        return;
    }

    if (liveCells.empty()) return;
    
    int padding = 2;
    int renderMinX = boundMinX - padding;
    int renderMaxX = boundMaxX + padding;
    int renderMinY = boundMinY - padding;
    int renderMaxY = boundMaxY + padding;

    int width = renderMaxX - renderMinX + 1;
    int height = renderMaxY - renderMinY + 1;

    std::ofstream file(filename);
    if (!file.is_open()) return;

    file << "P1\n" << width << " " << height << "\n";

    for (int y = renderMinY; y <= renderMaxY; ++y) {
        for (int x = renderMinX; x <= renderMaxX; ++x) {
            if (liveCells.count({x, y})) {
                file << "1 ";
            } else {
                file << "0 ";
            }
        }
        file << "\n";
    }
    file.close();
}

void Grid::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return;

    //Expects a file with just "x y" coordinates
    int x, y;
    while (file >> x >> y) {
        addCell(x, y);
    }
}