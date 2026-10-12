#pragma once
#include <string_view>
#include <array>

struct LevelDesc
{
    int id;
    std::string_view type;
    int num_chances;
};

typedef std::array<LevelDesc, 3> LevelDescArray;

constexpr LevelDescArray difficulty_levels {{
    {1, "Easy",   10},
    {2, "Medium",  5},
    {3, "Hard",    3}
}};