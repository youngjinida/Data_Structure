#include "Student.h"

ostream& operator<< (ostream& fout, const Student* st)
{
	fout.precision(2);
	fout.setf(ios::fixed);
	
	fout << "Student[" << setw(3) << st->getID() << "," << setw(12) << st->getName() << ",";
	fout << setw(5) << st->getGPA() << "]";
	return fout;
}
