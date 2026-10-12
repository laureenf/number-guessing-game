#pragma once
#include <iostream>
#include "LevelDesc.hpp"

constexpr int NUM_S_IN_MIN = 60;

// Print helpers

void print_welcome();
void print_difficulty_levels();

void print_user_prompt();
void print_user_prompt_v2();
void print_user_prompt_v3();

void print_invalid_level_err_msg();

void print_chosen_level(const std::string_view level_name);

void print_win_msg(const int num_attempts);
void print_incorrect_guess_msg(const int input_num, const int secret_num);
void print_lose_msg(const int secret_num);

void print_end_stats(const long long time_taken_in_s, const int num_games_played, const int num_games_won, const int num_attempts, const bool won_game, const std::optional<int> lowest_num_guesses_in_a_win);
