#include <iostream>
#include <random>
#include <charconv>
#include <string>
#include <chrono>
#include <optional>
#include <algorithm>
#include <array>
#include <string_view>

struct LevelDesc
{
    int id;
    std::string_view type;
    int num_chances;
};

constexpr std::array<LevelDesc, 3> difficulty_levels{{
    {1, "Easy",   10},
    {2, "Medium",  5},
    {3, "Hard",    3}
}};

constexpr int NUM_S_IN_MIN = 60;
constexpr int MIN_NUM = 1;
constexpr int MAX_NUM = 100;



// Wrapper to generate a random number given a fixed range
int generate_random_num()
{
    static std::mt19937 engine(std::random_device{}());
    static std::uniform_int_distribution<int> distribution(MIN_NUM, MAX_NUM);
    return distribution(engine);
}

// Parsing helpers

std::optional<int> parse_int_from_user_input()
{
    std::string line;
    if (!std::getline(std::cin, line))
        return std::nullopt;

    int value{};
    const auto [ptr, ec] =
        std::from_chars(line.data(), line.data() + line.size(), value);

    if (ec != std::errc{} || ptr != line.data() + line.size())
    {
        std::cout << "\nInvalid input. Please try again.\n";
        return std::nullopt;
    }

    return value;
}

// Validation helpers

bool validate_user_guess_range(const int input_num)
{
    if (input_num < MIN_NUM && input_num > MAX_NUM)
    {
        std::cout << "\n" << input_num << " is not within range -> [" << MIN_NUM << ", " << MAX_NUM << "]. Please try again.\n";
        return false;
    }
    return true;
}

bool validate_user_end_response(const std::string& response)
{
    return response.size() == 0 || (response.size() == 1 ? (response[0] == 'Y' || response[0] == 'y') : false);
}

// Print helpers

void print_welcome()
{
    std::cout << "Welcome to the Number Guessing Game!\n"
        "I'm thinking of a number between 1 and 100.\n"
        "You will have multiple chances to guess the correct number.\n\n";
}

void print_difficulty_levels()
{
    std::cout << "\nPlease select the difficulty level:\n";

    for (const auto& difficulty : difficulty_levels)
    {
        std::cout << difficulty.id << ". "
                << difficulty.type << " ("
                << difficulty.num_chances << " chances)\n";
    }
}

void print_user_prompt()
{
    std::cout << "Enter your choice: ";
}

void print_user_prompt_v2()
{
    std::cout << "Enter your guess: ";
}

void print_user_prompt_v3()
{
    std::cout << "\nWould you like to play again? (Y/n) ";
}

void print_invalid_level_err_msg()
{
    std::cout << "Invalid difficulty level. Please try again.\n";
}

void print_chosen_level(const std::string_view level_name)
{
    std::cout << "\nGreat! You have selected the " << level_name << " difficulty level.\n"
        "Let's start the game!\n";
}

void print_win_msg(const int num_attempts)
{
    std::cout << "\nCongratulations! You guessed the correct number in " << num_attempts << " attempts.\n\n";
}

void print_incorrect_guess_msg(const int input_num, const int secret_num)
{
    std::cout << "\nIncorrect! The number is " << (input_num < secret_num ? "greater" : "lesser") << " than " << input_num << ".\n";
}

void print_lose_msg(const int secret_num)
{
    std::cout << "\nYou have run out of chances! The number was: " << secret_num << "\nBetter luck next time :)\n\n";
}

void print_end_stats(const long long time_taken_in_s, const int num_games_played, const int num_games_won, const int num_attempts, const bool won_game, const std::optional<int> lowest_num_guesses_in_a_win)
{
    auto mins = time_taken_in_s / NUM_S_IN_MIN;
    auto seconds = time_taken_in_s % NUM_S_IN_MIN;

    std::string game_stats_str = "***** Game " + std::to_string(num_games_played) + " Statistics *****";
    std::cout << "\n" << game_stats_str << "\n";

    std::cout << "Time taken = " << mins << "m " << seconds << "s\n";
    std::cout << "Status = " << (won_game ? "WIN" : "LOSE") << "\n";
    std::cout << "Number of tries = " << num_attempts << "\n";

    for (size_t i = 0; i < game_stats_str.size(); ++i) std::cout << '*';
    std::cout << "\n\n";

    std::string overall_stats_str = "***** Overall Statistics *****";
    std::cout << "\n" << overall_stats_str << "\n";

    std::cout << "Number of Wins = " << num_games_won << " out of " << num_games_played << "\n";
    std::cout << "Lowest Number of Guesses = ";

    if (lowest_num_guesses_in_a_win)
    {
        std::cout << *lowest_num_guesses_in_a_win << "\n";
    }
    else
    {
        std::cout << "N/A" << "\n";
    }

    for (size_t i = 0; i < overall_stats_str.size(); ++i) std::cout << '*';
    std::cout << "\n\n";
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

        // Print Statistics

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
