#include <iostream>
#include <vector>
#include <algorithm>
#include "input_utils.h"

int part1(std::vector<std::string> &in_vec)
{
    int current_elf_cal = 0;
    int max_elf_cal = 0;
    for (std::string const &s : in_vec)
    {
        if (s.length() == 0)
        {
            if (current_elf_cal > max_elf_cal)
            {
                max_elf_cal = current_elf_cal;
            }
            current_elf_cal = 0;
            continue;
        }
        current_elf_cal += std::stoi(s);
    }
    return max_elf_cal;
}

int part2(std::vector<std::string> &in_vec)
{
    std::vector<int> top_three_elfs{0, 0, 0};
    int current_elf_cal = 0;

    for (std::string const &s : in_vec)
    {
        if (s.length() == 0)
        {
            auto m = std::min_element(top_three_elfs.begin(), top_three_elfs.end());
            if(current_elf_cal > *m) {
                *m = current_elf_cal;
            }
            current_elf_cal = 0;
            continue;
        }
        current_elf_cal += std::stoi(s);
    }

    int sum_top_three = 0;
    for (int elf : top_three_elfs)
    {
        sum_top_three += elf;
    }
    return sum_top_three;
}

int main()
{
    std::vector<std::string> in_vec;
    inputToStringVector(in_vec);
    std::cout << part1(in_vec) << "\n";
    std::cout << part2(in_vec) << "\n";
    return 0;
}
