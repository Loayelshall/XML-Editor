#ifndef BALANCE_TAGS_H
#define BALANCE_TAGS_H
#include <string>
#include <stack>
#include <iostream>
#include <vector>
#include "types.h"

void report_error(error_types error_type, int start_index, std::vector<balance_error> &balance_error_arr);
void balance_tags(std::string xml_string);
#endif