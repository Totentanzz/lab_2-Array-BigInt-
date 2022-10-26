#include "Stack.h"

//����������� �� ���������
Stack::Stack() {
}

//�����������, ����������� � �������� ��������� ������ �����
Stack::Stack(int size) : Array(size) {
}

//����������� �����������
Stack::Stack(const Stack& object) : Array(object) {
}

//����������
Stack::~Stack() {
}

//����� ���������� �������� � ���� (��������� � ������ �����)
void Stack::push(long long value) {
	shiftSliceR(0);
	insertByIndex(value, 0);
}

//����� ��������� ��������, �������� � ������ ����� (�� ������� 0)
long long Stack::peek() {
	if (getElmNum() == 0)
		throw("Exception: stack is empty");
	return getByIndex(0);
}

//����� �������� �������� � ������ �����
void Stack::pop() {
	if (getElmNum() <= 0)
		throw("Exception: stack is empty");
	deleteByIndex(0);
	shiftSliceL(0);
}
