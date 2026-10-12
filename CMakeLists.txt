cmake_minimum_required(VERSION 3.16)
project(number_guessing_game LANGUAGES CXX)

add_executable(number_guessing_game
    main.cpp
    src/InputHelpers.cpp
    src/PrintHelpers.cpp
)

target_compile_features(number_guessing_game PRIVATE cxx_std_17)

target_include_directories(number_guessing_game PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_compile_options(number_guessing_game PRIVATE
    -Wall -Wextra -Wpedantic
)
