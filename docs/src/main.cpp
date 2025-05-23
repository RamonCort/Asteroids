#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;
void ocultar()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false; // Set the cursor visibility to false
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}
int main(int argc, const char **argv)
{
    while (true) { 
	system("cls");
	ocultar();
    MARGEN_LIMITE();
    cursor(50, 14);
    printf("Welcome to the game ");
    cursor(44, 15);
    printf("Press any key to enter the game");
    cursor(50, 20);
    system("pause > NUL");
    cursor(50, 14);
    printf("                                                   "); 
    cursor(44, 15);
    printf("                                                   ");  
     cursor(50, 20);
    printf("                                                   "); 
    return 0;
}