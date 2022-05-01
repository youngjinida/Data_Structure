#ifndef CBT_H
#define CBT_H

#include <iostream>
using namespace std;

#include "TA_Entry.h"

#define CBT_ROOT 1

template<typename K, typename V>
class CompleteBinaryTree : public TA_Entry<K, V>
{
public:
	CompleteBinaryTree(int capa, string nm);
	int add_at_end(T_Entry<K, V>& elem);
	T_Entry<K, V>& getEndElement() { return this->t_GA[end]; }
	T_Entry<K, V>& getRootElement() { return this->t_GA[CBT_ROOT]; }
	int getEndIndex() { return end; }
	void removeCBTEnd();
	void fprintCBT(ostream& fout);
	void fprintCBT_byLevel(ostream& fout);
protected:
	void _printCBT_byLevel(ostream& fout, int idx, int level);
	int parentIndex(int index) { return index / 2; }
	int leftChildIndex(int index) { return index * 2; }
	int rightChildIndex(int index) { return (index * 2 + 1); }
	bool hasLeftChild(int index) { return ((index * 2) <= end); }
	bool hasRightChild(int index) { return ((index * 2 + 1) <= end); }
	int end;
};


template<typename K, typename V>
CompleteBinaryTree<K, V>::CompleteBinaryTree(int capa, string nm)
	:TA_Entry<K, V>(capa + 1, nm)
{
	end = 0;
}

template<typename K, typename V>
void CompleteBinaryTree<K, V>::fprintCBT(ostream& fout)
{
	if (end <= 0)
	{
		fout << this->getName() << " is empty now !!" << "\n";
		return;
	}

	int cnt = 0;
	for (int i = 1; i <= end; i++)
	{
		/*
		fout << setw(3);
		this->t_GA[i].print(fout);
		fout << "\n";
		*/
		
		fout << setw(3) << this->t_GA[i] << " ";
		if ((cnt + 1) % 3 == 0)
			fout << "\n";
		cnt++;
	}
}

template<typename K, typename V>
void CompleteBinaryTree<K, V>::_printCBT_byLevel(ostream& fout, int idx, int level)
{
	int index_child;

	if (hasRightChild(idx))
	{
		index_child = rightChildIndex(idx);
		_printCBT_byLevel(fout, index_child, level + 1);
	}

	for (int i = 0; i < level; i++)
		fout << "    ";

	this->t_GA[idx].print(fout);
	fout << "\n";

	if (hasLeftChild(idx))
	{
		index_child = leftChildIndex(idx);
		_printCBT_byLevel(fout, index_child, level + 1);
	}
}
template<typename K, typename V>
void CompleteBinaryTree<K, V>::fprintCBT_byLevel(ostream& fout)
{
	if (end <= 0)
	{
		fout << "CBT is EMPTY now !!" << endl;
		return;
	}
	_printCBT_byLevel(fout, CBT_ROOT, 0);
}
template<typename K, typename V>
int CompleteBinaryTree<K, V>::add_at_end(T_Entry<K, V>& elem)
{
	if (end >= this->capacity)
	{
		cout << this->getName() << " is FULL now !!" << endl;
		return end;
	}
	end++;
	this->t_GA[end] = elem;
	return end;
}
template<typename K, typename V>
void CompleteBinaryTree<K, V>::removeCBTEnd()
{
	end--;
	this->num_elements--;
}

#endif