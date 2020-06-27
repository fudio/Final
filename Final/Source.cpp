#include "Header.h"

void Taodslk(Dslk& l)
{
	l.head = NULL;
	l.tail = NULL;
}

//************Tạo Node*************

Node* TaoNode(Thuvien value)
{
	Node* n = new Node; // Cấp phát vùng nhớ dùng malloc()
	n->pNext = NULL;// Cho next trỏ tới NULL
	n->Sach = value; // Gán giá trị cho Node
	return n;//Trả về node mới đã có giá trị
}

void ThemNode(Dslk& l, Thuvien Sach)
{
	Node* n = TaoNode(Sach);
	if (l.head == NULL)
		l.head = l.tail = n;
	else
	{
		l.tail->pNext = n;
		l.tail = n;
	}
}

//*********Tính khoảng cách ngày************ 

//Source: http://mathforum.org/library/drmath/view/66535.html , https://daynhauhoc.com/t/thao-luan-c-tinh-khoang-thoi-gian-giua-2-thoi-diem-ngay-thang-nam/23812/5

int thisIsMagic(int year, int month, int day)
{
	if (month < 3) {
		year--;
		month += 12;
	}
	return 365 * year + year / 4 - year / 100 + year / 400 + (153 * month - 457) / 5 + day - 306;
}

//********Xoá Sách***************

void Xoasach(Dslk& l)
{
	Node* n = l.head;
	if (l.head == NULL)
		return;
	char masach[6];
	xuatsosach(l);
	std::cout << "NHAP MA SACH CAN XOA: ";
	std::cin.ignore();
	gets_s(masach);
	while (n != NULL) {
		// xoa Node dau tien.
		if (n == l.head && n->Sach.masach == masach) {
			Node* tam = n;
			l.head = n->pNext;
			delete tam;
			return;
		}
		// xoa Node cuoi cung.
		else if (n->Sach.masach == masach && n->pNext == NULL)
		{
			Node* tam = n;
			n = NULL;
			delete tam;
			return;
		}
		// xoa Node bat ky nhung khong phai la cuoi cung va dau tien.
		else if (n->pNext->Sach.masach == masach)
		{
			Node* tam = n->pNext;
			n->pNext = n->pNext->pNext;
			delete tam;
			return;
		}
		n = n->pNext;
	}
}

//************Tìm kiếm theo Mã sách*******

Node* TimNode(Dslk l, char* masach)
{
	Node* n = l.head;
	while (n != NULL)
	{
		if (strcmp(n->Sach.masach, masach))
			return n;
		n = n->pNext;
	}
	return NULL;
}

//************Chuyển Binary qua Dslk**********

void FiletoDslk(Dslk& l, char* file)
{
	std::fstream f;
	f.open(file, std::ios::in | std::ios::binary);
	Thuvien sach;
	while (f.read(reinterpret_cast<char*>(&sach), sizeof(Thuvien)))
		ThemNode(l, sach);
	f.close();
}

//************Chuyển Dslk sang Binary*******

void DslktoFile(Dslk& l, char* file)
{
	std::fstream f;
	f.open(file, std::ios::out | std::ios::binary);
	Node* n = l.head;
	if (n != NULL)
		while (f.write(reinterpret_cast<char*>(&(n->Sach)), sizeof(Thuvien)))
			n = n->pNext;
	f.close();
	Node* i = l.head;
	//Giải phóng vùng nhớ dslk
	while (!l.head)
	{
		i = l.head;
		l.head = i->pNext;
		delete i;
	}
	l.head = l.tail = NULL;
}

//**********Menu chức năng chính**********//

void menu_chinh()
{
	system("CLS");
	std::cout << "******MENU CHINH******\n";
	std::cout << "1.QUAN LY KHO\n";
	std::cout << "2.MUON SACH\n";
	std::cout << "3.TRA SACH\n";
	std::cout << "4.THONG KE\n";
	std::cout << "0.THOAT\n";
	std::cout << "CHON CHUC NANG: ";

}

//**********Nhập sách vào kho**********//

void menu_qlkho()
{
	system("CLS");
	std::cout << "******QUAN LY KHO******" << std::endl;
	std::cout << "1.THEM SACH" << std::endl;
	std::cout << "2.XOA SACH" << std::endl;
	std::cout << "3.CAP NHAT SACH" << std::endl;
	std::cout << "4.XEM DANH SACH" << std::endl;
	std::cout << "5.VE MENU CHINH" << std::endl;
	std::cout << "0.THOAT" << std::endl;

}

