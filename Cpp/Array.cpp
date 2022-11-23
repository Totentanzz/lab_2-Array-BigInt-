#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdlib>
#include "Array.h"
#include "DataException.h"
#include <fstream>

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
		if (N<0)
			throw length_error("Array constructor: size N is negative");
		size = N;
		elemNum = 0;
		arr = size>0 ? new long long[size] : nullptr;
		init(elemNum);
	}

	//����������� �����������
	Array::Array(const Array& object) {
		size = object.size;
		elemNum = object.elemNum;
		arr = size>0 ? new long long[size] : nullptr;
		memcpy(arr, object.arr, size * sizeof(long long));
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
		long long* arrCpy = size>0 ? new long long[size] : nullptr;
		memcpy(arrCpy, arr, size * sizeof(long long));
		return arrCpy;
	}

	/*
	* ����� ���������� ������� ������� �� amount ���������:
	* 1)� ������ ���� ������ ��������� ��������, �� ����� ��������� ���-��
	*   ���������
	* 2)����� ������ ��������� ������ ������� �� amount
	*/
	void Array::reduceCap(int amount) {
		if (amount < 0 || amount >= size)
			throw length_error("reduceCap: amount is negative");
		int newSize = size - amount;
		long long* arrCpy = newSize>0 ? new long long[newSize] : nullptr;
		memcpy(arrCpy, arr, newSize * sizeof(long long));
		delete[] arr;
		arr = arrCpy;
		size = newSize;
		elemNum = size < elemNum ? size : elemNum;
	}

	/*
	* �����, ����������� ������ �� ������������� ������� �� size1 � size2:
	* ����� ���������� ��������� ������ ��������� ��������
	*/
	void Array::makeEqualSize(int size1, int size2) {
		int maxSize = size1 < size2 ? size2 : size1;
		int oldSize = size;
		if (maxSize < oldSize)
			throw DataException("makeEqualSize: maxSize is less than oldSize", maxSize);
		long long* arrCpy = new long long[maxSize];
		memcpy(arrCpy, arr, oldSize * sizeof(long long));
		delete[] arr;
		arr = arrCpy;
		size = maxSize;
		init(oldSize);
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
		if (index < 0 || index > size)
			throw DataException("insertByIndex: index is out of array bounds", index);
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
			throw DataException("deleteByIndex: index is out of array bounds", index);
		int elem=0, digit=arr[index];
		for (size_t i = 0; i < size; i++) elem += (arr[i] != 0) ? 1 : 0;
		arr[index] = 0;
		if ((digit == 0 && elem != elemNum) || digit != 0) elemNum--;
	}
	
	//����� ��������� �� ������� �������
	long long& Array::getByIndex(int index) {
		if (index < 0 || index >= size)
			throw DataException("getByIndex: index is out of array bounds", index);
		return arr[index];
	}

	//����� ��������� ����� �������
	long long* Array::getSlice(int from, int to) {
		if (from < 0 || from > to || to >= size)
			throw DataException("getSlice: index is out of bounds",2,from,to);
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
		for (int i = 0; i < elemNum; i++) {
			if (arr[i] != 0) {
				state = false;
				break;
			}
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
			throw DataException("shiftSliceR: index is out of array bounds", index);
		size_t numOfElm = (arr[size - 1] == 0) ? size - index - 1 : size - index;
		if (arr[size - 1] != 0) expand();
		long long* pos = arr + index;
		memmove(pos + 1, pos, numOfElm * sizeof(long long));
		arr[index] = 0;
	}

	//����� ������ ����� ���� ��������� ������� �� ������� index
	void Array::shiftSliceL(int index) {
		if (index < 0 || index >= size)
			throw DataException("shiftSliceL: index is out of array bounds", index);
		long long* pos = arr + index;
		size_t numOfElm = size - index - 1;
		if (arr[index] != 0) elemNum--;
		memmove(pos, pos + 1, numOfElm * sizeof(long long));
		arr[size-1] = 0;
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
		if (from < 0)
			throw out_of_range("init: index is negative");
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
		int newSize = size * expCoef;
		long long* newArr = nullptr;
		int lstElem=0;
		for (size_t i = 0; i < size; i++)
			if (arr[i] != 0) lstElem = i;
		newArr = (size > 0) ? new long long[newSize] : new long long[1];
		memcpy(newArr, arr, size * sizeof(long long));
		delete[] arr;
		arr = newArr;
		size = (size != 0) ? newSize : 1;
		init(++lstElem);
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

	void Array::writeToBinFile(const char* file, int startPos) {
		ofstream ofstrm(file, ios::binary | ios::out | ios::_Nocreate);
		if (!ofstrm)
			throw ofstream::failure("Can't open file");
		ofstrm.seekp(startPos);
		ofstrm.write((char*)&size, sizeof(size));
		ofstrm.write((char*)&elemNum, sizeof(elemNum));
		for (size_t i = 0; i < size; i++) {
			ofstrm.write((char*)(arr + i), sizeof(arr[i]));
		}
		ofstrm.close();
	}

	void Array::readFromBinFile(const char* file, int startPos) {
		ifstream ifstrm(file, ios::binary | ios::in);
		if (!ifstrm) 
			throw ifstream::failure("Can't open file");
		ifstrm.seekg(startPos);
		if (size > 0) delete[] arr;
		ifstrm.read((char*)&size, sizeof(int));
		ifstrm.read((char*)&elemNum, sizeof(int));
		arr = new long long[size];
		for (size_t i = 0; i < size; i++) {
			long long num;
			ifstrm.read((char*)&num, sizeof(long long));
			arr[i] = num;
		}
		ifstrm.close();
	}

	Array& Array::operator+ (long long num) {
		addToEnd(num);
		return *this;
	}

	Array& Array::operator- () {
		deleteByIndex(elemNum - 1);
		return *this;
	}

	long long& Array::operator[] (int index) {
		return getByIndex(index);
	}

	Array& Array::operator= (const Array& other) {
		Array tmp(other);
		swapArray(*this,tmp);
		return *this;
	}


	Array& Array::operator<< (int index) { 
		shiftSliceL(index);
		return *this;
	}

	Array& Array::operator>> (int index) {
		shiftSliceR(index);
		return *this;
	}

	Array::operator long long*() {
		return arr;
	}

	Array::operator char*() {
		return (char*)arr;
	}

	ostream& operator<< (ostream& ostrm, Array& object) {
		ostrm << object.cStr() << endl;
		return ostrm;
	}

	istream& operator>> (istream& istrm, Array& object) {
		for (size_t i = object.elemNum; i < object.size; i++) {
			istrm >> object[i];
			object.elemNum++;
		}
		return istrm;
	}

	ofstream& operator<< (ofstream& ofstrm, Array& object) {
		ofstrm << object.size << ' ' << object.elemNum;
		for (size_t i = 0; i < object.size; i++) {
			ofstrm << ' ';
			ofstrm << object.arr[i];
		}
		ofstrm << endl;
		return ofstrm;
	}

	ifstream& operator>> (ifstream& ifstrm, Array& object) {
		if (object.size > 0) delete[] object.arr;
		ifstrm >> object.size >> object.elemNum;
		object.arr = new long long[object.size];
		for (size_t i = 0; i < object.size; i++) {
			long long num;
			ifstrm >> num;
			object.arr[i] = num;
		}
		return ifstrm;
	}