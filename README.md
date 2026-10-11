# Number Guessing Game

A command-line number guessing game written in C++17, created for the
[Number Guessing Game project](https://roadmap.sh/projects/number-guessing-game).

## Features

- Random target number between 1 and 100
- Three difficulty levels with different numbers of chances
- Input validation for difficulty choices and guesses
- Round timer and game statistics
- Overall win count and fewest successful guesses
- Option to play multiple rounds

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


## Example

```text
Welcome to the Number Guessing Game!
I'm thinking of a number between 1 and 100.

Please select the difficulty level:
1. Easy (10 chances)
2. Medium (5 chances)
3. Hard (3 chances)
Enter your choice: 2

Great! You have selected the Medium difficulty level.
Let's start the game!

Enter your guess: 50
Incorrect! The number is lesser than 50.

Enter your guess: 25
Incorrect! The number is greater than 25.

Enter your guess: 30
Congratulations! You guessed the correct number in 3 attempts.
```
