#include "compress.h"

std::vector<int> compress(std::string in){
    std::unordered_map <std::string, int> table;
    for(int i = 0; i < 256; i++){
        std::string ch = "";
        ch += char(i);
        table[ch] = i;
    }

    std::string p = "", c = "";
    p += in[0];
    int code = 256;
    std::vector<int> out;
    for(int i = 0; i < in.length(); i++){
        if(i != in.length() - 1){
            c += in[i+1];
        }
        if(table.find(p + c) != table.end()){
            p += c;
        } else {
            out.push_back(table[p]);
            table[p + c] = code;
            code++;
            p = c;
        }
        c = "";
    }
    out.push_back(table[p]);
    return out;
}


std::string decompress(std::vector<int> in)
{
    std::string out = "";
    std::unordered_map<int, std::string> table;
    for (int i = 0; i <= 255; i++) {
        std::string ch = "";
        ch += char(i);
        table[i] = ch;
    }
    int old = in[0], n;
    std::string s = table[old];
    std::string c = "";
    c += s[0];
    out += s;
    int count = 256;
    for (int i = 0; i < in.size() - 1; i++) {
        n = in[i + 1];
        if (table.find(n) == table.end()) {
            s = table[old];
            s = s + c;
        }
        else {
            s = table[n];
        }
        out += s;
        c = "";
        c += s[0];
        table[count] = table[old] + c;
        count++;
        old = n;
    }
    return out;
}