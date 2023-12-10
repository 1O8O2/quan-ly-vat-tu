#include <iostream>
#include <string>
#include <iomanip>
#include "UserInterface.h"
#include "dsHoaDon.h"
#include "dsNhanVien.h"
#include "dsVatTu.h"
#include "mylib.h"
#include "Constrain.h"
#include "ProcessionFile.h"

using namespace std;
extern string ContentNV[4];
extern string ContentHD[4];
extern string ContentVT[4];
extern string ContentCTHD[5];
extern string ContentTK[6];
extern int xKeyContentCTHD[7];
extern int xKeyContentNV[5];
extern int xKeyContentTK[8];

//----------- tim chi so cua ma nhan vien ---------
int FindIndexNV(dsNV ds, string ma) {
	for (int i = 0; i < ds.n_nv; i++) {
		if (ds.dsnv[i]->maNV == ma) {
			return i;
		}
	}
	return -1;
}

//----------- kiem tra da xoa nhan vien thanh cong hay chua -----------
bool IsDeleteNVSuccess(dsNV& ds, int index) {
	if (index < 0) {
		return false;
	}
	delete ds.dsnv[index];
	for (int i = index; i < ds.n_nv; i++) {
		ds.dsnv[i] = ds.dsnv[i + 1];
	}
	ds.n_nv--;
	return true;
}

//---------- kiem tra nhap lieu nhan vien ----------
bool CheckInfoNVEmpty(nhan_vien* nv) {
	if (nv->maNV.length() == 0 || nv->ho.length() == 0 || nv->ten.length() == 0 || nv->phai.length() == 0) {
		return false;
	}
	return true;
}

//---------- hien thong tin nhan vien -----------
void ShowNV(nhan_vien *nv, int pos) {
	int xKeyContent[5] = { 12, 30, 65, 100, 113 };

	gotoxy(xKeyContent[0] + 3, Y_Display + 4 + pos * 4);
	cout << left << setw(15) << nv->maNV;
	gotoxy(xKeyContent[1] + 3, Y_Display + 4 + pos * 4); 
	cout << left << setw(25) << nv->ho;
	gotoxy(xKeyContent[2] + 3, Y_Display + 4 + pos * 4); 
	cout << left << setw(25) << nv->ten;
	gotoxy(xKeyContent[3] + 3, Y_Display + 4 + pos * 4);
	cout << left << setw(5) << nv->phai;
}

//---------- in thong tin nhan vien tren 1 trang ---------
void ShowListNVOnePage(dsNV ds, int index, int CurNVPage, int TotalNVPage) {
	gotoxy(X_DisplayNum + 28, Y_DisplayNum);
	cout << "         ";
	gotoxy(X_DisplayNum, Y_DisplayNum);
	cout << "So luong nhan vien: " << ds.n_nv;
	int i;
	for (i = 0; i + index < ds.n_nv && i < NumberPerPage; i++) {
		ShowNV(ds.dsnv[i + index], i);
	}
	RemoveExceedMember(i, 4);
	gotoxy(X_Page + 6, Y_Page);
	cout << "          ";
	gotoxy(X_Page, Y_Page);
	cout << " Trang " << CurNVPage << "/" << TotalNVPage;
}

//---------- thay doi trang in nhan vien ----------
void ChangeNVManagerPage(dsNV ds, int CurNVPage, int TotalNVPage) {
	/*gotoxy(X_Title, Y_Title);
	cout << " Quan li nhan vien ";*/
	ShowListNVOnePage(ds, (CurNVPage - 1) * NumberPerPage, CurNVPage, TotalNVPage);
}

//--------- in thong tin nhan vien theo thu tu ten tang dan ------------
void ShowListNVOnePageAscending(nhan_vien* ds[], int sl, int index, int CurNVPageAscending, int TotalNVPageAscending) {
	gotoxy(X_DisplayNum, Y_DisplayNum);
	cout << "So luong nhan vien: " << sl;
	int i;
	for (i = 0; i + index < sl && i < NumberPerPage; i++) {
		ShowNV(ds[i + index], i);
	}
	RemoveExceedMember(i, 4);
	gotoxy(X_Page + 6, Y_Page);
	cout << "          ";
	gotoxy(X_Page, Y_Page);
	cout << "Trang " << CurNVPageAscending << " / " << TotalNVPageAscending;
}

//---------- thay doi trang in nhan vien tang dan ----------
void ChangeNVManagerPageAscending(nhan_vien* ds[], int sl, int CurNVPageAscending, int TotalNVPageAscending) {
	gotoxy(X_Title, Y_Title);
	cout << " Quan ly nhan vien ";
	ShowListNVOnePageAscending(ds, sl, (CurNVPageAscending - 1) * NumberPerPage, CurNVPageAscending, TotalNVPageAscending);
}

//---------- ve bang in danh sach nhan vien theo thu tu ten tang dan -------
void DisplayAscendingNV(nhan_vien* ds[], int sl, int CurNVPageAscending, int TotalNVPageAscending) {
	system("color 0E");
	ShowCur(0);
	system("cls");

	Display(ContentNV, sizeof(ContentNV) / sizeof(string), false);
	ShowListNVOnePageAscending(ds, sl, (CurNVPageAscending - 1) * NumberPerPage, CurNVPageAscending, TotalNVPageAscending);	gotoxy(X_Title, Y_Title);
	cout << " Quan ly nhan vien ";
}

