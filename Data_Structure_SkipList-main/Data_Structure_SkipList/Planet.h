#ifndef PLANET_H
#define PLANET_H
#include <iostream>

using namespace std;

class Planet
{
	friend ostream& operator<<(ostream& fout, Planet& p)
	{
		fout << "Planet (ID: " << p.getID() << ")";
		fout << ", Name: " << p.getName();
		fout << ", Relative Mass:" << p.getRelativeMass();
		fout << ", Distance: " << p.getDistance() << ")";
		return fout;
	}
public:
	Planet() {}
	~Planet() {}
	Planet(int id, string nm, double rm, double dist)
		:ID(id), name(nm), relativeMass(rm), distance(dist) {}
	int getID() { return ID; }
	string getName() { return name; }
	double getRelativeMass() { return relativeMass; }
	double getDistance() { return distance; }

private:
	int ID;
	string name;
	double relativeMass;
	double distance;
};

#endif // ! PLANET_H
