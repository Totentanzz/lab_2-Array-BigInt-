#pragma once
#include "Array.h"

//����� Queue (�������), ���������� ����������� ������ Array
class Queue : public Array {
public:

	Queue();

	Queue(int size);

	Queue(const Queue& object);

	~Queue();

	void push(long long value);

	long long peek();

	void pop();

private:
};

