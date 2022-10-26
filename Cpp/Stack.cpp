#include "Stack.h"

//Конструктор по умолчанию
Stack::Stack() {
}

//Конструктор, принимающий в качестве параметра размер стэка
Stack::Stack(int size) : Array(size) {
}

//Конструктор копирования
Stack::Stack(const Stack& object) : Array(object) {
}

//Деструктор
Stack::~Stack() {
}

//Метод добавления элемента в стэк (добавляет в начало стэка)
void Stack::push(long long value) {
	shiftSliceR(0);
	insertByIndex(value, 0);
}

//Метод просмотра элемента, лежащего в начале стэка (на позиции 0)
long long Stack::peek() {
	if (getElmNum() == 0)
		throw("Exception: stack is empty");
	return getByIndex(0);
}

//Метод удаления элемента с начала стэка
void Stack::pop() {
	if (getElmNum() <= 0)
		throw("Exception: stack is empty");
	deleteByIndex(0);
	shiftSliceL(0);
}
