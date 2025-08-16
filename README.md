🐍 Snake Game in C

This project is a console-based Snake Game written in C using conio.h and windows.h. The game runs inside the terminal and brings back the classic arcade feel of Snake.

🎯 Purpose of the Game

The goal of the Snake Game is simple: 
- Control the snake using WASD keys.
- Eat the fruit (*) to score points and grow longer.
- Avoid hitting the walls (#) or the snake’s own body (o).
- The game ends if you collide with a wall or yourself.

🎮 It’s designed for fun and practice, and also demonstrates concepts like:
- Arrays for storing the snake’s body.
- Real-time keyboard input handling
- Random number generation (fruit placement)
- File handling (saving and loading player scores)
- Console graphics (moving cursor, hiding cursor, redrawing screen)

⚙️ How the Game Works
- Startup Screen
- Player enters their name.
- Last score is loaded (if available).
- Game Setup.
- Snake starts at the center of the grid.
- A fruit is randomly placed inside the play area.
- Gameplay Loop.
- Snake moves in the chosen direction (W = up, S = down, A = left, D = right).
- Eating a fruit increases score and length.
- Collision with walls or itself ends the game.
- Game Over.
- Final score is displayed.
- Score is saved for the player.

🖥️ Controls

W → Move Up

S → Move Down

A → Move Left

D → Move Right

X → Quit the Game

📂 Features

- Player name and score saving.
- Previous score retrieval.
- Growing snake body.

Random fruit generation

Console-based graphics
