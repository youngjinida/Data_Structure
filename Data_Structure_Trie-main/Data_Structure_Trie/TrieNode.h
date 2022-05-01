#ifndef TRIE_NODE_H
#define TRIE_NODE_H

#include <iostream>
#include <string>
#include <list>
#define VALUE_INTERNEAL_NODE ""
using namespace std;

typedef list<string> STL_list;

template <typename E>
class TrieNode
{
public:
	TrieNode() {}
	TrieNode(char k, E v)
		:_key(k), _value(v)
	{
		_prev = _next = _parent = _child = NULL;
	}
	void setKey(char& k) { _key = k; }
	void setValue(E& v) { _value = v; }
	void setPrev(TrieNode<E>* prev) { _prev = prev; }
	void setNext(TrieNode<E>* next) { _next = next; }
	void setParent(TrieNode<E>* parent) { _parent = parent; }
	void setChild(TrieNode<E>* child) { _child = child; }
	char getKey()const { return _key; }
	E getValue()const { return _value; }
	TrieNode<E>* getPrev()const { return _prev; }
	TrieNode<E>* getNext()const { return _next; }
	TrieNode<E>* getParent()const { return _parent; }
	TrieNode<E>* getChild()const { return _child; }
	void _fprint(ostream& fout, TrieNode<E>* pTN, int indent);
private:
	char _key;
	E _value;
	TrieNode<E>* _prev;
	TrieNode<E>* _next;
	TrieNode<E>* _parent;
	TrieNode<E>* _child;
};
template<typename E>
void TrieNode<E>::_fprint(ostream& fout, TrieNode<E>* pTN, int indent)
{
	if (pTN == NULL)
	{
		fout << "\n";
		return;
	}
	else
	{
		fout << pTN->getKey();
		_fprint(fout, pTN->getChild(), indent + 1);
		if (pTN->getNext() == NULL)
			return;
		for (int i = 0; i < indent; ++i)
			fout << " ";
		_fprint(fout, pTN->getNext(), indent);
	}

}
#endif