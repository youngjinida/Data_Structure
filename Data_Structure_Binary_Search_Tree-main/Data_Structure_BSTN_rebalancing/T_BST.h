#ifndef T_BST_H
#define T_BST_H

#include "T_BSTN.h"
#include "T_Entry.h"
#include "T_Array.h"
#include <iostream>

using namespace std;

template<typename K, typename V>
class T_BST
{
public:
	T_BST() {}
	~T_BST() {}
	T_BST(string nm) :_root(NULL), num_entry(0), name(nm) {}
	string getName() { return name; }
	int getSize() const { return num_entry; }
	bool isEmpty() const { return (num_entry == 0); }
	void clear();
	T_BSTN<K, V>* getRoot() { return _root; }
	T_BSTN<K, V>** getRootAddr() { return &_root; }
	T_Entry<K, V>& getRootEntry() { return _root->getEntry(); }
	T_BSTN<K, V>* eraseBSTN(T_BSTN<K, V>** pp);
	void insertInOrder(const T_Entry<K, V> e);
	void insertAndRebalance(T_Entry<K, V> e);
	void traversal_inOrder(T_BSTN<K, V>* p, T_Array<V>& array_value);
	void traversal_preOrder(T_BSTN<K, V>* p, T_Array<V>& array_value);
	void traversal_postOrder(T_BSTN<K, V>* p, T_Array<V>& array_value);
	
	T_BSTN<K, V>* searchBSTN(K k);
	V searchBST(K k);

	T_Entry<K, V>& minEntry();
	T_Entry<K, V>& maxEntry();
	void fprint_with_Depth(ostream& fout);
	void fprint_inOrder(ostream& fout);

protected:
	T_BSTN<K, V>* _maxBSTN(T_BSTN<K, V>* subRoot);
	T_BSTN<K, V>* _minBSTN(T_BSTN<K, V>* subRoot);
	T_BSTN<K, V>* _insertInOrder(T_BSTN<K, V>** pp, T_BSTN<K, V>* parenPos, const T_Entry<K, V> e);
	T_BSTN<K, V>* _insertAndRebalance(T_BSTN<K, V>** ppTN, 
		T_BSTN<K, V>* pPr, T_Entry<K, V> e);
	T_BSTN<K, V>* _rotate_LL(T_BSTN<K, V>* pCurSubRoot);
	T_BSTN<K, V>* _rotate_RL(T_BSTN<K, V>* pCurSubRoot);
	T_BSTN<K, V>* _rotate_LR(T_BSTN<K, V>* pCurSubRoot);
	T_BSTN<K, V>* _rotate_RR(T_BSTN<K, V>* pCurSubRoot);
	T_BSTN<K, V>* _rebalance(T_BSTN<K, V>** ppTN);
	T_BSTN<K, V>* _searchBSTN(T_BSTN<K, V>* pos, K k);
	int _getHeight(T_BSTN<K, V>* pTN);
	int _getHeightDiff(T_BSTN<K, V>* pTN);
	void _fprint_with_Depth(T_BSTN<K, V>* pTN, ostream& fout, int depth);
	void _fprint_inOrder(T_BSTN<K, V>* pTN, ostream& fout);

private:
	T_BSTN<K, V>* _root;
	int num_entry;
	string name;
};



template<typename K, typename V>
void T_BST<K, V>::traversal_inOrder(T_BSTN<K, V>* p, T_Array<V>& array_value)
{
	T_BSTN<K, V>* pLc, * pRc;
	T_Entry<K, V> entry;
	V value;
	if (p == NULL)
		return;
	pLc = p->getpLc();
	pRc = p->getpRc();
	traversal_inOrder(pLc, array_value);
	entry = p->getEntry();
	value = entry.getValue();
	array_value.insertBack(value);
	traversal_inOrder(pRc, array_value);
}

