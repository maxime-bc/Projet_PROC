#include <iostream>
#include <string>
#include <sstream>
#include "automaton.h"
#include "edge.h"
#include "node.h"
#include <algorithm>
#include <set>

std::list<std::string> split(std::string const &str, char delimiter) {
    std::list<std::string> out;
    size_t start;
    size_t end = 0;

    while ((start = str.find_first_not_of(delimiter, end)) != std::string::npos) {
        end = str.find(delimiter, start);
        out.push_back(str.substr(start, end - start));
    }
    return out;
}

std::set<std::string> getAlphabet() {

    std::set<std::string> alphabet;
    for (const Edge &edge : EDGES) {
        std::list<std::string> tmp = split(edge.label, ',');

        for (const auto &v : tmp) {
            alphabet.insert(v);
        }
    }
    return alphabet;
}

bool isNodeComplete(const Node &node, const std::set<std::string> &labels) {

    std::set<std::string> allLabels;
    for (auto edge = EDGES.begin(); edge != EDGES.end();) {
        if (edge->source == node.id) {
            std::list<std::string> tmp = split(edge->label, ',');
            for (const auto &v : tmp) {
                allLabels.insert(v);
            }
        }
        edge++;
    }

    for (const auto &v : labels) {
        auto it = std::find(allLabels.begin(), allLabels.end(), v);
        if (it == allLabels.end()) {
            return false;
        }
    }
    return true;
}

bool isComplete() {
    std::set<std::string> alphabet = getAlphabet();

    if (NODES.empty() || EDGES.empty()) {
        return false;
    }

    for (const auto &node : NODES) {
        if (!isNodeComplete(node, alphabet)) {
            return false;
        }
    }
    return true;
}