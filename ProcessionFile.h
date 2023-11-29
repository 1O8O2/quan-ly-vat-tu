#pragma once
#include <fstream>
#include "UserInterface.h"
#include "dsNhanVien.h"
#include "dsVatTu.h"

using namespace std;

void Introduction();
void WriteNVToFile(dsNV ds);
void ReadNVFile(dsNV& ds);
void WriteAVt(Vt_Node root, ofstream& fileout);
void WriteVtList(Vt_Node root, ofstream& fileout);
void WriteVtToFile(Vt_Node root);
void ReadVtFile(Vt_Node& root);
