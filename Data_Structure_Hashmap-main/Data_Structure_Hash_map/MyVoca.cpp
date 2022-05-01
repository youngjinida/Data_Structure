#include "MyVoca.h"

ostream& operator<<(ostream& fout, MyVoca& mv)
{
	const string wd_ty[] = { "n", "v", "adh", "adv", "prepos" };
	List_str_itr itr;
	fout << mv.keyWord << "(" << wd_ty[mv.type] << "): '\n";
	fout << " - thesaurus(";

	for (itr = mv.thesaurus.begin(); itr != mv.thesaurus.end(); ++itr)
		fout << *itr<< ", ";

	fout << ")\n";
	fout << " - example usage(";

	for (itr = mv.usages.begin(); itr != mv.usages.end(); ++itr)
		fout << *itr << " ";
	fout << ")";

	return fout;
}