//--------- in danh sach nhan vien theo thu tu ten tang dan -----
void PrintListNV(dsNV ds) {
	int CurNVPageAscending = 1;
	int TotalNVPageAscending = (int)ceil((double)ds.n_nv / NumberPerPage);

	nhan_vien* temp_ds[Max_NV];
	int temp_sl = ds.n_nv;
	for (int i = 0; i < temp_sl; i++) {
		temp_ds[i] = ds.dsnv[i];
	}
	for (int i = 0; i < temp_sl; i++) {
		for (int j = i + 1; j < temp_sl; j++) {
			if (temp_ds[i]->ten > temp_ds[j]->ten) {
				nhan_vien* t = temp_ds[i];
				temp_ds[i] = temp_ds[j];
				temp_ds[j] = t;
			}
			else if (temp_ds[i]->ten == temp_ds[j]->ten) {
				if (temp_ds[i]->ho > temp_ds[j]->ho) {
					nhan_vien* t = temp_ds[i];
					temp_ds[i] = temp_ds[j];
					temp_ds[j] = t;
				}
			}
		}
	}

	DisplayAscendingNV(temp_ds, temp_sl, CurNVPageAscending, TotalNVPageAscending);

	int c;
	while (true) {
		while (_kbhit()) {
			c = _getch();
			if (c == ESC) {
				return;
			}
			if (c == 224) {
				c = _getch();//lay cac ki tu dac biet
				if (c == PAGE_UP && CurNVPageAscending > 1) {
					CurNVPageAscending--;
					ChangeNVManagerPageAscending(temp_ds, temp_sl, CurNVPageAscending, TotalNVPageAscending);
				}
				else if (c == PAGE_DOWN && CurNVPageAscending < TotalNVPageAscending) {
					CurNVPageAscending++;
					ChangeNVManagerPageAscending(temp_ds, temp_sl, CurNVPageAscending, TotalNVPageAscending);
				}
			}
		}
	}
}

//--------- chon nhan vien ----------
int PickItemNv(dsNV ds, int CurNVPage, int TotalNVPage) {
	ShowCur(0);

	//truong hop khong co nhan vien nao
	if (!ds.n_nv) {
		char signal;
		while (true) {
			signal = _getch();
			if (signal == ESC) {
				return -1;
			}
		}
	} 

	//--------highlight dong dang chon--------
	int lower_bound = (CurNVPage - 1) * NumberPerPage;
	int pick = lower_bound; //bien chi so cua mang
	int index = 0; //bien chi so cua phan tu trong bang
	int upper_bound = CurNVPage * NumberPerPage;
	HighlightLine2();
	HighLightArrow(5, Y_Display + 4 + index * 4);
	ShowNV(ds.dsnv[pick], index);

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
				DeleteArrow(5, Y_Display + 4 + index * 4);
				ShowNV(ds.dsnv[pick], index);
				pick--; index--;

				HighlightLine2();
				HighLightArrow(5, Y_Display + 4 + index * 4);
				ShowNV(ds.dsnv[pick], index);
			}
			break;
		case KEY_DOWN:
			if (pick + 1 < ds.n_nv && pick + 1 < upper_bound && index < NumberPerPage) {
				NormalLine();
				DeleteArrow(5, Y_Display + 4 + index * 4);
				ShowNV(ds.dsnv[pick], index);
				pick++; index++;

				HighlightLine2();
				HighLightArrow(5, Y_Display + 4 + index * 4);
				ShowNV(ds.dsnv[pick], index);
			}
			break;
		case PAGE_UP:
			if (CurNVPage > 1) {
				CurNVPage--;
				lower_bound = (CurNVPage - 1) * NumberPerPage;
				upper_bound = CurNVPage * NumberPerPage;
				DeleteArrow(5, Y_Display + 4 + index * 4);
				index = 0;
				pick = lower_bound;
				NormalLine();
				ChangeNVManagerPage(ds, CurNVPage, TotalNVPage);
				HighlightLine2();
				HighLightArrow(5, Y_Display + 4 + index * 4);
				ShowNV(ds.dsnv[pick], index);
			}
			break;
		case PAGE_DOWN:
			if (CurNVPage < TotalNVPage) {
				CurNVPage++;
				lower_bound = (CurNVPage - 1) * NumberPerPage;
				upper_bound = CurNVPage * NumberPerPage;
				DeleteArrow(5, Y_Display + 4 + index * 4);
				index = 0;
				pick = lower_bound;
				NormalLine();
				ChangeNVManagerPage(ds, CurNVPage, TotalNVPage);
				HighlightLine2();
				HighLightArrow(5, Y_Display + 4 + index * 4);
				ShowNV(ds.dsnv[pick], index);
			}
			break;
		case ENTER:
			NormalLine();
			DeleteArrow(5, Y_Display + 4 + index * 4);
			return pick; //luu lua chon de thuc hien chuc nang ham Menu
		case ESC:
			NormalLine();
			DeleteArrow(5, Y_Display + 4 + index * 4);
			return -1;
		}
	}
}

