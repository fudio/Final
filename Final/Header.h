#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <iomanip>
#include <ctime>

#define file_khosach  "khosach.bin"
#define file_sachmuon "sachmuon.bin"
#define file_sachtra  "sachtra.txt"

using namespace std;

struct Thuvien
{
	char masach[6];
	char tensach[30];
	char theloai[15];
	char nxb[15];
	int sl;
};

struct SachMuon
{
	char masach[6];
	char tennguoimuon[30];
	int ngay;
	int thang;
	int nam;
	int thoihan;
	int giatien;
	int soluong;
};

struct Sachquathoihan//sách quá thời hạn
{
	char tennguoimuon[30];
	char  masach[6];
	int giatientangthem;
};

struct Trasach
{
	char tennguoimuon[30];
	char masach[6];
	int ngay;
	int thang;
	int nam;
};

//*************Khai báo DSLK đơn*************

struct Node
{
	Thuvien Sach;
	Node* pNext;
};

struct Dslk
{
	Node* head;
	Node* tail;
};

//***********Tạo dslk****************
void Taodslk(Dslk& l);
//************Tạo Node*************
Node* TaoNode(Thuvien value);
void ThemNode(Dslk& l, Thuvien Sach);
//********Xoá Sách***************
void Xoasach(Dslk& l);
//************Tìm kiếm theo Mã sách*******
Node* TimNode(Dslk l, char* masach);
//************Chuyển Binary qua Dslk**********
void FiletoDslk(Dslk& l, char* file);
//************Chuyển Dslk sang Binary*******
void DslktoFile(Dslk& l, char* file);

//***********Tính khoảng cách ngày**********
int thisIsMagic(int year, int month, int day); //Source: http://mathforum.org/library/drmath/view/66535.html , https://daynhauhoc.com/t/thao-luan-c-tinh-khoang-thoi-gian-giua-2-thoi-diem-ngay-thang-nam/23812/5
//**********MENU**********//
void menu_chinh();
void menu_qlkho();
void menu_muonsach();
void menu_sachtra();
//**********Nhập sách vào kho**********//
void nhapsach();
void xuatkho(Thuvien dssach[], int m);
void xuatsosach();
void xoasach();
void suathongtinsach();
void nhapsach(Dslk& l);
void xuatsosach(Dslk l);
void suathongtinsach(Dslk l);
//************************MƯỢN SÁCH***********************//
void nhapsachmuon();
void xuatdanhsachmuon();
void suathongtinnguoimuon();
//****************************TRẢ SÁCH***********************//
void nhapsachtra();
//************Thống kê***************
