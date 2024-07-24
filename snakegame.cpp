// downloading libraries
#include<bits/stdc++.h>  
#include<conio.h> 
#include<windows.h> 

using namespace std;

#define MAX_LENGTH 1000 // defining max length of snake


//Directions
const char UP = 'U';
const char DOWN = 'D';
const char LEFT = 'L';
const char RIGHT = 'R';

int consoleWidth , consoleHeight;

void initScreen() // to initialize screen
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
    CONSOLE_SCREEN_BUFFER_INFO csbi; //buffering
    GetConsoleScreenBufferInfo(hConsole, &csbi); 
    consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1; 
    consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1; 
}
//defining coordinate
struct Point{
    int xCoord;
    int yCoord;
    Point(){
    }
    Point(int x, int y) 
    {
        xCoord = x;
        yCoord = y;
    }
};

class Snake{
    int length;
    char direction;
public:
    Point body[MAX_LENGTH]; 
    Snake(int x, int y)
    {
       length = 1; 
       body[0] = Point(x,y); 
       direction = RIGHT; 
    }

    int getLength(){
        return length; 
    }

    //cases for changing direction
    void chnageDir(char newDirection){
        if(newDirection == UP && direction != DOWN)
        {
            direction = newDirection;
        }
        else if(newDirection == DOWN && direction != UP)
        {
            direction = newDirection;
        }
        else if(newDirection ==LEFT && direction != RIGHT)
        {
            direction = newDirection;
        }
        else if(newDirection == RIGHT && direction !=LEFT)
        {
            direction = newDirection;
        }
    }

    // movement of snake
    bool move(Point food){
        for(int i=length-1;i>0;i--) 
        {
            body[i] = body[i-1]; 
        }

        switch(direction)
        {
            int val; 
            case UP:
                val = body[0].yCoord;
                body[0].yCoord = val-1; 
                break;
            case DOWN:
                val = body[0].yCoord;
                body[0].yCoord = val+1;
                break;
            case RIGHT:
                val = body[0].xCoord;
                body[0].xCoord = val+1;
                break;
            caseLEFT:
                val = body[0].xCoord;
                body[0].xCoord = val-1;
                break;

        }

        //snake bites itself
        for(int i=1;i<length;i++)
        {
            if(body[0].xCoord == body[i].xCoord && body[0].yCoord == body[i].yCoord) 
            {
                return false;
            }
        }

        //snake eats food
        if(food.xCoord == body[0].xCoord && food.yCoord == body[0].yCoord)
        {
            body[length] = Point(body[length-1].xCoord, body[length-1].yCoord); 
            length++; 
        }

        return true;

    }
};

class Board{
    Snake *snake; 
    const char SNAKE_BODY = 'O';
    Point food;
    const char FOOD = 'o';
    int score;
public:
    Board(){
        spawnFood(); 
        snake = new Snake(10,10); 
        score = 0;
    }

    ~Board(){
        delete snake; 
    }

    int getScore(){
        return score; 
    }

    void spawnFood(){
        int x = rand() % consoleWidth;
        int y = rand() % consoleHeight;
        food = Point(x, y); 
    }

    void displayCurrentScore(){
        gotoxy(consoleWidth/2,0);
        cout<<"Current Score : "<< score;
    }

    void gotoxy(int x, int y)
    {
        COORD coord; 
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
    }

    void draw(){
        system("cls"); 
        for(int i=0;i<snake->getLength();i++)
        {
            gotoxy(snake->body[i].xCoord, snake->body[i].yCoord);
            cout<<SNAKE_BODY; 
        }

        gotoxy(food.xCoord, food.yCoord); 
        cout<<FOOD; 

        displayCurrentScore(); 
    }

    bool update(){
       bool isAlive = snake->move(food);
       if(isAlive == false)
       {
           return false;
       }

        if(food.xCoord == snake->body[0].xCoord && food.yCoord == snake->body[0].yCoord)
        {
            score++;
            spawnFood();
        }
       return true;
    }

    void getInput(){
        if(kbhit())
        {
            int key = getch();
            if(key == 'w' || key == 'W')
            {
                snake->chnageDir(UP);
            }
            else if(key == 'a' || key == 'A')
            {
                snake->chnageDir(DIR_LEFT);
            }
            else if(key == 's' || key == 'S')
            {
                snake->chnageDir(DOWN);
            }
            else if(key == 'd' || key == 'D')
            {
                snake->chnageDir(RIGHT);
            }
        }
    }

};

int main(){
    srand(time(0));
    initScreen();
    Board *board = new Board();
    while(board->update())
    {
        board->getInput();
        board->draw();
        Sleep(500);
    }

    cout<<"Game over"<<endl;
    cout<<"Final score is :"<<board->getScore();
    return 0;
}
