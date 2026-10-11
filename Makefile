CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic
TARGET   := number_guessing_game
SOURCE   := main.cpp

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) $(SOURCE) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
