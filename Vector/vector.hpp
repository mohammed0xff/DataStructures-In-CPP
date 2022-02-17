#pragma once
#include <iostream>



template<typename T> class vector
{
public:


	vector();
	explicit vector(int size);
	vector(int size, T val);
	vector(const T arr[], size_t size);

	// Copy Constructor for lvalue objects
	vector(const vector& arg);

	// Move constructor for rvalue objects
	vector(vector&& arg);

	// Copy Assingment
	vector<T>& operator=(const vector<T>& arg);

	// Move assignment
	vector<T>& operator=(vector<T>&& arg);

	~vector();


	// --- ITERATOR ----

	class iterator;

	iterator begin();
	const iterator begin() const;

	iterator end();
	const iterator end() const;

	const iterator cbegin() const;
	const iterator cend() const;



	// --- Operations ----

	void push_back(const T& d);

	void pop_back();

	size_t capacity() const;

	size_t size() const;

	bool empty() const;

	void clear();

	// Requests a increase in capacity.
	// reverse function can't decrease the number of elements.
	void reserve(int newmalloc);

	// If the newsize is smaller, the last elements will be lost.
	// Has a default value param for custom values when resizing.
	void resize(size_t newsize);

	void shrink_to_fit();



	// --- Getters ---

	T& at(int n);
	const T& at(int n) const;

	T& operator[](int i);
	const T& operator[](int i) const;

	T& front();
	const T& front() const;

	T& back();
	const T& back() const;

	T* data();
	const T* data() const;

private:
	void validateIndex(int i);


private:
	T* m_data;
	size_t	m_size;
	size_t	m_space;

};



template<typename T>
class vector<T>::iterator
{
public:
	vector<T>::iterator(T* p)
		:m_ptr(p)
	{}

	// prefix 

	iterator& operator++()
	{
		m_ptr++;
		return *this;
	}

	iterator& operator--()
	{
		m_ptr--;
		return *this;
	}
	// postfix

	iterator& operator++(int)
	{
		m_ptr++;
		return *this;
	}

	iterator& operator--(int)
	{
		m_ptr--;
		return *this;
	}



	T& operator*()
	{
		return *m_ptr;
	}

	bool operator==(const vector<T>::iterator& rhs) const
	{
		return *m_ptr == *rhs.m_ptr;
	}

	bool operator!=(const vector<T>::iterator& rhs) const
	{
		return *m_ptr != *rhs.m_ptr;
	}

private:
	T* m_ptr;
};



// Default Constructor 

template<class T>
vector<T>::vector()
	: m_size(0)
	, m_data(0)
	, m_space(0)
{}



// Constructor with size

template<class T>
vector<T>::vector(int size)
	: m_size(0)
	, m_data(new T[size])
	, m_space(size)
{
	for (int i = 0; i < m_size; ++i) {
		m_data[i] = T();
	}
}


// Constructor with size & value 

template<class T>
vector<T>::vector(int size, T val)
	: m_size(size)
	, m_data(new T[size])
	, m_space(size)
{
	for (int i = 0; i < m_size; i++) {
		m_data[i] = val;
	}
}

// Constructor with C array
template<class T>
vector<T>::vector(const T arr[], size_t arrSize) 
{
	reserve(arrSize);
	m_size = arrSize;
	for (size_t i = 0; i < arrSize; i++)
	{
		m_data[i] = arr[i];
	}
}




// Copy Constructor 

template<class T>
vector<T>::vector(const vector<T>& rhs)
	: m_size(rhs.m_size)
	, m_data(new T[rhs.m_size])
	, m_space(rhs.m_size)
{
	for (int i = 0; i < rhs.m_size; i++) {
		m_data[i] = rhs[i];
	}

	// You can use the push_back 
	// but you can prevent the overhead of the calling 
	// for each element in rhs vector.
}



// Copy Assignment Operator  
template<class T>
vector<T>& vector<T>::operator=(const vector<T>& rhs)
{
	// prevent self assignment.
	if (this != &rhs) {
		// if current space is sufficient
		if (rhs.m_size <= m_space)
		{
			m_size = rhs.m_size;
			for (int i = 0; i < rhs.m_size; i++)
			{
				m_data[i] = rhs.m_data[i];
			}
		}
		else {
			T* ptr = new T[rhs.m_size];
			for (int i = 0; i < rhs.m_size; i++)
				ptr[i] = rhs.m_data[i];
			delete[] m_data;
			m_size = rhs.m_size;
			m_space = rhs.m_size;
			m_data = ptr;
		}
	}
	return (*this);

};

