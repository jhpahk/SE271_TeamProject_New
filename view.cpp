#include <iostream>

#include "model.h"
#include "control.h"
#include "view.h"

void UI::show_studyroom(StudyRoom* studyroom) {
	// ��ü �¼��� �� ���� �ٸ� y coordinate Ž��
	int size = studyroom->get_cur_using_num();
	int* distinct_y = new int[size];
	int y_count = 0;
	int seat_num = 0;

	for (int i = 0; i < size; i++) {
		if (i == 0) {
			distinct_y[y_count] = studyroom->get_seat(i)->pos.y;
			y_count++;
			continue;
		}
		bool existing = false;
		for (int j = 0; j < y_count; j++) {
			if (studyroom->get_seat(i)->pos.y == distinct_y[j]) {
				existing = true;
				break;
			}
		}
		if (!existing) {
			distinct_y[y_count] = studyroom->get_seat(i)->pos.y;
			y_count++;
		}
	}
	// y coordinate ���� x coordinate �з��ؼ� ����, 0��° index�� �ش� y coordinate�� �����ϴ� x coordinate�� ����
	IntList* coordinates = new IntList[y_count];
	for (int i = 0; i < y_count; i++) {
		coordinates[i].append(0);
	}
	for (int i = 0; i < size; i++) {
		for (int y_index = 0; y_index < y_count; y_index++) {
			if (studyroom->get_seat(i)->pos.y == distinct_y[y_index]) {
				coordinates[y_index].append(studyroom->get_seat(i)->pos.x);
				coordinates[y_index].set_value(0, coordinates[y_index][0] + 1);
			}
		}
	}
	// print
	for (int y_index = 0; y_index < y_count; y_index++) {
		// �¼��� ��ġ�Ǿ� ���� ���� ������ ���� print (y coordinate ����)
		if (y_index == 0) {
			for (int blank = 0; blank < distinct_y[0] * 6; blank++) {
				std::cout << std::endl;
			}
		}
		else {
			for (int blank = 0; blank < (distinct_y[y_index] - distinct_y[y_index - 1] - 1) * 6; blank++) {
				std::cout << std::endl;
			}
		}
		// ���� y coordinate ������ ���� �ٸ� �¼��� ������ ������ �����ϴ� gaps ����Ʈ
		IntList gaps;
		for (int i = 1; i <= coordinates[y_index][0]; i++) {
			if (i == 1) {
				gaps.append(coordinates[y_index][i] + 1);
				continue;
			}
			gaps.append(coordinates[y_index][i] - coordinates[y_index][i - 1]);
		}
		// �������� ���, �� �پ� ���, �� �¼��� 12x6 ũ�� ����
		for (int high = 0; high < 6; high++) {
			for (int bing = 0; bing < coordinates[y_index][0]; bing++) {
				// �¼� ��ȣ ���
				seat_num = 0;
				for (int yi = 0; yi < y_index; yi++) {
					seat_num += coordinates[yi][0];
				}
				seat_num += (bing + 1);
				//  gaps ����Ʈ���� ���� �¼��� ���� �¼��� ������ �ҷ��� �ش��ϴ� ��ŭ ���� ���
				for (int i = 0; i < gaps[bing] - 1; i++) {
					std::cout << "            ";
				}
				// ���� ���̿� ���� �¼� ��� ���
				if (high == 0) {
					std::cout << " ---------- ";
				}
				else if (high == 1) {
					std::cout << "|          |";
				}
				else if (high == 2) {
					if (seat_num < 10) {
						std::cout << "|    0" << seat_num << "    |";
					}
					else {
						std::cout << "|    " << seat_num << "    |";
					}
				}
				else if (high == 3) {
					if ((studyroom->get_seat(seat_num - 1))->is_reserved()) {
						std::cout << "|  �����  |";
					}
					else {
						std::cout << "|          |";
					}
				}
				else if (high == 4) {
					std::cout << "|          |";
				}
				else if (high == 5) {
					std::cout << " ---------- ";
				}
			}
			std::cout << std::endl;
		}
	}
	delete[] distinct_y;
	delete[] coordinates;
}

void UI::show_seat_status(Seat* seat) {
	std::cout << "�¼� ��ȣ : " << seat->get_seat_num() << std::endl;
	std::cout << "���� ���� : ";
	if (seat->is_reserved()) {
		std::cout << "�����" << std::endl;
		std::cout << "������(Student Number) : " << seat->get_res_student()->get_student_num() << std::endl;
		std::cout << "���� �ð� : �̱���" << std::endl;
	}
	else {
		std::cout << "����Ǿ� ���� ���� (���� ����)" << std::endl;
	}
}