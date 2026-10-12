#include "PrintHelpers.hpp"



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
