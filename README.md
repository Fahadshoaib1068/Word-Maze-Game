# 🔠 Word Maze: The Ultimate Word Search Challenge (C++ Console Game)

A colorful and interactive **Word Search Puzzle game** built in **C++**, played entirely in the console.  
This game challenges players to find hidden words from a dictionary inside a randomly generated letter grid — with **hints, highlights, and progress tracking**.

It demonstrates **arrays, string manipulation, random generation, and console color graphics** using the Windows API.

---

## 📖 About

**Word Maze** is a console-based puzzle game where you search for words hidden in random grids of letters.  
Words may appear **horizontally, vertically, or diagonally**, and you must identify their **starting position** to earn points.  

The game features:
- Dynamic grid generation (`5x5`, `7x7`, `10x10`, or random sizes)
- Highlighted found words
- A one-time hint system
- Time and attempt tracking

---

## ✨ Features

- 🧩 **Dynamic Grid Sizes** — Choose between 5×5, 7×7, 10×10, or random grids.  
- 🔤 **Random Word Placement** — Words are placed in random directions (8 possible orientations).  
- 🎨 **Colored Console Display** — Uses `windows.h` for colorful text and highlights found words.  
- 💡 **Hint System** — Gives one hint per game by revealing a nearby starting position.  
- ⏱ **Performance Tracking** — Shows number of attempts and total time taken.  
- 📚 **Built-in Dictionary** — Includes default words like `stack`, `input`, `output`, `tree`, `program`, and more.  
- 🧠 **Smart Word Validation** — Detects words in any direction and prevents duplicates.  
- 📈 **Progress Display** — Shows remaining and found words during the session.  

---

## 🛠 Installation & Run

### Requirements
- **Windows OS** (uses `windows.h` for colors)  
- **C++ Compiler** (e.g., MinGW, MSVC, or g++ with Windows console support)  

### Steps 
   ```bash
   git clone https://github.com/your-username/Word-Maze.git
   cd Word-Maze
   g++ WordMaze.cpp -o WordMaze.exe
   WordMaze.exe
   ```

## 🚀 Gameplay

1. Choose a grid size (5x5, 7x7, 10x10, or random).
2. Words from the built-in dictionary will be hidden in the grid.
3. Enter your guesses as: <word> <row> <column>
4. Example: input 2 3
5. If correct, the word is highlighted in color.
6. Use the Hint option once per game to get a clue about a word’s location.
7. View your progress anytime using the Progress menu.
8. When all words are found, your attempt count and time taken are displayed.

## 🎮 Menu Options

| Option | Description |
|--------|-------------|
| `1` | Play Game |
| `2` | Exit Game |

During Game:

| Option | Description |
|--------|-------------|
| `1` | Guess a word |
| `2` | Use Hint (one-time) |
| `3` | Print Board |
| `4` | Show Progress |
| `5` | Exit |

## 📜 License

This project is licensed under the MIT License.
You’re free to use, modify, and distribute it.

## 👤 Author

Made by @Fahadshoaib1068
