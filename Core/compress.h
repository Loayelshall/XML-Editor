#ifndef COMPRESS_H
#define COMPRESS_H
#include <string>
#include <iostream>
#include <stdlib.h>
#include <unordered_map>
#include <vector>
#include "types.h"

std::vector<int> compress(std::string in);
std::string decompress(std::vector<int> in);

#endif