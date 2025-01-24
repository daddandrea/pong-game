# Pong Game

This is a simple 2D Pong game created using **C++**, **OpenGL**, and **SDL2**. The game starts in the main menu, where you can configure the player types (Player or CPU) and start the game. Below are instructions for compiling and running the game on both Linux and Windows, along with gameplay controls.

---

## Features
- **Main Menu**:
  - Start the game with default or customized settings.
  - Change **Character 1** and **Character 2** to be either Players or CPUs.
  - **Note**: The game will not start if both characters are set to CPUs.
- **Gameplay**:
  - Players can move and parry using their respective controls.
  - **Player 1 (Left)**:
    - Movement: `W` (up) and `S` (down).
    - Parry: `Space`.
  - **Player 2 (Right)**:
    - Movement: `Up Arrow` (up) and `Down Arrow` (down).
    - Parry: `Space`.

---

## Compilation and Execution Instructions

### Linux

1. **Install Required Dependencies**:
   Ensure you have the following libraries installed:
   - `g++`
   - `SDL2`
   - `SDL2_ttf`
   - `OpenGL`

   You can install them using your package manager:
   ```bash
   sudo apt install g++ libsdl2-dev libsdl2-ttf-dev libgl1-mesa-dev
   ```

2. **Clone the Repository**:
   ```bash
   git clone https://github.com/daddandrea/pong-game
   cd pong-game
   ```

3. **Compile the Game**:
   Use the provided `Makefile` to compile the game:
   ```bash
   make
   ```

4. **Run the Game**:
   After compiling, you can run the game with:
   ```bash
   make run
   ```

5. **Clean the Build**:
   To remove all compiled files and the executable:
   ```bash
   make clean
   ```

---

### Windows

1. **Install Required Tools and Libraries**:
   - **Compiler**: Install `MinGW` or another compiler supporting C++17.
   - **Libraries**: Download and set up the following:
     - [SDL2 Development Libraries](https://libsdl.org/download-2.0.php)
     - [SDL2_ttf Development Libraries](https://www.libsdl.org/projects/SDL_ttf/)
     - OpenGL (usually comes with Windows drivers).

2. **Set Up the Build Environment**:
   - Add the paths to SDL2, SDL2_ttf, and OpenGL to your system's include and library directories.
   - Copy `SDL2.dll` and `SDL2_ttf.dll` into the directory containing the compiled executable.

3. **Compile the Game**:
   Use the `Makefile` to compile the game:
   ```bash
   make
   ```

4. **Run the Game**:
   Execute the generated `Pong.exe` in the terminal or by double-clicking the file:
   ```bash
   ./Pong.exe
   ```

5. **Clean the Build**:
   To remove all compiled files and the executable:
   ```bash
   make clean
   ```

---

## Gameplay Instructions

1. **Main Menu**:
   - Use your mouse to click the buttons.
   - **Start Game**: Begins the game with the current settings.
   - **Character 1 / Character 2**: Toggles between Player and CPU.

2. **In-Game Controls**:
   - **Player 1 (Left)**:
     - Move Up: `W`
     - Move Down: `S`
     - Parry: `Space`
   - **Player 2 (Right)**:
     - Move Up: `Up Arrow`
     - Move Down: `Down Arrow`
     - Parry: `Space`

---

## Notes

- **CPU Limitation**: If both characters are set to CPU, the game will not start. Ensure at least one character is set to Player.
- **Debugging**: If you encounter issues, run the game with debugging tools like `gdb` (Linux) or `Debugging Tools for Windows`.

---
