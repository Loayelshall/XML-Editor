#ifndef XML2JSON_H
#define XML2JSON_H
#include <string>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "types.h"

int xml2json(tree_node *root, int level, std::string *input, std::vector<std::string> children_data_arr = std::vector<std::string>(1, "main"));
#endif