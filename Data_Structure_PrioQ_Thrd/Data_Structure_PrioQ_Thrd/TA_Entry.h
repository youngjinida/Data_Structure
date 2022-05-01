#ifndef TA_ENTRY_H
#define TA_ENTRY_H
#include "T_Entry.h"

template<typename K, typename V>
class TA_Entry
{
public:
	TA_Entry(int n, string nm);
	~TA_Entry() {};
	int size() { return num_elements; }
	bool empty() { return num_elements == 0; }
	string getName() { return this->name; }
	void reserve(int new_capacity);
	void insert(int i, T_Entry<K, V> element);
	void insertBack(T_Entry<K, V> element);
	void remove(int i);
	T_Entry<K, V>& at(int i);
	void set(int i, T_Entry<K, V>& element);
	void fprint(ostream& fout, int elements_per_line);
	void fprintSample(ostream& fout, int elements_per_line, int num_sample_lines);
	bool isValidIndex(int i);
	T_Entry<K, V>& operator[](int index) { return t_GA[index]; }

protected:
	T_Entry<K,V> *t_GA;
	int num_elements;
	int capacity;
	string name;
};

template<typename K, typename V>
TA_Entry<K, V>::TA_Entry(int n, string nm)
	:num_elements(0), name(nm), capacity(n)
{
	this->t_GA = new T_Entry<K, V>[this->capacity];
	if (t_GA == NULL)
	{
		cout << "t_GA initialize fail\n";
		exit;
	}
}

template<typename K, typename V>
void TA_Entry<K, V>::reserve(int new_capacity)
{
	if (this->capacity >= new_capacity)
		return;
	T_Entry<K, V>* nt_GA = new T_Entry<K, V>[new_capacity];
	if (nt_GA == NULL)
	{
		cout << "nt_GA initialize fail\n";
		exit;
	}
	cout << this->getName() << " expand capacity to" << setw(3) << new_capacity << "\n";

	for (int i = 0; i < num_elements; ++i)
		nt_GA[i] = this->t_GA[i];
	delete[] this->t_GA;
	this->t_GA = nt_GA;
}

template<typename K, typename V>
bool TA_Entry<K, V>::isValidIndex(int i)
{
	if ((i < 0) || (i > num_elements))
		return false;
	else
		return true;
}

template<typename K,typename V>
void TA_Entry<K, V>::insert(int i, T_Entry<K,V> element)
{
	if (num_elements >= capacity)
	{
		int new_capacity;
		new_capacity = ((2 * capacity) > 1) ? 2 * capacity : 1;
		reserve(new_capacity);
	}
	if (isValidIndex(i))
	{
		for (int j = num_elements - 1; j >= i; --j)
			t_GA[j + 1] = t_GA[j];
		t_GA[i] = element;
		++num_elements;
	}
}

template<typename K, typename V>
void TA_Entry<K, V>::insertBack(T_Entry<K, V> element)
{
	if (num_elements >= capacity)
	{
		int new_capacity;
		new_capacity = ((2 * capacity) > 1) ? 2 * capacity : 1;
		reserve(new_capacity);
	}
	t_GA[num_elements] = element;
	++num_elements;
}

template<typename K, typename V>
void TA_Entry<K, V>::fprint(ostream& fout, int elements_per_line)
{
	int cnt = 0;
	while (cnt < size()) {
		t_GA[cnt].fprint(fout);
		cnt++;
		if (elements_per_line == 1) {
			fout << "\n";
			continue;
		}
		else {
			fout << "   ";
			if (cnt % elements_per_line == 0) {
				fout << "\n";
			}
		}
	}
	fout << "\n";
}

#endif // !TA_ENTRY_H
