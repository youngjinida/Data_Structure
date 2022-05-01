#ifndef HASH_DICTIONARY_H
#define HASH_DICTIONARY_H

#include "HashMap.h"

#define HASH_TABLE_SIZE 101

template<typename K, typename V>
class HashDict :public HashMap<K, V> {
public:
	typedef typename HashMap<K, V>::Iterator Iterator;
	typedef typename HashMap<K, V>::Entry Entry;
	class Range {
	private:
		Iterator _begin;
		Iterator _end;
	public:
		Range() {}
		Range(const Iterator& b, const Iterator& e)
			:_begin(b), _end(e) {}
		Iterator& begin() { return _begin; }
		Iterator& end() { return _end; }
	};
public:
	HashDict(int cap = HASH_TABLE_SIZE);
	Range findAll(const K& k);
	Iterator insert(const K& k, const V& v);
};


template<typename K,typename V>
HashDict<K,V>::HashDict(int cap)
	:HashMap<K, V>(cap) {}

template<typename K, typename V>
typename HashDict<K,V>::Iterator
HashDict<K, V>::insert(const K& k, const V& v)
{
	Iterator p = this->_find(k);
	Iterator q = this->_insert(p, Entry(k, v));
	return q;
}

template<typename K, typename V>
typename HashDict<K, V>::Range
HashDict<K, V>::findAll(const K& k)
{
	Iterator b = this->_find(k);
	Iterator p = b;
	
	while ((p != this->end()) && ((*p).getKey() == k))
	{
		++p;
	}
	return Range(b, p);
}

#endif // !HASH_DICTIONARY_H

