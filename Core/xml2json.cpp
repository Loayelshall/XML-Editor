#include "xml2json.h"

int xml2json(tree_node *root, int level, std::string *input, std::vector<tree_node *> children_data_arr)
{
    //comment
    if (root->get_name() == COMMENT_TAG)
    {
        return 0;
    }

    // children
    std::vector<tree_node *> children = root->get_children();
    std::map<std::string, std::vector<tree_node *>> children_data_map;
    std::map<std::string, int> children_data_wait;
    int remaining_children = 0;
    if (children.size())
    {
        for (auto child : children)
        {
            if (child->get_name() != COMMENT_TAG)
            {
                children_data_map[child->get_name()].push_back(child);
                children_data_wait[child->get_name()] = 1;
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
            if (children_data_arr.size() > 1)
            {
                if (root == children_data_arr.front())
                {
                    *input += "\"" + root->get_name() + "\": [{\n";
                }
                else
                {
                    *input += "{\n";
                }
            }
            else
            {
                *input += "\"" + root->get_name() + "\": {\n";
            }
            if (root->get_attr().size())
            {
                for (auto attr : root->get_attr())
                {
                    for (int i = 0; i < level + 2; i++)
                    {
                        *input += "    ";
                    }
                    *input += "\"@" + attr.key + "\": " + "\"" + attr.value + "\"";
                    if (attr.key == root->get_attr().back().key && attr.value == root->get_attr().back().value && root->get_data().empty() && children.empty())
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
                    size_t index = 0;
                    while (true)
                    {

                        index = root->get_data().find("\"", index);
                        if (index == std::string::npos)
                            break;
                        std::string data = root->get_data();
                        data.replace(index, index + 1, "\\\"");
                        root->set_data(data);
                        index += 2;
                    }
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
            size_t index = 0;
            while (true)
            {
                index = root->get_data().find("\"", index);
                if (index == std::string::npos)
                    break;
                std::string data = root->get_data();
                data.replace(index, index + 1, "\\\"");
                root->set_data(data);
                index += 2;
            }
            if (children_data_arr.size() > 1)
            {
                if (root == children_data_arr.front())
                {
                    *input += "\"" + root->get_name() + "\": [" + "\"" + root->get_data() + "\"";
                }
                else
                {
                    *input += "\"" + root->get_data() + "\"";
                }
            }
            else
            {
                *input += "\"" + root->get_name() + "\": " + "\"" + root->get_data() + "\"";
            }
        }
    }

    for (int i = 0; i < children.size(); i++)
    {
        if (children[i]->get_name() != COMMENT_TAG)
        {
            if (children_data_wait[children[i]->get_name()] == 0)
            {
                continue;
            }
            int remaning_children = std::accumulate(children_data_wait.begin(), children_data_wait.end(), 0, [](int value, const std::map<std::string, int>::value_type &p)
                                                    { return value + p.second; });
            for (auto child : children_data_map[children[i]->get_name()])
            {
                int status_check = xml2json(child, level + 1, input, children_data_map[children[i]->get_name()]);
                if (status_check)
                {
                    if ((remaning_children == 1 && child == children_data_map[children[i]->get_name()].back()) || children.size() == 1)
                    {
                        *input += "\n";
                    }
                    else
                    {
                        *input += ",\n";
                    }
                }
            }
            children_data_wait[children[i]->get_name()] = 0;
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
            if (children_data_arr.size() > 1 && children_data_arr.back() == root)
            {
                *input += "}]";
            }
            else
            {
                *input += "}";
            }
        }
        else
        {
            if (children_data_arr.size() > 1 && children_data_arr.back() == root)
            {
                *input += "]";
            }
        }
    }
    return 1;
}