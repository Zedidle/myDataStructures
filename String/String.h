#include "iostream"
using namespace std;

namespace String {
	
	
	int find_substr(string a, string b) {
		int n = a.size();
		int i = 0;
		while (i < n) {
			int k = 0;
			if (a[i] = b[k]) {
				int j = i;
				while (j < n && k < b.size()) {
					if (a[j] != b[k]) break;
					j++;
					k++;
				}
				if(k == b.size()) return i;
			}
			i++;
		}
		return -1;
	}


	// KMP算法 ？


	

	void Test() {
		string a = "gggooollhello";
		cout << a.find("hello") << endl;
		cout << find_substr(a, "hel2lo") << endl;

		cout << int('1') <<endl;
		a += 'a';
		cout << a << endl;

	}
	


}
