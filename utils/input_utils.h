#ifndef UTILS_INPUT_UTILS_H
#include <string>
#include <vector>

std::string readInput(std::string filename="input.txt");
void inputToStringVector(std::vector<std::string> &ret, std::string filename="input.txt");

#endif // UTILS_INPUT_UTILS_H