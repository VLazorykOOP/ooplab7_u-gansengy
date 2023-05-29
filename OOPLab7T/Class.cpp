#include <iostream>

using namespace std;

class User {
private:
	string name;
	string email;
	string password;
	int score;
protected:
	bool access;
	bool exam_pass_status;
public:
	User(string name, string email, string password) {
		this->name = name;
		this->email = email;
		this->password = password;
		access = false;
		exam_pass_status = false;
	}
	void changeAccess(bool key) {
		access = key;
	}
	void changeExamStatus(bool key) {
		exam_pass_status = key;
	}
	void addScore(int score) {
		this->score = score;
	}
	string getName() {
		return name;
	}
	string getEmail() {
		return email;
	}
	string getPassword() {
		return password;
	}
	int getScore() {
		return score;
	}
	bool getAccess() {
		return access;
	}
	bool getExamPassStatus() {
		return exam_pass_status;
	}
};