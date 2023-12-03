#include <iostream>
#include <vector>
#include <map>
#include <unordered_set>
#include "input_utils.h"

// Admittedly not the nicest solution :)

class PartNumber
{
public:
    std::string _current_number_str = "";
    bool _is_near_symbol{false};
    std::vector<std::vector<char>> *_schematic;

    PartNumber(std::vector<std::vector<char>> *schematic)
    {
        _schematic = schematic;
    };
    int getValueNextChar(char c, int row, int col)
    {
        if (c == '.' || !isdigit(c))
        {
            int value = evaluateCurrentString();
            reset();
            return value;
        }

        if (is_near_symbol(*_schematic, row, col))
        {
            _is_near_symbol = true;
        }
        _current_number_str += c;
        return 0;
    };

    int evaluateCurrentString()
    {
        if (_current_number_str.empty())
        {
            return 0;
        }
        if (!_is_near_symbol)
        {
            return 0;
        }
        return stoi(_current_number_str);
    }

    void reset()
    {
        _is_near_symbol = false;
        _current_number_str = "";
    }

    bool is_symbol(char c)
    {
        if (c == '.')
        {
            return false;
        }
        return !isdigit(c);
    }

    bool is_near_symbol(std::vector<std::vector<char>> &schematic, int row, int col)
    {
        bool is_near_symbol = false;
        std::vector<std::pair<int, int>> relative_coordinates = {
            {-1, -1},
            {-1, 0},
            {-1, 1},
            {0, -1},
            {0, 1},
            {1, -1},
            {1, 0},
            {1, 1}};

        for (const auto &[drow, dcol] : relative_coordinates)
        {
            int query_row = row + drow;
            if (query_row < 0 || query_row >= schematic.size())
            {
                continue;
            }
            int query_col = col + dcol;
            if (query_col < 0 || query_col >= schematic[row].size())
            {
                continue;
            }
            if (is_symbol(schematic[query_row][query_col]))
            {
                is_near_symbol = true;
            }
        }
        return is_near_symbol;
    }
};

class GearContainer
{
public:
    // Create map with gear index as key and vector of adjacent numbers as value.
    GearContainer(std::vector<std::vector<char>> &schematic)
    {
        // First pass build up all the gears.
        for (int i = 0; i < schematic.size(); ++i)
        {
            std::vector<char> &row = schematic[i];
            for (int j = 0; j < row.size(); ++j)
            {
                char c = row[j];
                if (c == '*')
                {
                    gears[i * row.size() + j] = std::vector<int>{};
                }
            }
        }

        for (int i = 0; i < schematic.size(); ++i)
        {
            std::vector<char> &row = schematic[i];
            std::string s = "";
            std::unordered_set<int> near_gears;

            // For each number, find all adjacent gears,
            // then add number to map[gear].push_back(number).
            for (int j = 0; j < row.size(); ++j)
            {
                char c = row[j];
                if (isdigit(c))
                {
                    s += c;
                    for (auto start_index : getNearGears(schematic, i, j))
                    {
                        near_gears.insert(start_index);
                    }
                }
                else
                {
                    if (s.empty())
                    {
                        continue;
                    }
                    int value = stoi(s);
                    for (auto key : near_gears)
                    {
                        gears[key].push_back(value);
                    }
                    // reset state
                    s = "";
                    near_gears.clear();
                }
            }
            if (!s.empty())
            {
                int value = stoi(s);
                for (auto key : near_gears)
                {
                    gears[key].push_back(value);
                }
                // reset state
                s = "";
                near_gears.clear();
            }
        }
    }

    std::vector<int> getNearGears(std::vector<std::vector<char>> &schematic, int row, int col)
    {
        // Return a vector of all adjacent gears (by their key into map)
        bool is_near_star = false;
        std::vector<std::pair<int, int>> relative_coordinates = {
            {-1, -1},
            {-1, 0},
            {-1, 1},
            {0, -1},
            {0, 1},
            {1, -1},
            {1, 0},
            {1, 1}};
        std::vector<int> near_gears{};
        int num_cols = schematic[0].size();

        for (const auto &[drow, dcol] : relative_coordinates)
        {
            int query_row = row + drow;
            if (query_row < 0 || query_row >= schematic.size())
            {
                continue;
            }
            int query_col = col + dcol;
            if (query_col < 0 || query_col >= schematic[row].size())
            {
                continue;
            }
            if (schematic[query_row][query_col] == '*')
            {
                near_gears.push_back(query_row * num_cols + query_col);
            }
        }
        return near_gears;
    }

    // Gear id is (row*num_cols + cols)
    // Only works because all rows are of same length.
    // Like flattening an image.
    std::map<int, std::vector<int>> gears;
};

int part2(std::vector<std::vector<char>> &schematic)
{
    GearContainer gc{schematic};
    int sum = 0;
    for (auto const &[gear_idx, num_vec] : gc.gears)
    {
        if (num_vec.size() == 2)
        {
            sum += num_vec[0] * num_vec[1];
        }
    }
    return sum;
}

int part1(std::vector<std::vector<char>> &schematic)
{
    int sum = 0;
    PartNumber num{&schematic};
    for (int i = 0; i < schematic.size(); ++i)
    {
        std::vector<char> &row = schematic[i];
        for (int j = 0; j < row.size(); ++j)
        {
            char c = row[j];
            sum += num.getValueNextChar(c, i, j);
        }
        // Handle end of row.
        sum += num.getValueNextChar('.', 0, 0);
        num.reset();
    }

    return sum;
}

int main()
{
    std::vector<std::vector<char>> schematic;
    inputToCharMatrix(schematic);

    std::cout << part1(schematic) << "\n";
    std::cout << part2(schematic) << "\n";
    return 0;
}
