#include <iostream>
#include <string>
#include "dsHoaDon.h"
#include "dsVatTu.h"
#include "GlobalVariables.h"
#include "Constrain.h"
#include "UserInterface.h"
#include <iomanip>

using namespace std;

extern string ContentNV[4];
extern string ContentHD[4];
extern string ContentVT[4];
extern string ContentCTHD[5];
extern string ButtonFunc[2];
extern string HDInPeriod[5];
extern int xKeyButton[4];
extern int xKeyContentCTHD[6];
extern int xKeyContentHD[4];
extern int xKeyContentNV[5];

void Init_hd(hoa_don& hd) {
	hd.soHD = "";
	hd.ngay_lapHD.ngay = 0;
	hd.ngay_lapHD.thang = 0;
	hd.ngay_lapHD.nam = 0;
	hd.loai;
}

//----------- tao moi 1 node kieu hoa_don -----------
hd_Node* MakeHdNode(hoa_don data) {
	hd_Node* temp = new hd_Node;
	temp->data = data;
	temp->next = NULL;
	return temp;
}

hoa_donTK_Node* MakeHdTkNode(hoa_don data, string maNV, string ho, string ten) {
	hoa_donTK_Node* temp = new hoa_donTK_Node;

	// Map data from hoa_don to hoa_donTK
	temp->data.soHD = data.soHD;
	temp->data.ngay_lapHD = data.ngay_lapHD;
	temp->data.loai = data.loai;
	temp->data.ho = ho;
	temp->data.ten = ten;
	temp->data.maNV = maNV;



	temp->next = NULL;
	return temp;
}

//---------- them vao cuoi danh sach -----------
void AddLastListHD(ds_hoa_don*& dshd, hoa_don hd) {
	hd_Node* newNode = MakeHdNode(hd);
	if (dshd->head == NULL) {
		dshd->head = newNode;
		dshd->n_hd++;
		return;
	}
	hd_Node* temp = dshd->head;
	while (temp->next != NULL) {
		temp = temp->next;
	}
	temp->next = newNode;
	dshd->n_hd++;
}

//--------- toa bang nhap hoa don ------------
void InputFormHD(string ct[], int sl, int length) {
		gotoxy(X_Title + 65, Y_Title);
		cout << " Lap hoa don ";

		for (int i = 0; i < sl; i++) {
			gotoxy(X_InputForm, 7 + i * 4);
			cout << ct[i];

			if (i == 1) {
				gotoxy(X_InputForm + 20, 7 + i * 4);
				cout << " / ";

				gotoxy(X_InputForm + 30, 7 + i * 4);
				cout << " / ";
			}
		}
		for (int j = 0; j < sl + 1; j++) {
			for (int i = X_InputForm - 2; i < X_InputForm - 2 + length; i++) {
				gotoxy(i, 5 + j * 4);
				cout << char(219);
			}
		}
		for (int iy = Y_InputForm; iy <= Y_InputForm + sl * 4; iy++) {
			gotoxy(X_InputForm - 2, iy);
			cout << char(219);

			gotoxy(X_InputForm - 2 + length, iy);
			cout << char(219);
		}
		gotoxy(X_InputForm + 13, Y_InputForm + 14);
		cout << "  Nhap  ";

		gotoxy(X_InputForm + 30, Y_InputForm + 14);
		cout << "  Xuat  ";
}

