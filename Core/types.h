#ifndef TYPES_H
#define TYPES_H
#include <string>

enum error_types{
    MISSING_TAG,
    WRONG_TAG
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

class tree_node
{
private:
	std::string name;
	std::string data;
	std::string attr;
	std::vector<tree_node *> children;

public:
	tree_node(std::string tag, std::string node_data, std::string node_attr)
	{
		name = tag;
		data = node_data;
		attr = node_attr;
	}
	std::string get_name()
	{
		return name;
	}
	void set_name(std::string node_name)
	{
		name = node_name;
	}
	std::string get_attr()
	{
		return attr;
	}
	void set_attr(std::string node_attr)
	{
		attr = node_attr;
	}
	std::string get_data()
	{
		return data;
	}
	void set_data(std::string node_data)
	{
		data = node_data;
	}
	void add_child(tree_node *child)
	{
		children.push_back(child);
	}
	tree_node *pop_child()
	{
		tree_node *child = children.back();
		children.pop_back();
		return child;
	}
};

#endif