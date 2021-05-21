#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <list>
#include "node.h"
#include <set>

std::list<std::string> split(std::string const &str, char delimiter);

bool isComplete();

bool isNodeComplete(const Node &node, const std::set<std::string> &labels);

#endif //AUTOMATON_H