//-------- nhap nhan vien ----------
void inputNV(dsNV& ds, bool Edited, bool Deleted, int& CurNVPage, int& TotalNVPage) {
	ShowCur(1);
	bool Saved = true;//kiem tra luu lai hay chua
	string ID;//ma nhan vien
	//string ID_temp;
	string nv_ho;//ho nhan vien
	string nv_ten;//ten nhan vien
	string nv_phai;// phai nhan vien
	string ho_ten;
	int temp = 0;
	int step = 1;//cac buoc nhap lieu
	int cur_step = step;
	int target = -1;
	int target2 = -1;

	char signal;
	
	while (true) {
		switch (step) {
		case 1: //Nhap ma nhan vien
			if (Edited) {
				string ContentNV[3] = { "Ma NV", "Ho va Ten", "Phai" };
				int IndexNv = PickItemNv(ds, CurNVPage, TotalNVPage);
				target2 = IndexNv; //dung de luu chi so de case 4 thuc hien thao tac chinh sua
				if (IndexNv == -1) {
					TotalNVPage = (int)ceil((double)ds.n_nv / NumberPerPage);
					ShowListNVOnePage(ds, (CurNVPage - 1) * NumberPerPage, CurNVPage, TotalNVPage);
					return;
				}

				//in ra bang nhap thong tin
				CreateInputForm(ContentNV, 3, 50);

				//gan thong tin co san cua node
				ID = ds.dsnv[IndexNv]->maNV;
				ho_ten = ds.dsnv[IndexNv]->ho + " " + ds.dsnv[IndexNv]->ten;
				nv_phai = ds.dsnv[IndexNv]->phai;

				//in thong tin node muon chinh sua
				gotoxy(X_Add + 5, Y_Add);
				cout << left << setw(15) << ID;
				gotoxy(X_Add + 5, Y_Add + 4);
				cout << left << setw(15) << ho_ten;
				gotoxy(X_Add + 5, Y_Add + 8);
				cout << left << setw(15) << nv_phai;
				step++;
				break;
			}
			//kiem tra viec xoa thong tin
			if (Deleted) {
				int IndexNv = PickItemNv(ds, CurNVPage, TotalNVPage);

				//truong hop nhan nut ESC
				if (IndexNv == -1) {
					TotalNVPage = (int)ceil((double)ds.n_nv / NumberPerPage);
					ShowListNVOnePage(ds, (CurNVPage - 1) * NumberPerPage, CurNVPage, TotalNVPage);
					return;
				}

				//truong hop nhan vien da lap hoa don 
				if (ds.dsnv[IndexNv]->used) {
					Notification("Nhan vien da trong hoa don. Khong the xoa!");
					ShowNV(ds.dsnv[IndexNv], IndexNv);
					return;
				}

				target = RemoveConfirm();
				RemoveFormComplete(1);
				if (target == 2) {
					int idx = IndexNv;
					NormalLine();
					IndexNv = IndexNv % 10;
					ShowNV(ds.dsnv[idx], IndexNv);
					return;
				}
				if (!IsDeleteNVSuccess(ds, FindIndexNV(ds, ds.dsnv[IndexNv]->maNV))) {
					Notification("Xoa khong thanh cong!");
					ShowCur(1);
				}
				else {
					Notification("Xoa thanh cong!");
				}
				TotalNVPage = (int)ceil((double)ds.n_nv / NumberPerPage);
				if (CurNVPage > TotalNVPage)
					CurNVPage--;
				ChangeNVManagerPage(ds, CurNVPage, TotalNVPage);
				return;
			}

			cur_step = step;
			TypeWordAndNumber(ID, step, Edited, Saved, 10, 5);
			if (cur_step != step) {
				break;
			}
			if (!Saved) {
				RemoveFormComplete(3);
				return;
			}
			target = FindIndexNV(ds, ID);
			if (ID == "") {
				Notification("Ma nhan vien khong duoc phep rong!");
				break;
			}
			//Kiem tra truong hop ma nhan vien da ton tai
			if (target != -1) {
				Notification("Ma nhan vien da ton tai!");
				ID = "";
				RemoveForm(1);
				break;
			}
			step++;
			break;
		case 2: //Nhap ho va ten
			cur_step = step;
			TypeWordAndSpace(ho_ten, step, Edited, Saved, 30, 5);
			if (cur_step != step) {
				break;
			}
			if (ho_ten == "") {
				Notification("Ho va ten khong duoc phep rong!");
				break;
			}
			for (int i = ho_ten.length() - 1; i >= 0; i--) {
				if (ho_ten[i] == ' ') {
					temp = i;
					break;
				}
			}
			nv_ho = ho_ten.substr(0, temp);
			nv_ten = ho_ten.substr(temp + 1);
			step++;
			break;
		case 3: //Nhap phai
			cur_step = step;
			TypeOnlyAWord(nv_phai, step, Edited, Saved, 5, 5);
			if (cur_step != step) {
				break;
			}
			if (nv_phai == "") {
				Notification("Gioi tinh khong duoc phep rong!");
				break;
			}
			step++;
			break;
		case 4: 
			if (Edited) {
				ds.dsnv[target2]->maNV = ID;
				ds.dsnv[target2]->ho = nv_ho;
				ds.dsnv[target2]->ten = nv_ten;
				ds.dsnv[target2]->phai = nv_phai;
				Notification("Chinh sua thanh cong!");
				RemoveFormComplete(3);
				ChangeNVManagerPage(ds, CurNVPage, TotalNVPage);
				return;
			}
			else { //dung insert order
				int i;
				for (i = 0; i < ds.n_nv && ds.dsnv[i]->maNV < ID; i++);
				for (int k = ds.n_nv - 1; k >= i; k--) {
					ds.dsnv[k + 1] = ds.dsnv[k];
				}
				ds.dsnv[i] = new nhan_vien;
				ds.dsnv[i]->maNV = ID;
				ds.dsnv[i]->ho = nv_ho;
				ds.dsnv[i]->ten = nv_ten;
				ds.dsnv[i]->phai = nv_phai;
				ds.n_nv++;
				Notification("Them thanh cong!");
				CurNVPage = (FindIndexNV(ds, ds.dsnv[i]->maNV) / NumberPerPage) + 1;
			}
			ID = "";
			nv_ho = "";
			nv_ten = "";
			nv_phai = "";
			ho_ten = "";
			temp = 0;
			step = 1;
			TotalNVPage = (int)ceil((double)ds.n_nv / NumberPerPage);
			ChangeNVManagerPage(ds, CurNVPage, TotalNVPage);
			RemoveForm(3);
			break;
		}
	}
	ShowCur(0);
}

//----------- Menu quan ly nhan vien ---------
void MenuManageNV(dsNV& ds) {
	system("color 0E");
	ShowCur(0);
	system("cls");
	int CurNVPage = 1;
	int TotalNVPage = (int)ceil((double)ds.n_nv / NumberPerPage);
	Display(ContentNV, sizeof(ContentNV) / sizeof(string), true);
	ShowListNVOnePage(ds, 0, CurNVPage, TotalNVPage);
	gotoxy(X_Title, Y_Title);
	cout << " Quan ly nhan vien ";
	int event;
	while (true) {
		while (_kbhit()) {
			event = _getch();//nhan biet cac ki tu dac biet
			if (event == ESC) {
				return;
			}
			if (event == 224) {
				event = _getch();//lay cac ki tu dac biet
				if (event == PAGE_UP && CurNVPage > 1) {
					CurNVPage--;
					ChangeNVManagerPage(ds, CurNVPage, TotalNVPage);
				}
				else if (event == PAGE_DOWN) {
					TotalNVPage = (int)ceil((double)ds.n_nv / NumberPerPage);
					if (CurNVPage < TotalNVPage) {
						CurNVPage++;
						ChangeNVManagerPage(ds, CurNVPage, TotalNVPage);
					}
				}
				else if (event == INSERT) {//them moi nhan vien
					if (ds.n_nv >= Max_NV) {
						Notification("Danh sach nhan vien da day, khong the them!");
						return;
					}
					string ContentNV[3] = { "Ma NV", "Ho va Ten", "Phai" };
					CreateInputForm(ContentNV, 3, 50);
					inputNV(ds, false, false, CurNVPage, TotalNVPage);
					ShowCur(0);
				}
				else if (event == DEL) {
					if (ds.n_nv == 0) {
						Notification("Danh sach rong, khong the xoa");
						return;
					}
					inputNV(ds, false, true, CurNVPage, TotalNVPage);
					ShowCur(0);
				}
				else if (event == HOME) {
					if (ds.n_nv == 0) {
						Notification("Danh sach rong, khong the chinh sua");
						return;
					}
					inputNV(ds, true, false, CurNVPage, TotalNVPage);
					ShowCur(0);
				}
			}
		}
	}
}


