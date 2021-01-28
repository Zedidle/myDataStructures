#include "iostream"
#include "vector"
using namespace std;





namespace BinaryTree{

	class BinaryTree {
		struct Node {
			Node(int val) {
				val = val;
				count = 1;
				height = 1;
				Node* parent = nullptr;
				Node* left = nullptr;
				Node* right = nullptr;
			}

			Node* parent;
			Node* left;
			Node* right;
			int val;
			int count;
			int height;
		};

		Node* root;
		
		public:
			BinaryTree() {
				root = nullptr;
			}


		void insert(int val) {
			if (root == nullptr) {
				root = new Node(val);
			}
			Node* tmp = root;
			Node* pre;
			int dir = 0;
			while (tmp != nullptr) {
				pre = tmp;
				if (tmp->val > val) {
					tmp = tmp->left;
					dir = 0;
				}
				else if (tmp->val < val) {
					tmp = tmp->right;
					dir = 1;
				}
			}
			Node* tmp = new Node(val);
			tmp->parent = pre;
			if (dir) {
				pre->right = tmp;
			}
			else {
				pre->left = tmp;
			}
		}

		void InorderTraverse() {
			_InorderTraverse(root);
		}

		private:
		void _InorderTraverse(Node* node) {
			if(node == nullptr) return;
			_InorderTraverse(node->left);
			cout << node->val << ", " << node->parent->val << endl;
			_InorderTraverse(node->right);
		}
	};


	void Test() {
		BinaryTree bTree;
		vector<int> ins_values = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		for (int i : ins_values) {
			bTree.insert(i);
		}
		bTree.InorderTraverse();
	}

};