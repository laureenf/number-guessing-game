#include <iostream>
#include <random>
#include <cassert>
#include <map>

// Source - https://stackoverflow.com/a/29382078
// Posted by SleuthEye, modified by community. See post 'Timeline' for change history
// Retrieved 2026-10-11, License - CC BY-SA 3.0

int random_int(int min, int max)
{
   return min + rand() % (max + 1 - min);
}

// Wrapper to generate a random number given a fixed range

int generate_random_num(void)
{
    int min = 1;
    int max = 100;

    return random_int(min, max);
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
    
    bool flag = false;

    do
    {
        std::cout << "\nPlease select the difficulty level:\n";
        
        for (const auto& [k, v] : difficulty_levels)
        {
            std::cout << k << ". " << v.first << " (" << v.second << " chances)\n";
        }

        std::cout << "Enter your choice: ";

        int level;
        std::cin >> level;

        if (!(level >= difficulty_levels.begin()->first && level <= difficulty_levels.rbegin()->first))
        {
            std::cout << "\n" << level << " is not a valid option. Please try again.\n";
            continue;
        }
        
        int num_chances = difficulty_levels[level].second;

        std::cout << "\nGreat! You have selected the " << difficulty_levels[level].first << " difficulty level.\n"
        "Let's start the game!\n";

        srand(time(0));
        int rand_num = generate_random_num();

        bool win = false;
        int turn_counter = 1;

        do
        {
            std::cout << "\nEnter your guess: ";

            int input;
            std::cin >> input;

            if (input == rand_num)
            {
                std::cout << "\nCongratulations! You guessed the correct number in " << turn_counter \
                    << " attempts.\n\n";
                win = true;
                break;
            }
            else
            {
                std::cout << "\nIncorrect! The number is " << (input < rand_num ? "greater" : "lesser") << " than " << input << ".\n";
            }
        } while (++turn_counter <= num_chances);

        if (!win)
        {
            std::cout << "\nYou have run out of chances! The number was: " << rand_num << "\nBetter luck next time :)\n\n";
        }

        std::cout << "\nWould you like to play again? (Y/n) ";
        char ch_input;
        std::cin >> ch_input;

        flag = ch_input == 'Y' || ch_input == 'y';
    }
    while (flag);

    return 0;
}