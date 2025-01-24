# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -Iinclude
LDFLAGS_LINUX = `pkg-config --libs sdl2 SDL2_ttf` -lGL -lGLU -ldl -lfreetype
LDFLAGS_WINDOWS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lopengl32 -lglu32

# Source files and object files
SRC = src/ball.cpp src/game.cpp src/game_object.cpp src/main.cpp src/character.cpp src/player.cpp src/collider.cpp src/text_renderer.cpp src/cpu.cpp src/essentials.cpp src/scene_manager.cpp src/debugger.cpp src/button.cpp
OBJ_DIR = objects
OBJ = $(patsubst src/%.cpp,$(OBJ_DIR)/%.o,$(SRC))

# Header files for dependency tracking
HEADERS = $(wildcard include/*.h)

# Output binary
TARGET = Pong

# Detect platform
OS := $(shell uname -s)
ifeq ($(OS),Linux)
	LDFLAGS = $(LDFLAGS_LINUX)
else
	LDFLAGS = $(LDFLAGS_WINDOWS)
endif

# Default rule
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

# Compile .cpp files into .o files with header dependencies
$(OBJ_DIR)/%.o: src/%.cpp $(HEADERS) | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Create object directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Run the program after building
run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean run