// Move Constructor 

template<class T>
vector<T>::vector(vector<T>&& rhs)
	: m_size(rhs.m_size)
	, m_data(rhs.m_data)
	, m_space(rhs.m_size)
{
	rhs.m_data = nullptr;
}



// Move assignment operator  
template<class T>
vector<T>& vector<T>::operator=(vector<T>&& rhs)
{
	if (this != &rhs) {
		m_size = rhs.m_size;
		m_space = rhs.m_space;

		// Its perfectly safe to delete a null pointer.
		// So we dont need to check if the lhs was empty.
		delete[] m_data;
		m_data = rhs.m_data;
		rhs.m_data = nullptr;
	}
	return (*this);
}


template <typename T>
vector<T>::~vector()
{
	// Its perfectly safe to delete a null pointer.
	delete[] m_data;
}





template<typename T>
typename vector<T>::iterator vector<T>::begin()
{
	return vector<T>::iterator(&m_data[0]);
}

template<typename T>
typename const vector<T>::iterator vector<T>::begin() const
{
	return vector<T>::iterator(&m_data[0]);
}

template<typename T>
typename vector<T>::iterator vector<T>::end()
{
	return vector<T>::iterator(&m_data[m_size - 1]);
}

template<typename T>
typename const vector<T>::iterator vector<T>::end() const
{
	return vector<T>::iterator(&m_data[m_size - 1]);
}

template<typename T>
typename const vector<T>::iterator vector<T>::cbegin() const
{
	return vector<T>::iterator(&m_data[0]);
}

template<typename T>
typename const vector<T>::iterator vector<T>::cend() const
{
	return vector<T>::iterator(&m_data[m_size - 1]);
}




template<class T>
bool vector<T>::empty() const
{
	return (m_size == 0);
}


template<class T>
size_t vector<T>::capacity() const
{
	return m_space;
}


template<class T>
void vector<T>::reserve(int newSpace)
{
	if (newSpace <= m_space) return;

	T* ptr = new T[newSpace];

	for (int i = 0; i < m_size; ++i)
		ptr[i] = m_data[i];

	delete[] m_data;
	m_data = ptr;
	m_space = newSpace;
}


template<class T>
void vector<T>::resize(size_t newSize)
{
	reserve(newSize);
	m_size = newSize;
}


template<class T>
size_t vector<T>::size() const
{
	return m_size;
}




// Operations

template<class T>
void vector<T>::push_back(const T& val)
{
	if (m_space == 0)
		reserve(8);
	else if (m_size == m_space)
		reserve(m_space * 2);

	m_data[m_size++] = val;

}


template<class T>
void vector<T>::pop_back() {
	if (m_size > 0) {
		m_size--;
	}
}

// Accessors

template<class T>
void vector<T>::validateIndex(int i) {
	if (i < 0 || i >= m_size) {
		std::cerr << "Index got out of range!\n";
		abort();
	}
}


template<class T>
T& vector<T>::at(int i)
{
	validateIndex(i);
	return m_data[i];
}


template<class T>
const T& vector<T>::at(int i) const
{
	validateIndex(i);
	return m_data[i];
}


template<class T>
T& vector<T>::operator[](int i)
{
	validateIndex(i);
	return m_data[i];
}


template<class T>
const T& vector<T>::operator[](int i) const
{
	validateIndex(i);
	return m_data[i];
}


template<class T>
T& vector<T>::front()
{
	return m_data[0];
}


template<class T>
const T& vector<T>::front() const
{
	return m_data[0];
}


template<class T>
T& vector<T>::back()
{
	return m_data[m_size - 1];
}


template<class T>
const T& vector<T>::back() const
{
	return m_data[m_size - 1];
};



template<class T>
void vector<T>::clear() {
	delete[] m_data;
	m_data = nullptr;
	m_size = 0;
	m_space = 0;
}


template<class T>
void vector<T>::shrink_to_fit() {

	T* ptr = new T[m_size];
	m_space = m_size;
	for (size_t i = 0; i < m_size; i++) {
		ptr[i] = m_data[i];
	}
	delete[] m_data;
	m_data = ptr;
}



template<class T>
T* vector<T>::data() {
	return m_data;
}

template<class T>
const T* vector<T>::data() const {
	return m_data;
}

