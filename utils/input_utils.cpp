#include "input_utils.h"

#include <string>
#include <fstream>
#include <sstream>
#include <cassert>
#include <vector>

std::string readInput(std::string filename)
{
    std::ifstream input_file(filename);
    assert(input_file.is_open());
    std::stringstream stream;
    stream << input_file.rdbuf();
    return stream.str();
}

void inputToStringVector(std::vector<std::string> &ret, std::string filename)
{
    std::ifstream input_file(filename);
    assert(input_file.is_open());
    std::string line;
    while (std::getline(input_file, line))
    {
        ret.push_back(line);
    }
}

void inputToCharMatrix(std::vector<std::vector<char>> &ret, std::string filename)
{
    std::ifstream input_file(filename);
    assert(input_file.is_open());
    std::string line;
    while (std::getline(input_file, line))
    {
        std::vector<char> row;
        for (char c : line)
        {
            row.push_back(c);
        }
        ret.push_back(row);
    }
}
