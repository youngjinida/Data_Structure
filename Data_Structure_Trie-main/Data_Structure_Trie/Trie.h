#ifndef TRIE_H
#define TRIE_H
#include "TrieNode.h"

#define MAX_STR_LEN 50

using namespace std;

typedef list<string>::iterator STL_list_itr;
enum SearchMode { FULL_MATCH, PREFIX_MATCH };

template<typename E>
class Trie
{
public:
	Trie() {}
	~Trie() {}
	Trie(string name);
	void insertExternalTN(TrieNode<E>* pTN, const char* keyword, E value);
	void insert(const char* keyword, E value);
	TrieNode<E>* find(const char* keyword);
	void findPrefixMatch(const char* pPrefix, STL_list& predictWords);
	void deleteKeyword(const char* keyword);
	void eraseTrie();
	void fprintTrie(ostream& fout);
protected:
	TrieNode<E>* _find(const char* keyword, SearchMode sm = FULL_MATCH);
	void _traverse(TrieNode<E>* pTN, STL_list& list_keywords);
private:
	TrieNode<E>* _root;
	int num_keys;
	string trie_name;

};

template<typename E>
Trie<E>::Trie(string name)
{
	trie_name = name;
	_root = new TrieNode<E>('\0', "");
	num_keys = 0;
}

template<typename E>
TrieNode<E>* Trie<E>::_find(const char* keyword, SearchMode sm)
{
	const char* keyPtr;
	TrieNode<E>* pTN, * found;
	if (keyword == NULL)
		return NULL;

	keyPtr = keyword;
	pTN = this->_root;
	while ((pTN != NULL) && (*keyPtr != '\0'))
	{
		while ((pTN != NULL) && (pTN->getKey() < *keyPtr))
		{
			if (pTN -> getNext() == NULL)
				return NULL;
			pTN = pTN->getNext();
		}
		if ((pTN != NULL) && (pTN->getKey() > *keyPtr))
			return NULL;
		else if (pTN == NULL)
			return NULL;
		else if ((pTN->getKey() == *keyPtr) && (*keyPtr != '\0'))
		{
			pTN = pTN->getChild();
			keyPtr++;
			if (*keyPtr == '\0')
			{
				if (sm == FULL_MATCH)
				{
					if (pTN->getKey() == '\0')
						return pTN;
					else
						return NULL;
				}
				else if (sm == PREFIX_MATCH)
				{
					return pTN;
				}
			}
			else if ((pTN->getKey() == '\0') && (*keyPtr != '\0'))
			{
				if (pTN->getNext() != NULL)
				{
					pTN = pTN->getNext();
					continue;
				}
				else
					return NULL;
			}
			else
				continue;
		}
	}
}

template<typename E>
TrieNode<E>* Trie<E>::find(const char* keyword)
{
	TrieNode<E>* pTN = NULL;
	pTN = _find(keyword, FULL_MATCH);
	return pTN;
}

template<typename E>
void Trie<E>::insertExternalTN(TrieNode<E>* pTN, const char* keyword, E value)
{
	TrieNode<E>* pTN_New = NULL;

	pTN_New = new TrieNode<E>('\0', value);
	pTN->setChild(pTN_New);
	(pTN->getChild())->setParent(pTN);
}

template<typename E>
void Trie<E>::insert(const char* keyword, E value)
{
	TrieNode<E>* pTN = NULL, * pTN_New = NULL;
	char keyWording[MAX_STR_LEN];
	const char* keyPtr = keyword;
	if (keyword == NULL)
		return;
	
	if (_find(keyword, FULL_MATCH) != NULL) // 중복되는 단어가 이미 있는가를 검증
		return;

	pTN = this->_root;
	while ((pTN != NULL) && (*keyPtr != '\0'))
	{
		if ((pTN->getKey() < *keyPtr) && (pTN->getNext() == NULL) && (*keyPtr != '\0'))
			break;
		while ((pTN->getKey() < *keyPtr) && (pTN->getNext() != NULL))
			pTN = pTN->getNext();
		while ((pTN != NULL) && (pTN->getKey() == *keyPtr) && (*keyPtr != '\0'))
		{
			pTN = pTN->getChild();
			keyPtr++;
		}
		if ((pTN->getKey() > *keyPtr) && (*keyPtr != '\0'))
			break;
	}

	if ((pTN->getKey() != '\0') && (*keyPtr == '\0'))
	{
		pTN_New = new TrieNode<E>('\0', value);
		pTN_New->setParent(pTN->getParent());
		(pTN_New->getParent())->setChild(pTN_New);
		pTN_New->setNext(pTN);
		pTN->setPrev(pTN_New);
		this->num_keys++;
		return;
	}
	else if ((pTN->getKey() < *keyPtr) && (pTN->getNext() == NULL) && (*keyPtr != '\0'))
	{
		pTN_New = new TrieNode<E>(*keyPtr, VALUE_INTERNEAL_NODE);
		pTN_New->setParent(pTN->getParent());
		pTN_New->setPrev(pTN);
		pTN->setNext(pTN_New);
		pTN = pTN_New;
		keyPtr++;
		while (*keyPtr != '\0')
		{
			pTN_New = new TrieNode<E>(*keyPtr, VALUE_INTERNEAL_NODE);
			pTN->setChild(pTN_New);
			pTN_New->setParent(pTN);
			pTN = pTN->getChild();
			keyPtr++;
		}
		if (*keyPtr == '\0')
		{
			insertExternalTN(pTN, keyword, value);
			this->num_keys++;
			return;
		}
	}
	else if ((pTN->getKey() > *keyPtr) && (*keyPtr != '\0'))
	{
		pTN_New = new TrieNode<E>(*keyPtr, VALUE_INTERNEAL_NODE);
		pTN_New->setParent(pTN->getParent());
		pTN_New->setNext(pTN);
		if (pTN->getPrev() == NULL)
		{
			if (pTN->getParent() != NULL)
				(pTN->getParent())->setChild(pTN_New);
		}
		else
		{
			(pTN->getPrev())->setNext(pTN_New);
		}
		pTN_New->setPrev(pTN->getPrev());
		pTN->setPrev(pTN_New);

		pTN = pTN_New;
		keyPtr++;
		while (*keyPtr != '\0')
		{
			pTN_New = new TrieNode<E>(*keyPtr, VALUE_INTERNEAL_NODE);
			pTN->setChild(pTN_New);
			pTN_New->setParent(pTN);
			pTN = pTN->getChild();
			keyPtr++;
		}
		if (*keyPtr == '\0')
		{
			insertExternalTN(pTN, keyword, value);
			this->num_keys++;
			return;
		}
	}

}

