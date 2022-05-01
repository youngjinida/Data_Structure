#ifndef HPQ_H
#define HPQ_H
#include <Windows.h>
#include "CompleteBinaryTree.h"

template<typename K, typename V>
class HeapPrioQueue : public CompleteBinaryTree<K, V>
{
public:
	HeapPrioQueue(int capa, string nm)
		:CompleteBinaryTree<K, V>(capa, nm) {}
	~HeapPrioQueue() {}
	bool isEmpty() { return size() == 0; }
	bool isFull() { return size() == this->capacity; }
	int insert(T_Entry<K, V>& elem);
	T_Entry<K, V>* removeHeapMin();
	T_Entry<K, V>* getHeapMin();
	void fprintHeapQ(ostream& fout);
	int size() { return this->end; }
	void initCS(LPCRITICAL_SECTION cs) { this->pCS = cs; }
private:
	CRITICAL_SECTION* pCS;
};


template<typename K, typename V>
void HeapPrioQueue<K, V>::fprintHeapQ(ostream& fout)
{
	if (size() <= 0)
	{
		fout << "HeapPriorityQueue is Empty !!" << endl;
		return;
	}
	else
	{
		this->fprintCBT(fout);
	}
}

template<typename K, typename V>
int HeapPrioQueue<K, V>::insert(T_Entry<K, V>& elem)
{
	int index, parent_index;
	T_Entry<K, V> temp;
	if (isFull())
	{
		cout << this->getName() << " is Full !!" << endl;
		return size();
	}
	index = this->add_at_end(elem);

	while (index != CBT_ROOT) {
		parent_index = this->parentIndex(index);
		if (this->t_GA[index].getKey() > this->t_GA[parent_index].getKey())
			break;
		else {
			temp = this->t_GA[index];
			this->t_GA[index] = this->t_GA[parent_index];
			this->t_GA[parent_index] = temp;
			index = parent_index;
		}
	}
	return size();
}

template<typename K, typename V>
T_Entry<K, V>* HeapPrioQueue<K, V>::getHeapMin()
{
	T_Entry<K, V>* pMinElem;
	if (size() <= 0)
	{
		return NULL;
	}
	pMinElem = (T_Entry<K, V>*) new T_Entry<K, V>;
	*pMinElem = this->getRootElement();
	return pMinElem;
}

template<typename K, typename V>
T_Entry<K, V>* HeapPrioQueue<K, V>::removeHeapMin()
{
	int idx_p, idx_c, idx_rc;
	T_Entry<K, V>* pMinElem;
	T_Entry<K, V> temp, t_p, t_c;
	int HPQ_size = size();
	if (HPQ_size <= 0)
		return NULL;

	pMinElem = (T_Entry<K, V>*) new T_Entry<K, V>;
	*pMinElem = this->getRootElement();

	if (HPQ_size == 1)
	{
		this->removeCBTEnd();
	}
	else
	{
		idx_p = CBT_ROOT;
		this->t_GA[idx_p] = this->t_GA[this->end];
		this->end--;

		while (this->hasLeftChild(idx_p))
		{
			idx_c = this->leftChildIndex(idx_p);
			idx_rc = this->rightChildIndex(idx_p);
			if (this->hasRightChild(idx_p) && (this->t_GA[idx_c] > this->t_GA[idx_rc]))
				idx_c = idx_rc;
			t_p = this->t_GA[idx_p];
			t_c = this->t_GA[idx_c];
			if (t_p > t_c)
			{
				temp = this->t_GA[idx_p];
				this->t_GA[idx_p] = this->t_GA[idx_c];
				this->t_GA[idx_c] = temp;
				idx_p = idx_c;
			}
			else
				break;
		}
	}
	return pMinElem;
}
#endif