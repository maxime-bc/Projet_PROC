#ifndef SVG_H
#define SVG_H

#include <string>
#include "node.h"

std::string generateNodeSVG(const Node &node);

std::string generateSVGNodeLabel(const Node &node);

std::string generateEdgeLabelTextSVG(double x, double y, const std::string &label);

void dumpSVG(const std::string &outputFile);

std::tuple<std::string, double, double> generateCurvedArrowBetweenPoints(float x1, float y1, float x2, float y2);

std::string generateEdgesSVG();

#endif //SVG_H
