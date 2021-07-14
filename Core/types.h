#ifndef TYPES_H
#define TYPES_H
#include <string>

enum error_types{
    MISSING_TAG,
    WRONG_TAG,
    COMMENT_CLOSE,
    XML_CLOSE
};

typedef struct
{
    std::string name;
    int start_index;
} tag;

typedef struct
{
    int type;
    int index;
} balance_error;

#endif