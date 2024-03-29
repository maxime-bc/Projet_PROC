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
#include "automaton.h"


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

std::tuple<double, double> getCenter(double x1, double y1, double x2, double y2) {
    return std::make_tuple((x1 + x2) / 2, (y1 + y2) / 2);
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

std::string
generateAutomatonSVG(const std::list<std::tuple<std::string, std::string>> &edgesToAnimate, bool isAccepted) {
    std::stringstream nodesCircles, nodesLabels, initialStates, finalStates, global;

    nodesCircles << "<!-- nodes -->\n<g stroke-width='2'>\n";
    nodesLabels << "<!-- label for nodes -->\n<g dominant-baseline='middle' text-anchor='middle' fill='black'>\n";
    initialStates << "<!-- initial states -->\n<g fill='none' stroke='red' marker-end='url(#head)'>\n";
    finalStates << "<!-- final states -->\n<g fill='none' stroke='red' marker-end='url(#head)'>\n";

    for (auto &node : NODES_LIST) {
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
           << finalStates.str() << "</g>\n" + generateEdges(edgesToAnimate, isAccepted);
    return global.str();
}

std::string generateEdgeLabels(double x, double y, const std::string &label) {
    std::stringstream edgeLabelTextSVG;
    edgeLabelTextSVG << "<text x='" << x << "' y='" << y << "'>" << label
                     << "</text>\n";
    return edgeLabelTextSVG.str();
}

bool edgeToAnimate(const std::string &source, const std::string &dest,
                   const std::list<std::tuple<std::string, std::string>> &edgesToAnimate) {

    for (auto edge: edgesToAnimate) {
        if (source == std::get<0>(edge) && dest == std::get<1>(edge)) {
            return true;
        }
    }
    return false;
}


std::string generateEdges(const std::list<std::tuple<std::string, std::string>> &edgesToAnimate, bool isAccepted) {
    std::stringstream edges, labels, frames;
    std::map<std::string, std::tuple<std::string, std::string, double, double>> pathAndLabelPos;

    edges << "<!-- edges -->\n<g fill='none' marker-end='url(#head)'>\n";
    labels << "<!-- label for edges -->\n<g fill='black' text-anchor='middle'>\n";
    int counter = 0;

    for (auto &edge : EDGES_LIST) {
        auto nodesIterator = NODES_LIST.begin();
        std::advance(nodesIterator, getNodeIndex(edge.source));
        Node sourceNode = *nodesIterator;

        nodesIterator = NODES_LIST.begin();
        std::advance(nodesIterator, getNodeIndex(edge.dest));
        Node destNode = *nodesIterator;

        std::string curvePath;
        double lx, ly;

        if (!edge.path.empty()) {
            curvePath = edge.path;
        } else if (edge.source == edge.dest) { // create an arc
            std::stringstream path;
            path << "M " << sourceNode.xPos + 5 << " " << sourceNode.yPos + sourceNode.size << " A 15 20 0 1 1 "
                 << sourceNode.xPos - 5 << " " << sourceNode.yPos + sourceNode.size;

            curvePath = path.str();
            lx = sourceNode.xPos + sourceNode.size;
            ly = sourceNode.yPos + sourceNode.size + 0.5 * sourceNode.size;
        } else {
            std::tuple<std::string, double, double> curveAndLabelPos;
            auto[sx1, sy1, sx2, sy2] = getSegmentEndpointsBetweenTwoCircles(sourceNode.xPos, sourceNode.yPos,
                                                                            sourceNode.size, destNode.xPos,
                                                                            destNode.yPos, destNode.size);
            curveAndLabelPos = generateCurvedArrowBetweenPoints(sx1, sy1, sx2, sy2);

            curvePath = std::get<0>(curveAndLabelPos);
            lx = std::get<1>(curveAndLabelPos);
            ly = std::get<2>(curveAndLabelPos);
        }
        edges << "<path d='" << curvePath << "' stroke='" << edge.color << "'/>\n";

        if ((edge.xPos != 0 && edge.yPos != 0) || !edge.path.empty()) {
            std::tuple<double, double> points = getCenter(sourceNode.xPos, sourceNode.yPos, destNode.xPos,
                                                          destNode.yPos);
            lx = std::get<0>(points) += edge.xPos;
            ly = std::get<1>(points) += edge.yPos;
        }

        labels << generateEdgeLabels(lx, ly, edge.label);
        pathAndLabelPos[edge.source + edge.dest] = std::make_tuple(curvePath, edge.label, lx, ly);
    }

    for (const auto &elem: edgesToAnimate) {
        const auto&[source, dest] = elem;
        const auto&[path, label, lx, ly] = pathAndLabelPos[source + dest];

        Node sourceNode = getNode(source);
        Node destNode = getNode(dest);

        frames << generateFrame(counter, path, lx, ly, sourceNode, label, isAccepted) << "\n";

        if (counter == edgesToAnimate.size() - 1) {
            // last edge, we need to add a frame for the last node and output arrow if accepted
            frames << generateLastFrame(counter + 1, destNode, isAccepted) << "\n";
        }
        counter += 1;
    }

    edges << "</g>\n";
    labels << "</g>\n";
    return edges.str() + labels.str() + frames.str();
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

std::string generateStyle(int nodesCount, double delay) {

    std::stringstream style;
    style << "<style type=\"text/css\">\n.frame { visibility: hidden;"
             " animation: frames " << nodesCount * delay << "s linear infinite\n}\n\n";

    for (int i = 0; i < nodesCount; ++i) {
        style << "#_frame_" << i << " { animation-delay: " << i * delay << "s }\n";
    }

    style << "\n@keyframes frames\n{ 0%  {visibility:visible}\n20% {visibility:hidden}\n}\n</style>";
    return style.str();
}

std::string
generateFrame(int frameId, const std::string &path, double lx, double ly, const Node &node,
              const std::string &edgeLabel, bool isAccepted) {
    std::stringstream frame;
    // TODO : add a last frame
    std::string fillColor, strokeColor;

    if (isAccepted) {
        fillColor = "lightGreen";
        strokeColor = "green";
    } else {
        fillColor = "lightCoral";
        strokeColor = "red";
    }

    frame << "<g id='_frame_" << frameId << "' class='frame'>\n<g stroke-width='2' >\n<circle stroke='" << strokeColor
          << "' fill='" << fillColor << "' cx='" << node.xPos << "' cy='" << node.yPos << "' r='" << node.size
          << "' />\n<path d='" << path
          << "' stroke='" << strokeColor << "' fill='none'/>\n";

    if (frameId == 0) { // first frame == draw input arrow
        std::string initialPath = generateArrow(node.xPos, node.yPos, node.size, "initial", node.initial);
        frame << "<!-- initial -->\n<path d='" << initialPath << "' stroke='" << strokeColor << "' fill='none'/>\n";
    }

    frame << "</g>\n<g text-anchor='middle' stroke='" << strokeColor
          << "'>\n" << "<text x='" << lx << "' y='" << ly << "'>" << edgeLabel
          << "</text>\n<text dominant-baseline='middle' x='" << node.xPos << "' y='" << node.yPos << "'>" << node.label
          << "</text>\n</g>\n</g>";

    return frame.str();

}

std::string generateLastFrame(int frameId, const Node &node, bool isAccepted) {
    std::stringstream frame;
    // TODO : add a last frame
    std::string fillColor, strokeColor;

    if (isAccepted) {
        fillColor = "lightGreen";
        strokeColor = "green";
    } else {
        fillColor = "lightCoral";
        strokeColor = "red";
    }

    frame << "<g id='_frame_" << frameId << "' class='frame'>\n<g stroke-width='2' >\n<circle stroke='" << strokeColor
          << "' fill='" << fillColor << "' cx='" << node.xPos << "' cy='" << node.yPos << "' r='" << node.size
          << "' />\n";

    if (isAccepted) {
        std::string finalPath = generateArrow(node.xPos, node.yPos, node.size, "final", node.final);
        frame << "<!-- final -->\n<path d='" << finalPath << "' stroke='green' fill='none'/>\n";
    }

    frame << "</g>\n<g text-anchor='middle' stroke='" << strokeColor
          << "'>\n" << "<text dominant-baseline='middle' x='" << node.xPos << "' y='" << node.yPos << "'>" << node.label
          << "</text>\n</g>\n</g>";

    return frame.str();
}

void dumpSVGWithWord(const std::string &outputFile, const std::string &word) {
    std::stringstream svgContent;
    std::list<std::tuple<std::string, std::string >> edgesToAnimate;

    if (!isDeterministic()) {
        std::cerr << "ERROR : automaton is not deterministic." << std::endl;
        return;
    }

    auto[isAccepted, traversedNodes] = traverse(getInitialState(), word);

    for (auto source = traversedNodes.begin(), dest = ++traversedNodes.begin();
         dest != traversedNodes.end(); ++source, ++dest) {
        edgesToAnimate.emplace_back(*source, *dest);
    }

    svgContent << "<svg xmlns='http://www.w3.org/2000/svg' xmlns:xlink='http://www.w3.org/1999/xlink' "
                  "width='800' height='600' viewBox='0 0 800 600'>\n\n"
               << generateStyle(edgesToAnimate.size() + 1, 1.5) <<
               "<rect x='0' y='0' width='800' height='600' fill='none' stroke='black' "
               "stroke-width='2'/>\n"
               "<defs>\n<marker id='head' orient='auto' markerWidth='10' markerHeight='10'\n"
               "refX='10' refY='5'>\n<path d='M 0 0 V 10 L 10 5 Z' fill='black' />\n</marker>\n</defs>\n\n"
               << generateAutomatonSVG(edgesToAnimate, isAccepted) << "</svg>";

    std::ofstream fileStream;
    fileStream.open(outputFile);
    fileStream << svgContent.str();
    fileStream.close();
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