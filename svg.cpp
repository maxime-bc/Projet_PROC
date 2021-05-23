#include <cmath>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <tuple>
#include <map>
#include "svg.h"
#include "node.h"
#include "edge.h"


std::tuple<double, double, double, double>
getSegmentEndpointsBetweenTwoCircles(double x1, double y1, double r1, double x2, double y2, double r2) {
    double sx1 = x1 + (((x2 - x1) * r1) / sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
    double sy1 = y1 + (((y2 - y1) * r1) / sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
    double sx2 = x2 - (((x2 - x1) * r2) / sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
    double sy2 = y2 - (((y2 - y1) * r2) / sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
    return std::make_tuple(sx1, sy1, sx2, sy2);
}

std::tuple<double, double> getPositionByDegree(double x, double y, double radius, double degree) {
    double theta = M_PI * degree / 180;
    return std::make_tuple(x + radius * cos(theta), y - radius * sin(theta));
}

std::string
generateArrow(double xPos, double yPos, double size, const std::string &type, const std::string &direction) {
    std::map<std::string, double> directionToDegree = {{"east",       0},
                                                       {"north-east", 45},
                                                       {"north",      90},
                                                       {"north-west", 135},
                                                       {"west",       180},
                                                       {"south-west", 225},
                                                       {"south",      270},
                                                       {"south-east", 315}};

    double degree = directionToDegree.at(direction);
    std::tuple<double, double> startPosition = getPositionByDegree(xPos, yPos, size, degree);
    std::tuple<double, double> endPosition = getPositionByDegree(std::get<0>(startPosition), std::get<1>(startPosition),
                                                                 size, degree);
    std::tuple<std::string, double, double> arrowPath;
    if (type == "initial") {
        arrowPath = generateCurvedArrowBetweenPoints(std::get<0>(endPosition),
                                                     std::get<1>(endPosition),
                                                     std::get<0>(startPosition),
                                                     std::get<1>(startPosition), 0);
    } else if (type == "final") {
        arrowPath = generateCurvedArrowBetweenPoints(std::get<0>(startPosition),
                                                     std::get<1>(startPosition),
                                                     std::get<0>(endPosition),
                                                     std::get<1>(endPosition), 0);
    }
    return std::get<0>(arrowPath);
}

std::tuple<double, double> polarToCartesian(double centerX, double centerY, double radius, double angleInDegrees) {
    double angleInRadians = (angleInDegrees - 90) * M_PI / 180;
    return std::make_tuple(centerX + (radius * cos(angleInRadians)), centerY + (radius * sin(angleInRadians)));
}

std::tuple<std::string, double, double>
generateArc(double x, double y, double radius, double startAngle, double endAngle) {
    std::stringstream arc;
    auto[startX, startY] = polarToCartesian(x, y, radius, endAngle);
    auto[endX, endY] = polarToCartesian(x, y, radius, startAngle);

    int largeArcFlag = endAngle - startAngle <= 180 ? 0 : 1;

    arc << "M " << startX << " " << startY << " A " << radius << " " << radius << " 0 " << largeArcFlag << " 0 "
        << endX << " " << endY;
    return std::make_tuple(arc.str(), startX, startY); // TODO : choose better pos
}


std::string generateAutomatonSVG() {
    std::stringstream nodesCircles, nodesLabels, initialStates, finalStates, global;

    nodesCircles << "<!-- nodes -->\n<g stroke-width='2'>\n";
    nodesLabels << "<!-- label for nodes -->\n<g dominant-baseline='middle' text-anchor='middle' fill='black'>\n";
    initialStates << "<!-- initial states -->\n<g fill='none' stroke='red' marker-end='url(#head)'>\n";
    finalStates << "<!-- final states -->\n<g fill='none' stroke='red' marker-end='url(#head)'>\n";

    for (auto &node : NODES) {
        nodesCircles << "<circle cx='" << node.xPos << "' cy='" << node.yPos << "' r='" << node.size << "' stroke='"
                     << node.color << "' fill='" << node.backgroundColor << "'/>\n";

        nodesLabels << "<text x='" << node.xPos << "' y='" << node.yPos << "'>" << node.label << "</text>\n";

        if (!node.initial.empty()) {
            std::string path = generateArrow(node.xPos, node.yPos, node.size, "initial", node.initial);
            initialStates << "<path d='" << path << "'/>\n";
        }
        if (!node.final.empty()) {
            std::string path = generateArrow(node.xPos, node.yPos, node.size, "final", node.final);
            finalStates << "<path d='" << path << "'/>\n";
        }
    }

    global << nodesCircles.str() << "</g>\n" << nodesLabels.str() << "</g>\n" << initialStates.str() << "</g>\n"
           << finalStates.str() << "</g>\n" + generateEdges();
    return global.str();
}

std::string generateEdgeLabels(double x, double y, const std::string &label) {
    std::stringstream edgeLabelTextSVG;
    edgeLabelTextSVG << "<text x='" << x << "' y='" << y << "'>" << label
                     << "</text>\n";
    return edgeLabelTextSVG.str();
}

std::string generateEdges() {
    std::stringstream edges, labels;
    edges << "<!-- edges -->\n<g stroke='black' fill='none' marker-end='url(#head)'>\n";
    labels << "<!-- label for edges -->\n<g fill='black' text-anchor='middle'>\n";

    for (auto &edge : EDGES) {
        auto nodesIterator = NODES.begin();
        std::advance(nodesIterator, getNodeIndex(edge.source));
        Node sourceNode = *nodesIterator;

        nodesIterator = NODES.begin();
        std::advance(nodesIterator, getNodeIndex(edge.dest));
        Node destNode = *nodesIterator;

        std::string curvePath;
        double lx, ly;

        if (edge.source == edge.dest) { // create an arc
            auto[path, cx1, cy1] = generateArc(sourceNode.xPos + sourceNode.size,
                                               sourceNode.yPos + sourceNode.size, sourceNode.size, 0,
                                               270); // TODO: change radius parameter ?
            curvePath = path;
            lx = cx1 + 2 * sourceNode.size;
            ly = cy1 + 2 * sourceNode.size;
        } else {
            auto[sx1, sy1, sx2, sy2] = getSegmentEndpointsBetweenTwoCircles(sourceNode.xPos, sourceNode.yPos,
                                                                            sourceNode.size, destNode.xPos,
                                                                            destNode.yPos, destNode.size);
            std::tuple<std::string, double, double> curveAndLabelPos;
            if (sourceNode.xPos == destNode.xPos || sourceNode.yPos == destNode.yPos) { // lines
                curveAndLabelPos = generateCurvedArrowBetweenPoints(sx1, sy1, sx2, sy2, 0);
            } else {
                curveAndLabelPos = generateCurvedArrowBetweenPoints(sx1, sy1, sx2, sy2);
            }
            curvePath = std::get<0>(curveAndLabelPos);
            lx = std::get<1>(curveAndLabelPos);
            ly = std::get<2>(curveAndLabelPos);
        }
        edges << "<path d='" << curvePath << "'/>\n";
        labels << generateEdgeLabels(lx, ly, edge.label);
    }

    edges << "</g>\n";
    labels << "</g>\n";
    return edges.str() + labels.str();
}

std::tuple<std::string, double, double>
generateCurvedArrowBetweenPoints(double x1, double y1, double x2, double y2, double offset) {
    std::stringstream curve;
    double mpx = (x2 + x1) * 0.5;
    double mpy = (y1 + y2) * 0.5;
    double theta = std::atan2(y2 - y1, x2 - x1) - M_PI / 2;
    double cx1 = mpx + offset * cos(theta);
    double cy1 = mpy + offset * sin(theta);
    curve << "M" << x1 << " " << y1 << " Q " << cx1 << " " << cy1 << " " << x2 << " " << y2;
    return std::make_tuple(curve.str(), cx1, cy1);
}

void dumpSVG(const std::string &outputFile) {

    std::stringstream svgContent, svgNodes, svgNodesLabels;
    std::list<std::string> nodesPaths, nodesIOArrowsPaths;

    svgContent << "<svg xmlns='http://www.w3.org/2000/svg' xmlns:xlink='http://www.w3.org/1999/xlink' "
                  "width='800' height='600' viewBox='0 0 800 600'>\n\n"
                  "<rect x='0' y='0' width='800' height='600' fill='none' stroke='black' "
                  "stroke-width='2'/>\n"
                  "<defs>\n<marker id='head' orient='auto' markerWidth='10' markerHeight='10'\n"
                  "refX='10' refY='5'>\n<path d='M 0 0 V 10 L 10 5 Z' fill='black' />\n</marker>\n</defs>\n\n"
               << generateAutomatonSVG() << "</svg>";

    std::ofstream fileStream;
    fileStream.open(outputFile);
    fileStream << svgContent.str();
    fileStream.close();
}