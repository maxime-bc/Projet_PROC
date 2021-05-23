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

std::string joinSet(const std::set<std::string> &set, char separator);

void complete(const std::string &wellId, float xPos, float yPos);

#endif //AUTOMATON_H
