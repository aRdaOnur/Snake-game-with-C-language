//S 9/27/2024 | 1:30
#include <stdio.h>
#include <conio.h> 
#include <curses.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define MAX_LENGTH 100
#define SNAKE_SKIN "X" 
#define FOOD_SIGN "a"

struct snake {
    int x[MAX_LENGTH];
    int y[MAX_LENGTH];
    int length;
};


// functions
void snakeMovement(char key, struct snake *s);
void drawSnake(struct snake *s);
void generateRandomFood(int rows, int cols, int foodsCordinates[10][2]);
void checkIsFoodEated(int fc[10][2], struct snake *s);
void showTheFoods(int fc[10][2]);
void didSnakeEateItsTail(struct snake *s, char *lastChar);

int main() {
    // initial things for curseslib
    initscr();
    noecho();
    cbreak();
    curs_set(0);

    // the snake struct
    struct snake s;
    s.length = 3;// first length of the snake

    // we should define all the cordinates
    for (int i = 0; i < s.length; i++) {
        s.x[i] = 10;
        s.y[i] = 10;
    }


    int rows, cols;
    getmaxyx(stdscr, rows, cols);// to get terminal size 

    int foodsCordinates[10][2];// foods' cordinates 
    srand(time(NULL)); // using current time as a seed to use random 
    // too create random foods
    generateRandomFood(rows, cols, foodsCordinates);

    // the main game loop
    char lastChar = 'd';
    while (1) {
        if (_kbhit()) { 
            lastChar = _getch(); 
        }
        if (lastChar == 'q') { 
            printw("The Game is Over!!");
            break;
        }
        
        clear();
        // checking food and print the foods
        checkIsFoodEated(foodsCordinates, &s);
        showTheFoods(foodsCordinates);
        


        // to controle the snake 
        snakeMovement(lastChar, &s);
        didSnakeEateItsTail(&s, &lastChar);
        drawSnake(&s);
        
        refresh();
        Sleep(100); 
        
    }

    getch();
    endwin();
    return 0;
}

void snakeMovement(char key, struct snake *s) {
    for (int i = s->length - 1; i > 0; i--) {
        s->x[i] = s->x[i - 1];
        s->y[i] = s->y[i - 1];
    }
    if (key == 'w') s->y[0]--;
    else if (key == 's') s->y[0]++;
    else if (key == 'a') s->x[0]--;
    else if (key == 'd') s->x[0]++;
}

void generateRandomFood(int rows, int cols, int foodsCordinates[10][2]) {
    for (int i = 0; i < 10; i++) {
        int x = (rand() % rows);
        int y = (rand() % cols);
        foodsCordinates[i][0] = x;
        foodsCordinates[i][1] = y;        
    }
}


void checkIsFoodEated(int fc[10][2], struct snake *s) {
    for(int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (s->x[j] == fc[i][1] && s->y[j] == fc[i][0]) { 
                fc[i][0] = fc[i][1] = -1; // the cordinates of food will be -1 
                s->length++;
            }
        }
    }
    
}

void showTheFoods(int fc[10][2]) {
    for (int i = 0; i < 10; i ++) {
        mvprintw(fc[i][0], fc[i][1], FOOD_SIGN);// (y, x, food-sign)
    }
}

void drawSnake(struct snake *s) { 
    for (int i = 0; i < s->length; i++) {
        mvprintw(s->y[i], s->x[i],  SNAKE_SKIN);// (y, x, snake-sign)
    }
}

void didSnakeEateItsTail(struct snake *s, char *lastChar) {
    for (int i = 1; i < s->length; i++) {
        if (s->x[0] == s->x[i] && 
            s->y[0] == s->y[i]) {*lastChar = 'q';}
    }
}