#include <fstream>
#include <iostream>
#include <string>
#include "ProcessionFile.h"

using namespace std;

void Introduction() {
	system("color 0E"); //nen den chu mau vang
	ShowCur(0);
	string temp;
	ifstream file("ptithcm.txt", ios::in);

	if (file.good()) {
		while (file.eof() == false) {
			getline(file, temp);
			cout << temp << endl;
		}
	}
	else {
		cout << "\n Liet ke file that bai" << endl;
	}
	Sleep(500);
	return;
}

//-------- ghi file nhan vien ----------
void WriteNVToFile(dsNV ds) {
	ofstream fileout;
	fileout.open("DSNV.TXT", ios_base::out);// ios_base::out la de ghi vao file
	if (fileout.is_open()) {
		for (int i = 0; i < ds.n_nv; i++) {
			fileout << ds.dsnv[i]->maNV << "\n" << ds.dsnv[i]->ho << "\n" << ds.dsnv[i]->ten << "\n" << ds.dsnv[i]->phai << "\n";
			fileout << ds.dsnv[i]->used << "\n";
			if (!ds.dsnv[i]->used) continue;
			fileout << ds.dsnv[i]->dshd->n_hd << "\n";
			
			hd_Node* hd = ds.dsnv[i]->dshd->head;
			for (int j = 0; j < ds.dsnv[i]->dshd->n_hd; j++) {
				fileout << hd->data.soHD << "\n";
				fileout << hd->data.ngay_lapHD.ngay << "\n" 
						<< hd->data.ngay_lapHD.thang << "\n" 
						<< hd->data.ngay_lapHD.nam << "\n";
				fileout << hd->data.loai << "\n";
				fileout << hd->data.dscthd->n_cthd << "\n";

				cthd_Node* cthd = hd->data.dscthd->head;
				for (int k = 0; k < hd->data.dscthd->n_cthd; k++) {
					fileout << cthd->data.maVT << "\n";
					fileout << cthd->data.sl << "\n";
					fileout << cthd->data.donGia << "\n";
					fileout << cthd->data.VAT << "\n";
					cthd = cthd->next;
				}
				hd = hd->next;
			}
		}
	}
	else {
		Notification("Ket noi file de ghi vao that bai");
	}
	fileout.close();
}

//--------- doc file nhan vien ---------
void ReadNVFile(dsNV& ds) {
	ifstream filein;
	filein.open("DSNV.TXT", ios_base::in);// ios_base::in la de doc

	int idx = 0;
	if (filein.is_open()) {
		while (!filein.eof()) {
			nhan_vien* nv = new nhan_vien;
			getline(filein, nv->maNV);
			if (nv->maNV == "") continue; //neu ma->nv rong nghia la ds rong
			getline(filein, nv->ho);
			getline(filein, nv->ten);
			getline(filein,nv->phai);
			
			string nv_used;
			getline(filein, nv_used);
			(nv_used == "1") ? nv->used = true : nv->used = false;

			if (nv->used) {
				int sl_hd;
				filein >> sl_hd;
				filein.ignore();
				for (int i = 0; i < sl_hd; i++) {
					hoa_don hd;
					getline(filein, hd.soHD);
					filein >> hd.ngay_lapHD.ngay;
					filein >> hd.ngay_lapHD.thang;
					filein >> hd.ngay_lapHD.nam;
					filein >> hd.loai;
					AddLastListHD(nv->dshd, hd);
					
					hd_Node* hd_node = nv->dshd->head;
					while (hd_node->next != NULL) {
						hd_node = hd_node->next;
					}
					hd_node->data.dscthd = new ds_chi_tiet_hd;

					int sl_cthd;
					filein >> sl_cthd;
					for (int j = 0; j < sl_cthd; j++) {
						filein.ignore();
						chi_tiet_hd cthd;
						getline(filein, cthd.maVT);
						filein >> cthd.sl;
						filein >> cthd.donGia;
						filein >> cthd.VAT;
						AddLastCthd(hd_node->data.dscthd, cthd);
					}
					filein.ignore();
				}
			}

			// cap nhat phan tu trong mang con tro
			ds.dsnv[idx++] = nv;
			// cap nhat so luong phan tu trong mang
			ds.n_nv++;

		}
	}
	else {
		Notification("Ket noi file de doc vao that bai");
	}
	filein.close();
}

//---------- ghi file vat tu ----------
void WriteAVt(Vt_Node root, ofstream& fileout) {
	fileout << root->data.ma_vt << endl;
	fileout << root->data.ten_vt << endl;
	fileout << root->data.dvt << endl;
	fileout << root->data.sl_ton << endl;
	fileout << root->data.used << endl;
}

void WriteVtList(Vt_Node root, ofstream& fileout) {
	if (root != NULL) {
		WriteVtList(root->left, fileout);
		WriteAVt(root, fileout);
		WriteVtList(root->right, fileout);
	}
}

void WriteVtToFile(Vt_Node root) {
	ofstream fileout;
	fileout.open("DSVT.TXT", ios_base::out);// ios_base::out la de ghi vao file

	if (fileout.is_open()) {
		WriteVtList(root, fileout);
	}
	else {
		Notification("Ket noi file de ghi vao that bai");
	}
	fileout.close();
}

//-------- ghi file vat tu -----------
void ReadVtFile(Vt_Node& root) {
	ifstream filein;
	filein.open("DSVT.TXT", ios_base::in);// ios_base::in la de doc

	if (filein.is_open()) {
		while (!filein.eof()) {
			vat_tu vt;
			getline(filein, vt.ma_vt);
			if (vt.ma_vt == "") continue; //neu ma_vt rong nghia la ds rong
			getline(filein, vt.ten_vt);
			getline(filein, vt.dvt);
			filein >> vt.sl_ton;

			int vt_used;
			filein >> vt_used;
			(vt_used == 1) ? vt.used = true : vt.used = false;
			filein.ignore();

			root = AddVt(root, vt);
		}
	}
	else {
		Notification("Ket noi file de doc vao that bai");
	}
	filein.close();
}
