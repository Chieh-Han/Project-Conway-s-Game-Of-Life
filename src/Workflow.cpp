#include "Workflow.h"
#include "Grid.h"

#include <iostream>
#include <filesystem>
#include <random>

namespace fs = std::filesystem;

void Workflow::run() {
    std::string command;
    while (true) {
        std::cout << "\n[Menu] load | random | run | exit\n> ";
        std::cin >> command;

        if (command == "load") loadFile();
        else if (command == "random") generateRandom();
        else if (command == "run") startSimulation();
        else if (command == "exit") break;
        else std::cout << "Unknown command!" << std::endl;
    }
}

void Workflow::loadFile() {
    std::string path;
    std::cout << "Enter filename: ";
    std::cin >> path;
    grid.loadFromFile(path);
    std::cout << "Loaded. Population: " << grid.getPopulation() << std::endl;
}

void Workflow::generateRandom() {
    int n, range;
    std::cout << "Number of cells: "; std::cin >> n;
    std::cout << "Coordinate range (e.g., 20): "; std::cin >> range;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-range, range);

    for (int i = 0; i < n; ++i) {
        grid.addCell(dis(gen), dis(gen));
    }
    std::cout << "Added " << n << " random cells." << std::endl;
}

void Workflow::startSimulation() {
    int steps;
    std::cout << "Number of steps: " << std::endl; std::cin >> steps;

    if (fs::exists(outputDir)) {
        fs::remove_all(outputDir);
    }
    fs::create_directory(outputDir);
    std::cout << "Starting simulation for " << steps << " steps..." << std::endl;

    for (int t = 0; t <= steps; ++t) {
        std::string filename = outputDir + "/grid_" + std::to_string(t) + ".pbm";
        grid.saveToPBM(filename);
        if (t < steps) grid.step();
    }
    std::cout << "Simulation finished! Files saved in /" << outputDir << std::endl;
}