# Makefile for Space Shooter game

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2 -Isrc/include
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Directories
SRC_DIR = src/object
INCLUDE_DIR = src/include
BUILD_DIR = build

# Source files
SOURCES = $(SRC_DIR)/main.cpp $(SRC_DIR)/jeu.cpp $(SRC_DIR)/player.cpp $(SRC_DIR)/enemy.cpp \
          $(SRC_DIR)/kamikaze.cpp $(SRC_DIR)/sniper.cpp $(SRC_DIR)/bullet.cpp $(SRC_DIR)/map.cpp \
          $(SRC_DIR)/camera.cpp $(SRC_DIR)/input.cpp $(SRC_DIR)/gui.cpp $(SRC_DIR)/spawner.cpp \
          $(SRC_DIR)/pathfinding.cpp

OBJECTS = $(BUILD_DIR)/main.o $(BUILD_DIR)/jeu.o $(BUILD_DIR)/player.o $(BUILD_DIR)/enemy.o \
          $(BUILD_DIR)/kamikaze.o $(BUILD_DIR)/sniper.o $(BUILD_DIR)/bullet.o $(BUILD_DIR)/map.o \
          $(BUILD_DIR)/camera.o $(BUILD_DIR)/input.o $(BUILD_DIR)/gui.o $(BUILD_DIR)/spawner.o \
          $(BUILD_DIR)/pathfinding.o

HEADERS = $(INCLUDE_DIR)/jeu.h $(INCLUDE_DIR)/player.h $(INCLUDE_DIR)/enemy.h \
          $(INCLUDE_DIR)/bullet.h $(INCLUDE_DIR)/map.h $(INCLUDE_DIR)/camera.h \
          $(INCLUDE_DIR)/input.h $(INCLUDE_DIR)/gui.h $(INCLUDE_DIR)/spawner.h \
          $(INCLUDE_DIR)/pathfinding.h

# Target executable
TARGET = SpaceShooter

# Default target
all: $(TARGET)

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Build the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Compile source files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Dependencies (header files)
$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp $(INCLUDE_DIR)/jeu.h
$(BUILD_DIR)/jeu.o: $(SRC_DIR)/jeu.cpp $(INCLUDE_DIR)/jeu.h $(INCLUDE_DIR)/player.h $(INCLUDE_DIR)/enemy.h $(INCLUDE_DIR)/map.h $(INCLUDE_DIR)/camera.h $(INCLUDE_DIR)/input.h $(INCLUDE_DIR)/gui.h $(INCLUDE_DIR)/spawner.h
$(BUILD_DIR)/player.o: $(SRC_DIR)/player.cpp $(INCLUDE_DIR)/player.h $(INCLUDE_DIR)/input.h $(INCLUDE_DIR)/map.h $(INCLUDE_DIR)/bullet.h $(INCLUDE_DIR)/camera.h
$(BUILD_DIR)/enemy.o: $(SRC_DIR)/enemy.cpp $(INCLUDE_DIR)/enemy.h $(INCLUDE_DIR)/player.h $(INCLUDE_DIR)/map.h $(INCLUDE_DIR)/bullet.h $(INCLUDE_DIR)/pathfinding.h
$(BUILD_DIR)/kamikaze.o: $(SRC_DIR)/kamikaze.cpp $(INCLUDE_DIR)/enemy.h $(INCLUDE_DIR)/player.h $(INCLUDE_DIR)/map.h $(INCLUDE_DIR)/pathfinding.h
$(BUILD_DIR)/sniper.o: $(SRC_DIR)/sniper.cpp $(INCLUDE_DIR)/enemy.h $(INCLUDE_DIR)/player.h $(INCLUDE_DIR)/map.h $(INCLUDE_DIR)/bullet.h $(INCLUDE_DIR)/pathfinding.h
$(BUILD_DIR)/bullet.o: $(SRC_DIR)/bullet.cpp $(INCLUDE_DIR)/bullet.h $(INCLUDE_DIR)/map.h
$(BUILD_DIR)/map.o: $(SRC_DIR)/map.cpp $(INCLUDE_DIR)/map.h
$(BUILD_DIR)/camera.o: $(SRC_DIR)/camera.cpp $(INCLUDE_DIR)/camera.h $(INCLUDE_DIR)/player.h
$(BUILD_DIR)/input.o: $(SRC_DIR)/input.cpp $(INCLUDE_DIR)/input.h
$(BUILD_DIR)/gui.o: $(SRC_DIR)/gui.cpp $(INCLUDE_DIR)/gui.h $(INCLUDE_DIR)/player.h
$(BUILD_DIR)/spawner.o: $(SRC_DIR)/spawner.cpp $(INCLUDE_DIR)/spawner.h $(INCLUDE_DIR)/enemy.h $(INCLUDE_DIR)/map.h
$(BUILD_DIR)/pathfinding.o: $(SRC_DIR)/pathfinding.cpp $(INCLUDE_DIR)/pathfinding.h $(INCLUDE_DIR)/map.h

# Clean build files
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Run the game
run: $(TARGET)
	./$(TARGET)

# Install SFML dependencies (Ubuntu/Debian)
install-deps:
	sudo apt-get update
	sudo apt-get install libsfml-dev

# Debug build
debug: CXXFLAGS += -g -DDEBUG
debug: $(TARGET)

# Help
help:
	@echo "Available targets:"
	@echo "  all        - Build the game (default)"
	@echo "  clean      - Remove build files"
	@echo "  run        - Build and run the game"
	@echo "  debug      - Build with debug symbols"
	@echo "  install-deps - Install SFML dependencies (Ubuntu/Debian)"
	@echo "  help       - Show this help message"

# Declare phony targets
.PHONY: all clean run debug install-deps help