template<typename K, typename V>
void T_BST<K, V>::traversal_preOrder(T_BSTN<K, V>* p, T_Array<V>& array_value)
{
	T_BSTN<K, V>* pLc, * pRc;
	T_Entry<K, V> entry;
	V value;
	if (p == NULL)
		return;
	pLc = p->getpLc();
	pRc = p->getpRc();
	entry = p->getEntry();
	value = entry.getValue();
	array_value.insertBack(value);

	traversal_preOrder(pLc, array_value);
	traversal_preOrder(pRc, array_value);
}

template<typename K, typename V>
void T_BST<K, V>::traversal_postOrder(T_BSTN<K, V>* p, T_Array<V>& array_value)
{
	T_BSTN<K, V>* pLc, * pRc;
	T_Entry<K, V> entry;
	V value;
	if (p == NULL)
		return;
	pLc = p->getpLc();
	pRc = p->getpRc();
	traversal_postOrder(pLc, array_value);
	traversal_postOrder(pRc, array_value);

	entry = p->getEntry();
	value = entry.getValue();
	array_value.insertBack(value);
}

template <typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::searchBSTN(K k)
{
	T_BSTN<K, V>* pEntry;
	pEntry = _searchBSTN(_root, k);
	return pEntry;
}

template <typename K, typename V>
V T_BST<K, V>::searchBST(K k)
{
	T_BSTN<K, V>* pEntry;
	V value;

	pEntry = _searchBSTN(_root, k);
	value = pEntry->getValue();
	return value;
}

template <typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_searchBSTN(T_BSTN<K, V>* pos, K k)
{
	K ent_k;
	T_BSTN<K, V>* pos_result = NULL;
	
	if (pos == NULL)
		return NULL;

	ent_k = pos->getKey();
	if (ent_k == k)
		pos_result = pos;
	else if (ent_k > k)
		pos_result = _searchBSTN(pos->getpLc(), k);
	else if (ent_k < k)
		pos_result = _searchBSTN(pos->getpRc(), k);

	return pos_result;
}

template <typename K, typename V>
T_Entry<K, V>& T_BST<K, V>::maxEntry()
{
	T_BSTN<K, V>* pMax;
	pMax = _maxBSTN(_root);
	return pMax->getEntry();
}

template <typename K, typename V>
T_Entry<K, V>& T_BST<K, V>::minEntry()
{
	T_BSTN<K, V>* pMin;
	pMin = _minBSTN(_root);
	return pMin->getEntry();
}

template <typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_maxBSTN(T_BSTN<K, V>* subRoot)
{
	T_BSTN<K, V>* pos, * pLc;
	if ((subRoot == NULL) || (NULL == subRoot->getpRc()))
		return subRoot;
	pos = subRoot;
	while ((pos->getpRc()) != NULL)
		pos = pos->getpRc();
	return pos;
}

template <typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_minBSTN(T_BSTN<K, V>* subRoot)
{
	T_BSTN<K, V>* pos, * pLc;
	if ((subRoot == NULL) || (NULL == subRoot->getpLc()))
		return subRoot;
	pos = subRoot;
	while ((pos->getpLc()) != NULL)
		pos = pos->getpLc();
	return pos;
}

template <typename K, typename V>
void T_BST<K, V>::_fprint_inOrder(T_BSTN<K, V>* pTN, ostream& fout)
{
	T_BSTN<K, V>* pRc, * pLc;
	pLc = pTN->getpLc();
	pRc = pTN->getpRc();
	if (pLc != NULL)
		_fprint_inOrder(pLc, fout);
	fout << pTN->getEntry << "\n";
	if (pRc != NULL)
		_fprint_inOrder(pRc, fout);
}

template <typename K, typename V>
void T_BST<K, V>::fprint_inOrder(ostream& fout)
{
	T_BSTN<K, V>* root = getRoot();
	if (num_entry == 0)
	{
		fout << getName() << " is empty now !!\n";
		return;
	}
	_fprint_inOrder(root, fout);
}

