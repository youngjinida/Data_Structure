#ifndef T_ARRAY_H
#define T_ARRAY_H

#include <iostream>
#include <iomanip>

using namespace std;
enum SortingOrder { INCREASING, DECREASING };

template<typename T>
class T_Array
{
	void _quickSort(T* arr, int size, int left, int right, SortingOrder sortOrder);
	int _partition(T* arr, int size, int left, int right, int pivotIndex, SortingOrder sortOrder);
public:
	T_Array(int n, string nm);
	~T_Array();
	int size() { return num_elements; }
	bool empty() { return num_elements == 0; }
	string getName() { return this->name; }
	void reserve(int new_capacity);
	void insert(int i, T element);
	void insertBack(T element);
	void remove(int i);
	T& at(int i);
	void set(int i, T& element);
	T& getMin(int begin, int end);
	T& getMax(int begin, int end);
	void shuffle();
	int sequential_search(T search_key);
	int binary_search(T search_key);
	void selection_sort(SortingOrder sortOrder = INCREASING);
	void quick_sort(SortingOrder sortOrder = INCREASING);
	bool isValidIndex(int i);
	void fprint(ostream& fout, int elements_per_line);
	void fprintSample(ostream& fout, int elements_per_line, int num_sample_lines);
	T& operator[](int index) { return t_array[index]; }

private:
	T* t_array;
	int num_elements;
	int capacity;
	string name;
};

template<typename T>
T_Array<T>::T_Array(int n, string nm)
{
	this->capacity = n;
	this->t_array = new T[this->capacity];
	if (t_array == NULL)
	{
		cout << "Error\n";
		exit;
	}
	this->num_elements = 0;
	this->name = nm;
}


template<typename T>
T_Array<T>::~T_Array()
{
	if (this->t_array != NULL)
		delete[] this->t_array;
}

template<typename T>
void T_Array<T>::reserve(int new_capacity)
{
	if (this->capacity >= new_capacity)
		return;
	T* t_nArray = new T[new_capacity];
	if (t_nArray == NULL)
	{
		cout << "Error\n";
		exit;
	}
	cout << this->getName() << " expands capacity to" << setw(3) << new_capacity << "\n";
	for (int i = 0; i < num_elements; ++i)
		t_nArray[i] = this->t_array[i];
	delete[] this->t_array;
	this->t_array = t_nArray;
	this->capacity = new_capacity;
}

template<typename T>
bool T_Array<T>::isValidIndex(int index)
{
	if ((index < 0) || (index > num_elements))
		return false;
	else
		return true;
}

template<typename T>
void T_Array<T>::insert(int i, T element)
{
	if (num_elements >= capacity)
	{
		int new_capacity;
		new_capacity = ((2 * capacity) > 1) ? 2 * capacity : 1;
		reserve(new_capacity);
	}
	if (isValidIndex(i))
	{
		for (int j = num_elements - 1; j >= i; --j)
			t_array[j + 1] = t_array[j];
		t_array[i] = element;
		++num_elements;
	}
}

template<typename T>
void T_Array<T>::insertBack(T element)
{
	if (num_elements >= capacity)
	{
		int new_capacity;
		new_capacity = (2 * capacity > 1) ? 2 * capacity : 1;
		reserve(new_capacity);
	}
	t_array[num_elements] = element;
	++num_elements;
}

template<typename T>
void T_Array<T>::remove(int i)
{
	if (isValidIndex(i))
	{
		for (int j = i + 1; j < num_elements; ++j)
			t_array[j - 1] = t_array[j];
		--num_elements;
	}

	if (num_elements < (capacity / 2))
	{
		int new_capacity;
		new_capacity = capacity/2;
		T* t_nArray = new T[new_capacity];
		if (t_nArray == NULL)
			return;

		cout << this->getName() << "reduces capacity to" << setw(3) << new_capacity << "\n";
		for (int j = 0; j < num_elements; ++j)
			t_nArray[j] = t_array[j];

		delete[] t_array;
		t_array = t_nArray;
		capacity = new_capacity;
	}
}

template<typename T>
T& T_Array<T>::at(int i)
{
	if (isValidIndex(i))
		return t_array[i];
}

template<typename T>
void T_Array<T>::set(int i, T& element)
{
	if (isValidIndex(i))
		t_array[i] = element;
}

template<typename T>
void T_Array<T>::shuffle()
{
	srand(time(0));
	int rand_1, rand_2;
	int idx_1, idx_2;
	T temp;
	for (int i = 0; i < num_elements; ++i)
	{
		rand_1 = rand();
		rand_2 = rand();
		idx_1 = (rand_1 << 15 | rand_2) % num_elements;
		rand_1 = rand();
		rand_2 = rand();
		idx_2 = (rand_1 << 15 | rand_2) % num_elements;

		temp = t_array[idx_1];
		t_array[idx_1] = t_array[idx_2];
		t_array[idx_2] = temp;
	}
}

template<typename T>
T& T_Array<T>::getMin(int begin, int end)
{
	T minValue;
	int index_min;
	minValue = t_array[begin];
	index_min = begin;
	for (int idx = begin + 1; idx <= end; ++idx)
	{
		if (t_array[idx] < minValue)
		{
			minValue = t_array[idx];
			index_min = idx;
		}
	}
	return t_array[index_min];
}

template<typename T>
T& T_Array<T>::getMax(int begin, int end)
{
	T maxValue;
	int index_max;
	maxValue = t_array[begin];
	index_max = begin;
	for (int idx = begin + 1; idx <= end; ++idx)
	{
		if (maxValue < t_array[idx])
		{
			maxValue = t_array[idx];
			index_max = idx;
		}
	}

	return t_array[index_max];
}

