#include <iostream>
#include <windows.h>

using namespace std;
//задает коодинаты курсора до обновления консоли
void gotoxy(int x, int y) {
    COORD pos = { x, y };
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}
//размеры игрового поля и змейки
const int WIDTH = 20;
const int HEIGHT = 16;
const int MAX_LEN_SNAKE = (WIDTH - 3) * (HEIGHT - 2);

//управление
const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;

//начальное направление змейки
int snake_dir = UP;
bool isRunning = true;

//игровое поле
char map[] =
"###################\n"
"#                 #\n"
"#                 #\n"
"#                 #\n"
"#                 #\n"
"#                 #\n"
"#                 #\n"
"#                 #\n"
"#                 #\n"
"#                 #\n"
"#                 #\n"
"#                 #\n"
"#                 #\n"
"#                 #\n"
"#                 #\n"
"###################\n";

//символ головы змейки
char snake = 'O';
int snake_x[MAX_LEN_SNAKE] = { 0 };//координаты змейки
int snake_y[MAX_LEN_SNAKE] = { 0 };
int snake_len = 1;//длина
int food_x = 1 + (rand() % (WIDTH - 3));//генерация координат змейки
int food_y = 1 + (rand() % (HEIGHT - 2));
char food = '*'; //символ еды

int main()
{
    snake_x[0] = WIDTH / 2;//начальное положение змейки
    snake_y[0] = HEIGHT / 2;
    double time = clock(); //начало времени для обновления

    while (isRunning) {
        //клавиши управления
        if (GetKeyState('W') & 0x8000)
        {
            snake_dir = UP;
        }
        if (GetKeyState('A') & 0x8000)
        {
            snake_dir = LEFT;
        }
        if (GetKeyState('S') & 0x8000)
        {
            snake_dir = DOWN;
        }
        if (GetKeyState('D') & 0x8000)
        {
            snake_dir = RIGHT;
        }

        //основа обновления времени
        if ((clock() - time) / CLOCKS_PER_SEC >= 0.3) {
            time = clock();
            if (snake_x[0] == food_x && snake_y[0] == food_y) {
                ++snake_len;
                food_x = 1 + (rand() % (WIDTH - 3));
                int food_y = 1 + (rand() % (HEIGHT - 2));
            }

            for (int i = snake_len - 2; i >= 0; --i) {
                snake_x[i + 1] = snake_x[i];
                snake_y[i + 1] = snake_y[i];
            }
            //движение змейки
            if (snake_dir == UP) {
                --snake_y[0];
            }
            if (snake_dir == DOWN) {
                ++snake_y[0];
            }
            if (snake_dir == RIGHT) {
                ++snake_x[0];
            }
            if (snake_dir == LEFT) {
                --snake_x[0];
            }
            //врезание в стены
            if (snake_x[0] == 0 || snake_y[0] == 0 || snake_x[0] == WIDTH - 2 || snake_y[0] == HEIGHT - 1) {
                isRunning = false;
            }
            for (int i = 1; i < snake_len; ++i) {
                if (snake_x[0] == snake_x[i] && snake_y[0] == snake_y[i]) {
                    isRunning = false;
                    i = snake_len;
                }
            }
            //счёт
            gotoxy(0, 0);
            cout << "Length: " << snake_len << endl;
            map[food_y * WIDTH + food_x] = food;

            for (int i = 0; i < snake_len; ++i) { //врезание змейки в себя
                map[snake_y[i] * WIDTH + snake_x[i]] = snake;
            }
            cout << map; //врезание змейки в себя
            for (int i = 0; i < snake_len; ++i) {
                map[snake_y[i] * WIDTH + snake_x[i]] = ' ';
            }
        }
    }
    gotoxy(2, HEIGHT / 2); //вывод текста в конце игры
    cout << "YOU SCORE IS " << snake_len;
    gotoxy(WIDTH, HEIGHT);
}