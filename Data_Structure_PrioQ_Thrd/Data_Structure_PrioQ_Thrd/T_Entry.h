#ifndef T_ENTRY_H
#define T_ENTRY_H
#include <iostream>
using namespace std;

template<typename K, typename V>
class T_Entry
{
	friend ostream& operator<<(ostream& fout, const T_Entry<K, V> e)
	{
		//fout << "[" << setw(3) << e.getKey() << ", " << e.getValue() << "]";
		fout << "[" << setw(3) << e.getValue() << "]";
		return fout;
	}
public:
	T_Entry() {}
	~T_Entry() {}
	T_Entry(K key, V value) : _key(key), _value(value) {}
	void setKey(const K& key) { _key = key; }
	K getKey() const { return _key; }
	void setValue(const V& value) { _value = value; }
	V getValue() const { return _value; }
	bool operator>(const T_Entry& right) { return _key > right.getKey(); }
	bool operator>=(const T_Entry& right) { return _key >= right.getKey(); }
	bool operator<(const T_Entry& right) { return _key < right.getKey(); }
	bool operator<=(const T_Entry& right) { return _key <= right.getKey(); }
	bool operator==(const T_Entry& right)
	{ return (_key == right.getKey())&&(_value == right.getValue()); }
	T_Entry& operator=(const T_Entry& right)
	{
		_key = right.getKey();
		_value = right.getValue();
		return (*this);
	}
	void print(ostream& fout);

private:
	K _key;
	V _value;
};

template<typename K, typename V>
void T_Entry<K, V>::print(ostream& fout)
{
	fout << "[" << setw(2) << this->getKey() << ", " << this->getValue() << "]";
}


#endif
