#include <bits/stdc++.h>
#include <fstream>
#include <conio.h>   //input part
#include <windows.h> //to sleep
using namespace std;
bool gameOver;

//map dimensions
const int width = 75;
const int height = 25;

//variable for position of head
int x, y;

//variable for position of fruit
int fX, fY;

//score
int score;
int highScore = 0;

//x coordinated and y coordinates of tail
int tailX[width * height], tailY[width * height];
int tailN; //length of tail

enum eDirection
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
eDirection direction; //holds direction of the snake

void ClearScreen()
{
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}
void Setup()
{

    gameOver = false;
    direction = STOP;
    tailN = 0;
    x = width / 2;
    y = width / 2;
    fX = (rand() % (width - 1)) + 1;
    fY = (rand() % height);

    score = 0;
}

void Draw()
{
    ClearScreen();

    for (int i = 0; i < width + 1; i++)
        cout << "#"; //top wall;
    cout << endl;

    //map
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j <= width; j++)
        {
            if (j == 0)
                cout << "#"; //left wall
            else if (i == y && j == x)
                cout << "O"; //head
            else if (i == fY && j == fX)
                cout << "F"; //fruit
            else if (j == width)
                cout << "#"; //right wall at width
            else
            {
                int k;
                for (k = 0; k < tailN; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << 'o';
                        break;
                    }
                }
                if (k == tailN)
                    cout << " ";
            }
        }
        cout << endl;
    }

    for (int i = 0; i < width + 1; i++)
        cout << "#"; //bottom wall;
    cout << endl;
    cout << "SCORE : " << score;
}

void Input()
{
    if (_kbhit() == true) //true if keyboard pressed
    {
        switch (tolower(_getch()))
        {
        case 'a':
        {
            if (direction != RIGHT || tailN == 0)
                direction = LEFT;
            break;
        }
        case 'd':
        {
            if (direction != LEFT || tailN == 0)
                direction = RIGHT;
            break;
        }
        case 'w':
        {
            if (direction != DOWN || tailN == 0)
                direction = UP;
            break;
        }
        case 's':
        {
            if (direction != UP || tailN == 0)
                direction = DOWN;
            break;
        }
        case 'q':
        {
            gameOver = true;
            break;
        }
        }
    }
}

void Logic()
{
    tailX[0] = x;
    tailY[0] = y;
    //tail
    int prevX = tailX[0], prevY = tailY[0];
    int prevX2, prevY2;

    for (int i = 1; i < tailN; i++)
    {
        prevX2 = tailX[i];
        prevY2 = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prevX2;
        prevY = prevY2;
    }

    //changing direction
    switch (direction)
    {
    case LEFT:
    {

        x--;
        break;
    }
    case RIGHT:
    {

        x++;
        break;
    }
    case UP:
    {

        y--; //since top of screen is 0;
        break;
    }
    case DOWN:
    {

        y++;
        break;
    }
    }

    if (x >= width)
        x = 1;
    else if (x <= 0)
        x = width - 1;

    if (y >= height)
        y = 0;
    else if (y < 0)
        y = height - 1;
    //checking ig hit self
    for (int i = 1; i < tailN; i++)
    {
        if (x == tailX[i] && y == tailY[i])
        {
            gameOver = true;
            break;
        }
    }

    if (x == fX && y == fY)
    {
        score += 10;
        //
        fstream hs;
        hs.open("score.txt", ios::in);
        hs >> highScore;
        hs.close();
        //
        highScore = max(score, highScore);
        //
        hs.open("score.txt", ios::out);
        hs << highScore;
        hs.close();
        //
        fX = (rand() % (width - 1)) + 1;
        fY = (rand() % height);
        tailN++;
    }
}
void menu()
{
    system("cls");
    cout << "S.Start\nH.High Score\nQ.Exit\n";
}

int main()
{
    char opt = 'a';
    while (opt != 'Q')
    {
        menu();
        opt = getch();
        opt = toupper(opt);
        switch (opt)
        {
        case 'S':
        {
            srand(time(0));
            Setup();
            while (gameOver != true)
            {
                Draw();
                Input();
                Logic();
                Sleep(100);
            }
            system("cls");
            break;
        }
        case 'H':
        {
            system("cls");
            fstream hs;
            hs.open("score.txt", ios::in);
            hs >> highScore;
            hs.close();
            cout << "\nHIGHSCORE : " << highScore << endl;
            getch();

            break;
        }
        case 'Q':

            break;
        default:
            system("cls");
        }
    }
}