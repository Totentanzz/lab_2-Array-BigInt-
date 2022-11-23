#define _CRT_SECURE_NO_WARNINGS

#include "Test.h"

using namespace std;

void main() {
	BigInt third("999876535110876535110870144003693144809900000");
	BigInt fourth("9998765351108765351108701440036931448099000");
	runTest(test20);
	/*for (int i = 0; i < 1; i++) {
		cout << third << i << endl;
		third = third + sac;
	}
	cout << third;
	for (int i = 0; i < 1; i++) {
		cout << third << i << endl;
		third = third - sac;
	}
	cout << third;*/
}