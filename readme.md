# Pacman (but multithreaded)

A multithreaded Pacman clone implemented in C++ using SFML for graphics. The game features classic Pacman gameplay with player and ghost AI running in separate threads, synchronized using mutexes and semaphores.

## Features

- **Classic Pacman Gameplay:** Navigate the maze, eat pellets, avoid ghosts, and collect power-ups.
- **Multithreading:** Player and each ghost run in their own threads for concurrent movement and AI.
- **SFML Graphics:** Smooth 2D rendering using the SFML library.
- **Menu System:** Start, quit, and enter player name via a graphical menu.
- **Power-Ups:** Eat power pellets to turn ghosts vulnerable.
- **Ghost AI:** Each ghost has its own movement logic and can be "scared" when Pacman is powered up.
- **Score and Lives Tracking:** Displayed in-game.

## Project Structure

```
game.sh                # Build and run script
main.cpp               # Main game logic and threading
player.h               # Player (Pacman) class
ghost.h                # Ghost class and AI
menu.h                 # Menu system
gridmaker.h            # (Unused) Example of threading with philosophers problem
sprites/               # Game assets (sprites, fonts)
.vscode/settings.json  # VSCode settings
```

## Requirements

- **C++ Compiler** (e.g., g++)
- **SFML Library** (Graphics, Window, System)
- Linux or compatible environment (for pthreads and semaphores)

## Installation

1. **Install SFML:**

   On Ubuntu:
   ```sh
   sudo apt-get install libsfml-dev
   ```

2. **Clone the repository:**
   ```sh
   git clone <your-repo-url>
   cd pacman_threaded
   ```

3. **Ensure all assets are present:**
   - The sprites directory must contain all required images and the font file.

## Building and Running

Use the provided shell script:

```sh
./game.sh
```

This will:
- Compile main.cpp
- Link with SFML
- Run the game
- Clean up build artifacts

## Controls

- **Arrow Keys:** Move Pacman
- **Enter:** Select menu options / confirm name
- **Escape:** Go back in menu
- **Up/Down:** Navigate menu

## Code Overview

- main.cpp: Handles game loop, threading, synchronization, and main logic.
- player.h: Defines the `player` class, movement, animation, and state.
- ghost.h: Defines the `ghost` class, AI, movement, and state.
- menu.h: Implements the graphical menu system.
- sprites: Contains all images and fonts used in the game.

## Threading Model

- **UI Thread:** Handles rendering and player input.
- **Ghost Threads:** Each ghost runs in its own thread, managing movement and AI.
- **Synchronization:** Uses `pthread_mutex_t` and POSIX semaphores to coordinate access to shared resources (e.g., grid, keys, permits).

## Customization

- **Sprites:** Replace images in sprites to change the appearance.
- **Maze Layout:** Edit the `grid` array in main.cpp to modify the maze.

## Troubleshooting

- **SFML Not Found:** Ensure SFML is installed and library paths are set.
- **Missing Sprites:** Make sure all images referenced in the code exist in the correct folders.
- **Threading Issues:** The game uses POSIX threads; ensure your system supports them.

## License

This project is for educational grading purposes.

---

**Enjoy playing Pacman!**
