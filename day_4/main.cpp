#include <iostream>
#include <unordered_set>
#include <vector>
#include <sstream>
#include <string>
#include <deque>

#include "input_utils.h"

std::unordered_set<int> lineToWinningNumbers(std::string const &line)
{
    int start_index = line.find(":") + 1;
    int stop_index = line.find("|");
    std::unordered_set<int> ret{};
    std::string num;
    std::stringstream ss{line.substr(start_index, stop_index - start_index)};
    while (std::getline(ss, num, ' '))
    {
        if (num.empty())
            continue;
        ret.insert(stoi(num));
    }
    return ret;
}

std::unordered_set<int> lineToPickedNumbers(std::string const &line)
{
    int start_index = line.find("|") + 1;
    std::unordered_set<int> ret{};

    std::string num;
    std::stringstream ss{line.substr(start_index)};
    while (std::getline(ss, num, ' '))
    {
        if (num.empty())
            continue;
        ret.insert(stoi(num));
    }
    return ret;
}

int part1(std::vector<std::string> input)
{
    int total_winnings = 0;
    for (auto const &line : input)
    {
        auto winning_nums = lineToWinningNumbers(line);
        auto picked_nums = lineToPickedNumbers(line);

        int line_winnings = 0;
        for (auto picked_num : picked_nums)
        {
            if (winning_nums.contains(picked_num))
                if (line_winnings == 0)
                {
                    line_winnings = 1;
                }
                else
                {
                    line_winnings *= 2;
                }
        }
        total_winnings += line_winnings;
    }
    return total_winnings;
}

int part2(std::vector<std::string> input)
{
    int num_scratches = 0;
    std::deque<int> lines_to_process;
    std::vector<int> known_answers;
    for (int i = 0; i < input.size(); i++)
    {
        lines_to_process.push_back(i);
        known_answers.push_back(-1);
    }

    while (lines_to_process.size())
    {
        int current = lines_to_process.front();
        lines_to_process.pop_front();
        int line_winnings = 0;
        if (known_answers[current] > -1)
        {
            line_winnings = known_answers[current];
        }
        else
        {
            std ::string &line = input[current];
            auto winning_nums = lineToWinningNumbers(line);
            auto picked_nums = lineToPickedNumbers(line);

            for (auto picked_num : picked_nums)
            {
                if (winning_nums.contains(picked_num))
                    line_winnings += 1;
            }
            known_answers[current] = line_winnings;
        }
        for (int i = 0; i < line_winnings; i++)
        {
            lines_to_process.push_front(current + i + 1);
        }
        num_scratches++;
    }
    return num_scratches;
}

int main()
{
    std::vector<std::string> input;
    inputToStringVector(input);

    std::cout << part1(input) << "\n";
    std::cout << part2(input) << "\n";
    return 0;
}
