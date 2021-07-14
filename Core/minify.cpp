#include "minify.h"

void minify(tree_node *root, std::string* input){
    //comment
    if(root->get_name() == COMMENT_TAG){
        *input += "<!--" + root->get_data() + "-->";
        return; 
    }
  


    //opening tag
    if(root->get_name() != "XML"){
          
        std::vector<attribute> attr = root->get_attr();
        if(attr.size() != 0){
            *input += "<" + root->get_name() + " ";
            for (int j = 0; j < attr.size(); j++)
            {
                *input += attr[j].key + "=\"" + attr[j].value + "\" ";
                if(j != attr.size() - 1){
                    *input += " ";
                }
            }
            *input += ">";
        } else {
            *input += "<" + root->get_name() + ">";
        }
    } else {
        if(!root->get_data().empty()){             
            *input += "<?" + root->get_data() + "?>";
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