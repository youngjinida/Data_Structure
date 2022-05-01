#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Student
{
	friend ostream& operator<< (ostream& fout, const Student* st);
public:
	Student(int id, string n, double g)
		:st_id(id), name(n), gpa(g) {}
	int getID() const { return st_id; }
	double getGPA() const { return gpa; }
	string getName() const { return name; }
	void setST_id(int id) { st_id = id; }
	void setGPA(double g) { gpa = g; }
	const Student& operator=(const Student& right)
	{
		this->st_id = right.getID();
		this->name = right.getName();
		this->gpa = right.getGPA();
		return *this;
	}
	bool operator>(const Student& right) { return st_id > right.st_id; }
	bool operator<(const Student& right) { return st_id < right.st_id; }
	bool operator>=(const Student& right) { return st_id >= right.st_id; }
	bool operator<=(const Student& right) { return st_id <= right.st_id; }
	bool operator==(const Student& right) { return st_id == right.st_id; }
private:
	int st_id;
	string name;
	double gpa;
};
#endif // !STUDENT_H