template<typename T>
int T_Array<T>::sequential_search(T search_key)
{
	int idx;
	for (idx = 0; idx < num_elements; ++idx)
	{
		if (t_array[idx] == search_key)
			return idx;
	}
	return -1;
}

template<typename T>
int T_Array<T>::binary_search(T search_key)
{
	int low, high, mid;
	low = 0;
	high = num_elements - 1;
	
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (t_array[mid] == search_key)
			return mid;
		else if (t_array[mid] < search_key)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return -1;
}

template<typename T>
void T_Array<T>::selection_sort(SortingOrder sortOrder)
{
	if (sortOrder == INCREASING)
	{
		int index_min;
		T min_Value, temp;
		for (int idx = 0; idx < num_elements; ++idx)
		{
			index_min = idx;
			min_Value = t_array[idx];
			for (int idx_2 = idx + 1; idx_2 < num_elements; ++idx_2)
			{
				if (min_Value > t_array[idx_2])
				{
					index_min = idx_2;
					min_Value = t_array[idx_2];
				}
			}
			if (index_min == idx)
			{
				temp = t_array[index_min];
				t_array[index_min] = t_array[idx];
				t_array[idx] = temp;
			}
		}
	}
	else
	{
		int index_max;
		T max_Value, temp;
		for (int idx = 0; idx < num_elements; ++idx)
		{
			index_max = idx;
			max_Value = t_array[idx];
			for (int idx_2 = idx + 1; idx_2 < num_elements; ++idx_2)
			{
				if (max_Value < t_array[idx_2])
				{
					index_max = idx_2;
					max_Value = t_array[idx_2];
				}
			}
			if (index_max == idx)
			{
				temp = t_array[index_max];
				t_array[index_max] = t_array[idx];
				t_array[idx] = temp;
			}
		}
	}
}

template<typename T>
void T_Array<T>::fprint(ostream& fout, int elements_per_line)
{
	int count = 0;
	while (count < num_elements)
	{
		for (int idx = 0; idx < elements_per_line; ++idx)
		{
			fout << t_array[count] << " ";
			++count;
			if (count % elements_per_line == 0)
				fout << "\n";
		}
	}
	fout << "\n";
}

template<typename T>
void T_Array<T>::fprintSample(ostream& fout, int elements_per_line, int num_sample_lines)
{
	string T_type;
	int last_block_start;
	int count = 0;
	
	T_type = typeid(T).name();
	for (int i = 0; i < num_sample_lines; ++i)
	{
		for (int j = 0; j < elements_per_line; j++)
		{
			if (count >= num_elements)
			{
				fout << "\n";
				return;
			}
			if ((T_type == string("int")) || (T_type == string("double")) ||
				(T_type == string("class std::basic_string<char,struct std::char traits<char>,class std::allocator<char> >")))
				fout << setw(10) << t_array[count];
			else
				fout << t_array[count] << " ";
			++count;
		}
		fout << "\n";
	}
	if (count < (num_elements - elements_per_line * num_sample_lines))
		count = num_elements - elements_per_line * num_sample_lines;
	fout << " .................. " << "\n";

	for (int i = 0; i < num_sample_lines; ++i)
	{
		for (int j = 0; j < elements_per_line; j++)
		{
			if (count >= num_elements)
			{
				fout << "\n";
				return;
			}
			if ((T_type == string("int")) || (T_type == string("double")) ||
				(T_type == string("class std::basic_string<char,struct std::char traits<char>,class std::allocator<char> >")))
				fout << setw(10) << t_array[count];
			else
				fout << t_array[count] << " ";
			++count;
		}
		fout << "\n";
	}
}

template<typename T>
int T_Array<T>::_partition(T* arr, int size, int left, int right, int pivotIndex, SortingOrder sortOrder)
{
	T pivotValue, temp;
	int new_pi;

	pivotValue = arr[pivotIndex];
	arr[pivotIndex] = arr[right];
	arr[right] = pivotValue;
	new_pi = left;

	if (sortOrder == INCREASING)
	{
		for (int idx = left; idx < right; ++idx)
		{
			if (pivotValue > arr[idx])
			{
				temp = arr[new_pi];
				arr[new_pi] = arr[idx];
				arr[idx] = temp;

				++new_pi;
			}
		}
		temp = arr[new_pi];
		arr[new_pi] = arr[right];
		arr[right] = temp;
	}
	else
	{
		for (int idx = left; idx < right; ++idx)
		{
			if (pivotValue <= arr[idx])
			{
				temp = arr[new_pi];
				arr[new_pi] = arr[idx];
				arr[idx] = temp;

				++new_pi;
			}
		}
		temp = arr[new_pi];
		arr[new_pi] = arr[right];
		arr[right] = temp;
	}

	return new_pi;
}

template<typename T>
void T_Array<T>::_quickSort(T* arr, int size, int left, int right, SortingOrder sortOrder)
{
	int pi, new_pi;
	if (left >= right)
		return;
	else
	{
		pi = (left + right) / 2;
	}

	new_pi = _partition(arr, size, left, right, pi, sortOrder);

	if (left < (new_pi - 1))
		_quickSort(arr, size, left, new_pi - 1, sortOrder);
	if ((new_pi + 1) < right)
		_quickSort(arr, size, new_pi + 1, right, sortOrder);
}

template<typename T>
void T_Array<T>::quick_sort(SortingOrder sortOrder)
{
	_quickSort(this->t_array, num_elements, 0, num_elements - 1, sortOrder);
}

#endif // !