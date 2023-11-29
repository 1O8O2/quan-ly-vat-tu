#pragma once
#include <iostream>
#include <string>

using namespace std;

struct vat_tu {
	string ma_vt;
	string ten_vt;
	string dvt;
	int sl_ton;
	bool used = false;
};

struct vt_Node {
	vat_tu data;
	vt_Node* left;
	vt_Node* right;
	int height;
};
typedef vt_Node* Vt_Node;

void CreateDsvt(Vt_Node& root);
Vt_Node MakeVtNode(vat_tu vt);
int height(Vt_Node root);
Vt_Node LeftRotation(Vt_Node x);
Vt_Node RightRotation(Vt_Node y);
int CountVtNode(Vt_Node root);
void UpdateArrVtList(Vt_Node root, Vt_Node VtNodeList[], int& index);
int getBalanceFactor(Vt_Node root);
Vt_Node AddVt(Vt_Node& root, vat_tu vt);
Vt_Node FindVtNode(Vt_Node root, string ID);
Vt_Node MinVtNode(Vt_Node root);
Vt_Node DeleteVt(Vt_Node& root, string ID);
void ShowVt(vat_tu vt, int pos);
void ShowListVtOnePage(Vt_Node root, int StartIndex, int CurVtPage, int TotalVtPage);
void ChangeVtManagerPage(Vt_Node root, int CurVtPage, int TotalVtPage);
Vt_Node PickItemVt(Vt_Node root, int& pick, int& CurVtPage, int& TotalVtPage);
void InputVt(Vt_Node& root, bool Edited, bool Deleted, int& CurVtPage, int& TotalVtPage);
void MenuManageVT(Vt_Node& root);
void ShowListVtOnePageAscending(Vt_Node ds[], int StartIndex, int sl, int CurVtPageAscending, int TotalVtPageAscending);
void ChangeVtManagerPageAscending(Vt_Node ds[], int sl, int CurVtPageAscending, int TotalVtPageAscending);
void DisplayAscendingNV(Vt_Node temp_ds[], int sl, int CurVtPageAscending, int TotalVtPageAscending);
void quickSort(Vt_Node temp_ds[], int left, int right);
int partition(Vt_Node temp_ds[], int left, int right);
void PrintListVT(Vt_Node root);