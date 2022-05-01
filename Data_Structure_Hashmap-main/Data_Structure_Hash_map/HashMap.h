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
	static bool _endOfBkt(const Iterator& p) { return p.ent == p.bkt->end(); }	// 들어온 엔트리가 바구니의 끝인지 검색
	class Iterator {
	public:
		Iterator(const BktArr& b_Arr, const B_Itr& b, const E_Itr& q = E_Itr())
			:bA(&b_Arr), bkt(b), ent(q) {}					// 현재 버킷과 몇 번째 버킷인지 버킷에서 몇 번째 엔트리인지
		Iterator() {}
		~Iterator() {}
		Entry& operator*() const { return *ent; }			// itr에 별표하면 엔트리를 반환해!
		bool operator==(const Iterator& p) const
		{
			if (bA != p.bA || bkt != p.bkt) return false;	// 니반복자가 가르키는 곳이랑 내반복자가 가르키는 곳이 같아야해
			else if (bkt == bA->end()) return true;			// 현재 바구니가 마지막 바구니인 경우도 맞긴하니까.... 그런게아닐까?
			else return (ent == p.ent());					// 현재 일단 제일 위에 if가 충족됬으니까 
															// 지금 ent와 p의 ent가 가르키는 곳이 같다면 같은거지

		}
		bool operator!=(const Iterator& p) const
		{
			if (bA != p.bA || bkt != p.bkt) return true;
			else if (bkt == bA->end()) return false;
			else return (ent != p.ent);
		}
		// end()는 아무것도 안들가있어!
		Iterator& operator++()
		{
			++ent;																// 현재 ent를 다음엔트리로 변경해!
			if (_endOfBkt(*this))												// 현재 엔트리가 버킷의 끝이야? 그럼씨팔
			{
				++bkt;															// 다음 버킷이나 보자!
				while (bkt != bA->end() && bkt->empty())						// 현재 버킷이 버킷의 끝이 아니고 버킷이 비어있다면
					++bkt;														// 다음 버킷을 봐!
				if (bkt == bA->end()) return *this;								// 다음 버킷이 없다구? 그럼 끝이지뭐.... 리턴!
				ent = bkt->begin();												// 다음 버킷 처음엔트리야!
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
	if (isEmpty())								// 현재 엔트리가 하나도 없으면 빈거지!
		return this->end();						// 이거나 먹어!
	B_Itr bkt = B.begin();						// 버킷의 처음으로!
	while (bkt->empty())
		++bkt;									// 버킷이 비어있다면 다음 버킷으로!
	return Iterator(B, bkt, bkt->begin());		// 현재 버킷과 버킷의 처음과 버킷의 마지막을 리턴..?
												// 놀래라 시발 다행이야...ㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠ
}

template <typename K, typename V>
typename HashMap<K, V>::Iterator
HashMap<K, V>::end()
{
	return Iterator(B, B.end());				// 그냥 못쓰는 마지막 엔드값을 주는거구나! 이건 이해좀가!
}

template <typename K, typename V>
typename HashMap<K, V>::Iterator
HashMap<K, V>::_find(const K& k)
{
	CyclicShiftHashCode hash;					// 해쉬 값 만드는 변수!
	int i = hash(k) % B.size();					// 해쉬 값에 현재 엔트리의 갯수를 나머지...? 왜그런거야 ㅠㅠ
	B_Itr bkt = B.begin() + i;					// 키에 해당하는 바구니를 선택!
	Iterator p(B, bkt, bkt->begin());			// 바구니의 시작부터 밑에 와일은 바구니의 끝까지 탐색해!
	while (!_endOfBkt(p) && (*p).getKey() != k)	// 이 버킷의 끝이 아니면서 이 버킷의 키가 찾아야하는 키와 같으면 탈출!
		++p.ent;
	return p;									// 해당하는 반복자를 리턴!
}

template <typename K, typename V>
typename HashMap<K, V>::Iterator
HashMap<K, V>::find(const K& k)
{
	Iterator p = _find(k);						// 키에 해당하는 바구니에 원소 k가 존재해?
	if (_endOfBkt(p))							// 아니 없어 ㅠㅠ 그냥 마지막의 주소를 반환해
		return end();
	else
		return p;								// 바구니안에 k에 해당하는 애가 이미 있어!
}

template <typename K, typename V>
typename HashMap<K, V>::Iterator
HashMap<K, V>::_insert(const Iterator& p, const Entry& e)
{
	E_Itr ins = p.bkt->insert(p.ent, e);		// 리스트에 p.ent 번째에 e를 삽입해!
	num_entry++;								// 숫자가 늘어나!
	return Iterator(B, p.bkt, ins);				// 버킷어레이어와 현재 버킷 그리고 엔트리를 반환해!
}

template <typename K, typename V>
typename HashMap<K, V>::Iterator
HashMap<K, V>::insert(const K& k, const V& v)
{
	Iterator p = _find(k);							// 키에 해당하는 바구니와 바구니에서 k의 위치를 확인
	if (_endOfBkt(p))								// 바구니에 키에 해당하는 값이 없네?
	{
		return _insert(p, Entry(k, v));				// 바구니의 끝에다가 엔트리 k, v값을 삽임!
	}
	else
	{
		p.ent->setValue(v);							// 바구니에 해당하는 k 값이 존재하니까 이 k 값에 삽입?
		return p;									// 그럼 겹치는 k값을 가지는 애가 들어오면 value가 바뀌네!
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
	max_ent = min_ent = B[0].size();				// 0번째 바구니의 크기
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
	B_Itr bkt = B.begin() + max_bkt;				// 제일 많이 담겨있는 바구니의 주소를 반환하고
	fprintBucket(fout, bkt);						// 그 바구니를 출력
}


#endif