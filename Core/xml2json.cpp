#include "xml2json.h"

int xml2json(tree_node *root, int level, std::string *input, std::vector<std::string> children_data_arr)
{
    //comment
    if (root->get_name() == COMMENT_TAG || children_data_arr.empty())
    {
        return 0;
    }

    // children
    std::vector<tree_node *> children = root->get_children();
    std::map<std::string, std::vector<std::string>> children_data_map;

    //opening tag
    if (children.size())
    {
        for (auto child : children)
        {
            if (child->get_name() != COMMENT_TAG)
            {
                children_data_map[child->get_name()].push_back(child->get_data());
            }
        }
    }
    for (int i = 0; i < level + 1; i++)
    {
        *input += "    ";
    }
    if (root->get_name() == "XML")
    {
        *input += "{\n";
    }
    else
    {
        if (children.size() || root->get_attr().size())
        {
            *input += "\"" + root->get_name() + "\": {\n";
            if (root->get_attr().size())
            {
                for (auto attr : root->get_attr())
                {
                    for (int i = 0; i < level + 2; i++)
                    {
                        *input += "    ";
                    }
                    *input += "\"@" + attr.key + "\": " + "\"" + attr.value + "\"";
                    if (attr.key == root->get_attr().back().key && attr.value == root->get_attr().back().value && root->get_data().empty())
                    {
                        *input += "\n";
                    }
                    else
                    {
                        *input += ",\n";
                    }
                }
                if (!root->get_data().empty())
                {
                    for (int i = 0; i < level + 2; i++)
                    {
                        *input += "    ";
                    }
                    *input += "\"title\": \"" + root->get_data() + "\"\n";
                    for (int i = 0; i < level + 1; i++)
                    {
                        *input += "    ";
                    }
                    *input += "}";
                }
            }
        }
        else
        {
            if (children_data_arr.size() == 1)
            {
                *input += "\"" + root->get_name() + "\": " + "\"" + root->get_data() + "\"";
            }
            else
            {
                *input += "\"" + root->get_name() + "\": [";
                for (auto child_data : children_data_arr)
                {
                    *input += "\"" + child_data + "\"";
                    if (child_data != children_data_arr.back())
                    {
                        *input += ", ";
                    }
                }
                *input += "]";
            }
        }
    }

    for (int i = 0; i < children.size(); i++)
    {
        if (children[i]->get_name() != "xml,comment")
        {
            int status_check = xml2json(children[i], level + 1, input, children_data_map[children[i]->get_name()]);
            children_data_map.erase(children[i]->get_name());
            if (status_check)
            {
                if (children_data_map.empty())
                {
                    *input += "\n";
                }
                else
                {
                    *input += ",\n";
                }
            }
        }
    }

    if (root->get_name() == "XML")
    {
        *input += "}";
    }
    else
    {
        if (root->get_data().empty())
        {
            for (int i = 0; i < level + 1; i++)
            {
                *input += "    ";
            }
            *input += "}";
        }
    }
    return 1;
}