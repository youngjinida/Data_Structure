#ifndef MY_VOCA_H
#define MY_VOCA_H

#include <iostream>
#include <string>
#include <list>
using namespace std;

enum Word_Type { NOUN, VERB, ADJ, ADV, PREPOS };

typedef list<string> List_str;
typedef list<string>::iterator List_str_itr;

class MyVoca
{
	friend ostream& operator<<(ostream& fout, MyVoca& mv);

public:
	MyVoca() {}
	~MyVoca() {}
	MyVoca(string kw, Word_Type wt, List_str thes, List_str ex_usg)
		:keyWord(kw), type(wt), thesaurus(thes), usages(ex_usg) {}
	string getKeyWord() { return keyWord; }
	
private:
	string keyWord;
	Word_Type type;
	List_str thesaurus;
	List_str usages;
};


#endif // !MY_VOCA_H

