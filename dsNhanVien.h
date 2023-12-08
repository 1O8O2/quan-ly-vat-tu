#pragma once
#include <iostream>
#include <string>
#include "dsHoaDon.h"
#include "dsVatTu.h"
#include "GlobalVariables.h"

using namespace std;

struct nhan_vien {
	string maNV;
	string ho;
	string ten;
	string phai;
	bool used = false;
	ds_hoa_don* dshd = new ds_hoa_don;
};

struct dsNV {
	nhan_vien *dsnv[Max_NV];
	int n_nv = 0;
};

int FindIndexNV(dsNV ds, string ma);
bool IsDeleteNVSuccess(dsNV& ds, int index);
bool CheckInfoNVEmpty(nhan_vien* nv);
void ShowNV(nhan_vien* nv, int pos);
void ShowListNVOnePage(dsNV ds, int index, int CurNVPage, int TotalNVPage);
void ShowListNVOnePageAscending(nhan_vien* ds[], int sl, int index, int CurNVPageAscending, int TotalNVPageAscending); void ChangeNVManagerPage(dsNV ds, int CurNVPage, int TotalNVPage);
void ChangeNVManagerPageAscending(nhan_vien* ds[], int sl, int CurNVPageAscending, int TotalNVPageAscending);
int PickItemNv(dsNV ds, int CurNVPage, int TotalNVPage);
void inputNV(dsNV& ds, bool Edited, bool Deleted, int& CurNVPage, int& TotalNVPage);
void MenuManageNV(dsNV& ds);
void DisplayAscendingNV(nhan_vien* ds[], int sl, int CurNVPageAscending, int TotalNVPageAscending);
void PrintListNV(dsNV ds);

int InputHD(nhan_vien*& nv);
int InputCTHD(Vt_Node& root, nhan_vien*& nv, Vt_Node vt, hd_Node* temp);
int PickNVMakeHD(dsNV ds, int CurNVPage, int TotalNVPage);
void DisplayMenuDSHD(nhan_vien* nv, hd_Node* temp, Vt_Node root, int CurHDPage, int TotalHDPage);
void MenuManagerHD(dsNV& ds, Vt_Node& root);

void DisplayTK(string ct[], int sl, bool used);
void ShowHDTK(hoa_donTK  hdtk, int pos);
void ShowListHDTKOnePage(ds_hoa_donTK* HdTkNodeList, int index, int CurHDPage, int TotalHDPage, date ngay1, date ngay2);
void CheckNgayNV(dsNV& ds, date ngay1, date ngay2, int i, ds_hoa_donTK*& dstk);
void ThongKeHD(dsNV ds);

void DisplayPrintingHD(nhan_vien* nv, hd_Node* hd, Vt_Node root, int CurCTHDPage, int TotalCTHDPage);
void CheckingHD(dsNV ds, Vt_Node root);

void InputDateForTopRevenue(date& date1, date& date2, bool& Saved);
void DisplayTopRevenue(dsNV ds, Vt_Node root);

void DisplayStatisticRevenue(dsNV ds);