template <typename K, typename V>
void T_BST<K, V>::_fprint_with_Depth(T_BSTN<K, V>* pTN, ostream& fout, int depth)
{
	T_BSTN<K, V>* pRc, * pLc;
	//T_Entry<K, V> pEntry;
	pRc = pTN->getpRc();
	pLc = pTN->getpLc();

	if (pRc != NULL)
		_fprint_with_Depth(pRc, fout, depth + 1);

	for (int i = 0; i < depth; ++i)
		fout << "   ";
	//pEntry = pTN->getEntry();
	fout << pTN->getEntry() << "\n";

	if (pLc != NULL)
		_fprint_with_Depth(pLc, fout, depth + 1);
}

template <typename K, typename V>
void T_BST<K, V>::fprint_with_Depth(ostream& fout)
{
	T_BSTN<K, V>* root = getRoot();
	if (num_entry == 0)
	{
		fout << getName() << "is Empty!!\n";
		return;
	}
	_fprint_with_Depth(root, fout, 0);
}

template<typename K, typename V>
int T_BST<K, V>::_getHeight(T_BSTN<K, V>* pTN)
{
	int height = 0;
	int height_Lc, height_Rc;
	if (pTN != NULL)
	{
		height_Lc = _getHeight(pTN->getpLc());
		height_Rc = _getHeight(pTN->getpRc());
		if (height_Lc > height_Rc)
			height = 1 + height_Lc;
		else
			height = 1 + height_Rc;
	}
	return height;
}

template<typename K, typename V>
int T_BST<K, V>::_getHeightDiff(T_BSTN<K, V>* pTN)
{
	int height_Diff = 0;
	if (pTN == NULL)
		return 0;
	height_Diff = _getHeight(pTN->getpLc()) - _getHeight(pTN->getpRc());
	return height_Diff;
}

template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::eraseBSTN(T_BSTN<K, V>** pp)
{
	T_BSTN<K, V>* newSubRoot = NULL, * temp, * w, * wLc;
	T_BSTN<K, V>* toBeErased;
	
	toBeErased = *pp;
	if (toBeErased == NULL)
		return NULL;
	if ((toBeErased->getpLc() == NULL) && (toBeErased->getpRc() == NULL))
	{
		newSubRoot = NULL;
	}
	else if ((toBeErased->getpLc() != NULL) && (toBeErased->getpRc() == NULL))
	{
		newSubRoot = toBeErased->getpLc();
		newSubRoot->setpPr(toBeErased->getpPr());
	}
	else if ((toBeErased->getpLc() == NULL) && (toBeErased->getpRc() != NULL))
	{
		newSubRoot = toBeErased->getpRc();
		newSubRoot->setpPr(toBeErased->getpPr());
	}
	else
	{
		int height_Diff = _getHeightDiff(toBeErased);
		T_BSTN<K, V>* pPr, * pLc, * pRc;
		T_BSTN<K, V>* pIoPd = NULL, *pIoPdLc, *pIoPdPr;
		T_BSTN<K, V>* pIoSs = NULL, * pIoSsRc, * pIoSsPr;
		pPr = toBeErased->getpPr();
		pLc = toBeErased->getpLc();
		pRc = toBeErased->getpRc();

		if (height_Diff > 0)
		{
			pIoPd = _maxBSTN(pLc);
			pIoPdLc = pIoPd->getpLc();
			pIoPdPr = pIoPd->getpPr();
			newSubRoot = pIoPd;

			if (pIoPd->getpPr() != toBeErased)
			{
				newSubRoot->setpLc(pLc);
				pIoPdPr->setpRc(pIoPdLc);
				if (pIoPdLc != NULL)
					pIoPdLc->setpPr(pIoPdPr);
			}
			newSubRoot->setpRc(pRc);
			newSubRoot->setpPr(pPr);
		}
		else
		{
			pIoSs = _minBSTN(pRc);
			pIoSsRc = pIoSs->getpRc();
			pIoSsPr = pIoSs->getpPr();
			newSubRoot = pIoSs;

			if (pIoSs->getpPr() != toBeErased)
			{
				newSubRoot->setpRc(pRc);
				pIoSsPr->setpLc(pIoSsRc);
				if (pIoSsRc != NULL)
					pIoSsRc->setpPr(pIoSsPr);
			}
			newSubRoot->setpLc(pLc);
			newSubRoot->setpPr(pPr);
		}

		if (pLc != pIoPd)
			pLc->setpPr(newSubRoot);

		if (pRc != pIoSs)
			pRc->setpPr(newSubRoot);
	}
	if (toBeErased == _root)
		_root = newSubRoot;
	delete toBeErased;
	*pp = newSubRoot;
	num_entry--;
	return newSubRoot;
}

