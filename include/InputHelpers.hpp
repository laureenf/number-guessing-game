#pragma once
#include <optional>
#include <string>
#include <charconv>
#include <iostream>


constexpr int MIN_NUM = 1;
constexpr int MAX_NUM = 100;

// Parsing helpers

std::optional<int> parse_int_from_user_input();

// Validation helpers

bool validate_user_guess_range(const int input_num);
bool validate_user_end_response(const std::string& response);