#include <iostream>
#include <vector>
#include <string>
#include <ctype.h>
#include "input_utils.h"

int part1(std::vector<std::string> &in_vec)
{
    int calibration_sum = 0;
    for (std::string &line : in_vec)
    {
        bool is_first_digit = true;
        int first_digit = 0;
        int last_digit = 0;
        for (char c : line)
        {
            if (!isdigit(c))
                continue;
            if (is_first_digit)
            {
                is_first_digit = false;
                first_digit = c - '0';
            }
            last_digit = c - '0';
        }
        calibration_sum += 10 * first_digit + last_digit;
    }
    return calibration_sum;
}

int getDigit(std::string &line)
{
    std::vector<std::string> number_strings{
        "one",
        "two",
        "three",
        "four",
        "five",
        "six",
        "seven",
        "eight",
        "nine",
    };

    if (isdigit(line[0]))
    {
        return line[0] - '0';
    }

    for (int i = 0; i < number_strings.size(); ++i)
    {
        if (line.starts_with(number_strings[i]))
        {
            return i + 1;
        }
    }
    return 0;
}

int part2(std::vector<std::string> &in_vec)
{
    int calibration_sum = 0;
    for (std::string &line : in_vec)
    {
        bool is_first_digit = true;
        int first_digit = 0;
        int last_digit = 0;
        for (int i = 0; i < line.length(); ++i)
        {
            std::string sub_str = line.substr(i, line.length() - i);
            if (int current_num = getDigit(sub_str))
            {
                if (is_first_digit)
                {
                    is_first_digit = false;
                    first_digit = current_num;
                }
                last_digit = current_num;
            }
        }
        calibration_sum += 10 * first_digit + last_digit;
    }
    return calibration_sum;
}

int main()
{
    std::vector<std::string> in_vec;
    inputToStringVector(in_vec);

    std::cout << part1(in_vec) << "\n";
    std::cout << part2(in_vec) << "\n";
    return 0;
}
