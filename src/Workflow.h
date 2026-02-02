#ifndef WORKFLOW_H
#define WORKFLOW_H

#include "Grid.h"
#include <string>

class Workflow {
private:
    Grid grid;
    std::string outputDir = "output";

public:
    // Starts the main loop
    void run();

private:
    void loadFile();
    void generateRandom();
    void startSimulation();
};

#endif