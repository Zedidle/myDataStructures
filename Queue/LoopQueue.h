#include "iostream"
#include "map"
using namespace std;


namespace LoopQueue {

	// 循环队列顺序存储版
	class LoopQueue {
		int* head;
		int start=0, end=0;
		int length;
		
		public:
			LoopQueue(int len) {
				length = len+1;
				head = (int*)malloc(sizeof(int) * length);
			}

			int get(int index) {
				return *(head + (start + index) % length);
			}

			void push(int value) {
				if ((end+1) % length == start) {
					cout<< "FULL!!!" << endl;
					return;
				}
				*(head + end) = value;
				 end = (end + 1) % length;
			}
			void pop() {
				if (start == end) {
					cout << "EMPTY!!!" << endl;
					return;
				}
				*(head + start) = NULL;
				start = (start + 1) % length;
			}

			void check() {
				int i = start;
				while (i != end) {
					cout << *(head + i) << " ";
					i = (i+1) % length;
				}
				cout << endl;
			}

			void checkCapacity() {
				int *temp = head;
				for (int i = 0; i < length-1; i++) {
					cout << temp << ":" << *(temp + i) << endl;
				}
			}
	};

	void Test() {
		LoopQueue lQueue(20);
		for (int i = 0; i < 20; i++) {
			lQueue.push(i);
		}
		for (int i = 0; i < 7; i++) {
			lQueue.pop();
		}
		for (int i = 10; i < 20; i++) {
			lQueue.push(i);
		}
		lQueue.check();

		cout << lQueue.get(0) << endl;
		cout << lQueue.get(2) << endl;
		cout << lQueue.get(5) << endl;
		cout << lQueue.get(8) << endl;
	}


	// 循环队列链式存储
	class LoopList {
		struct Node {
			int val = 0;
			Node* next = nullptr;
			Node* front = nullptr;

			~Node() {

			}
		};
		
		Node* head;
		Node* rear;
		int length;


		public:
			LoopList() {
				head = rear = (Node*) malloc (sizeof(Node));
			}

			void push(int value) {
				rear->val = value;
				rear->next = (Node*)malloc(sizeof(Node));
				rear->next->front = rear;
				rear = rear->next;
			}
			void pop() {
				if (head == rear) {
					cout << "EMPTY" <<endl;
					return;
				}
				Node* p = head;
				head = head->next;
				head->front = nullptr;
				delete p;
			}

			void check() {
				Node* p = head;
				while (p != rear) {
					cout << p->val << " ";
					p = p->next;
				}
				cout << endl;
			}

	};

	void Test1() {
		LoopList lList;
		for (int i = 0; i < 10; i++) {
			lList.push(i);
		}
		lList.check();
		for (int i = 0; i < 3; i++) {
			lList.pop();
		}
		lList.check();
		for (int i = 0; i < 10; i++) {
			lList.push(i+30);
		}
		lList.check();
		for (int i = 0; i < 13; i++) {
			lList.pop();
		}
		lList.check();

	}

}