#pragma once
#include "List.h"

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

	long long getByIndex(int index) override;

	long long* getSlice(int from, int to) override;

	void shiftSliceR(int index) override;

	void shiftSliceL(int index) override; 

	bool isEmpty() override;

	bool isElem(long long value) override;

	static void swapArray(Array& first, Array& second);

	static Array empty();
private:
	int size;
	int elemNum;
	long long* arr;
	static const int expCoef = 2;

	void init(int from);

	void expand();

	int countDigits(long long value);

};