//----------- tim so hoa don -------------
hd_Node* FindSoHDExist(ds_hoa_don* dshd, string ID) {
	if (dshd->head == NULL) {
		return NULL;
	}
	hd_Node* temp = dshd->head;
	while (temp != NULL) {
		if (temp->data.soHD == ID) {
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}

//----------- tinh tri gia -------------
int ComputeValue(int sl, double donGia, double VAT) {
	return (sl * donGia) + ((sl * donGia) * VAT / 100);
}

//----------- chon loai hoa don ----------
int PickHDType() {
	ShowCur(false);
	int pointer = 1;
	HighlightLine();
	gotoxy(X_InputForm + 13, Y_InputForm + 14);
	cout << "  Nhap  ";
	char event;
	while (true) {
		event = _getch();
		if (event == 224) {
			event = _getch();
		}
		switch (event) {
		case KEY_LEFT:
			if (pointer == 2) {
				NormalLine();
				gotoxy(X_InputForm + 30, Y_InputForm + 14);
				cout << "  Xuat  ";
				pointer--;

				HighlightLine();
				gotoxy(X_InputForm + 13, Y_InputForm + 14);
				cout << "  Nhap  ";
			}
			break;
		case KEY_RIGHT:
			if (pointer == 1) {
				NormalLine();
				gotoxy(X_InputForm + 13, Y_InputForm + 14);
				cout << "  Nhap  ";
				pointer++;

				HighlightLine();
				gotoxy(X_InputForm + 30, Y_InputForm + 14);
				cout << "  Xuat  ";
			}
			break;
		case ENTER:
			NormalLine();
			return pointer;
		}
	}
}

void ButtonFunction() {
	for (int i = 0; i < 2; i++) {
		gotoxy(xKeyButton[i * 2] + 5, Y_Display + 46);
		cout << ButtonFunc[i];

		for (int ix = xKeyButton[i * 2]; ix <= xKeyButton[i * 2 + 1]; ix++) {
			gotoxy(ix, Y_Display + 43);
			cout << char(205);

			gotoxy(ix, Y_Display + 49);
			cout << char(205);
		}

		for (int iy = Y_Display + 44; iy <= Y_Display + 49; iy++) {
			gotoxy(xKeyButton[i * 2], iy);
			cout << char(186);

			gotoxy(xKeyButton[i * 2 + 1], iy);
			cout << char(186);
		}

		gotoxy(xKeyButton[i * 2], Y_Display + 43);
		cout << char(201);
		gotoxy(xKeyButton[i * 2 + 1], Y_Display + 43);
		cout << char(187);
		gotoxy(xKeyButton[i * 2], Y_Display + 49);
		cout << char(200);
		gotoxy(xKeyButton[i * 2 + 1], Y_Display + 49);
		cout << char(188);
	}

}

//----------------- ve bang in cac chi tiet hoa don cua 1 hoa don ------------
void TableOfHD() {	
	ShowCur(0);

	//ve bang in thong tin cua hoa don
	gotoxy(X_Display + 15, Y_Display + 8);
	cout << "Thong tin hoa don";
	for (int ix = X_Display; ix <= X_Display + 50; ix++) {
		gotoxy(ix, Y_Display + 6);
		cout << char(220);

		gotoxy(ix, Y_Display + 10);
		cout << char(220);

		gotoxy(ix, Y_Display + 34);
		cout << char(220);
	}
	for (int iy = Y_Display + 7; iy <= Y_Display + 34; iy++) {
		gotoxy(X_Display, iy);
		cout << char(219);

		gotoxy(X_Display + 50, iy);
		cout << char(219);
	}

	//ve bang in thong tin vat tu cua hoa don
	for (int i = 0; i < 5; i++) {
		gotoxy(xKeyContentCTHD[i], Y_Display - 1);
		cout << ContentCTHD[i];
	}
	for (int ix = xKeyContentCTHD[0] - 2; ix <= xKeyContentCTHD[5] - 2; ix++) {
		gotoxy(ix, Y_Display - 3);
		cout << char(220);

		gotoxy(ix, Y_Display);
		cout << char(220);

		gotoxy(ix, Y_Display + 41);
		cout << char(220);
	}

	for (int i = 0; i < 6; i++) {
		for (int iy = Y_Display - 2; iy <= Y_Display + 41; iy++) {
			gotoxy(xKeyContentCTHD[i] - 2, iy);
			cout << char(219);
		}
	}
} 

//--------- ve bang in cac chi tiet hoa don cua 1 hoa don kem tri gia ----------
void TableOfHDWithValue() {
	TableOfHD();
	gotoxy(178, Y_Display - 1);
	cout << "Tri gia";
	
	for (int ix = xKeyContentCTHD[5] - 2; ix <= xKeyContentCTHD[6]; ix++) {
		gotoxy(ix, Y_Display - 3);
		cout << char(220);

		gotoxy(ix, Y_Display);
		cout << char(220);

		gotoxy(ix, Y_Display + 41);
		cout << char(220);
	}

	for (int iy = Y_Display - 2; iy <= Y_Display + 41; iy++) {
		gotoxy(xKeyContentCTHD[5] - 2, iy);
		cout << char(219);

		gotoxy(xKeyContentCTHD[6], iy);
		cout << char(219);
	}

	//ve bang in tong hoa don
	gotoxy(xKeyContentCTHD[0], Y_Display + 43);
	cout << "Tong gia tri hoa don: ";
	for (int ix = xKeyContentCTHD[0] - 2; ix <= xKeyContentCTHD[6]; ix++) {
		gotoxy(ix, Y_Display + 45);
		cout << char(220);
	}

	for (int iy = Y_Display + 42; iy <= Y_Display + 45; iy++) {
		gotoxy(xKeyContentCTHD[0] - 2, iy);
		cout << char(219);

		gotoxy(xKeyContentCTHD[6], iy);
		cout << char(219);
	}
}

//--------- in 1 chi tiet vat tu -------
void ShowCTHD(cthd_Node* cthd_temp, Vt_Node root, int pos) {
	Vt_Node vt_temp = FindVtNode(root, cthd_temp->data.maVT);
	gotoxy(xKeyContentCTHD[0], Y_Display + 3 + pos * 4);
	cout << cthd_temp->data.maVT;
	gotoxy(xKeyContentCTHD[1], Y_Display + 3 + pos * 4);
	cout << vt_temp->data.ten_vt;
	gotoxy(xKeyContentCTHD[2], Y_Display + 3 + pos * 4);
	cout << cthd_temp->data.sl;
	gotoxy(xKeyContentCTHD[3], Y_Display + 3 + pos * 4);
	cout << cthd_temp->data.donGia;
	gotoxy(xKeyContentCTHD[4], Y_Display + 3 + pos * 4);
	cout << cthd_temp->data.VAT;
}

//--------- in danh sach chi tiet hoa don trong 1 trang ----------
void ShowListCTHDOnePage(hd_Node* temp, Vt_Node root, int StartIndex, int CurHDPage, int TotalHDPage) {
	int sl = temp->data.dscthd->n_cthd;
	gotoxy(X_DisplayNum + 18, Y_DisplayNum);
	cout << "      ";
	gotoxy(X_DisplayNum, Y_DisplayNum);
	cout << "So luong vat tu: " << sl;
	cthd_Node* cthd_temp = temp->data.dscthd->head;
	int i = 0;
	for (int j = i; j < NumberPerPage; j++) {
		for (int k = 0; k < 5; k++) {
			for (int l = xKeyContentCTHD[k]; l < xKeyContentCTHD[k + 1] - 2; l++) {
				gotoxy(l, Y_Display + 3 + j * 4);
				cout << " ";
			}
		}
	}
	for (int i = 0; i < StartIndex && i < sl; i++) {
		cthd_temp = cthd_temp->next;
	}
	for (i = 0; i + StartIndex < sl && i < NumberPerPage; i++) {
		ShowCTHD(cthd_temp, root, i);
		cthd_temp = cthd_temp->next;
	}
	gotoxy(X_Page, Y_Page);
	cout << " Trang " << CurHDPage << "/" << TotalHDPage;
}

//--------- in 1 chi tiet vat tu voi tri gia -------
void ShowCTHDWithValue(cthd_Node* cthd_temp, Vt_Node root, int pos) {
	Vt_Node vt_temp = FindVtNode(root, cthd_temp->data.maVT);
	gotoxy(xKeyContentCTHD[0], Y_Display + 3 + pos * 4);
	cout << cthd_temp->data.maVT;
	gotoxy(xKeyContentCTHD[1], Y_Display + 3 + pos * 4);
	cout << vt_temp->data.ten_vt;
	gotoxy(xKeyContentCTHD[2], Y_Display + 3 + pos * 4);
	cout << cthd_temp->data.sl;
	gotoxy(xKeyContentCTHD[3], Y_Display + 3 + pos * 4);
	cout << cthd_temp->data.donGia;
	gotoxy(xKeyContentCTHD[4], Y_Display + 3 + pos * 4);
	cout << cthd_temp->data.VAT;
	gotoxy(xKeyContentCTHD[5], Y_Display + 3 + pos * 4);
	cout << addDot(ComputeValue(cthd_temp->data.sl, cthd_temp->data.donGia, cthd_temp->data.VAT));
}

//--------- in danh sach chi tiet hoa don trong 1 trang voi tri gia ----------
void ShowListCTHDOnePageWithValue(hd_Node* temp, Vt_Node root, int StartIndex, int CurCTHDPage, int TotalCTHDPage) {
	int sl = temp->data.dscthd->n_cthd;
	gotoxy(X_DisplayNum + 18, Y_DisplayNum);
	cout << "      ";
	gotoxy(X_DisplayNum, Y_DisplayNum);
	cout << "So luong vat tu: " << sl;
	cthd_Node* cthd_temp = temp->data.dscthd->head;
	int i = 0;
	for (int j = i; j < NumberPerPage; j++) {
		for (int k = 0; k < 6; k++) {
			for (int l = xKeyContentCTHD[k]; l < xKeyContentCTHD[k + 1] - 2; l++) {
				gotoxy(l, Y_Display + 3 + j * 4);
				cout << " ";
			}
		}
	}
	for (int i = 0; i < StartIndex && i < sl; i++) {
		cthd_temp = cthd_temp->next;
	}
	for (i = 0; i + StartIndex < sl && i < NumberPerPage; i++) {
		ShowCTHDWithValue(cthd_temp, root, i);
		cthd_temp = cthd_temp->next;
	}
	gotoxy(X_Page, Y_Page);
	cout << " Trang " << CurCTHDPage << "/" << TotalCTHDPage;
}


//----------- chon chuc nang trong muc lap hoa don -----------
int PickFuncHD(Vt_Node root, hd_Node* temp, int CurHDPage, int TotalHDPage) {
	ShowCur(0);
	int pointer = 0;
	DrawColor(xKeyButton[pointer * 2], Y_Display + 43, 30, 6, 1);
	gotoxy(xKeyButton[pointer * 2] + 5, Y_Display + 46);
	cout << ButtonFunc[pointer];
	char signal;
	while (true) {
		signal = _getch();
		if (signal == -32) {
			signal = _getch();
		}
		switch (signal) {
		case KEY_LEFT:
			if (pointer > 0) {
				DrawColor(xKeyButton[pointer * 2], Y_Display + 43, 30, 6, 0);
				gotoxy(xKeyButton[pointer * 2] + 5, Y_Display + 46);
				cout << ButtonFunc[pointer];

				pointer--;

				DrawColor(xKeyButton[pointer * 2], Y_Display + 43, 30, 6, 1);
				gotoxy(xKeyButton[pointer * 2] + 5, Y_Display + 46);
				cout << ButtonFunc[pointer];
			}
			break;
		case KEY_RIGHT:
			if (pointer < 1) {
				DrawColor(xKeyButton[pointer * 2], Y_Display + 43, 30, 6, 0);
				gotoxy(xKeyButton[pointer * 2] + 5, Y_Display + 46);
				cout << ButtonFunc[pointer];

				pointer++;

				DrawColor(xKeyButton[pointer * 2], Y_Display + 43, 30, 6, 1);
				gotoxy(xKeyButton[pointer * 2] + 5, Y_Display + 46);
				cout << ButtonFunc[pointer];
			}
			break;
		case PAGE_UP:
			if (CurHDPage > 1) {
				CurHDPage--;
				NormalLine();
				ShowListCTHDOnePage(temp, root, (CurHDPage - 1) * NumberPerPage, CurHDPage, TotalHDPage);
			}
			break;
		case PAGE_DOWN:
			if (CurHDPage < TotalHDPage) {
				CurHDPage++;
				NormalLine();
				ShowListCTHDOnePage(temp, root, (CurHDPage - 1) * NumberPerPage, CurHDPage, TotalHDPage);
			}
			break;
		case ENTER:
			NormalLine();
			return pointer;
		case ESC:
			NormalLine();
			return -1;
		}
	}
}

//------------- ve bang chon hoa don de in -------------
void DrawTablePickHD() {
	gotoxy(X_Title + 55, Y_Title);
	cout << "Chon hoa don";
	for (int i = 0; i < 3; i++) {
		gotoxy(xKeyContentHD[i] + 3, Y_Display);
		cout << ContentHD[i];
	}
	for (int ix = 120; ix <= 180; ix++) {
		gotoxy(ix, Y_Display - 2);
		cout << char(220);

		// ve thanh ngang ben tren so 2
		gotoxy(ix, Y_Display + 2);
		cout << char(220);

		//ve thanh ngang ben duoi
		gotoxy(ix, Y_Display + 45);
		cout << char(220);
	}
	//ve cac duong thang de phan chia cac cot
	for (int iy = Y_Display - 1; iy <= Y_Display + 45; iy++) {
		for (int i = 0; i < 4; i++) {
			gotoxy(xKeyContentHD[i], iy);
			cout << char(219);
		}
	}
}

//------------- in du lieu cua 1 hoa don -----------
void ShowHD(hoa_don hd, int pos) {
	gotoxy(xKeyContentHD[0] + 4, Y_Display + 4 + pos * 4);
	cout << hd.soHD;
	gotoxy(xKeyContentHD[1] + 4, Y_Display + 4 + pos * 4);
	cout << StandardDate(hd.ngay_lapHD.ngay, hd.ngay_lapHD.thang, hd.ngay_lapHD.nam);
	gotoxy(xKeyContentHD[2] + 4, Y_Display + 4 + pos * 4);
	(hd.loai == 'N') ? cout << "Nhap" : cout << "Xuat";
}

//------------ in cac hoa don trong 1 trang ---------
void ShowListHDOnePage(ds_hoa_don* dshd, int index, int CurHDPage, int TotalHDPage) {
	gotoxy(xKeyContentHD[0] + 20, Y_DisplayNum);
	cout << "         ";
	gotoxy(xKeyContentHD[0], Y_DisplayNum);
	cout << "So luong hoa don: " << dshd->n_hd;
	int i = 0;

	for (int j = i; j < NumberPerPage; j++) {
		for (int k = 0; k < 3; k++) {
			for (int l = xKeyContentHD[k] + 2; l < xKeyContentHD[k + 1] - 2; l++) {
				gotoxy(l, Y_Display + 4 + j * 4);
				cout << " ";
			}
		}
	}

	hd_Node* hd_temp = dshd->head;
	for (int i = 0; i < index && i < dshd->n_hd; i++) {
		hd_temp = hd_temp->next;
	}
	for (i = 0; i + index < dshd->n_hd && i < NumberPerPage; i++) {
		ShowHD(hd_temp->data, i);
		hd_temp = hd_temp->next;
	}
	gotoxy(X_Page, Y_Page);
	cout << " Trang " << CurHDPage << "/" << TotalHDPage;
}

//------------ chon hoa don ------------
hd_Node* PickHD(ds_hoa_don* dshd, int CurHDPage, int TotalHDPage) {
	ShowCur(0);

	int sl = dshd->n_hd;
	hd_Node** dshdNode = new hd_Node*[sl];
	hd_Node* temp = dshd->head;

	for (int i = 0; i < sl; i++) {
		dshdNode[i] = temp;
		temp = temp->next;
	}
	//truong hop khong co hoa don nao
	if (!dshd->n_hd) {
		char signal;
		while (true) {
			signal = _getch();
			if (signal == ESC) {
				return NULL;
			}
		}
	}

	//--------highlight dong dang chon--------
	int lower_bound = (CurHDPage - 1) * NumberPerPage;
	int pick = lower_bound;
	int index = 0;
	int upper_bound = CurHDPage * NumberPerPage;
	HighlightLine2();
	HighLightArrow(115, Y_Display + 4 + index * 4);
	ShowHD(dshdNode[pick]->data, index);

	//--------kiem tra nut len xuong
	char signal;
	while (true) {
		signal = _getch(); //kiem tra co nhap gi tu ban phim khong
		if (signal == -32) {
			signal = _getch();
		}
		switch (signal) {
		case KEY_UP:
			if (pick > lower_bound && index > 0) {
				NormalLine();
				DeleteArrow(115, Y_Display + 4 + index * 4);
				ShowHD(dshdNode[pick]->data, index);
				pick--; index--;

				HighlightLine2();
				HighLightArrow(115, Y_Display + 4 + index * 4);
				ShowHD(dshdNode[pick]->data, index);
			}
			break;
		case KEY_DOWN:
			if (pick + 1 < sl && pick + 1 < upper_bound && index < NumberPerPage) {
				NormalLine();
				DeleteArrow(115, Y_Display + 4 + index * 4);
				ShowHD(dshdNode[pick]->data, index);
				pick++; index++;

				HighlightLine2();
				HighLightArrow(115, Y_Display + 4 + index * 4);
				ShowHD(dshdNode[pick]->data, index);
			}
			break;
		case PAGE_UP:
			if (CurHDPage > 1) {
				CurHDPage--;
				lower_bound = (CurHDPage - 1) * NumberPerPage;
				upper_bound = CurHDPage * NumberPerPage;
				DeleteArrow(115, Y_Display + 4 + index * 4);
				index = 0;
				pick = lower_bound;
				NormalLine();
				
				HighlightLine2();
				HighLightArrow(115, Y_Display + 4 + index * 4);
				ShowHD(dshdNode[pick]->data, index);
			}
			break;
		case PAGE_DOWN:
			if (CurHDPage < TotalHDPage) {
				CurHDPage++;
				lower_bound = (CurHDPage - 1) * NumberPerPage;
				upper_bound = CurHDPage * NumberPerPage;
				DeleteArrow(115, Y_Display + 4 + index * 4);
				index = 0;
				pick = lower_bound;
				NormalLine();
				
				HighlightLine2();
				HighLightArrow(115, Y_Display + 4 + index * 4);
				ShowHD(dshdNode[pick]->data, index);
			}
			break;
		case ENTER:
			NormalLine();
			DeleteArrow(115, Y_Display + 4 + index * 4);
			return dshdNode[pick]; //luu lua chon de thuc hien chuc nang ham Menu
		case ESC:
			NormalLine();
			DeleteArrow(115, Y_Display + 4 + index * 4);
			return NULL;
		}
	}
}

