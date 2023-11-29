#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "mylib.h"
#include "GlobalVariables.h"

using namespace std;

void NormalLine();
void HighlightLine();
void HighlightLine2();
void HighLightArrow(int x, int y);
void DrawColor(int x, int y, int w, int h, int b_color);
void DeleteArrow(int x, int y);
void Notification(string nd);
void DrawTable();
int scrollMenu(); 
void Menu();
void DrawRemoveTable();
int RemoveConfirm();
void RemoveFormComplete(int sl);
void RemoveForm(int sl);
void Notification(string nd);
void DeleteNotification();
void Display(string ct[], int sl, bool used);
void DisplayForWatch(string ct[], int num_row, int num_item);
void RemoveExceedMember(int cnt, int sl);
void CreateInputForm(string ct[], int sl, int length);
void DrawBorderFuncNV(int x, int y, int length, int height);
int PrintOrUpdate(int index);
void DrawTableStatisticRevenue();
void DrawTableTopRevenue();
void NotificationTK();
void DeleteNotificationTK();