//================== cau e: lap hoa don ==================
//--------- nhap hoa don -------------
int InputHD(nhan_vien*& nv) {
	ShowCur(1);
	bool Saved = true;//kiem tra luu lai hay chua
	hoa_don hd;
	hd_Node* target;
	int step = 1;
	int cur_step = step;
	
	while (true) {
		switch (step) {
		case 1: {//Nhap so hoa don
			gotoxy(X_Add + 5, Y_Add + 8);
			cout << nv->maNV;

			cur_step = step;
			TypeWordAndNumber(hd.soHD, step, false, Saved, 10, 5);
			if (cur_step != step) {
				if (step == 0) {
					step = 1;
				}
				break;
			}
			if (!Saved) {
				return 0;
			}
			target = FindSoHDExist(nv->dshd, hd.soHD);
			if (hd.soHD == "") {
				Notification("So hoa don khong duoc phep rong!");
				break;
			}
			//Kiem tra truong hop so hoa don da ton tai
			if (target != NULL) {
				Notification("So hoa don da ton tai!");
				DeleteNotification();
				hd.soHD = "";
				RemoveForm(1);
				break;
			}
			step++;
			break; }
		case 2: //Nhap ngay lap hoa don
			cur_step = step;
			TypeDate(hd.ngay_lapHD.ngay, step, Saved, 32, 5, 0, 32);
			if (cur_step != step) {
				break;
			}
			if (hd.ngay_lapHD.ngay == 0) {
				Notification("Ngay lap hoa don khong duoc rong");
				break;
			}
			step++;
			break;
		case 3: { //Nhap thang lap hoa don
			int temp = step - 1;
			cur_step = temp;
			TypeDate(hd.ngay_lapHD.thang, temp, Saved, 13, 15, 0, 13);
			if (cur_step != temp) {
				step--;
				break;
			}
			if (hd.ngay_lapHD.thang == 0) {
				Notification("Thang lap hoa don khong duoc rong");
				break;
			}
			step++;
			break;
		}
		case 4: {//Nhap nam lap hoa don
			int temp = step - 2;
			cur_step = temp;
			TypeDate(hd.ngay_lapHD.nam, temp, Saved, 2100, 25, 1000, 2100);
			if (cur_step != temp) {
				step--;
				break;
			}
			if (hd.ngay_lapHD.nam == 0) {
				Notification("Nam lap hoa don khong duoc rong");
				break;
			}
			if (!CheckValidDate(hd.ngay_lapHD, step - 2)) {
				step = 2;
				break;
			}
			step++;
			break;
		}
		case 5: {//Nhap loai hoa don
			(PickHDType() == 1) ? hd.loai = 'N' : hd.loai = 'X';
			step++;
			break;
		}
		case 6:
			AddLastListHD(nv->dshd, hd);
			nv->used = true;
			Notification("Tao hoa don thanh cong!");
			system("cls");
			return 1;
		}
	}
	ShowCur(0);
}

//----------- nhap chi tiet hoa don ----------
int InputCTHD(Vt_Node& root, nhan_vien*& nv, Vt_Node vt, hd_Node* temp) {
	ShowCur(1);
	bool Saved = true;//kiem tra luu lai hay chua
	chi_tiet_hd cthd;
	Vt_Node dsvt_vt = FindVtNode(root, vt->data.ma_vt); //truy cap node vat tu trong danh sach vat tu de cap nhat so luong ton
	int step = 1;
	int cur_step = step;

	while (true) {
		switch (step) {
		case 1: //Nhap ma vat tu
			gotoxy(X_Add + 5, Y_Add);
			cout << vt->data.ma_vt;

			cthd.maVT = vt->data.ma_vt;
			step++;
			break;
		case 2: 
			gotoxy(X_Add + 5, Y_Add + 4);
			cout << vt->data.ten_vt;
			step++;
			break;
		case 3: //Nhap so luong vat tu
			cur_step = step;
			TypeOnlyNumber(cthd.sl, step, false, Saved, 1000000, 5);
			if (cur_step != step) {
				break;
			}
			if (!Saved) {
				return 0;
			}
			if (cthd.sl == 0) {
				Notification("So luong vat tu khong duoc rong!");
				break;
			}
			if (temp->data.loai == 'X' && dsvt_vt->data.sl_ton < cthd.sl) {
				string s = "So luong ton khong du. Hien chi con " +  to_string(dsvt_vt->data.sl_ton) + " san pham";
				Notification(s);

				gotoxy(X_Add + 5, Y_Add + 8);
				cout << "       ";
				cthd.sl = 0;
				break;
			}

			step++;
			break;
		case 4: { //Nhap don gia cua vat tu trong cthd
			cur_step = step;
			TypeDoubleNumber(cthd.donGia, step, Saved, 1000000.0, 5);
			if (cur_step != step) {
				break;
			}
			if (cthd.donGia == 0) {
				Notification("Don gia khong duoc rong!");
				break;
			}
			step++;
			break;
		}
		case 5: { //nhap %VAT
			cur_step = step;
			TypeDoubleNumber(cthd.VAT, step, Saved, 1000000.0, 5);
			if (cur_step != step) {
				break;
			}
			if (cthd.VAT == 0) {
				Notification("%VAT khong duoc rong!");
				break;
			}
			step++;
			break;
		}
		case 6: {
			AddLastCthd(temp->data.dscthd, cthd);
			if (temp->data.loai == 'X') {
				dsvt_vt->data.sl_ton -= cthd.sl;
			}
			else {
				dsvt_vt->data.sl_ton += cthd.sl;
			}
			dsvt_vt->data.used = true;
			system("cls");
			return 1;
		}
		}
	}
	ShowCur(0);
}

