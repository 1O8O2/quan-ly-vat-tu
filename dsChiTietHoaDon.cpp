#include <iostream>
#include <string>
#include "dsChiTietHoaDon.h"
#include "dsHoaDon.h"
#include "GlobalVariables.h"
#include "UserInterface.h"
#include "mylib.h"

using namespace std;
extern string ContentCTHD[5];
extern int XKeyContentCTHD[5];

void Init_cthd(chi_tiet_hd &cthd) {
	cthd.maVT = "";
	cthd.sl = 0;
	cthd.donGia = 0;
	cthd.VAT = 0;
}

//tao moi 1 node kieu chi_tiet_hd
cthd_Node* MakeCthdNode(chi_tiet_hd data) {
	cthd_Node* temp = new cthd_Node;
	temp->data = data;
	temp->next = NULL;
	return temp;
}

//them cuoi 1 chi tiet hoa don
void AddLastCthd(ds_chi_tiet_hd*& ds, chi_tiet_hd data) {
	cthd_Node* newNode = MakeCthdNode(data);
	if (ds->head == NULL) {
		ds->head = newNode;
	}
	else {
		cthd_Node* temp = ds->head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = newNode;
	}
	ds->n_cthd++;
}

//Xoa cuoi 1 chi tiet hoa don
bool DeleteLastCthd(ds_chi_tiet_hd& ds) {
	if (ds.head == NULL) {
		return false; //tra ve thong bao loi
	}

	cthd_Node* temp = ds.head;
	if (temp->next == NULL) {
		ds.head = NULL;
		ds.n_cthd--;
		delete temp;
		return true; //tra ve thong bao xoa thanh cong
	}
	while (temp->next->next != NULL) {
		temp = temp->next;
	}

	cthd_Node* last = temp->next;
	temp->next = NULL;
	ds.n_cthd--;
	delete last;
	return true; //tra ve thong bao xoa thanh cong
}
