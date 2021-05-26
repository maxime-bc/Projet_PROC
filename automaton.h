#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <list>
#include "node.h"
#include <set>

std::list<std::string> split(std::string const &str, char delimiter);

std::set<std::string> getAlphabet();

bool isComplete(const std::string &color = "");

void completeNode(const Node &node, const std::string &wellId, const std::set<std::string> &alphabet);

bool isNodeComplete(const Node &node, const std::set<std::string> &alphabet);

template<typename Iter>
std::string join(Iter begin, Iter end, char separator);

void complete(const std::string &wellId, float xPos, float yPos);

int countInitialStates();

bool isNodeDeterministic(const Node &node, const std::set<std::string> &alphabet, const std::string &color);

bool isDeterministic(const std::string &color = "");

bool traverse(const Node &node, std::string &word, bool showPath);

bool isAccepted(const std::string &word, bool showPath = false);

int getNextNodeIndex(const Node &currentNode, char symbol);

Node getInitialState();

#endif //AUTOMATON_H
