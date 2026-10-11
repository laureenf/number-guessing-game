#include <iostream>
#include <random>
#include <ctime>
#include <charconv>
#include <string>
#include <chrono>
#include <cstdlib>
#include <utility>
#include <map>

#define NUM_S_IN_MIN (60)
#define MIN_NUM      (1)
#define MAX_NUM      (100)

// Wrapper to generate a random number given a fixed range

int generate_random_num(void)
{
    static std::mt19937 engine(std::random_device{}());
    static std::uniform_int_distribution<int> distribution(MIN_NUM, MAX_NUM);
    return distribution(engine);
}

// Helper to find min

int min(int a, int b)
{
    return a < b ? a : b;
}

// MAIN

std::map<int, std::pair<std::string, int>> difficulty_levels = \
{
    {1, {"Easy",   10}},
    {2, {"Medium",  5}},
    {3, {"Hard",    3}},
};

int main()
{
    std::cout << "Welcome to the Number Guessing Game!\n"
        "I'm thinking of a number between 1 and 100.\n"
        "You will have multiple chances to guess the correct number.\n\n";
    
    bool flag = true;
    int min_guesses = 0;
    int game_counter = 0;
    int win_counter = 0;

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    do
    {
        std::cout << "\nPlease select the difficulty level:\n";
        
        for (const auto& [k, v] : difficulty_levels)
        {
            std::cout << k << ". " << v.first << " (" << v.second << " chances)\n";
        }

        std::cout << "Enter your choice: ";

        int level;

        std::string line;
        if (!std::getline(std::cin, line)) return 0;

        auto [ptr, ec] = std::from_chars(
            line.data(), line.data() + line.size(), level);

        if (ec != std::errc{} || ptr != line.data() + line.size())
        {
            std::cout << "\nInvalid option. Please try again.\n";
            continue;
        }

        if (!(level >= difficulty_levels.begin()->first && level <= difficulty_levels.rbegin()->first))
        {
            std::cout << "\n" << level << " is not within range. Please try again.\n";
            continue;
        }
        
        int num_chances = difficulty_levels[level].second;

        std::cout << "\nGreat! You have selected the " << difficulty_levels[level].first << " difficulty level.\n"
        "Let's start the game!\n";

        int rand_num = generate_random_num();

        auto start = std::chrono::high_resolution_clock::now();

        bool win = false;
        int turn_counter = 1;

        do
        {
            std::cout << "\nEnter your guess: ";

            int input_num;

            if (!std::getline(std::cin, line)) return 0;

            auto [ptr, ec] = std::from_chars(
                line.data(), line.data() + line.size(), input_num);

            if (ec != std::errc{} || ptr != line.data() + line.size())
            {
                std::cout << "\nInvalid option. Please try again.\n";
                continue;
            }

            // Input validation
            if (!(input_num >= MIN_NUM && input_num <= MAX_NUM))
            {
                std::cout << "\n" << input_num << " is not within range -> [" << MIN_NUM << ", " << MAX_NUM << "]. Please try again.\n";
                continue;
            }

            if (input_num == rand_num)
            {
                std::cout << "\nCongratulations! You guessed the correct number in " << turn_counter \
                    << " attempts.\n\n";
                min_guesses = min_guesses == 0 ? turn_counter : min(min_guesses, turn_counter);
                win = true;
                win_counter++;
                break;
            }
            else
            {
                std::cout << "\nIncorrect! The number is " << (input_num < rand_num ? "greater" : "lesser") << " than " << input_num << ".\n";
            }
            turn_counter++;
        } while (turn_counter <= num_chances);

        if (!win)
        {
            std::cout << "\nYou have run out of chances! The number was: " << rand_num << "\nBetter luck next time :)\n\n";
        }

        game_counter++;

        // Print Statistics

        auto end = std::chrono::high_resolution_clock::now();
        auto time_taken_in_s = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
        auto time_taken_in_min = time_taken_in_s / NUM_S_IN_MIN;
        time_taken_in_s = time_taken_in_s % NUM_S_IN_MIN;

        std::string game_stats_str = "***** Game " + std::to_string(game_counter) + " Statistics *****";
        std::cout << "\n" << game_stats_str << "\n";

        std::cout << "Time taken = " << time_taken_in_min << "m " << time_taken_in_s << "s\n";
        std::cout << "Status = " << (win ? "WIN" : "LOSE") << "\n";
        std::cout << "Number of tries = " << (win ? turn_counter : turn_counter - 1) << "\n";

        for (int i = 0; i < game_stats_str.size(); ++i) std::cout << '*';
        std::cout << "\n\n";
        
        std::string overall_stats_str = "***** Overall Statistics *****";
        std::cout << "\n" << overall_stats_str << "\n";

        std::cout << "Number of Wins = " << win_counter << " out of " << game_counter << "\n";
        std::cout << "Lowest Number of Guesses = " << min_guesses << "\n";

        for (int i = 0; i < overall_stats_str.size(); ++i) std::cout << '*';
        std::cout << "\n\n";

        // Turn check

        std::cout << "\nWould you like to play again? (Y/n) ";

        std::string response;
        if (!std::getline(std::cin, response)) return 0;

        flag = response.size() == 1 ? (response[0] == 'Y' || response[0] == 'y') : false;
    }
    while (flag);

    return 0;
}

#undef NUM_S_IN_MIN
#undef MIN_NUM
#undef MAX_NUM