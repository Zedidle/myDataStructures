#include "iostream"
using namespace std;
#include "vector"
#include "algorithm"





namespace BinaryTree{

	// AVLTree
	class AVLTree {
		struct Node {
			Node(int val) {
				this->val = val;
				count = 1;
				height = 1;
				parent = nullptr;
				left = nullptr;
				right = nullptr;
			}

			Node* parent;
			Node* left;
			Node* right;
			int val;
			int count;
			int height;

			Node* left_Rotate() {
				Node* R = right;
				right = R->left;
				R->left = this;
				R->parent = parent;
				parent = R;
				updateValue();
				R->updateValue();
				return R;
			}

			Node* right_Rotate() {
				Node* L = left;
				left = L->right;
				L->right = this;
				L->parent = parent;
				parent = L;
				updateValue();
				L->updateValue();
				return L;
			}

			void updateValue() {
				count = (left==nullptr?0:left->count) + (right==nullptr?0:right->count) + 1;
				height = max(left==nullptr?0:left->height, right == nullptr ? 0 : right->height) + 1;
			}
			int GetBalanceFactor() {
				return (left == nullptr ? 0 : left->height) - (right == nullptr ? 0 : right->height);
			}
		};

		Node* root;
		
		public:
			AVLTree() {
				root = nullptr;
			}

			void insert2(int val) {
				if (root == nullptr) {
					root = new Node(val);
					return;
				}
				vector<Node**> path;
				Node** tmp = &root;
				Node** pre = &root;
				int dir;
				while ((*tmp) != nullptr) {
					pre = tmp;
					path.push_back(tmp);
					if ((*tmp)->val > val) {
						tmp = &((*tmp)->left);
						dir = 0;
					}
					else if ((*tmp)->val < val) {
						tmp = &((*tmp)->right);
						dir = 1;
					}
				}
				if((*tmp) == (*pre)) return;

				(*tmp) = new Node(val);
				(*tmp)->parent = (*pre);
				path.push_back(pre);
				if (dir) {
					(*pre)->right = *tmp;
				}
				else {
					(*pre)->left = *tmp;
				}
				balance(path);
			}

			void balance(vector<Node**> & path) {
				reverse(path.begin(), path.end());
				for (Node**& p : path) {
					(*p)->updateValue();
					if ((*p)->GetBalanceFactor() >= 2) {
						if ((*p)->left->left == nullptr) { // LR
							(*p)->left = (*p)->left->left_Rotate();
						}
						(*p) = (*p)->right_Rotate(); // LL
					}
					else if ((*p)->GetBalanceFactor() <= -2) {
						if ((*p)->right->right == nullptr) { // RL
							(*p)->right = (*p)->right->right_Rotate();
						}
						(*p) = (*p)->left_Rotate(); // RR
					}
				}
			}

			Node* minValueNode(Node* node) {
				if(node == nullptr) return nullptr;
				while (node->left != nullptr) {
					node = node->left;
				}
				return node;
			}

		void insert(int val) {
			if (root == nullptr) {
				root = new Node(val);
				return;
			}
			_insert(root, val);
		}


		void remove(int val) {
			if (root == nullptr) return;
			vector<Node**> path;
			Node** tmp;
			_remove(root, val, path, tmp);
			balance(path);
		}



		void InorderTraverse() {
			_InorderTraverse(root);
		}


		void display() {
			printf("\n");
			if (root != nullptr)
				display(root, 1, 0);
			else
				printf("Empty");
			printf("\n");
		}

		void display(Node* cur, int depth, int state) {  // state: 1 -> left, 2 -> right , 0 -> root
			if(cur == nullptr) return;
			display(cur->right, depth + 1, 2);

			for (int i = 0; i < depth; i++)
				printf("     ");

			if (state == 1) // left
				printf("└───");
			else if (state == 2)  // right
				printf("┌───");

			std::cout << "[" << cur->val << "] - (" << cur->count << ", " << cur->height << ")" << std::endl;

			display(cur->left, depth + 1, 1);
		}

	private:
		void _InorderTraverse(Node* node) {
			if (node == nullptr) return;
			_InorderTraverse(node->left);
			cout << node->val << ", ";
			if (node->parent != nullptr) {
				cout << node->parent->val << endl;
			}
			_InorderTraverse(node->right);
		}

		void _insert(Node* node, int val) {
			if (val < node->val) {
				if (node->left == nullptr) {
					node->left = new Node(val);
					node->left->parent = node;
				}
				else {
					_insert(node->left, val);
				}
			}
			else if (val > node->val) {
				if (node->right == nullptr) {
					node->right = new Node(val);
					node->right->parent = node;
				}
				else {
					_insert(node->right, val);
				}
			}
		}

		void _remove(Node*& node, int val, vector<Node**> &path, Node**& tmp) {
			tmp = &node;
			while ((*tmp) != nullptr) {
				path.push_back(tmp);
				if ((*tmp)->val > val) {
					tmp = &((*tmp)->left);
				}
				else if ((*tmp)->val < val) {
					tmp = &((*tmp)->right);
				}
				else {
					break;
				}
			}
			if ((*tmp) == nullptr) return;
			if ((*tmp)->left == nullptr && (*tmp)->right == nullptr) { // 叶子结点，直接删除
				if ((*tmp)->parent->left == (*tmp)) {
					(*tmp)->parent->left = nullptr;
				}else if((*tmp)->parent->right == (*tmp)) {
					(*tmp)->parent->right = nullptr;
				}
				path.pop_back();
				delete (*tmp);
			}
			else if ((*tmp)->right == nullptr) { // 没有右子树，直接用左子树代替
				(*tmp)->val = (*tmp)->left->val;
				delete (*tmp)->left; // 很明显，作为左值和右值有区别
				(*tmp)->left = nullptr;
			}
			else {
				Node* m = minValueNode((*tmp)->right);
				(*tmp)->val = m->val;
				_remove((*tmp)->right, m->val, path, tmp);
			}

		}
	};

	void AVLTree_Test() {
		AVLTree avlTree;
		vector<int> ins_values = { 7, 1, 6, 8, 9, 2, 3, 4, 5, 10, 12, 11, 23, 43, 56, 75 };
		for (int i : ins_values) {
			avlTree.insert2(i);
			//avlTree.insert(i);
		}
		avlTree.display();

		cout << "After remove" << endl;
		vector<int> del_values = { 3, 4, 5, 65, 43, 11, 75, 56 };
		for (int i : del_values) {
			avlTree.remove(i);
		}
		avlTree.display();
		//avlTree.InorderTraverse();
	}

	void Test() {
		AVLTree_Test();
	}

}