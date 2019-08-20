#pragma once
#include <iostream>
#include <string>

using namespace std;

template<typename T>
class Array
{
	//int *arr;
	T *buf;
	int size;
	int capacity;
public:
	Array(int cap = 100) : buf(0), size(0), capacity(cap)
	{
		buf = new T[capacity];
	}
	~Array()
	{
		delete[] buf;
	}
	void Add(T data)
	{
		buf[size++] = data;
	}
	int GetSize() const
	{
		return size;
	}
	T operator[](int idx) const
	{
		return buf[idx];
	}
};