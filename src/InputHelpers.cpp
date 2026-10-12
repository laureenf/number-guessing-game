#include "InputHelpers.hpp"


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