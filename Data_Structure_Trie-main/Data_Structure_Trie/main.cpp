#include <iostream>
#include <fstream>
#include <list>
#include "Trie.h"
#include "TrieNode.h"
using namespace std;
const char* test_strings_A[] =
{
"a", "ab", "abc", "abcdefg", "abnormal", "abridge", "abreast", "abroad", "absence", "absolute",
"andrew",
"zealot", "yacht", "xerox",
"tina",
"arcade",
"timor", "tim", "ti",
"amy", "aramis",
"best", "christmas", "beyond", "church",
"apple", "desk", "echo", "car", "dog", "friend", "golf", "global",
"ABCD", "XYZ", "Korea"
};
const char* test_strings_B[] =
{
"act", "action", "age", "aged", "agenda", "cat", "stack", "stance", "star", "stare", "catfish"
};
void main()
{
	Trie<string> trieStr("TestTrie of Key Strings");
	int num_test_strings = 0;
	int trie_value;
	const char* pTest_Str;
	string sampleStr;
	TrieNode<string>* pTN;

	/* Testing Basic Operation in trie */
	cout << "Testing basic operations of trie inserting ..... " << endl;
	trieStr.insert("xyz", string("xyz"));
	trieStr.insert("ABCD", string("ABCD"));
	trieStr.insert("ABC", string("ABC"));
	trieStr.insert("AB", string("AB"));
	trieStr.insert("A", string("A"));
	trieStr.insert("xy", string("xy"));
	trieStr.insert("x", string("x"));
	trieStr.fprintTrie(cout);
	cout << "\nTesting TrieDestroy...\n";
	trieStr.eraseTrie();
	trieStr.fprintTrie(cout);
	/* Insert key strings into Trie_Str */
	num_test_strings = sizeof(test_strings_A) /
		sizeof(char*);
	cout << "\nInserting " << num_test_strings << "keywords into trie data structure.\n";
	for (int i = 0; i < num_test_strings; i++)
	{
		pTest_Str = test_strings_A[i];
		sampleStr = string(test_strings_A[i]);
		if ((pTest_Str == NULL) ||
			(*pTest_Str == '\0'))
			continue;
		trieStr.insert(pTest_Str, sampleStr);
		//cout << "Inserting " << i << "-th key_string " << pTest_Str << ", ";
		//trieStr.fprintTrie(cout);
		//cout.flush();
	}
	cout << "\nResult of the TrieAdd_InOder() for "
		<< num_test_strings << " keywords : \n";
	trieStr.fprintTrie(cout);
	cout << "\nTesting trie_find for " << num_test_strings
		<< " keywords from trie data structure.\n";
	for (int i = 0; i < num_test_strings; i++)
	{
		pTest_Str = test_strings_A[i];
		if ((pTest_Str == NULL) || (*pTest_Str == '\0'))
			continue;
		pTN = trieStr.find(pTest_Str);
		if (pTN != NULL)
		{
			cout << "Trie_find (" << pTest_Str << ") => trie_value(" << pTN->getValue() << ")\n";
		}
		else
		{
			cout << "Trie_find (" << pTest_Str << ") => not found !!\n";
		}
	}
	char prefix[] = "ab";
	STL_list predictWords;
	STL_list_itr itr;
	predictWords.clear();
	cout << "All predictive words with prefix (" << prefix << ") : ";
	trieStr.findPrefixMatch(prefix, predictWords);
	itr = predictWords.begin();
	for (int i = 0; i < predictWords.size(); i++)
	{
		cout << *itr << " ";
		++itr;
	}
	cout << endl;
	/* Testing TrieDeleteKey() */
	cout << "\nTesting trie_delete_key for" << num_test_strings << "keywords from trie data structure.\n";
	for (int i = 0; i < num_test_strings; i++) {
		pTest_Str = test_strings_A[i];
		if ((pTest_Str == NULL) || (*pTest_Str == '\0'))
			continue;
		cout << "Trie-Deleting (key : " << pTest_Str << ") ...\n";
		trieStr.deleteKeyword(pTest_Str);
		//trieStr.fprintTrie(cout);
	}

	cout << "\nTrie-Erase\n";
	//trieStr.eraseTrie();
	trieStr.fprintTrie(cout);
}