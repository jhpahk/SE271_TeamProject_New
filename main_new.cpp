#include <iostream>
#include <windows.h>

#include "model.h"
#include "control.h"
#include "view.h"

int main() {

	/// ������ ����, �¼� ����
	StudyRoom E7("E7", 10);
	std::cout << "DONE" << std::endl;
	
	Pos temp_pos(1, 2);
	E7.add_seat(Seat(&E7, 1, temp_pos));
	temp_pos(1, 3);
	E7.add_seat(Seat(&E7, 2, temp_pos));
	temp_pos(2, 3);
	E7.add_seat(Seat(&E7, 3, temp_pos));
	temp_pos(2, 4);
	E7.add_seat(Seat(&E7, 4, temp_pos));
	temp_pos(2, 5);
	E7.add_seat(Seat(&E7, 1, temp_pos));
	///

	UI main_interface;

	StudentDB database;

	LogIn log_in;
	ControlByStudent cs;
	ControlByAdmin ca;
	
	system("cls");

	while (true) {
		system("cls");
		int sel;
		std::cout << "\n--------------------     ������ ���� ���� ���α׷�     --------------------" << std::endl;
		std::cout << std::endl << std::endl << std::endl;
		std::cout << "1. �л� �α���     2. ������ �α���     3.�л� ȸ������     4.������ ȸ������     5. ����" << "\n\n�Է�: ";
		std::cin >> sel;
		if (std::cin.fail() || sel < 0 || sel > 5) {
			std::cout << "\n\n�߸��� �Է��Դϴ�";
			Sleep(500);
			std::cin.clear();
			std::cin.ignore(100, '\n');
			system("cls");
			continue;
		}
		else if (sel == 1) {
			system("cls");
			if (!log_in.student_log_in(&database, &cs)) {
				continue;
			}
			while (true) {
				system("cls");
				int sel;
				std::cout << "User: " << cs.get_student()->get_student_num() << std::endl << std::endl;
				std::cout << "1. ������ ����     2. �α׾ƿ�\n\n";
				std::cout << "�Է�: ";
				std::cin >> sel;
				if (std::cin.fail() || sel < 0 || sel > 2) {
					std::cout << "\n\n�߸��� �Է��Դϴ�";
					Sleep(500);
					std::cin.clear();
					std::cin.ignore(100, '\n');
					system("cls");
					continue;
				}
				else if (sel == 1) {
					std::cout << "\n\n1. E7     2. �ڷ� ����\n\n�Է�: ";
					std::cin >> sel;
					if (std::cin.fail() || sel < 0 || sel > 2) {
						std::cout << "\n\n�߸��� �Է��Դϴ�";
						Sleep(500);
						std::cin.clear();
						std::cin.ignore(100, '\n');
						system("cls");
						continue;
					}
					else if (sel == 1) {

					}
					else {
						continue;
					}
				}
				else {
					break;
				}
			}
		}
		else if (sel == 2) {
			system("cls");
			std::cout << "2 ����" << std::endl;
			break;
		}
		else if (sel == 3) {
			system("cls");
			Register student_reg;
			student_reg.register_student(&database);
			Sleep(500);
		}
		else if (sel == 4) {
			system("cls");
			Register admin_reg;
			admin_reg.register_admin(&database);
			Sleep(500);
		}
		else if (sel == 4) {
			system("cls");
			std::cout << "2 ����" << std::endl;
			break;
		}
		else {
			std::cout << "���α׷��� �����մϴ�.";
			Sleep(1000);
			system("cls");
			break;
		}
	}
	return 0;
}