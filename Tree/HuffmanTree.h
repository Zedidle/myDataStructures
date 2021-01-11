#include "iostream"
#include "vector"
#include "algorithm"
#include "map"
using namespace std;



namespace Huffman {
	struct Node {
		Node(int p) : power(p) {}
		Node(char c, int p) : c(c), power(p) {}

		int power = 0;
		int val = 0;
		char c;
		Node* L = nullptr;
		Node* R = nullptr;
	};

	class HuffmanTree {
		Node* root = nullptr;

		void InsertOrderList(vector<Node*> &F, Node* t) {
			F.push_back(t);
			int i = F.size()-1;
			while (i>0) {
				if (F[i - 1]->power > F[i]->power) {
					swap(F[i - 1], F[i]);
					i--;
				}
				else {
					break;
				}
			}
		}


		public:
			map<string, char> CodeToChar;
			map<char, string> CharToCode;
			Node* GetRoot() {
				return root;
			}

			HuffmanTree(vector<int> powers) {
				int n = powers.size();
				if (n == 1) {
					root = new Node(powers[0]);
				}

				sort(powers.begin(), powers.end());
				vector<Node* > F;
				for (int power : powers) {
					F.push_back(new Node(power));
				}
				Node* t = nullptr;
				while (F.size() > 1) {
					t = new Node(F[0]->power + F[1]->power);
					t->L = F[0];
					t->R = F[1];
					F.erase(F.begin(), F.begin() + 2);
					InsertOrderList(F, t);
				}
				root = t;
				t = NULL;
				delete t;
			}

			HuffmanTree(vector<pair<char, int>> powers) {
				int n = powers.size();
				if (n == 1) {
					root = new Node(powers[0].first, powers[0].second);
				}

				vector<Node* > F;
				for (auto power : powers) {
					F.push_back(new Node(power.first, power.second));
					//cout << "Consturctor, first, second : " << power.first << ", " << power.second << endl;
				}


				Node* t = nullptr;
				while (F.size() > 1) {
					t = new Node('_', F[0]->power + F[1]->power);
					t->L = F[0];
					t->R = F[1];
					F.erase(F.begin(), F.begin() + 2);
					InsertOrderList(F, t);
				}
				root = t;
				t = NULL;
				delete t;
			}

			void ShowCode() {
				for (auto m : CodeToChar) {
					cout << m.first << ": " << m.second << endl;
				}
				
			}

			void InorderTravesal() {
				_InorderTravesal(root);
			}

			void MakeCodeforchar() {
				_MakeCodeforchar(root, "");
			}

		private:
			void _InorderTravesal(Node* n) {
				if(n == nullptr) return;
				_InorderTravesal(n->L);
				if (n->L == nullptr && n->R == nullptr) {
					cout << "p, v, c: " << n->power << "，" << n->val << ", " << n->c << endl;
				}
				_InorderTravesal(n->R);
			}

			void _MakeCodeforchar(Node* n, string code) {
				if (n == nullptr) return;
				_MakeCodeforchar(n->L, code + '0');
				if (n->L == nullptr && n->R == nullptr) {
					CodeToChar[code] = n->c;
					CharToCode[n->c] = code;
				}
				_MakeCodeforchar(n->R, code + '1');
			}

	};

	void Test() {
		vector<int> powers = { 3,5,6,2,8,67,7 };
		HuffmanTree* hTree = new HuffmanTree(powers);
		hTree->InorderTravesal();
	}

	// 赫夫曼编码 每种编码都有一颗对应的赫夫曼树作为解码，而在编码时为字符设置权重来构建赫夫曼树； 作用是压缩一段文本；
	class HuffmanCode {
		HuffmanTree* hTree = nullptr;
		int total;

		public:
		string GetCodeByString(string s) {
			total = s.size();
			map<char, int> record;
			vector<pair<char, int>> powers;
			for (auto c : s) {
				if (record.find(c) == record.end()){
					record[c] = 1;
				}
				else {
					record[c]++;
				}
			}
			for (auto m : record) {
				if (m.second > 0) {
					powers.push_back({ m.first, m.second });
				}
			}

			sort(powers.begin(), powers.end(), [](pair<char, int> a, pair<char,int> b)->bool{
				return a.second < b.second;
			});

			if (hTree != nullptr) {
				delete hTree;
			}
			hTree = new HuffmanTree(powers);
			hTree->MakeCodeforchar();

			string ans = "";
			for (char c : s) {
				ans += hTree->CharToCode[c];
			}
			return ans;
		}

		void InorderTravesal() {
			if(hTree == nullptr) return;
			cout <<"total: " << total << endl;
			hTree->InorderTravesal();
		}

		string GetStringByCode(string code) {
			if (hTree == nullptr){
				cout << "You must 'GetCode' before 'GetString'";
			}
			string ans = "";
			Node* n = hTree->GetRoot();
			for (auto c : code) {
				if (n->L == nullptr && n->R == nullptr) {
					ans += n->c;
					n = hTree->GetRoot();
				}
				if (c == '0') {
					n = n->L;
				}
				else {
					n = n->R;
				}
			}
			if (n->L == nullptr && n->R == nullptr) {
				ans += n->c;
			}

			return ans;
		}

		void ShowCode() {
			hTree->ShowCode();
		}


	};


	void Test1() {
		HuffmanCode hCode;
		string s = "aaaaaaabbbbbccccccccccccdddddddddddddddddddddddddddddeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee";
		string code0 = hCode.GetCodeByString(s);
		cout <<"code0 :" << code0 << endl;
		string s1 = hCode.GetStringByCode(code0);
		cout << "code0 to string: " << s1 << endl;
		cout << "same:" << int(s == s1) << endl;

		cout << endl;


		//hCode.InorderTravesal();
		hCode.ShowCode();
		cout << endl;

		// 测试直接GetCodeByString 刷新
		string s2 = "abbcccddddeeeee";
		hCode.GetCodeByString(s2);
		hCode.ShowCode();


		string code = "010011011000000101010101111111111";
		cout << hCode.GetStringByCode(code) << endl;
	}




}