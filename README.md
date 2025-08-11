# 🐍 Snake Game in C

School project that implements the classic Snake game in C language, featuring a scoring system, multiple difficulties, and multiplayer mode.

## 🎮 Features

- **Single Player Mode**: Classic Snake game with scoring system
- **Multiplayer Mode**: Two players take turns
- **Difficulty System**: 3 levels (Easy, Normal, Hard)
- **Scoring System**: Save and load scores from file
- **Graphical Interface**: Board drawn with ASCII characters
- **Data Persistence**: Scores are automatically saved

## 🚀 Installation and Execution

### Requirements
- C compiler (GCC, Clang, etc.)
- Windows operating system (due to use of `windows.h` and `conio.h`)
- Full-screen terminal for best experience

### Compilation
```bash
gcc -o snake snake.c
```

### Execution
```bash
./snake
```

**⚠️ IMPORTANT**: Run the program in full-screen for the best gaming experience.

## 🎯 How to Play

### Controls
- **W**: Move up
- **A**: Move left
- **S**: Move down
- **D**: Move right

### Objective
- Eat the apples (■) to grow and earn points
- Avoid hitting the board walls
- Avoid hitting your own body
- Try to achieve the highest score possible

## 🎛️ Game Modes

### 1. PLAY (Single Player Mode)
- Classic Snake game
- Automatic scoring system
- Score saving with aliases

### 2. DIFFICULTY
- **Easy**: Slow movement (90ms)
- **Normal**: Medium speed (60ms)
- **Hard**: Fast movement (30ms)

### 3. MULTIPLAYER
- Two players take turns
- Score comparison at the end
- Automatic winner declaration

### 4. SCORES
- View saved scores
- List sorted by score

### 5. HOW TO PLAY
- Detailed game instructions

## 📁 Project Structure

```
snake/
├── snake.c          # Main source code
├── snake.exe        # Compiled executable
├── puntuaciones.txt # Score file (created automatically)
└── README.md        # This file
```

## 🏗️ Code Architecture

### Data Structures
- `struct snake`: Linked list for snake body
- `struct manzana`: Structure for game apples
- `struct Puntuacion`: Linked list for storing scores

### Main Functions
- **Game Management**: `estadoInicial()`, `mover()`, `crecer()`
- **Collision Detection**: `choqueTablero()`, `choqueSerpiente()`, `choqueManzana()`
- **Scoring System**: `insertarPuntuacion()`, `guardarPuntuaciones()`
- **Interface**: `imprimirTablero()`, `printSnake()`, `imprimirManzana()`

## 🎨 Technical Features

- **Dynamic Memory**: Use of `malloc()` for dynamic structures
- **Non-blocking Input**: Use of `kbhit()` and `getch()`
- **Cursor Positioning**: Custom `gotoxy()` function
- **Data Persistence**: File system for scores
- **Error Prevention**: Prevents 180° turns and memory management

## 📊 Scoring System

Scores are saved in the `puntuaciones.txt` file with the format:
```
1. ALIAS --------- SCORE
2. ALIAS --------- SCORE
...
```

## 🔧 Customization

### Change Game Speed
Modify the values in the `main()` function:
```c
case 1: velocidad = 90;  // Easy
case 2: velocidad = 60;  // Normal  
case 3: velocidad = 30;  // Hard
```

### Change Board Size
Modify the constants in `imprimirTablero()` and `choqueTablero()`.

## 🐛 Troubleshooting

### Compilation Error
- Make sure you have a C compiler installed
- On Windows, use MinGW or Visual Studio

### Display Issues
- Run in full-screen
- Use a terminal compatible with ASCII characters

### Performance Issues
- Close other applications for better performance
- In hard mode, the game can be very fast

---

**Enjoy playing Snake!** 🐍🎮
