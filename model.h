#pragma once

#include <vector>
#include <string>

class Pos;
class Student;
class Admin;
class Seat;
class StudyRoom;
class StudentDB;

class Pos {
public:
	Pos() : x{ 0 }, y{ 0 } {}
	Pos(int x, int y) : x{ x }, y{ y } {}
	int x;
	int y;

	void operator()(int input_x, int input_y) {
		x = input_x;
		y = input_y;
	}
};

class Student {
protected:
	int student_num = NULL;						// student number
	std::string password = NULL;				// password for login / reservation
	bool is_using = false;						// ���� �¼��� �����ϰ� �̿����ΰ�?
	StudyRoom* studyroom_using = nullptr;		// ���� �̿����� ������
	Seat* seat_using = nullptr;					// ���� �̿����� �¼�

public:
	Student() {}
	Student(int num) : student_num{ num } {}
	Student(int num, std::string pw) : student_num{ num }, password{ pw } {}

	virtual ~Student() {}

	// get data
	int get_student_num();
	std::string get_password();
	bool get_is_using();
	StudyRoom* get_studyroom_using();
	Seat* get_seat_using();

	// set data
	void set_student_num(int num);
	void set_password(std::string pwd);
	void set_is_using_reverse();
	void set_studyroom_using(StudyRoom* room);
	void set_seat_using(Seat* seat);
};

class Admin : public Student {
private:
	std::string admin_id;			// ������ ���� ���� ID
public:
	Admin() {}
	Admin(std::string ad_id) : admin_id{ ad_id } {}
	Admin(std::string ad_id, std::string pwd) : Student(0, pwd), admin_id{ ad_id } {}
	std::string get_admin_id();

	void set_admin_id(std::string ad_id);
};

class Seat {
private:
	StudyRoom* belong_to = nullptr;				// � �����ǿ� �ִ� �¼��ΰ�?
	int seat_num = NULL;						// �¼��� ���� ��ȣ
	bool reservation = false;					// ���� ����Ǿ� �ִ���
	Student* res_student = nullptr;				// ������ �л�
	bool away_from = false;						// �ڸ� ��� �����ΰ�?

public:
	Seat() {}
	Seat(StudyRoom* study_room, int num, Pos input_pos) : belong_to{ study_room }, seat_num{ num } {
		pos.x = input_pos.x;
		pos.y = input_pos.y;
	}

	virtual ~Seat() {}

	Pos pos;									// �¼��� ��ġ

	// get data
	StudyRoom* get_belong_to();
	int get_seat_num();
	bool is_reserved();
	Student* get_res_student();
	bool is_away_from();

	// set data
	void set_reservation_reverse();
	void set_res_student(Student* student);
	void set_away_from_reverse();
};

class StudyRoom {
private:
	std::string name = NULL;
	int max_seat_num = NULL;					// ��ü �¼� ��
	int cur_using_num = NULL;					// �̿����� �¼� ��
	std::vector<Seat> seats;					// StudyRoom�� ���Ե� Seat instance vector

public:
	StudyRoom() {}
	StudyRoom(std::string room_name, int max) : name{ room_name }, max_seat_num { max }, cur_using_num{ 0 } {}

	// get data
	std::string get_name();
	int get_max_seat_num();
	int get_cur_using_num();
	Seat* get_seat(int idx);
	std::vector<Seat> get_seats();

	// set data
	void set_name(std::string studyroom_name);
	void set_cur_using_num(int i);
	void add_seat(Seat seat);
};

// ���α׷��� ��ϵ� Student/Admin�� �����ϴ� StudentDB Ŭ����
class StudentDB {
private:
	std::vector<Student> student_database;				// ID, PW
	std::vector<Admin> admin_database;					// admin_ID, PW
public:
	int load_student_database();
	int load_student_admin_database();

	void save_student_database();
	void save_student_admin_database();

	void add_student(Student student);
	void add_admin(Admin admin);

	Student* get_student(int student_num);
	Admin* get_admin(std::string admin_id);
	int get_student_len();
	int get_admin_len();
};

class StudyRoomDB {
private:
	std::vector<StudyRoom*> studyroom_database;			// name, size /n x1, y1, x2, y2 ...
public:
	int load_studyroom_database();
	void save_studyroom_database();
	void add_studyroom(StudyRoom* studyroom);
	void delete_studyroom(StudyRoom* studyroom);
};