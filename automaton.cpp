#include <iostream>
#include <string>
#include <sstream>
#include "automaton.h"
#include "edge.h"
#include "node.h"
#include <algorithm>
#include <iterator>
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
        std::list<std::string> letters = split(edge.label, ',');

        for (const auto &letter : letters) {
            alphabet.insert(letter);
        }
    }
    return alphabet;
}

bool isNodeComplete(const Node &node, const std::set<std::string> &alphabet) {

    std::set<std::string> nodeLetters;

    for (auto edge = EDGES.begin(); edge != EDGES.end();) {
        if (edge->source == node.id) {
            std::list<std::string> letters = split(edge->label, ',');
            for (const auto &letter : letters) {
                nodeLetters.insert(letter);
            }
        }
        edge++;
    }

    for (const auto &letter : alphabet) {
        auto it = std::find(nodeLetters.begin(), nodeLetters.end(), letter);
        if (it == nodeLetters.end()) {
            return false;
        }
    }
    return true;
}

void completeNode(const Node &node, const std::string &wellId, const std::set<std::string> &alphabet) {

    std::set<std::string> nodeLetters;
    std::set<std::string> lettersToAdd;

    std::cout << "node " << node.id << std::endl;

    for (const auto &edge:  EDGES) {
        if (edge.source == node.id) {
            std::list<std::string> letters = split(edge.label, ',');

            std::cout << "letters" << std::endl;
            for (const auto &l : letters) {
                std::cout << l << std::endl;
            }
            std::cout << "end letter" << std::endl;

            for (const auto &letter : letters) {
                nodeLetters.insert(letter);
            }
        }
    }

    for (const auto &letter : alphabet) {
        auto it = std::find(nodeLetters.begin(), nodeLetters.end(), letter);
        if (it == nodeLetters.end()) {
            lettersToAdd.insert(letter);
        }
    }


    std::cout << "letterToAdd" << std::endl;
    for (const auto &l : lettersToAdd) {
        std::cout << l << std::endl;
    }
    std::cout << "end letterToAdd" << std::endl;

    createEdge(node.id, wellId, joinSet(lettersToAdd, ','));
}


bool isComplete(const std::string &color) {
    std::set<std::string> alphabet = getAlphabet();
    bool isComplete = false;

    for (auto &node : NODES) {
        isComplete = isNodeComplete(node, alphabet);
        if (!isComplete && !color.empty()) {
            node.backgroundColor = color;
        }
    }
    return isComplete;
}

std::string joinSet(const std::set<std::string> &set, char separator) {
    std::string s;

    for (auto const &e : set) {
        s += e;
        s += separator;
    }
    return s;
}

void complete(const std::string &wellId, float xPos, float yPos) {

    std::set<std::string> alphabet = getAlphabet();
    createNode(wellId, xPos, yPos);

    for (const auto &node : NODES) {
        completeNode(node, wellId, alphabet);
    }
}