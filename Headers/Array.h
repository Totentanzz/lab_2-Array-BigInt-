#pragma once
#include "List.h"
#include <iostream>

//Класс Array (массив), который является наследником класса List и наследуется классами
//Stack и Queue 
class Array : public List {
public:

	Array();

	Array(int N);

	Array(const Array& object);

	virtual ~Array();

	int getSize() override;

	int getElmNum() override;
	
	long long* getArr() override;

	void reduceCap(int amount);

	void makeEqualSize(int size1, int size2);

	char* cStr() override;

	void addToEnd(long long value) override;
	
	void insertByIndex(long long value, int index) override; 
	
	void deleteByIndex(int index) override;

	long long& getByIndex(int index) override;

	long long* getSlice(int from, int to) override;

	void shiftSliceR(int index) override;

	void shiftSliceL(int index) override; 

	bool isEmpty() override;

	bool isElem(long long value) override;

	static void swapArray(Array& first, Array& second);

	static Array empty();

	void writeToBinFile(const char* file, int startPos);

	void readFromBinFile(const char* file, int startPos);

	Array& operator+ (long long num);

	Array& operator- ();

	long long& operator[] (int index);

	Array& operator= (const Array& other);

	Array& operator<< (int index);

	Array& operator>> (int index);

	operator long long* ();

	operator char* ();

	friend std::ostream& operator<< (std::ostream& ostrm, Array& object);

	friend std::istream& operator>> (std::istream& istrm, Array& object);

	friend std::ofstream& operator<< (std::ofstream& ofstrm, Array& object);

	friend std::ifstream& operator>> (std::ifstream& ifstrm, Array& object);

private:
	int size;
	int elemNum;
	long long* arr;
	static const int expCoef = 2;

	void init(int from);

	void expand();

	int countDigits(long long value);

};