template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_rotate_LL(T_BSTN<K, V>* pCurSubRoot)
{
	T_BSTN<K, V>* pNewSubRoot, * pBR, * pCurParent;
	pCurParent = pCurSubRoot->getpPr();
	pNewSubRoot = pCurSubRoot->getpLc();
	pBR = pNewSubRoot->getpRc();
	pCurSubRoot->setpLc(pBR);
	if (pBR != NULL)
		pBR->setpPr(pCurSubRoot);
	pNewSubRoot->setpRc(pCurSubRoot);
	pNewSubRoot->setpPr(pCurParent);
	pCurSubRoot->setpPr(pNewSubRoot);
	return pNewSubRoot;
}

template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_rotate_RR(T_BSTN<K, V>* pCurSubRoot)
{
	T_BSTN<K, V>* pNewSubRoot, * pBL, * pCurParent;
	pCurParent = pCurSubRoot->getpPr();
	pNewSubRoot = pCurSubRoot->getpRc();
	pBL = pNewSubRoot->getpLc();
	pCurSubRoot->setpRc(pBL);
	if (pBL != NULL)
		pBL->setpPr(pCurSubRoot);
	pNewSubRoot->setpLc(pCurSubRoot);
	pNewSubRoot->setpPr(pCurParent);
	pCurSubRoot->setpPr(pNewSubRoot);
	return pNewSubRoot;
}

template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_rotate_LR(T_BSTN<K, V>* pCurSubRoot)
{
	T_BSTN<K, V>* pSubRoot, * pNewSubRoot, * pCurParent;
	T_BSTN<K, V>* pA, * pB, * pC, * pBL, *pBR;

	pC = pCurSubRoot;
	pCurParent = pCurSubRoot->getpPr();
	pA = pC->getpLc();
	pB = pA->getpRc();
	pBL = pB->getpLc();
	pBR = pB->getpRc();
	pSubRoot = _rotate_RR(pA);
	pC->setpLc(pSubRoot);
	pNewSubRoot = _rotate_LL(pSubRoot);
	/*
	pNewSubRoot->setpPr(pCurParent);
	
	pA->setpPr(pNewSubRoot);
	pC->setpPr(pNewSubRoot);
	if (pBL != NULL)
		pBL->setpPr(pA);
	if (pBR != NULL)
		pBR->setpPr(pA);
	*/
	return pNewSubRoot;
}

template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_rotate_RL(T_BSTN<K, V>* pCurSubRoot)
{
	T_BSTN<K, V>* pSubRoot, * pNewSubRoot, * pCurParent;
	T_BSTN<K, V>* pA, * pB, * pC, * pAL, * pCR;

	pA = pCurSubRoot;
	pCurParent = pCurSubRoot->getpPr();
	pC = pA->getpRc();
	pAL = pA->getpLc();
	pCR = pC->getpRc();
	pB = pC->getpLc();
	pSubRoot = _rotate_LL(pC);
	pC->setpRc(pSubRoot);
	pNewSubRoot = _rotate_RR(pA);
	/*
	pNewSubRoot->setpPr(pCurParent);

	pA->setpPr(pNewSubRoot);
	pC->setpPr(pNewSubRoot);
	if (pBL != NULL)
		pBL->setpPr(pA);
	if (pBR != NULL)
		pBR->setpPr(pA);
	*/
	return pNewSubRoot;
}


