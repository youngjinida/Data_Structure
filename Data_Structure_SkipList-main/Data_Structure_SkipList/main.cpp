#include <iostream>
#include "G_Skip_List.h"
#include "Planet.h"
#include <string>
using namespace std;
#define NUM_ELEMENTS 100
#define NUM_INT 10
#define NUM_TASK 10
#define NUM_PLANETS 9
#define BIG_RAND_MAX 1000000
void genBigRandArray(int* data, int size, int range_low, int range_high);
void main()
{
	Planet* pSolarPlanets;
	int* planetIDs;
	pSolarPlanets = new Planet[NUM_PLANETS];
	Planet suffledSolarPlanets[] = {
		Planet(7, "Uranus", 14.5, 2870),
		Planet(5, "Jupiter", 318, 778),
		Planet(3, "Earth", 1.0, 150),
		Planet(4, "Mars", 0.107, 228),
		Planet(6, "Saturn", 95.1, 1430),
		Planet(2, "Venus", 0.815, 108),
		Planet(8, "Neptune", 17.2, 4500),
		Planet(1, "Mercury", 0.0558, 57.9),
		Planet(9, "Pluto", 0.11, 5900)
	};
	//testTaskSkipList();
	cout << "\n=================" << endl;
	cout << "Testing SkipList<int, Planet> ..." << endl;
	SkipList<int, Planet> planetSkipList;
	typedef SkipList<int, Planet>::Position Pos_planet;
	Pos_planet pPlanet;
	int id;
	int deleteList[NUM_PLANETS] = { 2, 7, 6, 4, 8, 5, 3, 9, 1 };
	cout << "Inserting planets to";
	cout << "planet SkipList ..." << endl;
	for (int i = 0; i < NUM_PLANETS; i++)
	{
		cout << "inserting SolarPlanet[";
		cout << i << "]: " << suffledSolarPlanets[i] << endl;
		id = suffledSolarPlanets[i].getID();
		planetSkipList.SkipListInsert(cout, id, suffledSolarPlanets[i]);
		planetSkipList.PrintSkipList(cout);
		cout << endl;
	}
	cout << "\n********************* " << endl;
	for (int i = 0; i < NUM_PLANETS; i++)
	{
		cout << "Search planetSkipList and delete";
		cout << "the planet(";
		cout << deleteList[i] << ") : ";
		pPlanet = planetSkipList.SkipListSearch(deleteList[i]);
		if (pPlanet != Pos_planet(NULL))
		{
			cout << *pPlanet << endl;
			planetSkipList.SkipListRemove(cout, deleteList[i]);
		}
		planetSkipList.PrintSkipList(cout);
		cout << endl;
	}
}