#ifndef SVG_H
#define SVG_H

#include <string>

std::string generateNodeSVG(const Node &node);

std::string generateSVGNodeLabel(const Node &node);

void dumpSVG(const std::string& outputFile);

#endif //SVG_H
