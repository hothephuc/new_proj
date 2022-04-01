// #include<Windows.h>
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
   int x1, y1;
   char c1;
   int x2, y2;
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




//Draw Vertical line
void drawVertical(int size)
{
   for(int i = 0; i < size; i++)
   {
      std::cout << "|       ";        
   }
}

//Draw horizontal line
void drawHorizontal(int size)
{
   for(int i = 0; i < size; i++)
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
   
   int spot_Left = size * size;
   char type;
   int x, y;

   fillBoard(size, Board);
   
   while(spot_Left != 0)
   {
      type = 'A' + rand() % 26;
      for(int i = 0; i < 2; i++)
      {
         do
         {
            x = rand() % size;
            y = rand() % size;
         } while(isValid(Board, x, y));
         Board[x][y] = type;
      }
      spot_Left -= 2;
   }
}

//Draw Board
void drawBoard(int size, int cursor, char Board[][MAX])
{
   for(int i = 0; i < size; i++)
   {
      drawHorizontal(size);
      std::cout << "\n";
      drawVertical(size);
      std::cout << "|\n";
      
      for(int j = 0; j < size; j++)
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
            if(cell.x1 == i && cell.y1 == j || cell.x2 == i && cell.y2 == j)
            {
               std::cout << "\033[1;33m   " << Board[i][j]  << "   \033[0m";
            }
            else if(i == cursor / size && j == cursor % size)
            {
               std::cout << "\033[1;31m   " << Board[i][j]  << "   \033[0m";
            }
            else
            {
               std::cout << "   " << Board[i][j]  << "   ";
            }
         }
         else
         {
            std::cout << "       ";
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
   std::cout << "Press g to check if valid\n";
   std::cout <<"Press space bar to select.\n \n ";
}

void clrscr(){
   std::cout << "\033[2J\033[1;1H";
}

bool checkY(char Board[][MAX])
{
   if(cell.x1 < cell.x2)
   {
      int temp = cell.x1;
      cell.x1 = cell.x2;
      cell.x2 = temp;
   }
   for(int i = cell.x1; i <= cell.x2; i++)
   {   
     if(Board[i][cell.y1] != ' ' || Board[cell.x1][cell.y1] != Board[cell.x2][cell.y2])
         return false;
   }
    return true;
}

bool checkX(char Board[][MAX])
{
   if(cell.y1 < cell .y2)
   {
      int temp = cell.y1;
      cell.y1 = cell.y2;
      cell.y2 = temp;
   }
   for(int i = cell.y1; i <= cell.y2; i++)
   {   
      if(Board[cell.x1][cell.y1] != ' ' || Board[cell.x1][cell.y1] != Board[cell.x2][cell.y2])
         return false;
   }
    return true;
}

bool updateBoard(char Board[][MAX], int size)
{
   if(cell.c1 != cell.c2)
      return false;

   if(cell.x1 == cell.x2)
   {
      if(checkX(Board))
      {
         Board[cell.x1][cell.y1] = ' ';
         Board[cell.x2][cell.y2] = ' ';
      }
      return true;
   }

   if(cell.y1 == cell.y2)
   {
      if(checkY(Board))
      {
         Board[cell.x1][cell.y1] = ' ';
         Board[cell.x2][cell.y2] = ' ';
      }
      return true;
   }
   return false;
}

void move(int cursor,int size, char Board[][MAX]){
   cursor = cursor % (size*size);
   int n = 2, count = 0;
   char move;
   // clrscr();
   drawBoard(size, cursor, Board);
   //move = _getch();
   while(count != 2)
   {
      move = getch();
      switch(move){
         case 'w':{
            if(cursor < size){
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
               cell.x1 = cursor / size;
               cell.y1 = cursor % size;
               cell.c1 = Board[cell.x1][cell.y1];
               n++;
               count += 1;
               break;
            }
            else
            {
               cell.x2 = cursor / size;
               cell.y2 = cursor % size;
               cell.c2 = Board[cell.x2][cell.y2];
               n++;
               count += 1;
               break;
            }
         }
         case 'g':
         {
            return;
         }
      }
      system("clear");
      drawBoard(size, cursor, Board);
      // generateBoard(size);
   }
}

void playgame(char Board[][MAX], int size)
{
   int spot_left = size * size;
   int cursor = 0;
   createBoard(Board, size);
   // drawBoard(size, cursor, Board);
   while(spot_left >= 0)
   {
      move(0, size, Board);
      if(updateBoard(Board, size))
      {  
         updateBoard(Board, size);
         spot_left -= 2;
      }
      std::cout << spot_left << "\n\n";
   }
}