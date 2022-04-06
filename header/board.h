//#include<Windows.h>
#include <iostream>
#include "getch.h"

//Struct for singular linked list
struct Node
{
   char value;
   Node* next;
};

struct Pos
{
   int x1 = 1, y1 = 0;
   char c1;
   int x2 = 1, y2 = 0;
   char c2;
};

Pos cell;

//Tail = Null for generate Node
Node* header = NULL , *tail = NULL;

//Size for difficulty
const int easy_difficulty_size = 6, medium_difficulty_size = 8, hard_difficulty_size = 10, MAX = 1001;

//Insert new node to linked list
void insertNode(Node** header ,char item)
{
   Node* newNode = new Node;
   newNode->value = item;
   newNode->next = *header;
   *header = newNode;
}

//Create singular linked list
void LinkedList(char Board[][MAX], int size)
{
   for(int i = 0; i < size; i++)
   {
      for(int j = 0; j < size; j++)
      {
         insertNode(&header, Board[i][j]);
      }
   }
}

void clrscr(){
   std::cout << "\033[2J\033[1;1H";
}

//Draw Vertical line
void drawVertical(int size)
{
   for(int i = 0; i < size - 2; i++)
   {
      std::cout << "|       ";        
   }
}

//Draw horizontal line
void drawHorizontal(int size)
{
   for(int i = 0; i < size - 2; i++)
   {
      std::cout << " -------";
   }
}

//fill Array with " "
void fillBoard(int size, char Board[][MAX])
{
   for(int i = 0; i < size; i++)
   {
      for(int j = 0; j < size; j++)
      {
         Board[i][j] = ' ';
      }
   }
}

bool isValid(char Board[][MAX], int x, int y)
{
   if(Board[x][y] != ' ')
   {
      return true;
   }
   return false;
}

//Create Board
void createBoard(char Board[][MAX], int size)
{
   int spot_Left = (size - 2) * (size - 2);
   char type;
   int x, y;

   fillBoard(size, Board);
   
   // while(spot_Left != 0)
   // {
   //    type = 'A' + rand() % 26;
   //    for(int i = 0; i < 2; i++)
   //    {
   //       do
   //       {
   //          x = rand() % size;
   //          y = rand() % size;
   //       } while(isValid(Board, x, y));
   //       Board[x][y] = type;
   //    }
   //    spot_Left -= 2;
   // }

   for(int i = 1; i < size - 1 ; i++)
   {
      for(int j = 1; j < size - 1; j++)
      {
         while(spot_Left != 0)
         {
            type = 'A' + rand() % 26;
            for(int i = 0; i < 2; i++)
            {
               do
               {
                  x = 1 + rand() % (size - 2);
                  y = 1 + rand() % (size - 2);
               } while(isValid(Board, x, y));
               Board[x][y] = type;
            }
            spot_Left -= 2;
         }
      }
   }
}

//Draw Board
void drawBoard(int size, int cursor, char Board[][MAX], int score)
{
   Pos cursor_pos = cell;
   for(int i = 1; i < size - 1; i++)
   {
      drawHorizontal(size);
      std::cout << "\n";
      drawVertical(size);
      std::cout << "|\n";
      
      for(int j = 1; j < size - 1; j++)
      {
         //For Window
         
         // if(i == cursor / size && j == cursor % size){
         //    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
         // }
         //    std::cout << "|"; 
         //    std::cout << "   " << Board[i][j] << "   ";
         //    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

         //For Linux
         std::cout << "|";
         if(Board[i][j] != ' ')
         {
            if(i - 1 == cursor / size && j == cursor % size)
            {
               std::cout << "\033[1;31m   " << Board[i][j]  << "   \033[0m";
            }
            else if(cell.x1 == i && cell.y1 == j || cell.x2 == i && cell.y2 == j)
            {
               std::cout << "\033[1;33m   " << Board[i][j]  << "   \033[0m";
            }
            else
            {
               std::cout << "   " << Board[i][j]  << "   ";
            }
         }
         else
         {
            if(i - 1 == cursor / size && j == cursor % size)
            {
               std::cout << "\033[1;36m  NUL  \033[0m";
            }
            else
               std::cout << "  NUL  ";
         }
         //
      }
      std::cout << "|\n";
      drawVertical(size);
      std::cout << "|\n";
   }
   drawHorizontal(size);
   std::cout << "\n";
   std::cout <<"Use A,S,D,W to move.\n";
   std::cout <<"Press space bar to select.\n";
   std::cout << "Your score is: " << score << "\n";
}

bool checkY(char Board[][MAX])
{
   if(cell.y1 > cell.y2)
   {
      int temp = cell.y1;
      cell.y1 = cell.y2;
      cell.y2 = temp;
   }
   for(int i = cell.y1 + 1; i <= cell.y2; i++)
   {  
      if(Board[cell.x1][i] != cell.c1)
         return false;
   }
   return true;
}

