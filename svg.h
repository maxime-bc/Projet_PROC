#ifndef SVG_H
#define SVG_H

#include <string>
#include "node.h"

std::tuple<double, double> getPositionByDegree(double x, double y, double radius, double degree);

std::string generateNodeSVG(const Node &node);

std::string generateSVGNodeLabel(const Node &node);

std::string generateArrow(double xPos, double yPos, double size, const std::string &type, const std::string &direction);

std::string generateEdgeLabelTextSVG(double x, double y, const std::string &label);

void dumpSVG(const std::string &outputFile);

std::tuple<std::string, double, double>
generateCurvedArrowBetweenPoints(float x1, float y1, float x2, float y2, double offset = 30);

std::string generateEdgesSVG();

#endif //SVG_H
