#include "balance_tags.h"

void report_error(error_types error_type, int start_index, std::vector<balance_error> &balance_error_arr)
{
    balance_error error;
    error.type = error_type;
    error.index = start_index;
    balance_error_arr.push_back(error);
}

std::vector<balance_error> balance_tags(std::string xml_string)
{
    std::stack<tag> tag_stack;
    std::vector<balance_error> balance_error_arr;
    std::string string_buffer, attribute_buffer;
    for (size_t i = 0; i < xml_string.size(); i++)
    {
        tag tag_buffer;
        if (xml_string[i] == '<' && xml_string[i + 1] == '?')
        {
            int temp = i;
            i += 2;
            int xml_close_index = xml_string.find("?>", i, xml_string.length());
            if (xml_close_index == -1)
            {
                report_error(XML_CLOSE, temp, balance_error_arr);
                break;
            }
            else
            {
                i += xml_close_index + 2;
            }
        }
        else if (xml_string[i] == '<' && xml_string[i + 1] == '!')
        {
            //comment
            if (xml_string[i + 2] == '-' && xml_string[i + 3] == '-')
            {
                int temp = i;
                i += 4;
                int comment_close_index = xml_string.find("-->", i, xml_string.length());
                if (comment_close_index == -1)
                {
                    report_error(COMMENT_CLOSE, temp, balance_error_arr);
                    break;
                }
                else
                {
                    i += comment_close_index + 2;
                }
            }
            else
            {
                report_error(WRONG_TAG, i, balance_error_arr);
            }
        }
        else if (xml_string[i] == '<')
        {
            int start_index = i;
            i++;
            for (; xml_string[i] != '>' && xml_string[i] != ' '; i++)
            {
                tag_buffer.name.push_back(xml_string[i]);
                tag_buffer.start_index = start_index;
            }
            if (xml_string[i] == ' ')
            {
                for (; xml_string[i] != '>'; i++)
                {
                    attribute_buffer.push_back(xml_string[i]);
                }
            }
            std::cout << tag_buffer.name << '\n';
            if (tag_buffer.name[0] == '/')
            {
                if (tag_buffer.name.compare(1, tag_stack.top().name.size(), tag_stack.top().name) == 0)
                {
                    tag_stack.pop();
                    string_buffer.clear();
                }
                else
                {
                    if (string_buffer.empty() == 0)
                    {
                        // missing closing tag with string
                        report_error(MISSING_TAG, tag_stack.top().start_index, balance_error_arr);
                        tag_stack.pop();
                        string_buffer.clear();
                    }
                }
            }
            else
            {
                if (string_buffer.empty() == 0)
                {
                    // missing closing tag with string
                    report_error(MISSING_TAG, tag_stack.top().start_index, balance_error_arr);
                    tag_stack.pop();
                    string_buffer.clear();
                }
                if (xml_string[i - 1] != '/')
                {
                    tag_stack.push(tag_buffer);
                }
            }
        }
        else if (xml_string[i] != '\n' && xml_string[i] != ' ')
        {
            string_buffer.push_back(xml_string[i]);
        }
    }
    for (size_t i = 0; tag_stack.empty() != 1; i++)
    {
        report_error(WRONG_TAG, tag_stack.top().start_index, balance_error_arr);
        tag_stack.pop();
    }
    return balance_error_arr;
}
