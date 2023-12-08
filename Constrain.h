#pragma once
#include <iostream>
#include <string>
#include"dsHoaDon.h"

using namespace std;

void TypeOnlyAWord(string& result, int& step, bool Edited, bool& Saved, int Limit_word_lenght, int distance);
void TypeWordAndSpace(string& resultd, int& step, bool Edited, bool& Saved, int Limit_word_lenght, int distance);
void TypeOnlyNumber(int& result, int& step, bool Edited, bool& Saved, int Limit_number, int distance);
void TypeWordAndNumber(string& result, int &step, bool Edited, bool& Saved, int Limit_word_lenght, int distance);
void TypeDate(int& result, int& step, bool& Saved, int LimitReach, int distance, int min, int max);
void TypeDoubleNumber(double& result, int& step, bool& Saved, double Limit_number, int distance);
string StandardDate(int ngay, int thang, int nam);
string addDot(int number);
bool CheckValidDate(date& date1, int step);
bool checkPeriod(date d1, date d2, date d3);