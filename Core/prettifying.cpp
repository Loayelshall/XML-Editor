#include "prettifying.h"

void pretty(tree_node *root, int level,std::string input){
    //comment
    if(root->get_name() == "Comment"){
        input += "<!--" + root->get_data() + "-->\n";
        return; 
    }

    //opening tag
    for (int i = 0; i < level; i++)
    {
        input += "    ";
    }
    if(root->get_name() != "XML"){
        if(root->get_attr() != ""){
            input += "<" + root->get_name() + " " + root->get_attr() + ">\n";           
        } else {
            input += "<" + root->get_name() + ">\n";
        }
    }

    // children
    std::vector<tree_node *> children = root->get_children();
    for (int i = 0; i < children.size(); i++)
    {
        pretty(children[i], level + 1, input);
    }

    if(children.size() == 0){
        for (int i = 0; i <= level; i++)
        {
            input += "    ";
        }
        input += root->get_data() + "\n";

    }
    
    //closing tag
    for (int i = 0; i < level; i++)
    {
        input += "    ";
    }
    input += "<" + root->get_name() + "/>\n";
    return;

}