//--------- chon nhan vien de lap hoa hon ----------
int PickNVMakeHD(dsNV ds, int CurNVPage, int TotalNVPage) {
	Display(ContentNV, sizeof(ContentNV) / sizeof(string), false);
	ShowListNVOnePage(ds, (CurNVPage - 1) * NumberPerPage, CurNVPage, TotalNVPage);
	gotoxy(X_Title - 40, Y_Title);
	cout << " Chon nhan vien de lap hoa don ";
	int pick = PickItemNv(ds, CurNVPage, TotalNVPage);
	if (pick != -1) {
		return pick;
	}
	return -1;
}

//--------- chon vat tu them vao hoa don ----------
void DisplayMenuDSHD(nhan_vien* nv, hd_Node* temp, Vt_Node root, int CurHDPage, int TotalHDPage) {
	system("cls");
	gotoxy(X_Title, Y_Title);
	cout << " Chon vat tu de lap hoa don ";
	TableOfHD();
	ButtonFunction();
	gotoxy(X_Display + 5, Y_Display + 14);
	cout << "So hoa don             :   " << temp->data.soHD;
	gotoxy(X_Display + 5, Y_Display + 18);
	cout << "Ma nhan vien           :   " << nv->maNV;
	gotoxy(X_Display + 5, Y_Display + 22);
	cout << "Ho va ten nhan vien    :   " << nv->ho << " " << nv->ten;
	gotoxy(X_Display + 5, Y_Display + 26);
	cout << "Ngay lap hoa don       :   " << StandardDate(temp->data.ngay_lapHD.ngay, temp->data.ngay_lapHD.thang, temp->data.ngay_lapHD.nam);
	gotoxy(X_Display + 5, Y_Display + 30);
	string loai;
	temp->data.loai == 'N' ? loai = "Nhap" : loai = "Xuat";
	cout << "Loai hoa don           :   " << loai;

	ShowListCTHDOnePage(temp, root, (CurHDPage - 1) * NumberPerPage, CurHDPage, TotalHDPage);
}

//----------- menu quan ly hoa don -------------
void MenuManagerHD(dsNV& ds, Vt_Node& root) {
	ShowCur(0);
	system("cls");
	int CurNVPage = 1;
	int TotalNVPage = (int)ceil((double)ds.n_nv / NumberPerPage);
	int CurVtPage = 1;
	int TotalVtPage = (int)ceil((double)CountVtNode(root) / NumberPerPage);
	int CurHDPage = 1;
	int TotalHDPage = 1;
	int index = -1;

	while (true) {
		index = PickNVMakeHD(ds, CurNVPage, TotalNVPage);
		if (index == -1) { //truong hop bam nut ESC de thoat
			return;
		}

		//nhap thong tin hoa don
		InputFormHD(ContentHD, 4, 50);
		int x = InputHD(ds.dsnv[index]);

		if (x) { //neu x == 1 nghia la tao hoa don thanh cong, qua buoc tiep theo
			break;
		}
		else { //khong thi cho tao lai
			system("cls");
		}
	}
	//tim den node hoa don moi tao
	hd_Node* hd = ds.dsnv[index]->dshd->head;
	while (hd->next != NULL) {
		hd = hd->next;
	}
	hd->data.dscthd = new ds_chi_tiet_hd;

	//chon vat tu cho vao hoa don
	while (true) {
		CurHDPage = 1;
		TotalHDPage = (int)ceil((double)hd->data.dscthd->n_cthd / NumberPerPage);
		if (TotalHDPage == 0)
			TotalHDPage = 1;
		DisplayMenuDSHD(ds.dsnv[index], hd, root, CurHDPage, TotalHDPage);
		int idx_func = PickFuncHD(root, hd, CurHDPage, TotalHDPage);
		while (idx_func == 0) {
			system("cls");
			int pick = 0;
			Display(ContentVT, sizeof(ContentVT) / sizeof(string), false);
			ChangeVtManagerPage(root, CurVtPage, TotalVtPage);
			Vt_Node vt = PickItemVt(root, pick, CurVtPage, TotalVtPage);
			if (vt == NULL) {
				break;
			}
			CreateInputForm(ContentCTHD, 5, 50);
			int temp = InputCTHD(root, ds.dsnv[index], vt, hd);
			if (!temp) {
				break;
			}
		}
		if (idx_func == 1) {
			if (hd->data.dscthd->n_cthd != 0)
				return;
		}
	}
}


//=============== cau f: in hoa don ====================
//---------- the hien bang in hoa don -----------------
void DisplayPrintingHD(nhan_vien* nv, hd_Node* hd, Vt_Node root, int CurCTHDPage, int TotalCTHDPage) {
	system("cls");
	gotoxy(X_Title, Y_Title);
	cout << " In hoa don ";
	TableOfHDWithValue();
	gotoxy(X_Display + 5, Y_Display + 14);
	cout << "So hoa don             :   " << hd->data.soHD;
	gotoxy(X_Display + 5, Y_Display + 18);
	cout << "Ma nhan vien           :   " << nv->maNV;
	gotoxy(X_Display + 5, Y_Display + 22);
	cout << "Ho va ten nhan vien    :   " << nv->ho << " " << nv->ten;
	gotoxy(X_Display + 5, Y_Display + 26);
	cout << "Ngay lap hoa don       :   " << StandardDate(hd->data.ngay_lapHD.ngay, hd->data.ngay_lapHD.thang, hd->data.ngay_lapHD.nam);
	gotoxy(X_Display + 5, Y_Display + 30);
	string loai;
	hd->data.loai == 'N' ? loai = "Nhap" : loai = "Xuat";
	cout << "Loai hoa don           :   " << loai;
	ShowListCTHDOnePageWithValue(hd, root, (CurCTHDPage - 1) * NumberPerPage, CurCTHDPage, TotalCTHDPage);

	double TotalValue = 0;
	cthd_Node* cthd_temp = hd->data.dscthd->head;
	for (int i = 0; i < hd->data.dscthd->n_cthd; i++) {
		TotalValue += ComputeValue(cthd_temp->data.sl, cthd_temp->data.donGia, cthd_temp->data.VAT);
		cthd_temp = cthd_temp->next;
	}
	gotoxy(xKeyContentCTHD[4] + 5, Y_Display + 43);
	cout << fixed << setprecision(0) << addDot(TotalValue);

}

