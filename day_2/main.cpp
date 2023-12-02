#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include "input_utils.h"

constexpr int MAX_RED_CUBES = 12;
constexpr int MAX_GREEN_CUBES = 13;
constexpr int MAX_BLUE_CUBES = 14;

class Game
{
public:
    Game(int id)
    {
        _id = id;
        _max_map["red"] = 0;
        _max_map["green"] = 0;
        _max_map["blue"] = 0;
    }
    int _id;
    bool isPossible()
    {
        return _max_map["red"] <= MAX_RED_CUBES &&
               _max_map["green"] <= MAX_GREEN_CUBES &&
               _max_map["blue"] <= MAX_BLUE_CUBES;
    }

    int power()
    {
        return _max_map["red"] * _max_map["green"] * _max_map["blue"];
    }

    void update(std::string &color, int num_cubes)
    {
        _max_map[color] = std::max(_max_map[color], num_cubes);
    }
    std::map<std::string, int> _max_map;
};

Game gameFromLine(std::string &line)
{
    // Example line:
    // Game 1: 4 red, 8 green; 8 green, 6 red; 13 red, 8 green; 2 blue, 4 red, 4 green

    // Step 1, find game id "Game 1"
    std::size_t first_handful_start_index = line.find(":");

    constexpr std::size_t LEN_OF_WORD_GAME = 5;
    std::string game_id = line.substr(LEN_OF_WORD_GAME, first_handful_start_index - LEN_OF_WORD_GAME);

    Game game{std::stoi(game_id)};

    std::string remaining_line = line.substr(LEN_OF_WORD_GAME + game_id.length() + 1);
    // Step 2, For every grab of handful of cubes
    std::string s_grab; // e.g. "8 green, 6 red;"
    std::stringstream ss_grab{remaining_line};
    while (std::getline(ss_grab, s_grab, ';'))
    {
        // Step 3, For every sample
        std::string s_sample; // e.g. "8 green"
        std::stringstream ss_sample{s_grab};
        while (std::getline(ss_sample, s_sample, ','))
        {
            s_sample.erase(0, s_sample.find_first_not_of(' '));
            int cubes = std::stoi(s_sample.substr(0, s_sample.find(" ")));
            std::string key = s_sample.substr(s_sample.find(" ") + 1);
            game.update(key, cubes);
        }
    }

    return game;
}

std::ostream &operator<<(std::ostream &os, Game const &m)
{
    os << "Game " << m._id << " {\n";
    for (const auto &[key, value] : m._max_map)
    {
        os << "  " << key << ": " << value << "\n";
    }
    return os << "}\n";
}

int part1(std::vector<Game> &games)
{
    int sum_ids_possible_games = 0;
    for (Game &game : games)
    {
        if (game.isPossible())
        {
            sum_ids_possible_games += game._id;
        }
    }
    return sum_ids_possible_games;
}

int part2(std::vector<Game> &games)
{
    int sum_powers = 0;
    for (Game &game : games)
    {
        sum_powers += game.power();
    }
    return sum_powers;
}

int main()
{
    std::vector<std::string> in_vec;
    inputToStringVector(in_vec);
    std::vector<Game> games;

    for (std::string &line : in_vec)
    {
        games.push_back(gameFromLine(line));
    }

    std::cout << part1(games) << "\n";
    std::cout << part2(games) << "\n";
    return 0;
}
