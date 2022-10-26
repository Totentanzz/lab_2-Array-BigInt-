#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdlib>
#include "Array.h"

using namespace std;

	//����������� �� ���������
	Array::Array() {
		size = 1;
		elemNum = 0;
		arr = new long long[size];
		init(elemNum);
	}

	//�����������, ��������� ������ ������� N (���� N<=0, �� ������������� nullptr)
	Array::Array(int N) {
		size = N;
		elemNum = 0;
		if (size > 0) {
			arr = new long long[size];
			init(elemNum);
		}
		else arr = nullptr;
	}

	//����������� �����������
	Array::Array(const Array& object) {
		size = object.size;
		elemNum = object.elemNum;
		if (size > 0) {
			arr = new long long[size];
			memcpy(arr, object.arr, size * sizeof(long long));
		}
		else arr = nullptr;
	}

	//����������
	Array::~Array() {
		delete[] arr;
	}

	//����� ��������� ������� �������
	int Array::getSize() {
		return size;
	}

	//����� ��������� ���-�� ��������� �������
	int Array::getElmNum() {
		return elemNum;
	}

	//����� ��������� ������� (�����)
	long long* Array::getArr() {
		long long* arrCpy = nullptr;
		if (this->size > 0) {
			arrCpy = new long long[size];
			memcpy(arrCpy, arr, size * sizeof(long long));
		}
		return arrCpy;
	}

	/*
	* ����� ���������� ������� ������� �� amount ���������:
	* 1)� ������ ���� ������ ��������� ��������, �� ����� ��������� ���-��
	*   ���������
	* 2)����� ������ ��������� ������ ������� �� amount
	*/
	void Array::reduceCap(int amount) {
		if (amount > 0 && amount < size) {
			long long* arrCpy = new long long[size - amount];
			memcpy(arrCpy, arr, (size - amount) * sizeof(long long));
			delete[] arr;
			arr = arrCpy;
			if (size == elemNum) elemNum -= amount;
			size -= amount;
		}
	}

	/*
	* �����, ����������� ������ �� ������������� ������� �� size1 � size2:
	* ����� ���������� ��������� ������ ��������� ��������
	*/
	void Array::makeEqualSize(int size1, int size2) {
		int maxSize = size1 < size2 ? size2 : size1;
		int oldSize = size;
		if (maxSize > oldSize) {
			long long* arrCpy;
			arrCpy = new long long[maxSize];
			memcpy(arrCpy, arr, oldSize * sizeof(long long));
			delete[] arr;
			arr = arrCpy;
			size = maxSize;
			init(oldSize);
		}
	}

	/*
	* �����, ������������ �������� ������������� ������ Array:
	* 1)���� ������ �� ������, �� ������� ��� �������� � ������
	*   (����� ������� ��������� ��� ������� ��������,
	*    ����� ������ - ��� ���������)
	* 2)���� ������ ������, �� ������� nullptr � ������
	*/
	char* Array::cStr() {
		int cStrSize = 0, numValues = 0;
		char* cStr = nullptr;
		if (size > 0)
		{
			for (size_t i = 0; i < size; i++) 
				cStrSize += countDigits(arr[i]);
			cStr = new char[cStrSize + size + 2];
			cStr[0] = '[';
			for (size_t i = 1, j = 0; j < size; j++) {
				int digits = countDigits(arr[j]);
				_i64toa(arr[j], cStr + i,10);
				numValues++;
				i = i + digits;
				if (j == size - 1) {
					cStr[i++] = ']';
					cStr[i] = '\0';
				}
				else if (numValues >= elemNum) cStr[i++] = ' ';
				else cStr[i++] = ',';
			}
		}
		else {
			char emptyStr[] = "nullptr";
			cStr = new char[8];
			memcpy(cStr, emptyStr, 8 * sizeof(char));
		}
		return cStr;
	}

	//���� ���������� �������� � ����� �������
	void Array::addToEnd(long long value) {
		if (elemNum == size)
			expand();
		arr[elemNum++] = value;
	}

	//����� ������� �������� �� ������ � ������
	void Array::insertByIndex(long long value, int index) {
		if (index > size || index < 0)
			throw("Exception: out of bounds");
		if ((arr[index] == 0) && (elemNum < size)) arr[index] = value;
		else if (index == size) addToEnd(value);
		else {
			if ((elemNum - index) > (size - elemNum)) expand();
			long long* pos = arr + index;
			size_t numOfElm = elemNum - index;
			memmove(pos + 1, pos, numOfElm * sizeof(long long));
			arr[index] = value;
		}
		elemNum++;
	}

	//����� �������� ������� �� �������
	void Array::deleteByIndex(int index) {
		if (index < 0 || index >= size)
			throw("Exception: out of bounds");
		arr[index] = 0;
		elemNum--;
	}
	
	//����� ��������� �� ������� �������
	long long Array::getByIndex(int index) {
		if (index < 0 || index >= size)
			throw("Exception: out of bounds");
		return arr[index];
	}

	//����� ��������� ����� �������
	long long* Array::getSlice(int from, int to) {
		if (from < 0 || from > to || to >= size)
			throw("Exception: out of bounds");
		int sliceSize = to - from + 1;
		long long* arrSlice = new long long[sliceSize];
		memcpy(arrSlice, arr + from, sliceSize * sizeof(long long));
		return arrSlice;
	}

	/*
	* ����� �������� ������� �� �������:
	* 1)���������� 0, ���� �� ������ �� ����
	* 2)���������� 1, ���� ������ ����
	*/
	bool Array::isEmpty() {
		bool state = true;
		if (arr != nullptr) state = 0;
		for (int i = 0; i < elemNum; i++) {
			if (arr[i] != 0) {
				state = false;
				break;
			}
			else state = 1;
		}
		return state;
	}

	//����� ������ �������� � �������: ���������� 1, ���� �������, ����� 0
	bool Array::isElem(long long value) {
		bool state = false;
		long long* end = arr + size;
		long long* pos = find(arr, end, value);
		if (pos != end) state=true;
		return state;
	}

	//����� ������ ����� ���� ��������� �������, ������� � ��. �� ������� index
	void Array::shiftSliceR(int index) {
		if (index < 0 || index >= size)
			throw("Exception: out of bounds");
		size_t numOfElm = elemNum - index;
		if (size <= numOfElm) expand();
		long long* pos = arr + index;
		memmove(pos + 1, pos, numOfElm * sizeof(long long));
		arr[index] = 0;
	}

	//����� ������ ����� ���� ��������� ������� �� ������� index
	void Array::shiftSliceL(int index) {
		if (index < 0 || index >= size)
			throw("Exception: out of bounds");
		long long* pos = arr + index;
		size_t numOfElm = size - index - 1;
		memmove(pos, pos + 1, numOfElm * sizeof(long long));
		arr[numOfElm] = 0;
	}

	//����� ������ ������ ���� �������� Array
	void Array::swapArray(Array& first, Array& second) {
		int tmpSize = first.size;
		int tmpElemNum = first.elemNum;
		long long* tmpArr = first.arr;
		first.size = second.size;
		second.size = tmpSize;
		first.elemNum = second.elemNum;
		second.elemNum = tmpElemNum;
		first.arr = second.arr;
		second.arr = tmpArr;
	}

	/*
	* ����������� ����� empty, ������� ���������� ������ ������
	* (0 ���������, 0 �����, nullptr)
	*/
	Array Array::empty() {
		Array emptyArr(0);
		return emptyArr;
	}

	//����� ���������� 0 ���� ���������, ������� � �������� ��� �������� from
	void Array::init(int from) {
		for (size_t i = from; i < size; i++) {
			arr[i] = 0;
		}
	}

	/*
	* ����� ���������� �������:
	* 1)���� ������ ������, �� ��� ������ ������������� �� 1
	* 2)���� ������ �� ������, �� ������ ������������� � 2 ����
	* 3)����� ���������� ��������� ��� ������
	*/
	void Array::expand() {
		long long* newArr = nullptr;
		if (size > 0) newArr = new long long[size * expCoef];
		else newArr = new long long[1];
		memcpy(newArr, arr, size * sizeof(long long));
		delete[] arr;
		arr = newArr;
		if (size != 0) size *= expCoef;
		else size++;
		init(elemNum);
	}

	//����� �������� ���-�� ���� ����� value (������� ����)
	int Array::countDigits(long long value) {
		int digits = 0;
		if (value == 0 || value < 0) digits++;
		while (value != 0) {
			digits++;
			value /= 10;
		}
		return digits;
	}