//---------- In hoa don -----------
void CheckingHD(dsNV ds, Vt_Node root) {
	system("cls");
	dsNV ds_temp;

	int idx = 0;
	int pick = 0;
	for (int i = 0; i < ds.n_nv; i++) {
		if (ds.dsnv[i]->used == 1) {
			ds_temp.dsnv[idx++] = ds.dsnv[i];
		}
	}
	ds_temp.n_nv = idx;

	int CurNVPage = 1;
	int TotalNVPage = (int)ceil((double)ds_temp.n_nv / NumberPerPage);

	//chon nhan vien de in hoa don
	gotoxy(X_Title - 40, Y_Title);
	cout << " Chon nhan vien in hoa don ";
	Display(ContentNV, sizeof(ContentNV) / sizeof(string), false);
	ShowListNVOnePage(ds_temp, 0, CurNVPage, TotalNVPage);
	pick = PickItemNv(ds_temp, CurNVPage, TotalNVPage);
	if (pick == -1) {
		return;
	}

	int CurHDPage = 1;
	int TotalHDPage = (int)ceil((double)ds_temp.dsnv[pick]->dshd->n_hd / NumberPerPage);

	//chon hoa don 
	DrawTablePickHD();
	ShowListHDOnePage(ds_temp.dsnv[pick]->dshd, 0, CurHDPage, TotalHDPage);
	hd_Node* hd = PickHD(ds_temp.dsnv[pick]->dshd, CurHDPage, TotalHDPage);
	if (hd == NULL) {
		return;
	}

	//in hoa don
	int CurCTHDPage = 1;
	int TotalCTHDPage = (int)ceil((double)hd->data.dscthd->n_cthd/ NumberPerPage);

	DisplayPrintingHD(ds_temp.dsnv[pick], hd, root, CurCTHDPage, TotalCTHDPage);

	char signal;
	while (true) {
		signal = _getch(); //kiem tra co nhap gi tu ban phim khong
		if (signal == -32) {
			signal = _getch();
		}
		switch (signal) {
		case PAGE_UP:
			if (CurCTHDPage > 1) {
				CurCTHDPage--;
				ShowListCTHDOnePageWithValue(hd, root, (CurCTHDPage - 1) * NumberPerPage, CurCTHDPage, TotalCTHDPage);
			}
			break;
		case PAGE_DOWN:
			if (CurCTHDPage < TotalCTHDPage) {
				CurCTHDPage++;
				ShowListCTHDOnePageWithValue(hd, root, (CurCTHDPage - 1) * NumberPerPage, CurCTHDPage, TotalCTHDPage);
			}
			break;
		case ESC:
			NormalLine();
			return;
		}
	}
}


//============== cau g: In hoa don trong khoang thoi gian ==========
//---------- the hien bang thong ke ----------
void DisplayTK(string ct[], int sl, bool used) {
	//show key - the hien ra noi dung cua cac cot
	for (int i = 0; i < sl; i++) {
		gotoxy(xKeyContentTK[i] + 3, Y_Display);
		cout << ct[i];
	}

	//ve cac duong thang de phan chia cac cot
	for (int iy = Y_Display - 2; iy <= Y_Display + 45; iy++) {
		for (int i = 0; i < sl + 1; i++) {
			gotoxy(xKeyContentTK[i], iy);
			cout << char(219);
		}
	}

	//ve thanh ngang ben tren va duoi
	for (int ix = xKeyContentTK[0]; ix <= xKeyContentTK[sl]; ix++) {
		//ve thanh ngang ben tren so 1
		gotoxy(ix, Y_Display - 2);
		cout << char(220);

		// ve thanh ngang ben tren so 2
		gotoxy(ix, Y_Display + 2);
		cout << char(220);

		//ve thanh ngang ben duoi
		gotoxy(ix, Y_Display + 45);
		cout << char(220);
	}

	//dieu chinh goc
	for (int i = 0; i < 7; i++) {
		gotoxy(xKeyContentTK[i], Y_Display + 2);
		cout << char(219);

		gotoxy(xKeyContentTK[i], Y_Display + 45);
		cout << char(219);
	}
}
 
//---------- in 1 thong tin -------------
void ShowHDTK(hoa_donTK hdtk, int pos) {
	gotoxy(xKeyContentTK[0] + 3, Y_Display + 4 + pos * 4);
	cout << left << setw(15) << hdtk.maNV;
	gotoxy(xKeyContentTK[1] + 3, Y_Display + 4 + pos * 4);
	cout << left << setw(25) << hdtk.ho;
	gotoxy(xKeyContentTK[2] + 3, Y_Display + 4 + pos * 4);
	cout << left << setw(25) << hdtk.ten;
	gotoxy(xKeyContentTK[3] + 3, Y_Display + 4 + pos * 4);
	cout << left << setw(5) << hdtk.soHD;
	gotoxy(xKeyContentTK[4] + 3, Y_Display + 4 + pos * 4);
	cout << left << setw(5) << StandardDate(hdtk.ngay_lapHD.ngay, hdtk.ngay_lapHD.thang, hdtk.ngay_lapHD.nam);
	gotoxy(xKeyContentTK[5] + 3, Y_Display + 4 + pos * 4);
	(hdtk.loai == 'N') ? cout << "Nhap" : cout << "Xuat";
}

//---------- in 1 trang -----------
void ShowListHDTKOnePage(ds_hoa_donTK* HdTkNodeList, int index, int CurHDPage, int TotalHDPage, date ngay1, date ngay2) {
	int i = 0;

	for (int j = i; j < NumberPerPage; j++) {
		for (int k = 0; k < 3; k++) {
			for (int l = xKeyContentTK[k] + 2; l < xKeyContentTK[k + 1] - 2; l++) {
				gotoxy(l, Y_Display + 4 + j * 4);
				cout << " ";
			}
		}
	}

	hoa_donTK_Node* hdtk_temp = HdTkNodeList->head;
	for (int i = 0; i < index && i < HdTkNodeList->n_hdtk; i++) {
		hdtk_temp = hdtk_temp->next;
	}
	for (i = 0; i + index < HdTkNodeList->n_hdtk && i < NumberPerPage; i++) {
		ShowHDTK(hdtk_temp->data, i);
		hdtk_temp = hdtk_temp->next;
	}
	RemoveExceedMemberTK(i, 6);
	gotoxy(X_Page + 6, Y_Page);
	cout << "          ";
	gotoxy(X_Page, Y_Page);
	cout << " Trang " << CurHDPage << "/" << TotalHDPage;
}

