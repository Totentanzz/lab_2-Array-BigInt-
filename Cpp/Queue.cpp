#include "Queue.h"

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
		throw("Exception: queue is empty");
	return getByIndex(index);
}

//����� �������� �� ������ �������
void Queue::pop() {
	int index = getElmNum() - 1;
	if (index < 0)
		throw("Exception: queue is empty");
	deleteByIndex(index);
}