template<typename E>
void Trie<E>::_traverse(TrieNode<E>* pTN, STL_list& list_keywords)
{
	if (pTN == NULL)
		return;
	if (pTN->getChild() == NULL)
		list_keywords.push_back(pTN->getValue());
	else
		_traverse(pTN->getChild(), list_keywords);

	if (pTN->getNext() != NULL)
		_traverse(pTN->getNext(), list_keywords);
}

template<typename E>
void Trie<E>::findPrefixMatch(const char* pPrefix, STL_list& predictWords)
{
	TrieNode<E>* pTN = NULL;
	if (pPrefix == NULL)
		return;

	pTN = _find(pPrefix, PREFIX_MATCH);
	_traverse(pTN, predictWords);
}

template<typename E>
void Trie<E>::deleteKeyword(const char* keyword)
{
	TrieNode<E>* pTN = NULL, * root;
	TrieNode<E>* temp = NULL;
	int trie_val;
	
	if (NULL == _root || NULL == keyword)
		return;

	pTN = _find(keyword, FULL_MATCH);
	if (pTN == NULL)
	{
		cout << "Key [" << keyword << "] not found in trie\n";
		return;
	}

	while (true)
	{
		if (pTN == NULL)
			break;

		if ((pTN->getPrev() != NULL) && (pTN->getNext() != NULL))
		{
			temp = pTN;
			(pTN->getNext())->setPrev(pTN->getPrev());
			(pTN->getPrev())->setNext(pTN->getNext());

			delete temp;
			break;
		}
		else if ((pTN->getPrev() == NULL) && (pTN->getNext() != NULL))
		{
			temp = pTN;
			(pTN->getParent())->setChild(pTN->getNext());
			(pTN->getNext())->setPrev(NULL);
			
			delete temp;
			break;
		}
		else if ((pTN->getPrev() != NULL) && (pTN->getNext() == NULL))
		{
			temp = pTN;
			(pTN->getPrev())->setNext(NULL);

			delete temp;
			break;
		}
		else
		{
			temp = pTN;
			pTN = pTN->getParent();
			if (pTN != NULL)
				pTN->setChild(NULL);

			delete temp;
			break;
		}
	}
	this->num_keys--;
}

template<typename E>
void Trie<E>::eraseTrie()
{
	TrieNode<E>* pTN;
	TrieNode<E>* pTN_to_be_delete = NULL;

	if (this->_root == NULL)
		return;
	pTN = this->_root;

	while (pTN != NULL)
	{
		while ((pTN != NULL) && (pTN->getNext() != NULL))
			pTN = pTN->getNext();

		while (pTN->getChild() != NULL)
		{
			if (pTN->getNext() != NULL)
				break;
			pTN = pTN->getChild();
		}

		if (pTN->getNext() != NULL)
			continue;

		if (pTN->getPrev() != NULL)
		{
			pTN_to_be_delete = pTN;
			(pTN->getPrev())->setNext(NULL);
			pTN = pTN->getPrev();

			delete pTN_to_be_delete;
		}
		else
		{
			pTN_to_be_delete = pTN;
			if (pTN == this->_root)
			{
				this->num_keys = 0;
				return;
			}

			if (pTN->getParent() != NULL)
			{
				pTN = pTN->getParent();
				pTN->setChild(NULL);
			}

			delete pTN_to_be_delete;
		}
	}
}

template<typename E>
void Trie<E>::fprintTrie(ostream& fout)
{
	TrieNode<E>* pTN;
	int indent = 0;
	fout << "trie (" << this->trie_name << ") with " << this->num_keys << " trie_nodes\n";

	if (this->num_keys == 0)
	{
		fout << "Empty Trie !\n";
		return;
	}
	pTN = this->_root;
	pTN->_fprint(fout, pTN, indent);
}
#endif