//---------- them nhung hoa don hop le vao mang dstk ------------
void CheckNgayNV(dsNV& ds, date ngay1, date ngay2, int i, ds_hoa_donTK*& dstk) {
	hd_Node* temp = ds.dsnv[i]->dshd->head;

	while (temp != NULL) {
		if (checkPeriod(ngay1, ngay2, temp->data.ngay_lapHD)) {
			hoa_donTK_Node* newHDTKNode = MakeHdTkNode(temp->data, ds.dsnv[i]->maNV, ds.dsnv[i]->ho, ds.dsnv[i]->ten);
			if (dstk->head == NULL) {
				dstk->head = newHDTKNode;
			}
			else {
				hoa_donTK_Node* lastNode = dstk->head;
				while (lastNode->next != NULL) {
					lastNode = lastNode->next;
				}

				// Them node moi
				lastNode->next = newHDTKNode;
			}
			dstk->n_hdtk++;
		}
		temp = temp->next;
	}
}

//--------- menu the hien thong tin cac hoa don hop le --------------
void ThongKeHD(dsNV ds) {
	system("cls");

	date ngay1, ngay2;
	DisplayTK(ContentTK, sizeof(ContentTK) / sizeof(string), false);

	gotoxy(40, 2);
	cout << "BANG LIET KE CAC HOA DON TRONG KHOANG THOI GIAN";
	gotoxy(46, 3);
	cout << "Tu ngay ##/##/#### Den ngay ##/##/####";
	gotoxy(55, 3);
	ShowCur(1);

	ds_hoa_donTK* dstk = new ds_hoa_donTK; // Allocate memory for dstk
	dstk->head = NULL; // Initialize head to NULL
	dstk->n_hdtk = 0; // Initialize the node count

	bool Saved = true;
	int event;
	int CurX;
	int step = 1;
	int stepy = 0;
	while (true)
	{

		switch (step) {
		case 1: {
			TypeDate(ngay1.ngay, stepy, Saved, 32, -96, 0, 32);
			if (!Saved) {
				return;
			}
			if (ngay1.ngay == 0) {
				break;
			}
			step++;
			break; }
		case 2: 
			CurX = wherex();
			gotoxy(CurX + 1, 3);
			TypeDate(ngay1.thang, stepy, Saved, 13, -93, 0, 13);
			if (ngay1.thang == 0) {
				break;
			}
			step++;
			break;
		case 3: { 
			CurX = wherex();
			gotoxy(CurX + 1, 3);
			TypeDate(ngay1.nam, stepy, Saved, 2100, -90, 1000, 2100);
			if (ngay1.nam == 0) {
				break;
			}
			step++;
			break;
		}
		case 4: {
			gotoxy(75, 3);
			ShowCur(1);
			TypeDate(ngay2.ngay, stepy, Saved, 32, -76, 0, 32);
			if (ngay2.ngay == 0) {
				break;
			}
			step++;
			break;
		}
		case 5: {
			CurX = wherex();
			gotoxy(CurX + 1, 3);
			TypeDate(ngay2.thang, stepy, Saved, 13, -73, 0, 13);
			if (ngay2.thang == 0) {
				break;
			}
			step++;
			break;
		}
		case 6:
			CurX = wherex();
			gotoxy(CurX + 1, 3);
			TypeDate(ngay2.nam, stepy, Saved, 2100, -70, 1000, 2100);
			if (ngay2.nam == 0) {
				break;
			}
			break;
		}
		if (ngay1.ngay != 0 && ngay1.thang != 0 && ngay1.nam != 0 &&
			ngay2.ngay != 0 && ngay2.thang != 0 && ngay2.nam != 0) {
			break; // Exit the loop if all conditions are met
		}
		ShowCur(0);
	}

	for (int i = 0; i < ds.n_nv; i++) {
		CheckNgayNV(ds, ngay1, ngay2, i, dstk);
	}

	int CurHDPage = 1;
	int TotalHDPage = (int)ceil((double)dstk->n_hdtk / NumberPerPage);
	ShowListHDTKOnePage(dstk, 0, CurHDPage, TotalHDPage, ngay1, ngay2);

	char signal;
	while (true) {
		signal = _getch(); //kiem tra co nhap gi tu ban phim khong
		if (signal == -32) {
			signal = _getch();
		}
		switch (signal) {
		case PAGE_UP:
			if (CurHDPage > 1) {
				CurHDPage--;
				ShowListHDTKOnePage(dstk, (CurHDPage - 1) * NumberPerPage, CurHDPage, TotalHDPage, ngay1, ngay2);
			}
			break;
		case PAGE_DOWN:
			if (CurHDPage < TotalHDPage) {
				CurHDPage++;
				ShowListHDTKOnePage(dstk, (CurHDPage - 1) * NumberPerPage, CurHDPage, TotalHDPage, ngay1, ngay2);
			}
			break;
		case ESC:
			NormalLine();
			return;
		}
	}
}


