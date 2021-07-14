#ifndef TYPES_H
#define TYPES_H
#include <string>

#define COMMENT_TAG "xml,comment"

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

typedef struct
{
    std::string key;
    std::string value;
} attribute;

class tree_node
{
private:
	std::string name;
	std::string data;
	std::vector<attribute> attr;
	std::vector<tree_node *> children;

public:
	tree_node(std::string tag, std::string node_data, std::vector<attribute> node_attr = std::vector<attribute>())
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
	std::vector<attribute> get_attr()
	{
		return attr;
	}
	void set_attr(std::vector<attribute> node_attr)
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
	std::vector<tree_node *> get_children(){
		return children;
	}
};

#endif