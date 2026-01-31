// src/main.cpp
#include "Grid.h"
#include <iostream>
#include <string>
#include <filesystem>

int main(int argc, char* argv[]) {

    int steps = 10;
    std::string outputDir = "output";


    Grid grid;


    std::cout << "Initializing Glider pattern..." << std::endl;
    grid.addCell(1, 0);
    grid.addCell(2, 1);
    grid.addCell(0, 2);
    grid.addCell(1, 2);
    grid.addCell(2, 2);


    namespace fs = std::filesystem;
    if (!fs::exists(outputDir)) {
        fs::create_directory(outputDir);
    }

    std::cout << "Starting simulation for " << steps << " steps..." << std::endl;


    for (int t = 0; t <= steps; ++t) {
        //  grid_0.pbm, grid_1.pbm ...
        std::string filename = outputDir + "/grid_" + std::to_string(t) + ".pbm";


        grid.saveToPBM(filename);
        std::cout << "Step " << t << ": Saved " << filename
                  << " (Population: " << grid.getPopulation() << ")" << std::endl;


        if (t < steps) {
            grid.step();
        }
    }

    std::cout << "Simulation complete. Check the '" << outputDir << "' directory." << std::endl;
    return 0;
}