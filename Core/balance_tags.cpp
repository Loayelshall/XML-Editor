#include "balance_tags.h"

void balance_tags(std::string xml_string)
{
    std::stack<tag> tag_stack;
    std::vector<balance_error> balance_error_arr;
    std::string string_buffer;
    for (size_t i = 0; i < xml_string.size(); i++)
    {
        tag tag_buffer;
        if (xml_string[i] == '<')
        {
            int start_index = i;
            i++;
            for (size_t j = 0; xml_string[i] != '>'; j++, i++)
            {
                tag_buffer.name.push_back(xml_string[i]);
                tag_buffer.start_index = start_index;
            }
            std::cout << tag_buffer.name << '\n';
            if (tag_buffer.name[0] == '/')
            {

                if (tag_buffer.name.compare(1, tag_stack.top().name.size(), tag_stack.top().name) == 0)
                {
                    tag_stack.pop();
                    string_buffer.clear();
                }
            }
            else
            {
                if (string_buffer.empty() == 0)
                {
                    // missing closing tag with string
                    balance_error error;
                    error.type = MISSING_TAG;
                    error.index = tag_stack.top().start_index;
                    balance_error_arr.push_back(error);
                    string_buffer.clear();
                }
                tag_stack.push(tag_buffer);
            }
        }
        else if(xml_string[i] != '\n' && xml_string[i] != ' ')
        {
            string_buffer.push_back(xml_string[i]);
        }
    }
}

// stack ----> string
// stack ----> string + index open bracket tag with error