void menu_muonsach()
{
	system("CLS");
	std::cout << "******MENU MUON SACH******\n";
	std::cout << "1.MUON SACH\n";
	std::cout << "2.SUA PHIEU MUON\n";
	std::cout << "3.VE MENU CHINH\n";
	std::cout << "0.THOAT";

}

void menu_sachtra()
{
	std::cout << "1.NHAP NGUOI TRA SACH\n";
	std::cout << "2.VE MENU CHINH\n";
	std::cout << "0.THOAT";
}

void nhapsach()
{
	Thuvien sachnhap;
	int n;
	fstream f;
	std::cout << "NHAP SO LUONG SACH CAN NHAP:" << " ";
	std::cin >> n;
	f.open(file_khosach, std::ios::out | std::ios::app | ios::binary);
	for (int i = 0; i < n; i++)
	{
		std::cout << "NHAP MA SACH: ";
		std::cin.ignore();
		gets_s(sachnhap.masach);
		std::cout << "NHAP TEN SACH: ";
		fflush(stdin);
		gets_s(sachnhap.tensach);
		std::cout << "NHAP THE LOAI: ";
		fflush(stdin);
		gets_s(sachnhap.theloai);
		std::cout << "NHAP NHAP NHA XUAT BAN: ";
		fflush(stdin);
		gets_s(sachnhap.nxb);
		std::cout << "NHAP SO LUONG: ";
		std::cin >> sachnhap.sl;
		f.write(reinterpret_cast<char*>(&sachnhap), sizeof(Thuvien));
	}
	f.close();
}

//DSLK

void nhapsach(Dslk& l)
{
	Thuvien sachnhap;
	int n;
	fstream f;
	std::cout << "NHAP SO LUONG SACH CAN NHAP: ";
	std::cin >> n;
	for (int i = 0; i < n; i++)
	{
		std::cout << "NHAP MA SACH: ";
		std::cin.ignore();
		gets_s(sachnhap.masach);
		f << sachnhap.masach << std::endl;
		std::cout << "NHAP TEN SACH: ";
		fflush(stdin);
		gets_s(sachnhap.tensach);
		f << sachnhap.tensach << std::endl;
		std::cout << "NHAP THE LOAI: ";
		fflush(stdin);
		gets_s(sachnhap.theloai);
		f << sachnhap.theloai << std::endl;
		std::cout << "NHAP NHAP XUAT BAN: ";
		fflush(stdin);
		gets_s(sachnhap.nxb);
		f << sachnhap.nxb << std::endl;
		std::cout << "NHAP SO LUONG: ";
		std::cin >> sachnhap.sl;//nè sửa lại đi
		ThemNode(l, sachnhap); //thêm các ô nhớ sachnhap vào DSLK
	}
}

void xuatkho(Thuvien dssach[], int m)
{
	int j = 1;
	std::cout << "+-----+---------+-------------------------------+----------------+----------------+----------+" << std::endl;
	std::cout << "| STT | MA SACH |           TEN SACH            |    THE LOAI    |  NHA XUAT BAN  | SO LUONG |" << std::endl;
	std::cout << "+-----+---------+-------------------------------+----------------+----------------+----------+" << std::endl;
	for (int i = 0; i < m; i++)
	{
		std::cout << "| " << setw(3) << j++ << " |  " << setw(5) << dssach[i].masach << "  | " << setw(29) << dssach[i].tensach << " | " << setw(14);
		std::cout << dssach[i].theloai << " | " << setw(14) << dssach[i].nxb << " |   " << setw(4) << dssach[i].sl << "  |\n";


		std::cout << "+-----+---------+-------------------------------+----------------+----------------+----------+" << std::endl;
	}
}

void xuatsosach()
{
	std::fstream f;
	Thuvien dssach[200];
	f.open(file_khosach, ios::in | ios::binary);
	int i = 0;
	while (f.read(reinterpret_cast<char*>(&dssach[i]), sizeof(Thuvien)))
		i++;
	f.close();
	xuatkho(dssach, i);
	std::cout << "AN PHIM BAT KY DE TIEP TUC!";
	std::cin.get();
	std::cin.get();
}

//DSLK

