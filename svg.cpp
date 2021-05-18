#include <iostream>
#include <string>
#include <fstream>
#include "node.h"
#include "edge.h"

void dumpSVG(const std::string &outputFile) {

    std::ofstream fileStream;
    fileStream.open(outputFile);
    fileStream << "Writing this to a file.\n";
    fileStream.close();
}