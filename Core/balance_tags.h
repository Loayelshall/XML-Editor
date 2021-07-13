#ifndef BALANCE_TAGS_H
#define BALANCE_TAGS_H
#include <string>
#include <stack>
#include <iostream>
#include <vector>
#include "types.h"
#include <QVector>
#include <QStack>

void report_error(error_types error_type, int start_index, QVector<balance_error> &balance_error_arr);
QVector<balance_error> balance_tags(std::string xml_string);
#endif
