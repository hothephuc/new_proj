#include <iostream>
#include <random>
#include <time.h>
#include <conio.h>
// #include <boardGenerate.h>
// #include <logic_check.h>
// #include <endgameCheck.h>
// #include <vfx.h>
#include ".\header\board.h"
using namespace std;

//NOTE: hiện vẫn chưa xong các hàm để khiến cho số pokemon chẵn, nhưng vẫn có trường hợp lặp để làm Getmove

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
    
    int cursor = 0;

    generateBoard(size);
    move( cursor, size);
    return 0;
}
