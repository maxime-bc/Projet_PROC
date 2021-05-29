#ifndef SVG_H
#define SVG_H

#include <string>
#include "node.h"

std::tuple<double, double, double, double>
getSegmentEndpointsBetweenTwoCircles(double x1, double y1, double r1, double x2, double y2, double r2);

std::tuple<double, double> getPositionByDegree(double x, double y, double radius, double degree);

std::string generateAutomatonSVG(const std::list<std::tuple<std::string, std::string>> &edgesToAnimate = {},
                                 bool isAccepted = false);

std::string generateArrow(double xPos, double yPos, double size, const std::string &type, const std::string &direction);

std::string generateEdgeLabels(double x, double y, const std::string &label);

void dumpSVG(const std::string &outputFile);

void dumpSVGWithWord(const std::string &outputFile, const std::string &word);

std::string generateStyle(int nodesCount, double delay);

bool edgeToAnimate(const std::string &source, const std::string &dest,
                   const std::list<std::tuple<std::string, std::string>> &edgesToAnimate);

std::tuple<std::string, double, double>
generateCurvedArrowBetweenPoints(double x1, double y1, double x2, double y2, double offset = 15);

std::string generateEdges(const std::list<std::tuple<std::string, std::string>> &edgesToAnimate = {}, bool = false);

std::string
generateFrame(int frameId, const std::string &path, double cx, double cy, double size, double lx, double ly,
              const std::string &nodeLabel, const std::string &edgeLabel, bool isAccepted);

#endif //SVG_H
