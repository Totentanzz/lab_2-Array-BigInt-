#pragma once
#include "Queue.h"
#include "Stack.h"
#include "BigInt.h"
#include "BigDecimal.h"
#include "DataException.h"

using namespace std;

void test1() {
	Array a(-1);
}

void test2() {
	Array a(3);
	a.reduceCap(3);
}

void test3() {
	Array a(4);
	a.makeEqualSize(1, 2);
}

void test4() {
	Array a(5);
	a.insertByIndex(2, 6);
}

void test5() {
	Array a(6);
	a.deleteByIndex(-2);
}

void test6() {
	Array a(7);
	a.getByIndex(8);
}

void test7() {
	Array a(7);
	a.getSlice(5, 4);
}

void test8() {
	Array a(7);
	a.shiftSliceR(8);
}

void test9() {
	Array a(7);
	a.shiftSliceL(9);
}

void test10() {
	BigInt a("1324ab15.");
}

void test11() {
	BigInt a(1515);
	a.setSign(20);
}

void test12() {
	BigInt a(15213);
	BigInt b("0");
	a.divide(&b);
}

void test13() {
	BigDecimal a("1b32a.12c44");
}

void test14() {
	BigDecimal a("1321244");
}

void test15() {
	BigDecimal b("1234.1325");
	b.setSign(20);
}

void test16() {
	Queue a;
	a.peek();
}

void test17() {
	Queue a;
	a.pop();
}

void test18() {
	Stack a;
	a.peek();
}

void test19() {
	Stack a;
	a.pop();
}

void test20() {
	BigInt abc("9998765351108765351108701440036931448099000"), abc1;
	abc.writeToBinFile("1.txt");
	abc1.readFromBinFile("1.txt");
	cout << abc << abc1;
}

void test21() {
	BigInt first("9998765351108765351108701440036931448099000");
	BigInt second("9998765351108765351108701440036931448099000");
	for (int i = 0; i < 200; i++) {
		cout << first << i << endl;
		first = first * second;
	}
	cout << first;
	for (int i = 0; i < 200; i++) {
		cout << first << i << endl;
		first = first / second;
	}
	cout << first;
}

void test22() {
	BigInt first(8446744073709551617);
	BigInt second(8446744073709551618);
	for (int i = 0; i < 1000; i++) {
		cout << first << i << endl;
		first = first + second;
	}
	cout << first;
	for (int i = 0; i < 1000; i++) {
		cout << first << i << endl;
		first = first - second;
	}
	cout << first;
}

void test23() {
	BigDecimal bd1("8446744073709551618.8446744073709551618");
	BigDecimal bd2("999876535110876535110870144.0036931448099000");
	for (int i = 0; i < 1000; i++) {
		cout << bd1.cStr() << "    " << bd2.cStr() << endl;
		bd1.add(&bd2);
	}
	cout << bd1.cStr() << "    " << bd2.cStr() << endl;
	for (int i = 0; i < 1000; i++) {
		cout << bd1.cStr() << "    " << bd2.cStr() << endl;
		bd1.subtract(&bd2);
	}
	cout << bd1.cStr() << "    " << bd2.cStr() << endl;
}

void runTest(void(*func)(void)) {
	try
	{
		func();
	}
	catch (const DataException& ex)
	{
		cout << ex.what() << '\t' << ex.whatData() << endl;
	}
	catch (const iostream::failure& ex1) {
		cout << ex1.what() << "\nerror code: " << ex1.code() << endl;
	}
	catch (const exception& ex2)
	{
		cout << ex2.what() << endl;
	}
}