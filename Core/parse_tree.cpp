#include "parse_tree.h"

std::string trim(const std::string &s)
{
	auto start = s.begin();
	while (start != s.end() && std::isspace(*start))
	{
		start++;
	}

	auto end = s.end();
	do
	{
		end--;
	} while (std::distance(start, end) > 0 && std::isspace(*end));

	return std::string(start, end + 1);
}

std::vector<attribute> trim_attributes(std::string attr_string)
{
	attribute attr;
	std::vector<attribute> attr_vector;
	bool key_ready = 0, value_ready = 0;
	for (size_t i = 0; i < attr_string.length(); i++)
	{
		if (attr_string[i] != ' ')
		{
			if (attr_string[i] == '"')
			{
				i++;
				for (; attr_string[i] != '"'; i++)
				{
					attr.value.push_back(attr_string[i]);
				}
				key_ready = 1;
			}
			else
			{
				for (; attr_string[i] != '=' && attr_string[i] != ' ' && attr_string[i] != '\n' && attr_string[i] != '\r'; i++)
				{
					attr.key.push_back(attr_string[i]);
				}
				value_ready = 1;
			}
		}
		if (value_ready && key_ready)
		{
			attr_vector.push_back(attr);
			attr.key.clear();
			attr.value.clear();
			value_ready = 0;
			key_ready = 0;
		}
	}
	return attr_vector;
}

void parse_tree(tree_node *root, std::string xml_string)
{
	std::stack<tree_node *> node_stack;
	node_stack.push(root);
	int xmlTags = 0;
	std::string tag, attr, data;
	std::vector<attribute> attr_vector;
	for (size_t i = 0; i < xml_string.size(); i++)
	{
		if(xml_string[i] == '<' && xml_string[i + 1] == '?'){
			
			i += 2;
			for(; xml_string[i] != '?' && xml_string[i+1] != '>'; i++){
				data.push_back(xml_string[i]);
			}
			
			
			if(!xmlTags){
				node_stack.top()->set_data(data);
				xmlTags++;
			} else {
				tree_node *temp = new tree_node("XML", data);
				node_stack.top()->add_child(temp);		
			}
		
			data.clear();
			i += 2;
		} else if (xml_string[i] == '<' && xml_string[i + 1] != '/')
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
				attr_vector = trim_attributes(attr);
			}
			tree_node *temp = new tree_node(tag, data, attr_vector);
			node_stack.top()->add_child(temp);
			tag.clear();
			attr_vector.clear();
			if (xml_string[i - 1] != '/')
			{
				node_stack.push(temp);
			}
		}
		else if (xml_string[i] == '<' && xml_string[i + 1] == '/')
		{
			data = trim(data);
			node_stack.top()->set_data(data);
			i += node_stack.top()->get_name().length() + 2;
			node_stack.pop();
			data.clear();
		}
		else if (xml_string[i] != '\n' && xml_string[i] != '\r' && xml_string[i] != ' ')
		{
			for (; xml_string[i] != '<'; i++)
			{
				if (xml_string[i] != '\n' && xml_string[i] != '\r')
				{
					data.push_back(xml_string[i]);
				}
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
			tree_node *temp = new tree_node("Comment", data);
			data.clear();
			node_stack.top()->add_child(temp);
			i += 2;
		} 
	}
}