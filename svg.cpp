#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "node.h"
#include "edge.h"


std::string generateNodeSVG(const Node &node) {
    std::stringstream nodeSVG;
    nodeSVG << "<circle cx=\"" << node.xPos << "\" cy=\"" << node.yPos << "\" r=\"" << node.size << "\" stroke=\""
            << node.color << R"(" stroke-width="2" fill=")" << node.backgroundColor << "\" />\n";
    return nodeSVG.str();
}

std::string generateSVGNodeLabel(const Node &node) {
    std::stringstream nodeLabelSVG;
    nodeLabelSVG << "<text x=\"" << node.xPos << "\" y=\"" << node.yPos
                 << R"(" dominant-baseline="middle" text-anchor="middle" fill="black">)" << node.label << "</text>\n";
    return nodeLabelSVG.str();
}

void dumpSVG(const std::string &outputFile) {

    std::stringstream svgContent, svgNodes, svgNodesLabels;
    svgContent << "<svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" "
                  "width=\"800\" height=\"600\" viewBox=\"0 0 800 600\">\n\n"
                  "<rect x=\"0\" y=\"0\" width=\"800\" height=\"600\" fill=\"none\" stroke=\"black\" "
                  "stroke-width=\"2\"/>\n\n";

    for (auto &node : NODES) {
        svgNodes << generateNodeSVG(node);
        svgNodesLabels << generateSVGNodeLabel(node);
    }

    svgContent << "<!-- nodes -->\n" << svgNodes.str() << "\n<!-- nodes labels -->\n" << svgNodesLabels.str()
               << "\n</svg>";

    std::ofstream fileStream;
    fileStream.open(outputFile);
    fileStream << svgContent.str();
    fileStream.close();
}