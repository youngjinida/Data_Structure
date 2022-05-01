#ifndef HASHMAP_H
#define HASHMAP_H

#include <list>
#include <vector>


#include "MyVoca.h"
#include "T_Entry.h"
#include "CyclicShiftHashCode.h"
#define DEFAULT_HASH_TABLE_SIZE 101

using namespace std;

template<typename K, typename V>
class HashMap
{
public:
	typedef T_Entry<K, V> Entry;
	typedef list<Entry> Bucket;
	typedef vector<Bucket> BktArr;
	typedef typename BktArr::iterator B_Itr;
	typedef typename Bucket::iterator E_Itr;
	class Iterator;
public:
	HashMap(int cap = DEFAULT_HASH_TABLE_SIZE);
	HashMap() {}
	~HashMap() {}
	int getSize() const { return num_entry; }
	bool isEmpty() const { return (num_entry == 0); }
	Iterator find(const K& k);
	Iterator insert(const K& k, const V& v);
	void erase(const K& k);
	void earse(const Iterator& p);
	Iterator begin();
	Iterator end();
	void fprintBucketSizes(ostream& fout);
	void fprintBucket(ostream& fout, B_Itr bkt);

protected:
	Iterator _find(const K& k);
	Iterator _insert(const Iterator& p, const Entry& e);
	void _erase(const Iterator& p);
	static bool _endOfBkt(const Iterator& p) { return p.ent == p.bkt->end(); }	// ���� ��Ʈ���� �ٱ����� ������ �˻�
	class Iterator {
	public:
		Iterator(const BktArr& b_Arr, const B_Itr& b, const E_Itr& q = E_Itr())
			:bA(&b_Arr), bkt(b), ent(q) {}					// ���� ��Ŷ�� �� ��° ��Ŷ���� ��Ŷ���� �� ��° ��Ʈ������
		Iterator() {}
		~Iterator() {}
		Entry& operator*() const { return *ent; }			// itr�� ��ǥ�ϸ� ��Ʈ���� ��ȯ��!
		bool operator==(const Iterator& p) const
		{
			if (bA != p.bA || bkt != p.bkt) return false;	// �Ϲݺ��ڰ� ����Ű�� ���̶� ���ݺ��ڰ� ����Ű�� ���� ���ƾ���
			else if (bkt == bA->end()) return true;			// ���� �ٱ��ϰ� ������ �ٱ����� ��쵵 �±��ϴϱ�.... �׷��Ծƴұ�?
			else return (ent == p.ent());					// ���� �ϴ� ���� ���� if�� ���������ϱ� 
															// ���� ent�� p�� ent�� ����Ű�� ���� ���ٸ� ��������

		}
		bool operator!=(const Iterator& p) const
		{
			if (bA != p.bA || bkt != p.bkt) return true;
			else if (bkt == bA->end()) return false;
			else return (ent != p.ent);
		}
		// end()�� �ƹ��͵� �ȵ鰡�־�!
		Iterator& operator++()
		{
			++ent;																// ���� ent�� ������Ʈ���� ������!
			if (_endOfBkt(*this))												// ���� ��Ʈ���� ��Ŷ�� ���̾�? �׷�����
			{
				++bkt;															// ���� ��Ŷ�̳� ����!
				while (bkt != bA->end() && bkt->empty())						// ���� ��Ŷ�� ��Ŷ�� ���� �ƴϰ� ��Ŷ�� ����ִٸ�
					++bkt;														// ���� ��Ŷ�� ��!
				if (bkt == bA->end()) return *this;								// ���� ��Ŷ�� ���ٱ�? �׷� ��������.... ����!
				ent = bkt->begin();												// ���� ��Ŷ ó����Ʈ����!
			}
			return *this;
		}
		friend class HashMap;
	private:
		const BktArr* bA;
		B_Itr bkt;
		E_Itr ent;
	};
private:
	int num_entry;
	BktArr B;
};


template <typename K, typename V>
HashMap<K, V>::HashMap(int cap)
	:num_entry(0), B(cap) {}

template <typename K, typename V>
typename HashMap<K, V>::Iterator
HashMap<K, V>::begin()
{
	if (isEmpty())								// ���� ��Ʈ���� �ϳ��� ������ �����!
		return this->end();						// �̰ų� �Ծ�!
	B_Itr bkt = B.begin();						// ��Ŷ�� ó������!
	while (bkt->empty())
		++bkt;									// ��Ŷ�� ����ִٸ� ���� ��Ŷ����!
	return Iterator(B, bkt, bkt->begin());		// ���� ��Ŷ�� ��Ŷ�� ó���� ��Ŷ�� �������� ����..?
												// ��� �ù� �����̾�...�ФФФФФФФФФ�
}

template <typename K, typename V>
typename HashMap<K, V>::Iterator
HashMap<K, V>::end()
{
	return Iterator(B, B.end());				// �׳� ������ ������ ���尪�� �ִ°ű���! �̰� ��������!
}

