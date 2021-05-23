#ifndef SVG_H
#define SVG_H

#include <string>
#include "node.h"

std::tuple<double, double, double, double>
getSegmentEndpointsBetweenTwoCircles(double x1, double y1, double r1, double x2, double y2, double r2);

std::tuple<double, double> getPositionByDegree(double x, double y, double radius, double degree);

std::string generateAutomatonSVG();

std::string generateArrow(double xPos, double yPos, double size, const std::string &type, const std::string &direction);

std::string generateEdgeLabels(double x, double y, const std::string &label);

void dumpSVG(const std::string &outputFile);

std::tuple<std::string, double, double>
generateCurvedArrowBetweenPoints(double x1, double y1, double x2, double y2, double offset = 30);

std::string generateEdges();

#endif //SVG_H
