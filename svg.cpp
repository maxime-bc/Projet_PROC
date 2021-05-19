#include <cmath>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <tuple>
#include "svg.h"
#include "node.h"
#include "edge.h"


std::string generateNodeSVG(const Node &node) {
    std::stringstream nodeSVG;
    nodeSVG << "<circle cx=\"" << node.xPos << "\" cy=\"" << node.yPos << "\" r=\"" << node.size << "\" stroke=\""
            << node.color << R"(" stroke-width="2" fill=")" << node.backgroundColor << "\" />\n";
    return nodeSVG.str();
}

std::string generateSVGNodeLabel(const Node &node) { // TODO : change return type of all functions to stringstream ??
    std::stringstream nodeLabelSVG;
    nodeLabelSVG << "<text x=\"" << node.xPos << "\" y=\"" << node.yPos
                 << R"(" dominant-baseline="middle" text-anchor="middle" fill="black">)" << node.label << "</text>\n";
    return nodeLabelSVG.str();
}

std::string generateEdgeLabelTextSVG(double x, double y, const std::string &label) {
    std::stringstream edgeLabelTextSVG;
    edgeLabelTextSVG << "<text x=\"" << x << "\" y=\"" << y << R"(" fill="black" text-anchor="middle"> )" << label
                     << "</text>\n";
    return edgeLabelTextSVG.str();
};

std::string generateEdgesSVG() {
    std::stringstream edgesSVG;

    for (auto &edge : EDGES) {
        auto nodesIterator = NODES.begin();
        std::advance(nodesIterator, getNodeIndex(edge.source));
        Node sourceNode = *nodesIterator;

        auto edgesIterator = NODES.begin();
        std::advance(edgesIterator, getNodeIndex(edge.dest));
        Node destNode = *edgesIterator;

        auto[curvePath, cx1, cy1] = generateCurvedArrowBetweenPoints(sourceNode.xPos, sourceNode.yPos, destNode.xPos,
                                                                     destNode.yPos);

        edgesSVG << "<path d=\"" << curvePath << "\" stroke=\"black\" fill=\"none\"/>\n";

        edgesSVG << generateEdgeLabelTextSVG(cx1, cy1, edge.label);
    }

    return edgesSVG.str();
}

std::tuple<std::string, double, double> generateCurvedArrowBetweenPoints(float x1, float y1, float x2, float y2) {
    std::stringstream curve;

    // straight line
//    if (x1 == x2 || y1 == y2) { // TODO : move into another function
//        // TODO : compute the number of edges for each nodes, if number for node
//        curve << "M" << x1 << " " << y1 << " " << x2 << " " << y2 << " Z";
//        return curve.str();
//    }

    // edge source == dest, curve to the same point

    // mid-point of line:
    double mpx = (x2 + x1) * 0.5;
    double mpy = (y1 + y2) * 0.5;

    // angle of perpendicular to line:
    double theta = std::atan2(y2 - y1, x2 - x1) - M_PI / 2;

    // distance of control point from mid-point of line:
    double offset = 30;

    // location of control point:
    double cx1 = mpx + offset * cos(theta);
    double cy1 = mpy + offset * sin(theta);

    // construct the command to draw a quadratic curve

    curve << "M" << x1 << " " << y1 << " Q " << cx1 << " " << cy1 << " " << x2 << " " << y2;
    return std::make_tuple(curve.str(), cx1, cy1);
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

    svgContent << "<!-- nodes -->\n" << svgNodes.str()
               << "\n<!-- nodes labels -->\n" << svgNodesLabels.str()
               << "\n<!-- edges -->\n" << generateEdgesSVG()
               << "\n</svg>";

    std::ofstream fileStream;
    fileStream.open(outputFile);
    fileStream << svgContent.str();
    fileStream.close();
}