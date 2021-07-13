#include <string>
#include <fstream>
#include <streambuf>
#include <iostream>
#include <vector>
#include <stack>
#include "types.h"
#include "parse_tree.h"
#include "prettifying.h"

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
	std::string xml_string;
	xml_to_string("fixed.xml", xml_string);
	tree_node *root = new tree_node("XML", "", "");
	parse_tree(root, xml_string);
	

	
	std::string out = "";
	pretty(root, -1, &out);
	std::cout << out;

}
