// src/Grid.cpp
#include "Grid.h"
#include <fstream>
#include <iostream>
#include <map>
#include <algorithm>
#include <climits>

Grid::Grid() {}

void Grid::addCell(int x, int y) {
    liveCells.insert({x, y});
}

size_t Grid::getPopulation() const {
    return liveCells.size();
}


void Grid::step() {
    std::map<Coordinate, int> neighborCounts;


    for (const auto& cell : liveCells) {
        int x = cell.first;
        int y = cell.second;

        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (dx == 0 && dy == 0) continue;
                neighborCounts[{x + dx, y + dy}]++;
            }
        }
    }

    std::set<Coordinate> nextGeneration;


    for (const auto& entry : neighborCounts) {
        Coordinate pos = entry.first;
        int count = entry.second;
        bool isAlive = liveCells.count(pos);

        if (isAlive && (count == 2 || count == 3)) {
            nextGeneration.insert(pos);
        } else if (!isAlive && count == 3) {
            nextGeneration.insert(pos);
        }

    }

    liveCells = nextGeneration;
}


void Grid::saveToPBM(const std::string& filename) const {
    if (liveCells.empty()) {

        std::ofstream file(filename);
        file << "P1\n1 1\n0\n";
        return;
    }


    int minX = INT_MAX, maxX = INT_MIN;
    int minY = INT_MAX, maxY = INT_MIN;

    for (const auto& cell : liveCells) {
        if (cell.first < minX) minX = cell.first;
        if (cell.first > maxX) maxX = cell.first;
        if (cell.second < minY) minY = cell.second;
        if (cell.second > maxY) maxY = cell.second;
    }


    int padding = 2;
    minX -= padding; maxX += padding;
    minY -= padding; maxY += padding;

    int width = maxX - minX + 1;
    int height = maxY - minY + 1;

    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }


    file << "P1\n";
    file << width << " " << height << "\n";


    for (int y = minY; y <= maxY; ++y) {
        for (int x = minX; x <= maxX; ++x) {
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


    int x, y;
    while (file >> x >> y) {
        addCell(x, y);
    }
}