#pragma once // tránh đụng độ thư viện khi gọi chồng file lên nhau
#include <iostream>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <ctime> 
#include <dos.h>
#include <stdlib.h>
#include <windows.h>

using namespace std;

int CheckPwd();
void gotoxy(short x, short y);
int wherex(void);
int wherey(void);
void clreol();
void SetColor(WORD color);
void SetBGColor(WORD color);
void clearScreen();
void ShowCur(bool CursorVisibility);
void SizeConsole(SHORT Width, SHORT height);
void SizeConsole();
void cls(HANDLE hConsole);
void clrscr();
void fullscreen();
void setFullScreen();
void exitFullScreen();