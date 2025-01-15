# Compiler and linker settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -Iinclude -I/usr/include/freetype2 `pkg-config --cflags freetype2`
LDFLAGS = `pkg-config --libs freetype2` -lGL -lGLU -lSDL2 -ldl -lfreetype

# Source files and object files
SRC = src/ball.cpp src/debugger.cpp src/game.cpp src/game_object.cpp src/main.cpp src/character.cpp src/player.cpp src/collider.cpp
OBJ_DIR = objects
OBJ = $(patsubst src/%.cpp,$(OBJ_DIR)/%.o,$(SRC))

# Header files for dependency tracking
HEADERS = $(wildcard include/*.h)

# Output binary
TARGET = Pong

# Make rules
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

