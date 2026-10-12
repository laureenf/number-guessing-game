#include <random>
#include <charconv>
#include <string>
#include <chrono>
#include <optional>
#include <algorithm>

#include "LevelDesc.hpp"
#include "PrintHelpers.hpp"
#include "InputHelpers.hpp"


// Wrapper to generate a random number given a fixed range
int generate_random_num()
{
    static std::mt19937 engine(std::random_device{}());
    static std::uniform_int_distribution<int> distribution(MIN_NUM, MAX_NUM);
    return distribution(engine);
}


// MAIN

int main()
{
    print_welcome();

    bool keep_playing = true;
    int num_games_played = 0;
    int num_games_won = 0;

    std::optional<int> lowest_num_guesses_in_a_win;

    do
    {
        print_difficulty_levels();

        print_user_prompt();

        std::optional<int> level = parse_int_from_user_input();

        if (!level)
        {
            if (std::cin.eof())
                return 0;
            continue;
        }

        auto it = std::find_if(
            difficulty_levels.begin(),
            difficulty_levels.end(),
            [level](const LevelDesc& d)
            {
                return d.id == *level;
            }
        );

        if (it == difficulty_levels.end())
        {
            print_invalid_level_err_msg();
            continue;
        }

        print_chosen_level(it->type);

        int secret_num = generate_random_num();

        auto start = std::chrono::steady_clock::now();

        bool won_game = false;
        int num_attempts = 0;

        int num_chances = it->num_chances;

        do
        {
            print_user_prompt_v2();

            std::optional<int> input_num = parse_int_from_user_input();

            if (!input_num)
            {
                if (std::cin.eof())
                    return 0;
                continue;
            }

            if (!validate_user_guess_range(*input_num)) continue;

            num_attempts++;

            if (*input_num == secret_num)
            {
                print_win_msg(num_attempts);

                lowest_num_guesses_in_a_win = !lowest_num_guesses_in_a_win ? num_attempts : std::min(*lowest_num_guesses_in_a_win, num_attempts);
                won_game = true;
                num_games_won++;
                break;
            }
            else
            {
                print_incorrect_guess_msg(*input_num, secret_num);
            }
        } while (num_attempts < num_chances);

        if (!won_game)
        {
            print_lose_msg(secret_num);
        }

        num_games_played++;

        auto end = std::chrono::steady_clock::now();
        auto time_taken_in_s = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
        
        print_end_stats(time_taken_in_s, num_games_played, num_games_won, num_attempts, won_game, lowest_num_guesses_in_a_win);

        print_user_prompt_v3();

        std::string response;
        if (!std::getline(std::cin, response)) return 0;

        keep_playing = validate_user_end_response(response);
    }
    while (keep_playing);

    return 0;
}
