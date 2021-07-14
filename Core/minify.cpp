#include "minify.h"

void minify(tree_node *root, std::string* input){
    //comment
    if(root->get_name() == "Comment"){
        *input += "<!--" + root->get_data() + "-->";
        return; 
    }

    //opening tag
    if(root->get_name() != "XML"){
        if(root->get_attr() != ""){
            *input += "<" + root->get_name() + " " + root->get_attr() + ">";           
        } else {
            *input += "<" + root->get_name() + ">";
        }
    }

    // children
    std::vector<tree_node *> children = root->get_children();
    for (int i = 0; i < children.size(); i++)
    {
        minify(children[i], input);
    }

    if(children.size() == 0){
        std::string data = root->get_data();    
        *input += data;

    }
    
    if(root->get_name() != "XML"){
        //closing tag
        *input += "<" + root->get_name() + "/>";
    }
    
    return;

}