template <typename K, typename V>
T_BSTN<K, V> *T_BST<K, V>::_insertInOrder(T_BSTN<K, V>** pp, T_BSTN<K, V>* parenPos, const T_Entry<K, V> e)
{
	T_BSTN<K, V>* newPos, ** pChildPos;
	T_BSTN<K, V>* pos;
	T_Entry<K, V> ent;

	if (pp == NULL)
	{
		cout << "Error in creation of BinarySearchTree: address of the pointer to Root Node is NULL!\n";
		exit;
	}

	pos = *pp;
	if (pos == NULL)
	{
		pos = new T_BSTN<K, V>(e);
		if (parenPos == NULL)
			_root = pos;
		pos->setpPr(parenPos);
		*pp = pos;
		num_entry++;
		return pos;
	}

	ent = pos->getEntry();

	if (e < ent)
	{
		pChildPos = pos->getppLc();
		newPos = _insertInOrder(pChildPos, pos, e);
		if (newPos != NULL)
			pos->setpLc(newPos);
		return NULL;
	}
	else if (e >= ent)
	{
		pChildPos = pos->getppRc();
		newPos = _insertInOrder(pChildPos, pos, e);
		if (newPos != NULL)
			pos->setpRc(newPos);
		return NULL;
	}
}

template<typename K, typename V>
void T_BST<K, V>::insertInOrder(const T_Entry<K, V> e)
{
	_insertInOrder(&_root, NULL, e);
}

template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_rebalance(T_BSTN<K, V>** ppTN)
{
	int height_Diff = 0;
	height_Diff = _getHeightDiff(*ppTN);
	if (height_Diff > 1)
	{
		if (_getHeight((*ppTN)->getpLc()) > 0)
			*ppTN = _rotate_LL(*ppTN);
		else
			*ppTN = _rotate_LR(*ppTN);
	}
	else if(height_Diff < -1)
	{
		if (_getHeight((*ppTN)->getpRc()) > 0)
			*ppTN = _rotate_RR(*ppTN);
		else
			*ppTN = _rotate_RL(*ppTN);
	}

	return *ppTN;
}

template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_insertAndRebalance(T_BSTN<K, V>** ppTN, T_BSTN<K, V>* pPr, T_Entry<K, V> e)
{
	T_BSTN<K, V>* pTN, ** ppLc, ** ppRc;
	if (*ppTN == NULL)
	{
		pTN = new T_BSTN<K, V>(e);
		*ppTN = pTN;
		if (pPr != NULL)
			pTN->setpPr(pPr);
		(*ppTN)->setpLc(NULL);
		(*ppTN)->setpRc(NULL);
		++num_entry;
		return *ppTN;
	}
	
	T_Entry<K, V> BSTN_entry;
	BSTN_entry = (*ppTN)->getEntry();

	if (e < BSTN_entry)
	{
		ppLc = (*ppTN)->getppLc();
		pTN = _insertAndRebalance(ppLc, *ppTN, e);
		if (ppTN != NULL)
		{
			(*ppTN)->setpLc(pTN);
			*ppTN = _rebalance(ppTN);
		}
	}
	else
	{
		ppRc = (*ppTN)->getppRc();
		pTN = _insertAndRebalance(ppRc, *ppTN, e);
		if (ppTN != NULL)
		{
			(*ppTN)->setpLc(pTN);
			*ppTN = _rebalance(ppTN);
		}
	}
	return *ppTN;
}


template<typename K, typename V>
void T_BST<K, V>::clear()
{

}

template<typename K, typename V>
void T_BST<K, V>::insertAndRebalance(T_Entry<K, V> e)
{
	_insertAndRebalance(&_root, NULL, e);
}

#endif // !T_BST_H

