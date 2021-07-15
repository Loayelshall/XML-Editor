#include "prettifying.h"

void pretty(tree_node *root, int level,std::string* input){
    //comment
    if(root->get_name() == COMMENT_TAG){
        *input += "<!--" + root->get_data() + "-->\n";
        return; 
    }

    //opening tag
   
    if(root->get_name() != "XML"){
        if(root->get_name() == "XML,TAG"){
            *input += "<?" + root->get_data() + "?>\n";
        } else {
            for (int i = 0; i < level; i++)
            {
                *input += "    ";
            }
            std::vector<attribute> attr = root->get_attr();
            if(attr.size() != 0){
                *input += "<" + root->get_name() + " ";
                for (int j = 0; j < attr.size(); j++)
                {
                    *input += attr[j].key + "=\"" + attr[j].value + "\"";
                    if(j != attr.size()-1){
                        *input += " ";
                    }
                }
                *input += ">\n";
            } else {
                *input += "<" + root->get_name() + ">\n";
            }
        }
    } else {
        if(root->get_data() != ""){
            *input += "<?" + root->get_data() + "?>\n";
        }
    }

    // children
    std::vector<tree_node *> children = root->get_children();
    for (int i = 0; i < children.size(); i++)
    {
        pretty(children[i], level + 1, input);
    }

    if(children.size() == 0){
        if(root->get_name() != "XML"  && root->get_name() != "XML,TAG"){
            for (int i = 0; i <= level; i++)
            {
                *input += "    ";
            }
            std::string data = root->get_data();
            if(data[data.length()-1] != '\n'){ 
                *input += root->get_data() + "\n";
            }    
        }
        
    }
    
    if(root->get_name() != "XML" && root->get_name() != "XML,TAG"){
        //closing tag
        for (int i = 0; i < level; i++)
        {
            *input += "    ";
        }
        *input += "</" + root->get_name() + ">\n";
    }
    
    return;

}
