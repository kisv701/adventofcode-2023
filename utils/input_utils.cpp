#include "input_utils.h"

#include <string>
#include <fstream>
#include <sstream>
#include <cassert>

std::string readInput(std::string filename)
{
    std::ifstream input_file(filename);
    assert(input_file.is_open());
    std::stringstream stream;
    stream << input_file.rdbuf();
    return stream.str();
}