//============== cau h: In 10 vat tu co doanh thu cao nhat ==========
//---------- nhap ngay thang de thong ke ------------
void InputDateForTopRevenue(date& date1, date& date2, bool& Saved) {
	ShowCur(1);
	int step = 1;
	int cur_step = step;

	while (true) {
		switch (step) {
		case 1:
			cur_step = step;
			TypeDate(date1.ngay, step, Saved, 32, 5, 0, 32);
			if (!Saved) {
				return;
			}
			if (cur_step != step) {
				if (step == 0) {
					step = 1;
				}
				break;
			}
			if (date1.ngay == 0) {
				Notification("Ngay thong ke khong duoc rong");
				break;
			}
			step++;
			break;
		case 2: {
			int temp = step - 1;
			cur_step = temp;
			TypeDate(date1.thang, temp, Saved, 13, 15, 0, 13);
			if (cur_step != temp) {
				step--;
				break;
			}
			if (date1.thang == 0) {
				Notification("Thang thong ke khong duoc rong");
				break;
			}
			step++;
			break;
		}
		case 3: {
			int temp = step - 2;
			cur_step = temp;
			TypeDate(date1.nam, temp, Saved, 2100, 25, 1000, 2100);
			if (cur_step != temp) {
				step--;
				break;
			}
			if (date1.nam == 0) {
				Notification("Nam thong ke khong duoc rong");
				break;
			}
			if (!CheckValidDate(date1, step - 2)) {
				step = 1;
				break;
			}
			step++;
			break;
		}
		case 4: {
			int temp = step - 2;
			cur_step = temp;
			TypeDate(date2.ngay, temp, Saved, 32, 5, 0, 32);
			if (cur_step != temp) {
				break;
			}
			if (date2.ngay == 0) {
				Notification("Ngay thong ke khong duoc rong");
				break;
			}
			step++;
			break;
		}
		case 5: {
			int temp = step - 3;
			cur_step = temp;
			TypeDate(date2.thang, temp, Saved, 13, 15, 0, 13);
			if (cur_step != temp) {
				step--;
				break;
			}
			if (date2.thang == 0) {
				Notification("Thang thong ke khong duoc rong");
				break;
			}
			step++;
			break;
		}
		case 6: {
			int temp = step - 4;
			cur_step = temp;
			TypeDate(date2.nam, temp, Saved, 2100, 25, 1000, 2100);
			if (cur_step != temp) {
				step--;
				break;
			}
			if (date2.nam == 0) {
				Notification("Nam thong ke khong duoc rong");
				break;
			}
			if (!CheckValidDate(date2, step - 4)) {
				step = 4;
				break;
			}
			step++;
			break;
		}
		case 7:
			ShowCur(0);
			return;
		}
	}
}

//---------- the hien bang thong ke doanh thu ---------
void DisplayTopRevenue(dsNV ds, Vt_Node root) {
	DrawTableTopRevenue();

	date date1, date2;
	bool Saved = true;
	InputDateForTopRevenue(date1, date2, Saved);
	if (!Saved) {
		return;
	}

	cthd_with_val** TopRevenue = new cthd_with_val*[Max_itemVt];
	int idx = 0;
	for (int i = 0; i < ds.n_nv; i++) {
		hd_Node* hd_temp = ds.dsnv[i]->dshd->head;
		for (int j = 0; j < ds.dsnv[i]->dshd->n_hd; j++) {
			if (hd_temp->data.loai == 'X' && checkPeriod(date1, date2, hd_temp->data.ngay_lapHD)) {
				cthd_Node* cthd_temp = hd_temp->data.dscthd->head;
				for (int k = 0; k < hd_temp->data.dscthd->n_cthd; k++) {
					bool found = false;
					for (int m = 0; m < idx; m++) {
						if (TopRevenue[m]->cthd->maVT == cthd_temp->data.maVT) {
							TopRevenue[m]->revenue += ComputeValue(cthd_temp->data.sl, cthd_temp->data.donGia, cthd_temp->data.VAT);
							found = true;
							break;
						}
					}
					if (!found) {
						TopRevenue[idx] = new cthd_with_val;
						TopRevenue[idx]->cthd = &cthd_temp->data;
						TopRevenue[idx]->revenue = ComputeValue(cthd_temp->data.sl, cthd_temp->data.donGia, cthd_temp->data.VAT);
						idx++;
					}
					cthd_temp = cthd_temp->next;
				}
			}
			hd_temp = hd_temp->next;
		}
	}
	for (int i = 0; i < idx; i++) {
		for (int j = i + 1; j < idx; j++) {
			if (TopRevenue[i]->revenue < TopRevenue[j]->revenue) {
				cthd_with_val* temp = TopRevenue[i];
				TopRevenue[i] = TopRevenue[j];
				TopRevenue[j] = temp;
			}
		}
	}

	for (int i = 0; i < 10 && i < idx; i++) {
		Vt_Node vt = FindVtNode(root, TopRevenue[i]->cthd->maVT);
		gotoxy(xKeyContentNV[1] + 5, 12 + i * 4);
		cout << TopRevenue[i]->cthd->maVT;
		gotoxy(xKeyContentNV[2] + 5, 12 + i * 4);
		cout << vt->data.ten_vt;
		gotoxy(xKeyContentNV[3] + 2, 12 + i * 4);
		cout << addDot(TopRevenue[i]->revenue);
	}
	
	int signal = 0;
	while (true) {
		while (_kbhit()) {
			signal = _getch();
			if (signal == ESC) {
				for (int i = 0; i < idx; ++i) {
					delete TopRevenue[i];
				}
				delete[] TopRevenue;
				return;
			}
		}
	}
}


//============== cau i: Doanh thu cua hang trong 1 nam ===============
//---------- the hien bang thong ke doanh thu ----------
void DisplayStatisticRevenue(dsNV ds) {
	DrawTableStatisticRevenue();

	int year = 0, step = 1;
	bool Saved = true;
	while (true) {
		TypeDate(year, step, Saved, 2100, 10, 1000, 2100);

		if (!Saved) {
			return;
		}
		if (year == 0) {
			Notification("Nam lap hoa don khong duoc rong");
		}
		else {
			break;
		}
	}

	gotoxy(X_Display + 68, Y_Display - 3);
	cout << year;

	int TotalRevenueList[13] = {0};
	for (int i = 0; i < ds.n_nv; i++) {
		hd_Node* hd_temp = ds.dsnv[i]->dshd->head;
		for (int j = 0; j < ds.dsnv[i]->dshd->n_hd; j++) {
			if (hd_temp->data.ngay_lapHD.nam == year && hd_temp->data.loai == 'X') {
				cthd_Node* cthd_temp = hd_temp->data.dscthd->head;
				for (int k = 0; k < hd_temp->data.dscthd->n_cthd; k++) {
					TotalRevenueList[hd_temp->data.ngay_lapHD.thang] += ComputeValue(cthd_temp->data.sl, cthd_temp->data.donGia, cthd_temp->data.VAT);
					cthd_temp = cthd_temp->next;
				}
			}
			hd_temp = hd_temp->next;
		}
	}

	ShowCur(0);
	for (int i = 1; i <= 12; i++) {
		gotoxy(X_Display + 72, 10 + (i - 1) * 4);
		cout << fixed << setprecision(0) << addDot(TotalRevenueList[i]);
	}
	
	int signal = 0;
	while (true) {
		while (_kbhit()) {
			signal = _getch();
			if (signal == ESC) {
				return;
			}
		}
	}
}