# Compiler and linker settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -Iinclude -I/usr/include/freetype2 -Iexternal/imgui `pkg-config --cflags freetype2`
LDFLAGS = `pkg-config --libs freetype2` -lGL -lGLU -lSDL2 -ldl -lfreetype

# Source files and object files
SRC = src/ball.cpp src/game.cpp src/game_object.cpp src/main.cpp src/character.cpp src/player.cpp src/collider.cpp src/menu.cpp
IMGUI_SRC = external/imgui/imgui.cpp external/imgui/imgui_demo.cpp external/imgui/imgui_draw.cpp external/imgui/imgui_tables.cpp external/imgui/imgui_widgets.cpp external/imgui/imgui_impl_sdl2.cpp external/imgui/imgui_impl_opengl2.cpp
OBJ_DIR = objects
OBJ = $(patsubst src/%.cpp,$(OBJ_DIR)/%.o,$(SRC)) $(patsubst external/imgui/%.cpp,$(OBJ_DIR)/%.o,$(IMGUI_SRC))

# Header files for dependency tracking
HEADERS = $(wildcard include/*.h) $(wildcard external/imgui/*.h)

# Output binary
TARGET = Pong

# Make rules
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

# Compile .cpp files into .o files with header dependencies
$(OBJ_DIR)/%.o: src/%.cpp $(HEADERS) | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: external/imgui/%.cpp $(HEADERS) | $(OBJ_DIR)
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

