# Number Guessing Game

A command-line number guessing game written in C++.

## Requirements

- A C++17-compatible compiler, such as GCC or Clang
- `make` (optional, but used by the build instructions below)

## Build

From the project directory, run:

```sh
make
```

This creates the `number_guessing_game` executable.

If your source file has a different name, change the `SOURCE` value in the Makefile.

## Run

```sh
./number_guessing_game
```

Or build and run in one step:

```sh
make run
```

## How to play

Choose a difficulty:

| Choice | Difficulty | Guesses |
|---|---|---:|
| 1 | Easy | 10 |
| 2 | Medium | 5 |
| 3 | Hard | 3 |

The game selects a number from 1 to 100. Enter guesses as whole numbers; the game tells you whether the target is higher or lower. Invalid guesses are rejected and do not use a chance.

After each game, the program displays game and overall statistics. Enter `Y` to play again; any other response exits. End-of-file input (Ctrl+D on Unix-like systems) exits the program.
