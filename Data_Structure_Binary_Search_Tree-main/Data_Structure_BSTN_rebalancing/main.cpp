#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "T_BST.h"
#include "T_Array.h"
#include "T_Entry.h"
#include "Student.h"

using namespace std;
#define NUM_STUDENTS 15
void main()
{
	Student students[NUM_STUDENTS] =
	{
	Student(10, string("Kim, G-M"), 4.5),
	Student(11, string("Lee, S - M"), 4.4),
	Student(12, string("Park, S - S"), 4.3),
	Student(13, string("Lee, K-M"), 4.2),
	Student(14, string("Hong, G-M"), 4.1),
	Student(15, string("Jang, S-M"), 4.0),
	Student(16, string("Hwang, S - T"), 3.9),
	Student(17, string("Choi, Y-H"), 3.8),
	Student(18, string("Shin, D-J"), 3.7),
	Student(19, string("Kwak, S-B"), 3.6),
	Student(20, string("Kang, S-M"), 3.5),
	Student(21, string("Jong, S-T"), 3.4),
	Student(22, string("Lee, Y-H"), 3.3),
	Student(23, string("Sung, D-J"), 3.2),
	Student(24, string("Kong, S-B"), 3.1)
	};


	T_BST<double, Student*>
		BST_ST_keyGPA_Balanced("BST_Student_KeyGPA_Balanced");
	T_Entry<double, Student*> entry_GPA_pST;
	T_BSTN<double, Student*>** ppBST_ST_kGPA_root, * pBST_ST_kGPA_root;
	cout << "\n" << "Testing Binary Search Tree of Student_KeyGPA with Rebalancing" << "\n";
	ppBST_ST_kGPA_root = BST_ST_keyGPA_Balanced.getRootAddr();
	for (int i = 0; i < NUM_STUDENTS; i++)
	{
		entry_GPA_pST.setKey(students[i].getGPA());
		entry_GPA_pST.setValue(&students[i]);
		cout << "Insert inOrder (" << entry_GPA_pST << ") into "
			<< BST_ST_keyGPA_Balanced.getName() << "\n";
		//BST_ST.insertInOrder(entry_ID_pST);
		BST_ST_keyGPA_Balanced.insertAndRebalance(entry_GPA_pST);
	}
	cout << "\nElements in " << BST_ST_keyGPA_Balanced.getName() << " (in order of GPA) : "
		<< "\n";
	//BST_ST_keyGPA_Balanced.fprint_inOrder(cout);
	BST_ST_keyGPA_Balanced.fprint_with_Depth(cout);
	cout << "\nRemoving root entry in sequence ..." << "\n";
	for (int i = 0; i < NUM_STUDENTS; i++)
	{
		pBST_ST_kGPA_root = BST_ST_keyGPA_Balanced.getRoot();
		entry_GPA_pST = pBST_ST_kGPA_root->getEntry();
		cout << "\nat " << i << "-th erase " << entry_GPA_pST << "\n";
		BST_ST_keyGPA_Balanced.eraseBSTN(&pBST_ST_kGPA_root);
		BST_ST_keyGPA_Balanced.fprint_with_Depth(cout);
		if (!BST_ST_keyGPA_Balanced.isEmpty())
		{
			entry_GPA_pST = BST_ST_keyGPA_Balanced.maxEntry();
			cout << "Current max is " << entry_GPA_pST << "\n";
		}
	}
}