void xuatsosach(Dslk l)
{
	Node* n = l.head;
	int i = 1;
	std::cout << "+-----+---------+-------------------------------+----------------+----------------+----------+" << std::endl;
	std::cout << "| STT | MA SACH |           TEN SACH            |    THE LOAI    |  NHA XUAT BAN  | SO LUONG |" << std::endl;
	std::cout << "+-----+---------+-------------------------------+----------------+----------------+----------+" << std::endl;
	while (n != NULL)
	{
		std::cout << "| " << setw(3) << i++ << " |  " << setw(5) << n->Sach.masach << "  | " << setw(29) << n->Sach.tensach << " | " << setw(14);
		std::cout << n->Sach.theloai << " | " << setw(14) << n->Sach.nxb << " |   " << setw(4) << n->Sach.sl << "   |\n";
		n = n->pNext;
	}
	std::cout << "+-----+---------+-------------------------------+----------------+----------------+----------+" << std::endl;
}

void xoasach()
{
	std::fstream f;
	Thuvien dssach[150];
	int i = 0;
	f.open(file_khosach, std::ios::in | std::ios::binary);
	while (f.read(reinterpret_cast<char*>(&dssach[i]), sizeof(Thuvien)))
		i++;
	f.close();
	xuatkho(dssach, i);
	char masach[50];
	std::cout << "NHAP MA SACH CAN XOA:" << " ";
	std::cin.ignore();
	gets_s(masach);
	for (int j = 0; j < i; j++)
	{
		if (strcmp(dssach[j].masach, masach) == 0)
			for (int k = j; k < i - 1; k++)
			{
				dssach[k] = dssach[k + 1];
			}
		i--;
		break;

	}
	std::cout << "XOA THANH CONG" << std::endl;
	f.open(file_khosach, ios::out | ios::binary);
	for (int j = 0; j < i; j++)
	{
		f.write(reinterpret_cast<char*>(&dssach[j]), sizeof(Thuvien));
	}
	f.close();
}

//DSLK hàm xoá sách ở trên phần dslk

void suathongtinsach()
{
	std::fstream f;
	Thuvien dssach[150];
	int i = 0;
	f.open(file_khosach, std::ios::in | std::ios::binary);
	while (f.read(reinterpret_cast<char*>(&dssach[i]), sizeof(Thuvien)))
	{
		i++;
	}
	f.close();
	xuatkho(dssach, i);
	char masach[6];
	int s = 0;
	std::cout << "1.SUA MA SACH" << std::endl;
	std::cout << "2.SUA TEN SACH" << std::endl;
	std::cout << "3.SUA THE LOAI" << std::endl;
	std::cout << "4.SUA NHA XUAT BAN" << std::endl;
	std::cout << "5.SUA SO LUONG" << std::endl;
	std::cout << "CHON CHUC NANG: ";
	std::cin >> s;
	std::cout << "NHAP MA SACH: " << " ";
	std::cin.ignore();
	gets_s(masach);
	for (int j = 0; j < i; j++)
		if (strcmp(dssach[j].masach, masach) == 0)
			switch (s)
			{
			case 1:
				std::cout << "NHAP MA SACH MOI: " << " ";
				fflush(stdin);
				gets_s(dssach[j].masach);
				break;

				std::cout << "SUA THANH CONG";
				break;
			case 2:
				std::cout << "NHAP TEN SACH MOI: ";
				fflush(stdin);
				gets_s(dssach[j].tensach);
				break;

				std::cout << "SUA THANH CONG";
				break;
			case 3:
				std::cout << "NHAP THE LOAI MOI: " << " ";
				fflush(stdin);
				gets_s(dssach[j].theloai);

				std::cout << "SUA THANH CONG";
				break;
			case 4:
				std::cout << "NHAP NHA XUAT BAN MOI: " << " ";
				fflush(stdin);
				gets_s(dssach[j].nxb);
				std::cout << "SUA THANH CONG";
				break;
			case 5:
				std::cout << "NHAP SO LUONG MOI: " << " ";
				std::cin >> dssach[j].sl;
				std::cout << "SUA THANH CONG";
				break;
			}

	f.open(file_khosach, std::ios::out | ios::binary);
	for (int k = 0; k < i; k++)
	{
		f.write(reinterpret_cast<char*>(&dssach[k]), sizeof(Thuvien));
	}
	f.close();


}

//DSLK

