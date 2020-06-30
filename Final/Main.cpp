#include "Header.h"

int main()
{
	int flag;
	while (1)
	{
		std::cout << "CHON CACH THAO TAC VOI DU LIEU:\n";
		std::cout << "1.MANG\n";
		std::cout << "2.DANH SACH LIEN KET\n";
		std::cout << "0.THOAT\n";
		std::cout << "NHAP LUA CHON CUA BAN: ";
		int chon;
		std::cin >> chon;
		if (chon == 1)
		{
		start:menu_chinh();
			cin >> flag;
			if (flag == 0)
				exit(0);
			else
				switch (flag)
				{
				case 1:
				{
					int s;
					menu_qlkho();
					while (1)
					{
						cout << "CHON CHUC NANG: ";
						cin >> s;
						if (s == 0)
							exit(0);
						else
							switch (s)
							{
							case 1:
								nhapsach();
								goto start;
							case 2:
								xoasach();
								goto start;
							case 3:
								suathongtinsach();
								goto start;
							case 4:
								xuatsosach();
								goto start;
							case 5:
								goto start;
							case 0:
								exit(0);
							}
					}
				}
				case 2:
				{
					int s;
					menu_muonsach();
					while (1)
					{
						cout << endl;
						cout << "CHON CHUC NANG: ";
						cin >> s;
						if (s == 0)
							exit(0);
						else switch (s)
						{
						case 1:
							nhapsachmuon();
							goto start;
						case 2:
							suathongtinnguoimuon();
							goto start;
						case 3:
							xuatdanhsachmuon();
							goto start;

						case 4:
							goto start;
						case 0:
							exit(0);
						}
					}
				}
				case 3:
				{
					int s;
					menu_sachtra();
					while (1)
					{
						cout << "CHON CHUC NANG: ";
						cin >> s;
						switch (s)
						{
						case 1:
							nhapsachtra();
						case 2:
							goto start;
						case 0:
							exit(0);
						}
					}
				}
				}
		}
		else if (chon == 2)/***********************************************************************************************************************************************************************************************/
		{
			//****Hàm khỏi tạo DSLK
			char file[] = ".\\khosach.bin";    //địa chỉ file
			Dslk list;
			Taodslk(list);		//Tạo DSLK
			FiletoDslk(list, file);		//Chuyển dữ liệu từ file vào DSLK
		start1:menu_chinh();
			cin >> flag;
			if (flag == 0)
			{
				DslktoFile(list, file);  //Chuyển dữ liều từ Dslk vào file
				exit(0);
			}
			else
				switch (flag)
				{
				case 1:
				{
					int s;
					menu_qlkho();
					while (1)
					{
						cout << "CHON CHUC NANG: ";
						cin >> s;
						if (s == 0)
							exit(0);
						else
							switch (s)
							{
							case 1:
							{
								nhapsach(list);
								goto start1;
							}
							case 2:
								Xoasach(list);
								goto start1;
							case 3:
								suathongtinsach(list);
								goto start1;
							case 4:
							{
								xuatsosach(list);
								std::cout << "AN PHIM BAT KY DE TIEP TUC!";
								std::cin.get();
								std::cin.get();
								goto start1;
							}
							case 5: goto start1;
							case 0:
								DslktoFile(list, file);  //Chuyển dữ liều từ Dslk vào file
								exit(0);
							}
					}
				}
				case 2:
				{
					int s;
					menu_muonsach();
					while (1)
					{
						cout << endl;
						cout << "CHON CHUC NANG: ";
						cin >> s;
						if (s == 0)
							exit(0);
						else switch (s)
						{
						case 1:
							nhapsachmuon();
							goto start1;
						case 2:
							suathongtinnguoimuon();
							goto start1;
						case 3:
							xuatdanhsachmuon();
							goto start1;
						case 4:
							goto start1;
						case 0:
							DslktoFile(list, file);
							exit(0);
						}
					}
				}
				case 3:
				{
					int s;
					menu_sachtra();
					while (1)
					{
						cout << "CHON CHUC NANG: ";
						cin >> s;
						switch (s)
						{
						case 1:
							nhapsachtra();
							goto start1;
						case 2:
							goto start1;
						case 0:
							DslktoFile(list, file);
							exit(0);
						}
					}
				}
				}
		}
		else exit(0);

	}
}