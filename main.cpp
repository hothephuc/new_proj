#include <iostream>
#include <random>
#include <time.h>
// #include <conio.h>
// #include <boardGenerate.h>
// #include <logic_check.h>
// #include <endgameCheck.h>
// #include <vfx.h>
#include "./header/board.h"
using namespace std;

void print(char Board[][MAX], int size)
{
    for(int i = 0; i < size - 0; i++)
    {
        for(int j = 0; j < size - 0; j++)
        {
            if(Board[i][j] == ' ')
            {
                std::cout << "H ";
            }
            else std::cout << Board[i][j] << " ";
        }
        std::cout << "\n";
    }
}

int main()
{
    //for generating random character in linked list
    srand(time(0));
    std::random_device rd;

    /*
        3 size:
        - Easy: 6x6
        - Medium: 8x8
        - Hard: 10x10
    */
    int size = easy_difficulty_size + 2;
    char Board[size][MAX];

    playgame(Board, size);


    return 0;
}