void suathongtinsach(Dslk l)
{
	Node* n = l.head;
	char masachtim[6];
	xuatsosach(l);
	std::cout << "NHAP MA SACH CAN SUA: ";
	std::cin.ignore();
	gets_s(masachtim);
	fflush(stdin);
	while (true)
	{
		n = TimNode(l, masachtim);
		if (n != NULL)
			break;
	}
	//xuatkho(l);
	int s = 0;
	std::cout << "1.SUA MA SACH" << std::endl;
	std::cout << "2.SUA TEN SACH" << std::endl;
	std::cout << "3.SUA THE LOAI" << std::endl;
	std::cout << "4.SUA NHA XUAT BAN" << std::endl;
	std::cout << "5.SUA SO LUONG" << std::endl;
	std::cout << "0.VE MENU CHINH";
	std::cout << "CHON CHUC NANG: ";
	std::cin >> s;
	switch (s)
	{
	case 1:
		std::cout << "NHAP MA SACH MOI: ";
		fflush(stdin);
		gets_s(n->Sach.masach);
		break;
	case 2:
		std::cout << "NHAP TEN SACH MOI: ";
		fflush(stdin);
		gets_s(n->Sach.tensach);
		break;
	case 3:
		std::cout << "NHAP THE LOAI MOI: ";
		fflush(stdin);
		gets_s(n->Sach.theloai);
		break;
	case 4:
		std::cout << "NHAP NHA XUAT BAN MOI: ";
		fflush(stdin);
		gets_s(n->Sach.nxb);
		break;
	case 5:
		std::cout << "NHAP SO LUONG SACH MOI: ";
		fflush(stdin);
		std::cin >> n->Sach.sl;
		break;
	}
}

//************************MƯỢN SÁCH***********************//

void nhapsachmuon()
{
	SachMuon sachmuon;
	fstream f;
	int n;
	std::cout << "NHAP SO LUONG SACH CAN MUON: ";
	std::cin >> n;
	f.open(file_sachmuon, std::ios::out | std::ios::app | std::ios::binary);
	time_t now = time(0);    //hàm lấy thời gian hệ thống  Source: https://topdev.vn/blog/date-va-time-trong-c/
	tm* ltm = localtime(&now);
	for (int i = 0; i < n; i++)
	{
		std::cout << "NHAP TEN NGUOI MUON: " << " ";
		std::cin.ignore();
		gets_s(sachmuon.tennguoimuon);
		std::cout << "NHAP MA SACH: " << " ";
		//std::cin.ignore();
		std::cin >> sachmuon.masach;
		sachmuon.ngay = ltm->tm_mday;
		sachmuon.thang = 1 + ltm->tm_mon;
		sachmuon.nam = 1900 + ltm->tm_year;
		std::cout << "NHAP THOI HAN MUON: " << " ";
		std::cin >> sachmuon.thoihan;
		std::cout << "NHAP SO LUONG: " << " ";
		std::cin >> sachmuon.soluong;
		std::cout << "NHAP GIA TIEN: " << " ";
		std::cin >> sachmuon.giatien;
		f.write(reinterpret_cast<char*>(&sachmuon), sizeof(SachMuon));
	}
	f.close();
}

void xuatdanhsachmuon()
{
	SachMuon sachmuon;
	int j = 1;
	fstream f;
	f.open(file_sachmuon, std::ios::in | std::ios::binary);
	std::cout << "+-----+-------------------------------+---------+------------+----------+-----------+----------+" << std::endl;
	std::cout << "| STT |         TEN NGUOI MUON        | MA SACH |  NGAY MUON | THOI HAN |  SO LUONG | GIA TIEN |" << std::endl;
	std::cout << "+-----+-------------------------------+---------+------------+----------+-----------+----------+" << std::endl;
	while (f.read(reinterpret_cast<char*>(&sachmuon), sizeof(SachMuon)))
	{
		std::cout << "| " << setw(3) << j++ << " | " << setw(29) << sachmuon.tennguoimuon << " |  " << setw(5) << sachmuon.masach << "  | " << setw(2) << sachmuon.ngay << "/" << setw(2) << sachmuon.thang;
		std::cout << "|" << setw(4) << sachmuon.nam << " | " << setw(3) << sachmuon.thoihan << " ngay |   " << setw(4) << sachmuon.soluong << "    |   " << setw(4) << sachmuon.giatien << "   |\n";
		std::cout << "+-----+-------------------------------+---------+------------+----------+-----------+---------+" << std::endl;
	}
}

