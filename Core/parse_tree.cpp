#include "parse_tree.h"

void parse_tree(tree_node *root, std::string xml_string)
{
	std::stack<tree_node *> node_stack;
	node_stack.push(root);
	std::string tag, attr, data;
	for (size_t i = 0; i < xml_string.size(); i++)
	{
		if (xml_string[i] == '<' && xml_string[i + 1] != '/')
		{
			i++;
			for (; xml_string[i] != '>' && xml_string[i] != ' '; i++)
			{
				tag.push_back(xml_string[i]);
			}
			if (xml_string[i] == ' ')
			{
				i++;
				for (; xml_string[i] != '>'; i++)
				{
					attr.push_back(xml_string[i]);
				}
			}

			tree_node *temp = new tree_node(tag, data, attr);
			node_stack.top()->add_child(temp);
			tag.clear();
			attr.clear();
			if (xml_string[i - 1] != '/')
			{
				node_stack.push(temp);
			}
			
		}
		else if (xml_string[i] == '<' && xml_string[i + 1] == '/')
		{
			node_stack.top()->set_data(data);
			i += node_stack.top()->get_name().length() + 2;
			node_stack.pop();
			data.clear();
		}
		else if (xml_string[i] != '\n' && xml_string[i] != '\r' && xml_string[i] != ' ')
		{
			for (; xml_string[i] != '<'; i++)
			{
				data.push_back(xml_string[i]);
			}
			i--;
		}
		else if (xml_string[i] == '<' && xml_string[i + 1] == '!')
		{
			i += 3;
			for (; xml_string[i] != '-'; i++)
			{
				data.push_back(xml_string[i]);
			}
			tree_node *temp = new tree_node("Comment", data, "");
			data.clear();
			node_stack.top()->add_child(temp);
			i += 2;
		}
	}
}