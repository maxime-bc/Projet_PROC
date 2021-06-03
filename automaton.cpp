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
    for (const Edge &edge : EDGES_LIST) {
        std::list<std::string> letters = split(edge.label, ',');

        for (const auto &letter : letters) {
            alphabet.insert(letter);
        }
    }
    return alphabet;
}

bool isNodeComplete(const Node &node, const std::set<std::string> &alphabet) {

    std::set<std::string> nodeLetters;

    for (auto edge = EDGES_LIST.begin(); edge != EDGES_LIST.end();) {
        if (edge->source == node.id) {
            std::list<std::string> letters = split(edge->label, ',');
            nodeLetters.insert(letters.begin(), letters.end());
        }
        edge++;
    }

    return std::all_of(alphabet.begin(), alphabet.end(), [&nodeLetters](const std::string &letter) {
        auto it = std::find(nodeLetters.begin(), nodeLetters.end(), letter);
        return !(it == nodeLetters.end());
    });
}

void completeNode(const Node &node, const std::string &wellId, const std::set<std::string> &alphabet) {

    std::set<std::string> nodeLetters, lettersToAdd;

    for (const auto &edge:  EDGES_LIST) {
        if (edge.source == node.id) {
            std::list<std::string> letters = split(edge.label, ',');
            nodeLetters.insert(letters.begin(), letters.end());
        }
    }

    for (const auto &letter : alphabet) {
        auto it = std::find(nodeLetters.begin(), nodeLetters.end(), letter);
        if (it == nodeLetters.end()) {
            lettersToAdd.insert(letter);
        }
    }

    if (!lettersToAdd.empty()) {
        createEdge(node.id, wellId, join(lettersToAdd.begin(), lettersToAdd.end(), ','));
    }
}


bool isComplete(const std::string &color) {
    std::set<std::string> alphabet = getAlphabet();
    bool isComplete = false;

    for (auto &node : NODES_LIST) {
        isComplete = isNodeComplete(node, alphabet);
        if (!isComplete && !color.empty()) {
            node.backgroundColor = color;
        }
    }
    return isComplete;
}

template<typename Iter>
std::string join(Iter begin, Iter end, char separator) {
    std::string s;

    while (begin != end) {
        s += *begin;
        s += separator;
        ++begin;
    }

    if (!s.empty()) {
        s.pop_back();
    }
    return s;
}

void complete(const std::string &wellId, float xPos, float yPos) {

    if (isComplete()) {
        std::cerr << "ERROR : automaton is already complete." << std::endl;
        return;
    }

    std::set<std::string> alphabet = getAlphabet();
    createNode(wellId, xPos, yPos);

    for (const auto &node : NODES_LIST) {
        completeNode(node, wellId, alphabet);
    }
}

int countInitialStates() {
    int initialStates = 0;
    for (const auto &node : NODES_LIST) {
        if (!node.initial.empty()) {
            initialStates += 1;
        }
    }
    return initialStates;
}

bool isNodeDeterministic(const Node &node, const std::set<std::string> &alphabet, const std::string &color) {

    bool isDeterministic = true;

    // 1 - retrieve all symbols from edges starting from node.
    // If symbols appears more than one time, node is not deterministic.
    std::set<std::string> viewedLetters;
    for (auto edge = EDGES_LIST.begin(); edge != EDGES_LIST.end();) {
        if (edge->source == node.id) {
            std::list<std::string> letters = split(edge->label, ',');
            for (const auto &letter : letters) {
                // if the letter was already seen
                if (viewedLetters.find(letter) != viewedLetters.end()) {
                    if (!color.empty()) {
                        edge->color = color;
                    }
                    isDeterministic = false;
                } else {
                    viewedLetters.insert(letter);
                }
            }
        }
        edge++;
    }

    // 2 - check if entire alphabet is used
    for (const auto &letter: alphabet) {
        if (viewedLetters.find(letter) == viewedLetters.end()) {
            isDeterministic = false;
            break;
        }
    }
    return isDeterministic;
}

Node getInitialState() {

    int index = 0;
    for (const Node &node : NODES_LIST) {
        if (!node.initial.empty()) {
            break;
        }
        index += 1;
    }

    auto initialState = NODES_LIST.begin();
    std::advance(initialState, index);
    return *initialState;
}

int getNextNodeIndex(const Node &currentNode, char symbol) {

    for (const auto &edge : EDGES_LIST) {
        if (edge.source == currentNode.id) {
            std::list<std::string> letters = split(edge.label, ',');

            if (std::any_of(letters.cbegin(), letters.cend(),
                            [&symbol](const std::string &x) { return x.at(0) == symbol; })) {
                return getNodeIndex(edge.dest);
            }
        }
    }
    return -1;
}

std::tuple<bool, std::list<std::string>> traverse(const Node &node, const std::string &word) {

    std::list<std::string> traversedNodesLabels;
    Node currentNode = node;
    int strIndex = 0;

    traversedNodesLabels.push_back(currentNode.label);

    while (strIndex < word.length()) {
        int nextNodeIndex = getNextNodeIndex(currentNode, word.at(strIndex));

        auto destNode = NODES_LIST.begin();
        std::advance(destNode, nextNodeIndex);
        currentNode = *destNode;
        traversedNodesLabels.push_back(currentNode.label);
        strIndex++;
    }

    return std::make_tuple(!currentNode.final.empty(), traversedNodesLabels);
}

bool isDeterministic(const std::string &color) {
    std::set<std::string> alphabet = getAlphabet();
    if (countInitialStates() != 1) {
        return false;
    }

    return std::all_of(NODES_LIST.begin(), NODES_LIST.end(), [&alphabet, &color](const Node &node) {
        return isNodeDeterministic(node, alphabet, color);
    });
}

bool isAccepted(const std::string &word, bool showPath) {

    if (!isDeterministic()) {
        std::cerr << "ERROR : automaton is not deterministic." << std::endl;
        return false;
    }

    auto[isAccepted, traversedNodes] = traverse(getInitialState(), word);

    if (showPath) {
        std::string joinedNodes = join(traversedNodes.begin(), traversedNodes.end(), ',');
        if (isAccepted) {
            std::cout << joinedNodes << std::endl;
        } else {
            std::cerr << joinedNodes << "\nERROR : " << word << " is not accepted by automaton." << std::endl;
        }
    }
    return isAccepted;
}