void suathongtinnguoimuon()
{
	fstream f;
	SachMuon dssachmuon[200];
	f.open(file_sachmuon, std::ios::in | std::ios::binary);
	int i = 0;
	f.open(file_khosach, std::ios::in);
	while (f.read(reinterpret_cast<char*>(&dssachmuon[i]), sizeof(SachMuon)))
	{
		i++;
	}
	xuatdanhsachmuon();
	f.close();
	char tennguoimuon[50];
	char masach[50];
	int s;
	std::cout << "1.SUA TEN NGUOI MUON" << std::endl;
	std::cout << "2.SUA MA SACH" << std::endl;
	std::cout << "3.SUA THOI HAN" << std::endl;
	std::cout << "4.SUA SO LUONG" << std::endl;
	std::cout << "5.SUA GIA TIEN" << std::endl;
	std::cout << "CHON CHUC NANG: ";
	std::cin >> s;
	std::cout << "NHAP TEN NGUOI MUON: " << " ";
	fflush(stdin);
	gets_s(tennguoimuon);
	std::cout << "NHAP MA SACH: " << " ";
	fflush(stdin);
	gets_s(masach);
	for (int j = 0; j < i; j++)
		if (strcmp(dssachmuon[j].tennguoimuon, tennguoimuon) == 0 && strcmp(dssachmuon[j].masach, masach) == 0)
			switch (s)
			{
			case 1:
				std::cout << "NHAP TEN NGUOI MUON MOI: " << " ";
				fflush(stdin);
				gets_s(dssachmuon[j].tennguoimuon);
				std::cout << "SUA THANH CONG";
				break;
			case 2:
				std::cout << "NHAP MA SACH MOI: " << " ";
				fflush(stdin);
				gets_s(dssachmuon[j].masach);
				std::cout << "SUA THANH CONG";
				break;
			case 3:
				std::cout << "NHAP THOI HAN MOI: " << " ";
				std::cin >> dssachmuon[j].thoihan;
				std::cout << "SUA THANH CONG";
				break;
			case 4:
				std::cout << "NHAP SO LUONG MOI: " << " ";
				std::cin >> dssachmuon[j].soluong;
				std::cout << "SUA THANH CONG";
				break;
			case 5:
				std::cout << "NHAP GIA TIEN MOI: " << " ";
				std::cin >> dssachmuon[j].giatien;
				std::cout << "SUA THANH CONG: ";
				break;
			}
	f.open(file_sachmuon, std::ios::out | std::ios::binary);
	for (int j = 0; j < i; j++)
		f.write(reinterpret_cast<char*>(&dssachmuon[j]), sizeof(SachMuon));
	f.close();
}

//****************************TRẢ SÁCH***********************//

void nhapsachtra()
{
	Trasach sachtra[30];
	int n;
	fstream f;
	fstream f1;
	std::cout << "NHAP SO LUONG SACH CAN TRA: " << " ";
	std::cin >> n;
	f.open(file_sachtra, std::ios::out | std::ios::app | std::ios::binary);
	time_t now = time(0);    //hàm lấy thời gian hệ thống  Source: https://topdev.vn/blog/date-va-time-trong-c/
	tm* ltm = localtime(&now);
	for (int i = 0; i < n; i++)
	{
		std::cout << "NHAP TEN NGUOI TRA: " << " ";
		fflush(stdin);
		gets_s(sachtra[i].tennguoimuon);
		std::cout << "NHAP MA SACH: " << " ";
		std::cin.ignore();
		gets_s(sachtra[i].masach);
		sachtra[i].ngay = ltm->tm_mday;
		sachtra[i].thang = 1 + ltm->tm_mon;
		sachtra[i].nam = 1900 + ltm->tm_year;
		//int songaymuon = thisIsMagic(dssachtra[i].nam, dssachtra[i].thang, dssachtra[i].ngay) - thisIsMagic(dssachmuon.nam, dssachmuon.thang, dssachmuon.ngay);    //số ngày mượn 
		f.write(reinterpret_cast<char*>(&sachtra[i]), sizeof(Trasach));
	}
	f.close();
	SachMuon dssachmuon[200];
	f1.open(file_sachmuon, std::ios::in | std::ios::binary);
	int j = 0;
	while (f1.read(reinterpret_cast<char*>(&dssachmuon[j]), sizeof(SachMuon)))
	{
		j++;
	}
	f1.close();
	for (int i = 0; i < n; i++)
	{
		for (int k = 0; k < j; k++)
			if (strcmp(sachtra[i].tennguoimuon, dssachmuon[k].tennguoimuon) == 0 && strcmp(sachtra[i].masach, dssachmuon[k].masach) == 0)
				for (int l = k; l < j - 1; l++)
					dssachmuon[l] = dssachmuon[l + 1];
		j--;
	}
	f1.open(file_sachmuon, std::ios::out | std::ios::binary);
	j = 0;
	while (f1.write(reinterpret_cast<char*>(&dssachmuon[j]), sizeof(SachMuon)))
	{
		j++;
	}
	f1.close();
}


//************Thống kê***************
