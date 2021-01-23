#include <string>
#include <iostream>
#include <algorithm>
using namespace std;


namespace TreeHead {
	template<typename T>
	class SmallHeap {
		T* vec = new T;
		T* head = vec;
		T* cur = head;
		T* end;
		int size;
		public:
			SmallHeap(int size) {
				this->size = size;
				vec = (T*)malloc(sizeof(T) * 10);
				end = vec + size;
			}

			void push_back(T t) {
				if(cur == end) return;
				*cur = t;
				cur ++;
				cout << "push_back cur: "<< cur << endl;
			}

			void Show() {
				T* temp = head;
				while (temp != cur) {
					cout << *temp << " ";
					temp ++ ;
				}
				cout << endl;
			}

			~SmallHeap() { 
				// 为何直接关掉，无法释放内存；导致下次启动时奔溃
				while (head != end) {
					delete head;
					head++;
				}
			}
	};

	void Test() {
		//int *p = new int(10);
		//cout << *p <<endl;
		//int i = 20;
		//*p = i;
		//cout << *p << endl;

		SmallHeap<int>* sHeap = new SmallHeap<int>(100);
		for (int i = 0; i < 10; i++) {
			sHeap->push_back(i);
		}
		sHeap->Show();
	}
}

