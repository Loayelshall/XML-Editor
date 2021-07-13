#include <string>
#include <fstream>
#include <streambuf>
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

void xml_to_string(std::string file_path, std::string &destination)
{
    std::ifstream file_stream(file_path);

    file_stream.seekg(0, std::ios::end);
    destination.reserve(file_stream.tellg());
    file_stream.seekg(0, std::ios::beg);
    destination.assign((std::istreambuf_iterator<char>(file_stream)),
                       std::istreambuf_iterator<char>());
    return;
}
class tree_Node{
private:
	string name;
	string data;
	string attr;
	vector <tree_Node*> children ;
	int numofchild;
public:
	tree_Node (string tag, string data, string attr)
{
		name=tag;
		numofchild=0;
		this ->data = data;
		this ->attr= attr;
}
	string get_data() {return data;}
	void add_child(tree_Node* child)
	{
		children.push_back(child);
		numofchild++;
	}
	 tree_Node* pop_child()
	{
        
		return children[numofchild--];
	}
};
void get_tree(tree_Node* root ,string str);
int main()
{
	string str;
	xml_to_string("test.xml", str);
	tree_Node root ("XML","","");
	get_tree(&root,str);
	/*stack <tree_Node*> Dstack;
	 Dstack.push(&root);
	string tag, attri;
	string data;
	/*for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == '<'&& str[i+1] != '/' )
		{
			i++;
			for ( int j = 0; str[i] != '>' && str[i] != ' '; j++, i++)
			{
				tag.push_back(str[i]);
			}
			if (str[i] == ' ')
			{
				for ( int j = 0; str[i] != '>'; j++, i++)
				{
					attri.push_back(str[i]);
				}
			}
			else if (str[i] == '>')
			{
				attri="";
				i++;
			}
			if (str[i] != '<')
			{
				while (str[i] != '<')
				{
					data.push_back(str[i]);
					i++;
				}
			}
			else
			{
				data ="";
			}

			tree_Node* temp= new tree_Node(tag,data,attri);
			Dstack.top()->add_child(temp);
			Dstack.push(temp);
		}



		else if (str[i] == '<' && str[i+1] == '/' )
		{
			Dstack.pop();
			while (str[i]!='>')
			{
				i++;
			}
		}
	}*/

	
}
void get_tree(tree_Node* root ,string str)
{
	stack <tree_Node*> Dstack;
		Dstack.push(root);
		string tag, attri;
		string data;
		for (size_t i = 0; i < str.size(); i++)
			{
				if (str[i] == '<'&& str[i+1] != '/' )
				{
					i++;
					for ( int j = 0; str[i] != '>' && str[i] != ' '; j++, i++)
					{
						tag.push_back(str[i]);
					}
					if (str[i] == ' ')
					{
						for ( int j = 0; str[i] != '>'; j++, i++)
						{
							attri.push_back(str[i]);
						}
						i++;
					}
					else if (str[i] == '>')
					{
						attri="";
						i++;
					}
					
					if (str[i] != '<')
					{
						while (str[i] != '<')
						{
							data.push_back(str[i]);
							i++;
						}
					}
					else
					{
						data ="";
					}

					tree_Node* temp= new tree_Node(tag,data,attri);
					Dstack.top()->add_child(temp);
					Dstack.push(temp);
				}



				else if (str[i] == '<' && str[i+1] == '/' )
				{
					Dstack.pop();
					while (str[i]!='>')
					{
						i++;
					}
				}
			}
		
}
