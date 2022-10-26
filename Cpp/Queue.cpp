#include "Queue.h"

//Конструктор по умолчанию
Queue::Queue() {
}

//Конструктор, принимающий в качестве параметра размер очереди
Queue::Queue(int size) : Array(size) {
}

//Конструктор копирования
Queue::Queue(const Queue& object) : Array(object) {
}

//Деструктор
Queue::~Queue() {
}

//Метод добавления элемента в конец очереди
void Queue::push(long long value) {
	shiftSliceR(0);
	insertByIndex(value,0);
}

//Метод просмотра элемента из начала очереди
long long Queue::peek() {
	int index = getElmNum() - 1;
	if (index < 0)
		throw("Exception: queue is empty");
	return getByIndex(index);
}

//Метод удаления из начала очереди
void Queue::pop() {
	int index = getElmNum() - 1;
	if (index < 0)
		throw("Exception: queue is empty");
	deleteByIndex(index);
}
