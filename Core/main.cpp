#include <string>
#include <fstream>
#include <streambuf>
#include <iostream>
#include "balance_tags.h"

void xml_to_string(std::string file_path, std::string &destination)
{
    std::ifstream file_stream(file_path);

    file_stream.seekg(0, std::ios::end);
    destination.reserve(file_stream.tellg());
    file_stream.seekg(0, std::ios::beg);
    destination.assign((std::istreambuf_iterator<char>(file_stream)),
                       std::istreambuf_iterator<char>());
    return;
}

int main()
{
    std::string str;
    xml_to_string("test.xml", str);
    balance_tags(str);
    // std::cout << str;
}
