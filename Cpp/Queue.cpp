#include "Queue.h"
#include <stdexcept>

//����������� �� ���������
Queue::Queue() {
}

//�����������, ����������� � �������� ��������� ������ �������
Queue::Queue(int size) : Array(size) {
}

//����������� �����������
Queue::Queue(const Queue& object) : Array(object) {
}

//����������
Queue::~Queue() {
}

//����� ���������� �������� � ����� �������
void Queue::push(long long value) {
	shiftSliceR(0);
	insertByIndex(value,0);
}

//����� ��������� �������� �� ������ �������
long long Queue::peek() {
	int index = getElmNum() - 1;
	if (index < 0)
		throw std::out_of_range("Queue is empty");
	return getByIndex(index);
}

//����� �������� �� ������ �������
void Queue::pop() {
	int index = getElmNum() - 1;
	if (index < 0)
		throw std::out_of_range("Queue is empty");
	deleteByIndex(index);
}
