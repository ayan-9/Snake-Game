#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define HEIGHT 20
#define WIDTH 40

int snakeTailX[100], snakeTailY[100];
int snakeTailLen;
int gameover, key, score;
int x, y, fruitx, fruity;

char playerName[50];

// Move console cursor to (x, y)
void gotoxy(int x, int y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Hide blinking cursor
void hideCursor() {
    CONSOLE_CURSOR_INFO cursor;
    cursor.dwSize = 1;
    cursor.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

// Save score to a file
void saveScore(const char *name, int score) {
    FILE *fp = fopen("player.txt", "w");
    if (fp != NULL) {
        fprintf(fp, "%s %d\n", name, score);
        fclose(fp);
    }
}

// Load score from file
int loadPreviousScore(const char *name) {
    FILE *fp = fopen("player.txt", "r");
    if (fp == NULL) return -1;

    char fileName[50];
    int lastScore;
    if (fscanf(fp, "%s %d", fileName, &lastScore) == 2) {
        if (strcmp(name, fileName) == 0) {
            fclose(fp);
            return lastScore;
        }
    }
    fclose(fp);
    return -1;
}

// Display startup screen
void startupScreen() {
    system("cls");
    printf("************************************\n");
    printf("         WELCOME TO SNAKE GAME      \n");
    printf("************************************\n\n");
    printf("Enter your name: ");
    gets(playerName);

    int prevScore = loadPreviousScore(playerName);
    if (prevScore != -1)
        printf("Welcome back %s! Your last score was: %d\n", playerName, prevScore);
    else
        printf("Hello %s! No previous record found.\n", playerName);

    printf("\nPress any key to start the game...");
    getch();
}

void setup() {
    gameover = 0;
    key = 0;
    score = 0;
    snakeTailLen = 0;

    x = WIDTH / 2;
    y = HEIGHT / 2;

    fruitx = rand() % (WIDTH - 2) + 1;
    fruity = rand() % (HEIGHT - 2) + 1;
}

void draw() {
    gotoxy(0, 0);

    for (int i = 0; i < WIDTH + 2; i++) printf("-");
    printf("\n");

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j <= WIDTH; j++) {
            if (j == 0) printf("#");

            if (i == y && j == x)
                printf("O");
            else if (i == fruity && j == fruitx)
                printf("*");
            else {
                int print = 0;
                for (int k = 0; k < snakeTailLen; k++) {
                    if (snakeTailX[k] == j && snakeTailY[k] == i) {
                        printf("o");
                        print = 1;
                        break;
                    }
                }
                if (!print)
                    printf(" ");
            }

            if (j == WIDTH) printf("#");
        }
        printf("\n");
    }

    for (int i = 0; i < WIDTH + 2; i++) printf("-");
    printf("\n");

    printf("Player: %s | Score: %d\n", playerName, score);
    printf("Use W A S D to move. Press X to quit.\n");
}

void input() {
    if (_kbhit()) {
        switch (tolower(_getch())) {
        case 'a':
            if (key != 2) key = 1;
            break;
        case 'd':
            if (key != 1) key = 2;
            break;
        case 'w':
            if (key != 4) key = 3;
            break;
        case 's':
            if (key != 3) key = 4;
            break;
        case 'x':
            gameover = 1;
            break;
        }
    }
}

void logic() {
    int prevX = snakeTailX[0];
    int prevY = snakeTailY[0];
    int prev2X, prev2Y;

    snakeTailX[0] = x;
    snakeTailY[0] = y;

    for (int i = 1; i < snakeTailLen; i++) {
        prev2X = snakeTailX[i];
        prev2Y = snakeTailY[i];
        snakeTailX[i] = prevX;
        snakeTailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (key) {
    case 1: x--; break;
    case 2: x++; break;
    case 3: y--; break;
    case 4: y++; break;
    }

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        gameover = 1;

    for (int i = 0; i < snakeTailLen; i++) {
        if (snakeTailX[i] == x && snakeTailY[i] == y)
            gameover = 1;
    }

    if (x == fruitx && y == fruity) {
        score += 10;
        fruitx = rand() % (WIDTH - 2) + 1;
        fruity = rand() % (HEIGHT - 2) + 1;
        snakeTailLen++;
    }
}

int main() {
    hideCursor();
    startupScreen();
    setup();

    while (!gameover) {
        draw();
        input();
        logic();
        Sleep(100);
    }

    gotoxy(0, HEIGHT + 5);
    printf("\nGame Over, %s! Your final score: %d\n", playerName, score);
    saveScore(playerName, score);

    printf("Press any key to exit...");
    getch();
    return 0;
}
