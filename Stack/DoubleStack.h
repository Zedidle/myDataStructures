#include "iostream"
#include "vector"
#include "string"
#include "map"
using namespace std;



namespace DoubleStack {


	class DoubleStack {
		int length;
		int* head;
		int leftend = 0;
		int rightend;

		int leftsize = 0;
		int rightsize = 0;

		public:
		DoubleStack(int len) {
			length = len;
			head = (int*) malloc(sizeof(int)*length);
			rightend = length-1;
		}

		void push(int value, int dir) {
			if (leftend > rightend) {
				cout << "FULL" << endl;
				return;
			}

			if (dir == 0) {
				*(head + leftend) = value;
				leftend ++;
				leftsize ++;
			}
			else {
				*(head + rightend) = value;
				rightend--;
				rightsize++;
			}
		}

		void pop(int dir) {
			if (dir == 0) {
				if (leftend > 0) {
					leftend --;
					*(head + leftend) = NULL;
					leftsize --;
				}
				else {
					cout << "LeftStack Empty" << endl;
				}
			}
			else {
				if (rightend < length - 1) {
					rightend ++;
					*(head + rightend) = NULL;
					rightsize -- ;
				}
				else {
					cout << "RightStack Empty" << endl;
				}
			}
		}

		void check() {
			cout << "leftsize: " << leftsize << endl;
			cout << "rightsize: " << rightsize << endl; 
			for (int i = 0; i < length; i++) {
				cout << *(head + i) << " ";
			}
			cout <<endl;
		}
	};


	void Test() {
		DoubleStack dStack(21);
		for (int i = 0; i < 21; i++) {
			dStack.push(i, i % 2== 0);
		}
		dStack.check();
		for (int i = 0; i < 32; i++) {
			dStack.pop(i % 2 == 0);
		}
		dStack.check();
	}

}
