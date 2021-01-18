#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> &read_lines(const std::string &filename)
{
    std::vector<std::string>* content = new std::vector<std::string>();
    std::ifstream file;
    file.open(filename, std::ios::in);
    if(file.is_open())
    {
        std::string line_content;
        while(!file.eof())
        {
            getline(file, line_content);
            content->push_back(line_content);
            line_content = "";
        }
    }
    file.close();
    return *content;
}

int main(int argc, char **argv)
{
    std::string filename = "./123.txt";
    for(auto content : read_lines("123.txt"))
    {
        std::cout << content << std::endl;
    }
    return 0;
}
