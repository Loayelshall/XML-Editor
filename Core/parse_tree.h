#ifndef PARSE_TREE_H
#define PARSE_TREE_H
#include <string>
#include <stack>
#include <iostream>
#include <vector>
#include <cctype>
#include "types.h"

std::string trim(const std::string &s);
std::vector<attribute> trim_attributes(std::string attr_string);
void parse_tree(tree_node *root, std::string xml_string);
#endif