bool checkX(char Board[][MAX])
{
   if(cell.x1 > cell .x2)
   {
      int temp = cell.x1;
      cell.x1 = cell.x2;
      cell.x2 = temp;
   }
   for(int i = cell.x1 + 1; i <= cell.x2; i++)
   {  
      if(Board[i][cell.y1] != cell.c1)
         return false;
   }
   return true;
}

bool check_x_vacant(int y1, int y2, int x,char board[][MAX]){
   int min = y1;
   int max = y2;
   if(y2 < y1){
      min = y2;
      max = y1;
   }
   for(int i = min; i <= max; i++){
      if((i == cell.y1 && x == cell.x1 )||(i == cell.y2 && x == cell.x2)){
         continue;
      }
      if(board[x][i] != ' '){
         return false;
      }
   }
   return true;
}

bool check_y_vacant(int x1, int x2,int y, char board[][MAX]){
   int min = x1;
   int max = x2;
   if(x2 < x1){
      min = x2;
      max = x1;
   }
   for(int i = min; i <= max; i++){
      if((i == cell.x1 && y == cell.y1 )||(i == cell.x2 && y == cell.y2)){
         continue;
      }
      if(board[i][y] != ' '){
         return false;
      }
   }
   return true;
}

bool check_L(char Board[][MAX]){
   bool match = 0;
   if((check_y_vacant(cell.x1, cell.x2, cell.y2,Board) && check_x_vacant(cell.y1, cell.y2,cell.x1, Board)) || (check_x_vacant(cell.y2, cell.y1, cell.x2, Board) && check_y_vacant(cell.x1, cell.x2, cell.y1, Board))){
      match = 1;
   }
   return match;
}

bool updateBoard(char Board[][MAX], int size)
{
   //prevent player from checking same cell twice
   if(cell.x1 == cell.x2 && cell.y1 == cell.y2)
      return false;

   //prevent player from checking two different cells
   if(cell.c1 != cell.c2)
   {
      return false;
   }

   //check horizontally
   if(cell.x1 == cell.x2)
   {
      if(checkY(Board))
      {
         Board[cell.x1][cell.y1] = ' ';
         Board[cell.x2][cell.y2] = ' ';
         return true;
      }
   }

   //check vertically
   if(cell.y1 == cell.y2)
   {
      if(checkX(Board))
      {
         Board[cell.x1][cell.y1] = ' ';
         Board[cell.x2][cell.y2] = ' ';
         return true;
      }
   }

   //check L
   if(check_L(Board)){
      Board[cell.x1][cell.y1] = ' ';
      Board[cell.x2][cell.y2] = ' ';
      return true;
   }
   return false;
}

void move(int cursor,int size, char Board[][MAX], int score){
   cursor =  1 + cursor % (size*size);;
   int n = 2, count = 0;
   char move;
   // clrscr();
   drawBoard(size, cursor, Board, score);
   //move = _getch();
   while(count != 2)
   {
      move = _getch();
      switch(move){
         case 'w':{
            if(cursor < size - 2){
               continue;
            }
            cursor -= size;
            break;
         }
         case 's':{
            cursor += size;
            break;
         }
         case 'd':{
            cursor += 1;
            break;
         }
         case 'a':{
            cursor -= 1;
            break;
         }
         case ' ':
         {
            if(n % 2 == 0)
            {
               cell.x1 = (cursor / size) + 1;
               cell.y1 = cursor % size;
               cell.c1 = Board[cell.x1][cell.y1];
               n++;
               count += 1;
               break;
            }
            else
            {
               cell.x2 = (cursor / size) + 1;
               cell.y2 = cursor % size;
               cell.c2 = Board[cell.x2][cell.y2];
               n++;
               count += 1;
               break;
            }
         }
      }
      // system("clear");
      clrscr();
      drawBoard(size, cursor, Board, score);
   }
}

void checkwin(char Board[][MAX], int size)
{
   for(int i = 1; i < size - 1; i++)
   {
      for(int j = 1; j < size - 1; j++)
      {
         if(Board[i][j] != ' ')
         {
            std::cout << "\nYOU LOSE";
            return;
         }
      }
   }
   std::cout << "\nYOU WON!!";
}

void playgame(char Board[][MAX], int size)
{
   int spot_left = (size - 2) * (size - 2);
   int cursor = 0, score = 0;
   createBoard(Board, size);
   while(spot_left != 0)
   {
      move(0, size, Board);
      if(updateBoard(Board, size))
      {  
         spot_left -= 2;
         score += 100;
         updateBoard(Board, size);
      }  
   }
   checkwin(Board, size);
}




 