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
    while(std::getline(input_file, line))
    {
        ret.push_back(line);
    }
}
