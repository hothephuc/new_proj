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
    int size = easy_difficulty_size;
    char Board[size][MAX];
    int cursor = 0;

    playgame(Board, size);
    return 0;
}
