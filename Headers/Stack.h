#pragma once
#include "Array.h"

//����� Stack, ���������� ����������� ������ Array
class Stack : public Array {
public:

	Stack();

	Stack(int size);

	Stack(const Stack& object);

	~Stack();

	void push(long long value);

	long long peek();

	void pop();

private:
};
