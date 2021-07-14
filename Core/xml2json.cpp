#include "prettifying.h"

void xml2json(tree_node *root, int level, std::string *input)
{
    //comment
    if (root->get_name() == "Comment")
    {
        // *input += "<!--" + root->get_data() + "-->\n";
        return;
    }

    // children
    std::vector<tree_node *> children = root->get_children();

    //opening tag
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
        if (root->get_attr() != "")
        {
            *input += "<" + root->get_name() + " " + root->get_attr() + ">\n";
        }
        else
        {
            if (children.size())
            {
                *input += "\"" + root->get_name() + "\": {\n";
            }
            else
            {
                *input += "\"" + root->get_name() + "\": " + "\"" + root->get_data() + "\",\n";
            }
        }
    }

    for (int i = 0; i < children.size(); i++)
    {
        xml2json(children[i], level + 1, input);
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
            *input += "}\n";
        }
    }
    return;
}