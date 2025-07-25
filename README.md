# SpaceShooter 🎮

A 2D shooter game developed as a freshman college project using C++ and SFML.

## 📖 About

SpaceShooter is a scrolling shooter game where players control a spaceship through the map. Enemy that come from spawners will try to shoot you or charge you. This project was created as part of my first year college project to demonstrate programming skills, game development concepts, software development.

**Note:** This is a college project that may receive future updates and improvements as I continue learning and developing our programming skills.

## 👥 Authors

- **Cesar** - ALL

*project report can be found in the `documentation/` folder.*

## 🛠️ Installation & Setup

### Prerequisites

- **Linux (Ubuntu/Debian):**
  ```bash
  sudo apt update
  sudo apt install build-essential libsfml-dev
  ```

### Building the Game

#### Linux Build
```bash
# Clone the repository
git clone https://github.com/cesarombredane/space_shooter.git
cd space_shooter

# Build the game
make

# Run the game
./SpaceShooter
```

## 🎮 Controls

- **A** - Move left
- **D** - Move right  
- **S** - Move down
- **W** - Move up
- **Space** - Shoot
- **Escape** - Exit game
- **LShift** - Exit game

## 📁 Project Structure

```
space_shooter/
├── src/
│   ├── include/          # Header files (.h)
│   │   ├── bullet.h
│   │   ├── camera.h
│   │   ├── enemy.h
│   │   ├── gui.h
│   │   ├── input.h
│   │   ├── jeu.h
│   │   ├── map.h
│   │   ├── pathfinding.h
│   │   ├── player.h
│   │   └── spawner.h
│   ├── object/           # Source files (.cpp)
│   │   ├── bullet.cpp
│   │   ├── camera.cpp
│   │   ├── enemy.cpp
│   │   ├── gui.cpp
│   │   ├── input.cpp
│   │   ├── jeu.cpp
│   │   ├── kamikaze.cpp
│   │   ├── main.cpp
│   │   ├── map.cpp
│   │   ├── pathfinding.cpp
│   │   ├── player.cpp
│   │   ├── sniper.cpp
│   │   └── spawner.cpp
│   └── assets/           # Game assets
│       ├── graphics/     # Sprites and textures
│       │   ├── background.png
│       │   ├── bullet.png
│       │   ├── kamikaze.png
│       │   ├── player.png
│       │   ├── sniper.png
│       │   └── tileset.png
│       ├── sounds/       # Audio files
│       │   ├── death_enemy.wav
│       │   ├── death.wav
│       │   ├── impact_enemy.wav
│       │   ├── impact_player.wav
│       │   ├── piou.wav
│       │   └── speed.wav
│       ├── maps/         # Level maps
│       │   ├── map1.txt
│       │   ├── map2.txt
│       │   └── map3.txt
│       └── beon.ttf      # Font file
├── build/                # Compiled object files (generated)
├── Makefile             # Build configuration
├── .gitignore           # Git ignore rules
└── README.md            # This file
```

## 🔧 Technical Details

- **Language:** C++11
- **Graphics Library:** SFML (Simple and Fast Multimedia Library)
- **Platform:** Linux (primary)
- **Build System:** Make

## 📄 License

This project is developed for educational purposes as part of the ISN curriculum.
