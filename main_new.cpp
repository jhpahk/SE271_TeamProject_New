#include <iostream>
#include <windows.h>

#include "model.h"
#include "control.h"
#include "view.h"

int main() {

	/// ������ ����, �¼� ����
	StudyRoom E7("E7", 11);
	Pos temp_pos(0, 0);
	E7.add_seat(Seat(&E7, 1, temp_pos));
	temp_pos(1, 0);
	E7.add_seat(Seat(&E7, 2, temp_pos));
	temp_pos(2, 0);
	E7.add_seat(Seat(&E7, 3, temp_pos));
	temp_pos(3, 0);
	E7.add_seat(Seat(&E7, 4, temp_pos));
	temp_pos(0, 1);
	E7.add_seat(Seat(&E7, 5, temp_pos));
	temp_pos(1, 1);
	E7.add_seat(Seat(&E7, 6, temp_pos));
	temp_pos(2, 1);
	E7.add_seat(Seat(&E7, 7, temp_pos));
	temp_pos(3, 1);
	E7.add_seat(Seat(&E7, 8, temp_pos));
	temp_pos(1, 3);
	E7.add_seat(Seat(&E7, 9, temp_pos));
	temp_pos(2, 3);
	E7.add_seat(Seat(&E7, 10, temp_pos));
	temp_pos(3, 3);
	E7.add_seat(Seat(&E7, 11, temp_pos));
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
		std::cout << "\n\n--------------------     ������ ���� ���� ���α׷�     --------------------" << std::endl;
		std::cout << std::endl << std::endl << std::endl;
		std::cout << "1. �л� �α���     2. ������ �α���     3.�л� ȸ������     4.������ ȸ������     5. ����" << "\n\n�Է�: ";
		std::cin >> sel;
		if (std::cin.fail() || sel < 1 || sel > 5) {
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
				std::cout << "\n\nUser: " << cs.get_student()->get_student_num() << std::endl << std::endl;
				if (cs.get_student()->get_is_using()) {
					std::cout << "���� " << cs.get_student()->get_studyroom_using()->get_name() << "�������� " << cs.get_student()->get_seat_using()->get_seat_num() << "�� �¼��� �������Դϴ�.\n\n";
				}
				std::cout << "\n\n1. ������ ����     2. �α׾ƿ�\n\n";
				std::cout << "�Է�: ";
				std::cin >> sel;
				if (std::cin.fail() || sel < 1 || sel > 2) {
					std::cout << "\n\n�߸��� �Է��Դϴ�";
					Sleep(500);
					std::cin.clear();
					std::cin.ignore(100, '\n');
					system("cls");
					continue;
				}
				else if (sel == 1) {
					system("cls");
					std::cout << "\n\n1. E7     2. �ڷ� ����\n\n�Է�: ";
					std::cin >> sel;
					if (std::cin.fail() || sel < 1 || sel > 2) {
						std::cout << "\n\n�߸��� �Է��Դϴ�";
						Sleep(500);
						std::cin.clear();
						std::cin.ignore(100, '\n');
						system("cls");
						continue;
					}
					else if (sel == 1) {
						cs.get_student()->set_studyroom_using(&E7);
						while (true) {
							system("cls");
							std::cout << "\n\n���� ������ ������: E7\n\n";
							main_interface.show_studyroom(&E7);
							std::cout << "\n\n1. ����     2. ���� ���     3. �¼� ���� Ȯ��     4. �ڷ� ����\n\n�Է�: ";
							std::cin >> sel;
							if (std::cin.fail() || sel < 1 || sel > 4) {
								std::cout << "\n\n�߸��� �Է��Դϴ�";
								Sleep(500);
								std::cin.clear();
								std::cin.ignore(100, '\n');
								system("cls");
								continue;
							}
							else if (sel == 1) {
								if (cs.get_student()->get_is_using()) {
									std::cout << "\n\n�̹� �¼��� �������Դϴ�.";
									Sleep(500);
									continue;
								}
								int seat_sel;
								std::cout << "\n\n������ �¼��� ��ȣ�� �Է��Ͻʽÿ�: ";
								std::cin >> seat_sel;
								
								if (std::cin.fail() || seat_sel < 1 || seat_sel > cs.get_student()->get_studyroom_using()->get_max_seat_num()) {
									std::cout << "\n\n�߸��� �Է��Դϴ�.";
									std::cin.clear();
									std::cin.ignore(100, '\n');
									Sleep(500);
									continue;
								}
								cs.make_reservation(cs.get_student()->get_studyroom_using()->get_seat(seat_sel - 1));
								std::cout << "\n\n������ �Ϸ�Ǿ����ϴ�.";
								Sleep(500);
								continue;
							}
							else if (sel == 2) {
								std::string check_pwd;
								if (!cs.get_student()->get_is_using()) {
									std::cout << "\n\n���� �������� �¼��� �����ϴ�.";
									Sleep(500);
									continue;
								}
								std::cout << "\n\n��й�ȣ�� �Է��� �ֽʽÿ�: ";
								std::cin >> check_pwd;
								if (check_pwd != cs.get_student()->get_password()) {
									std::cout << "\n\n�߸��� ��й�ȣ�Դϴ�.";
									Sleep(500);
									continue;
								}
								cs.cancel_reservation();
							}
							else if (sel == 3) {
								int seat_sel;
								std::cout << "\n\n�¼� ��ȣ�� �Է��� �ֽʽÿ�: ";
								std::cin >> seat_sel;
								if (std::cin.fail() || seat_sel < 1 || seat_sel > cs.get_student()->get_studyroom_using()->get_max_seat_num()) {
									std::cout << "\n\n�߸��� �Է��Դϴ�.";
									std::cin.clear();
									std::cin.ignore(100, '\n');
									Sleep(500);
									continue;
								}
								while (true) {
									system("cls");
									main_interface.show_seat_status(cs.get_student()->get_studyroom_using()->get_seat(seat_sel - 1));
									std::cout << "\n\n1. �ڷ� ����\n\n�Է�: ";
									std::cin >> sel;
									if (std::cin.fail() || seat_sel < 1 || seat_sel > cs.get_student()->get_studyroom_using()->get_max_seat_num()) {
										std::cout << "\n\n�߸��� �Է��Դϴ�.";
										std::cin.clear();
										std::cin.ignore(100, '\n');
										Sleep(500);
										continue;
									}
									if (sel == 1) {
										break;
									}
								}
							}
							else {
								break;
							}
						}
					}
					else {
						continue;
					}
				}
				else if (sel == 2) {
					cs.set_student(nullptr);
					break;
				}
			}
		}
		else if (sel == 2) {
			system("cls");
			if (!log_in.admin_log_in(&database, &ca)) {
				continue;
			}
			while (true) {
				system("cls");
				std::cout << "\n\n1. ������ ����     2. �α׾ƿ�\n\n";
				std::cout << "�Է�: ";
				std::cin >> sel;
				if (std::cin.fail() || sel < 1 || sel > 2) {
					std::cout << "\n\n�߸��� �Է��Դϴ�";
					Sleep(500);
					std::cin.clear();
					std::cin.ignore(100, '\n');
					system("cls");
					continue;
				}
				else if (sel == 1) {
					while (true) {
						system("cls");
						std::cout << "\n\n1. E7     2. �ڷ� ����\n\n�Է�: ";
						std::cin >> sel;
						if (std::cin.fail() || sel < 1 || sel > 2) {
							std::cout << "\n\n�߸��� �Է��Դϴ�";
							Sleep(500);
							std::cin.clear();
							std::cin.ignore(100, '\n');
							system("cls");
							continue;
						}
						else if (sel == 1) {
							while (true) {
								system("cls");
								ca.get_admin()->set_studyroom_using(&E7);
								main_interface.show_studyroom(ca.get_admin()->get_studyroom_using());
								std::cout << "\n\n�����ڴ� �¼� Ȯ�ΰ� �¼� ���� ���� ��Ҹ� �����մϴ�.\n\n1. �¼� Ȯ��     2. ���� ���� ���     3. �α׾ƿ�\n\n�Է�: ";
								std::cin >> sel;
								if (std::cin.fail() || sel < 1 || sel > 3) {
									std::cout << "\n\n�߸��� �Է��Դϴ�.";
									std::cin.clear();
									std::cin.ignore(100, '\n');
									Sleep(500);
									continue;
								}
								else if (sel == 1) {
									int seat_sel;
									std::cout << "\n\n�¼� ��ȣ�� �Է��� �ֽʽÿ�: ";
									std::cin >> seat_sel;
									if (std::cin.fail() || seat_sel < 1 || seat_sel > ca.get_admin()->get_studyroom_using()->get_max_seat_num()) {
										std::cout << "\n\n�߸��� �Է��Դϴ�.";
										std::cin.clear();
										std::cin.ignore(100, '\n');
										Sleep(500);
										continue;
									}
									while (true) {
										system("cls");
										main_interface.show_seat_status(ca.get_admin()->get_studyroom_using()->get_seat(seat_sel - 1));
										std::cout << "\n\n1. �ڷ� ����\n\n�Է�: ";
										std::cin >> sel;
										if (std::cin.fail() || seat_sel < 1 || seat_sel > ca.get_admin()->get_studyroom_using()->get_max_seat_num()) {
											std::cout << "\n\n�߸��� �Է��Դϴ�.";
											std::cin.clear();
											std::cin.ignore(100, '\n');
											Sleep(500);
											continue;
										}
										if (sel == 1) {
											break;
										}
									}
								}
								else if (sel == 2) {
									int seat_sel;
									std::cout << "\n\n�¼� ��ȣ�� �Է��� �ֽʽÿ�: ";
									std::cin >> seat_sel;
									if (std::cin.fail() || seat_sel < 1 || seat_sel > ca.get_admin()->get_studyroom_using()->get_max_seat_num()) {
										std::cout << "\n\n�߸��� �Է��Դϴ�.";
										std::cin.clear();
										std::cin.ignore(100, '\n');
										Sleep(500);
										continue;
									}
									if (!ca.get_admin()->get_studyroom_using()->get_seat(seat_sel - 1)->is_reserved()) {
										std::cout << "\n\n����Ǿ� ���� ���� �¼��Դϴ�.";
										Sleep(500);
										continue;
									}
									ca.force_cancel_reservation(ca.get_admin()->get_studyroom_using()->get_seat(seat_sel - 1));
								}
								else {
									break;
								}
							}
						}
						else if (sel == 2) {
							break;
						}
					}
				}
				else if (sel == 2) {
					break;
				}
			}
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