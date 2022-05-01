#include "MyVoca.h"
#include <iostream>
#include <fstream>
#include <string>
#include "HashMap.h"
#include "HashMap.cpp"
#include "CyclicShiftHashCode.h"
#include "T_Entry.h"
#include "HashDictionary.h"
#include "MyVoca.h"
#include "MyVocaList.h"

void main()
{
	MyVoca* pVoca, voca;
	list<string> thesaurus, usages;
	int word_count;
	MyVoca mv;
	string keyWord;
	HashDict<string, MyVoca*> myVocaDict;
	HashDict<string, MyVoca*>::Iterator itr;
	HashDict<string, MyVoca*>::Range range;
	T_Entry<string, MyVoca*> vocaEntry;

	
	cout << "Inserting My Vocabularies to myVocaDict . . . " << "\n";
	word_count = 0;
	for (int i = 0; i < NUM_MY_TOEIC_VOCA; i++)
	{
		pVoca = &myToeicVocaList[i]; keyWord = myToeicVocaList[i].getKeyWord(); myVocaDict.insert(keyWord, pVoca);
	}
	cout << "Total " << myVocaDict.getSize() << " words in my Voca_Dictionary .."
		<< "\n";
	// check all vocabularies in the hash_dictionary
	for (itr = myVocaDict.begin(); itr != myVocaDict.end(); ++itr)
	{
		pVoca = (*itr).getValue();
		cout << *pVoca << "\n";
	}
	cout << "\n";
	myVocaDict.fprintBucketSizes(cout);
	cout << "\n";
	//string testWord = "mean";
	string testWord = "offer";
	range = myVocaDict.findAll(testWord);
	cout << "Thesaurus of [" << testWord << "]: \n";
	for (itr = range.begin(); itr != range.end(); ++itr)
	{
		pVoca = (*itr).getValue();
		cout << *pVoca << "\n";
	}
	cout << "\n";
} // end main()