template <typename K, typename V>
typename HashMap<K, V>::Iterator
HashMap<K, V>::_find(const K& k)
{
	CyclicShiftHashCode hash;					// �ؽ� �� ����� ����!
	int i = hash(k) % B.size();					// �ؽ� ���� ���� ��Ʈ���� ������ ������...? �ֱ׷��ž� �Ф�
	B_Itr bkt = B.begin() + i;					// Ű�� �ش��ϴ� �ٱ��ϸ� ����!
	Iterator p(B, bkt, bkt->begin());			// �ٱ����� ���ۺ��� �ؿ� ������ �ٱ����� ������ Ž����!
	while (!_endOfBkt(p) && (*p).getKey() != k)	// �� ��Ŷ�� ���� �ƴϸ鼭 �� ��Ŷ�� Ű�� ã�ƾ��ϴ� Ű�� ������ Ż��!
		++p.ent;
	return p;									// �ش��ϴ� �ݺ��ڸ� ����!
}

template <typename K, typename V>
typename HashMap<K, V>::Iterator
HashMap<K, V>::find(const K& k)
{
	Iterator p = _find(k);						// Ű�� �ش��ϴ� �ٱ��Ͽ� ���� k�� ������?
	if (_endOfBkt(p))							// �ƴ� ���� �Ф� �׳� �������� �ּҸ� ��ȯ��
		return end();
	else
		return p;								// �ٱ��Ͼȿ� k�� �ش��ϴ� �ְ� �̹� �־�!
}

template <typename K, typename V>
typename HashMap<K, V>::Iterator
HashMap<K, V>::_insert(const Iterator& p, const Entry& e)
{
	E_Itr ins = p.bkt->insert(p.ent, e);		// ����Ʈ�� p.ent ��°�� e�� ������!
	num_entry++;								// ���ڰ� �þ!
	return Iterator(B, p.bkt, ins);				// ��Ŷ��̾�� ���� ��Ŷ �׸��� ��Ʈ���� ��ȯ��!
}

template <typename K, typename V>
typename HashMap<K, V>::Iterator
HashMap<K, V>::insert(const K& k, const V& v)
{
	Iterator p = _find(k);							// Ű�� �ش��ϴ� �ٱ��Ͽ� �ٱ��Ͽ��� k�� ��ġ�� Ȯ��
	if (_endOfBkt(p))								// �ٱ��Ͽ� Ű�� �ش��ϴ� ���� ����?
	{
		return _insert(p, Entry(k, v));				// �ٱ����� �����ٰ� ��Ʈ�� k, v���� ����!
	}
	else
	{
		p.ent->setValue(v);							// �ٱ��Ͽ� �ش��ϴ� k ���� �����ϴϱ� �� k ���� ����?
		return p;									// �׷� ��ġ�� k���� ������ �ְ� ������ value�� �ٲ��!
	}
}

template <typename K, typename V>
void HashMap<K, V>::erase(const K& k)
{
	Iterator p = _find(k);
	if (_endOfBkt(p))
		return;
	_erase(p);
}

template <typename K, typename V>
void HashMap<K, V>::earse(const Iterator& p)
{
	_erase(p);
}


template <typename K, typename V>
void HashMap<K, V>::_erase(const Iterator& p)
{
	p.bkt->erase(p.ent);
	--num_entry;
}

template <typename K, typename V>
void HashMap<K, V>::fprintBucket(ostream& fout, B_Itr bkt)
{
	Iterator p(B, bkt, bkt->begin());
	V pVoca;
	while (p.ent != bkt->end())
	{
		pVoca = (*p).getValue();
		fout << *pVoca << "\n";
		++p.ent;
	}
}

template <typename K, typename V>
void HashMap<K, V>::fprintBucketSizes(ostream& fout)
{
	int bkt_size;
	int max_ent, min_ent, total;
	int num_bkts, max_bkt = 0;
	double avg = .0;
	max_ent = min_ent = B[0].size();				// 0��° �ٱ����� ũ��
	total = 0;
	num_bkts = B.size();
	for (int bkt = 0; bkt < num_bkts; ++bkt)
	{
		bkt_size = B[bkt].size();
		fout << "Bucket[" << setw(3) << bkt << "]: " << bkt_size << " entries\n";
		if (bkt_size > max_ent)
		{
			max_ent = bkt_size;
			max_bkt = bkt;
		}
		if (bkt_size < min_ent)
		{
			min_ent = bkt_size;
		}
		total += bkt_size;
	}
	avg = total / num_bkts;
	fout.precision(2);
	fout << "\nMax_ ent (" << setw(2) << max_ent << "), min_ent" << setw(2) << min_ent << "), avg ("
		<< setw(5) << avg << ")\n";

	fout << "Bucket with maximum (" << max_ent << ") entries: \n";
	B_Itr bkt = B.begin() + max_bkt;				// ���� ���� ����ִ� �ٱ����� �ּҸ� ��ȯ�ϰ�
	fprintBucket(fout, bkt);						// �� �ٱ��ϸ� ���
}


#endif