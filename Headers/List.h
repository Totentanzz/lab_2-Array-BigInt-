#pragma once

//јбстрактный класс List, который наследуетс€ классом Array
class List
{
public:
	
	virtual int getSize() = 0;

	virtual int getElmNum() = 0;

	virtual long long* getArr() = 0;

	virtual char* cStr() = 0;

	virtual void addToEnd(long long value) = 0;

	virtual void insertByIndex(long long value, int index) = 0;

	virtual void deleteByIndex(int index) = 0;

	virtual long long getByIndex(int index) = 0;

	virtual long long* getSlice(int from, int to) = 0;

	virtual void shiftSliceR(int index) = 0;

	virtual void shiftSliceL(int index) = 0;

	virtual bool isEmpty() = 0;

	virtual bool isElem(long long value) = 0;

protected:
private:
};

