#include "bits/stdc++.h"
//#include "iostream"
#include "RedBlackTree.h"
using namespace std;

RBTree::Node::Node(int val) {
	this->val = val;
	color = RED;
	left = right = parent = nullptr;
}

RBTree::RBTree() {
	root = nullptr;
}

int RBTree::getColor(Node*& node) {
	if (node == nullptr) {
		return BLACK;
	}
	return node->color;

}

void RBTree::setColor(Node*& node, int color) {
	if(node == nullptr) return;
	node->color = color;
}


void RBTree::rotateLeft(Node*& ptr) {
	Node* R = ptr->right;
	ptr->right = R->left;
	if (ptr->right != nullptr) { // 1 不要忽视nullptr的情况，边界条件很重要
		ptr->right->parent = ptr;
	}

	R->left = ptr;
	R->parent = ptr->parent;

	if (R->parent == nullptr) { // 2 别漏了根节点
		root = R;
	}
	else if (ptr == ptr->parent->left) {
		ptr->parent->left = R;
	}
	else {
		ptr->parent->right = R;
	}

	ptr->parent = R;
}

void RBTree::rotateRight(Node*& ptr) {
	Node* L = ptr->left;
	ptr->left = L->right;
	if (ptr->left != nullptr) {
		ptr->left->parent = ptr;
	}

	L->right = ptr;
	L->parent = ptr->parent;

	if (L->parent == nullptr) {
		root = L;
	}
	else if (ptr == ptr->parent->right) {
		ptr->parent->right = L;
	}
	else {
		ptr->parent->left = L;
	}

	ptr->parent = L;
}


void RBTree::Insert(int val) { // 3	整个insert 都要注意细节以及循环
	cout << "ins val: " << val << endl;
	Node* node = new Node(val), * P = nullptr, **N = &root;

	if (root == nullptr) {
		root = node;
		setColor(root, BLACK);
		return;
	}

	while (nullptr != *N) {
		if ((*N)->val == val) return; // 重复
		P = *N;
		N = (*N)->val > val ? &((*N)->left) : &((*N)->right);
	}

	(*N) = node;
	(*N)->parent = P;

	fixInsertRBTree(*N);
}

void RBTree::fixInsertRBTree(Node* N) {
	Node* P = N->parent, *PP = nullptr, *Uncle = nullptr;

	while (getColor(P) == RED && P->parent!=nullptr) {
		PP = P->parent;
		Uncle = P == PP->left ? PP->right : PP->left;

		if(getColor(Uncle) == BLACK){
			swap(P->color, PP->color); // 8 因为P为RED，因此PP必然为BLACK，换色的目的在于旋转前后维持支点颜色
			if (P == PP->left) {
				if (N == P->right) {
					swap(P->color, N->color);
					rotateLeft(P);
				}
				rotateRight(PP);
			}
			else {
				if (N == P->left) {
					swap(P->color, N->color);
					rotateRight(P);
				}
				rotateLeft(PP);
			}

			break;
		}

		setColor(Uncle, BLACK);
		setColor(P, BLACK);
		setColor(PP, RED);
		N = PP;
		P = N->parent;
	}

	setColor(root, BLACK);
}


void RBTree::Remove(int val) {
	cout << "Remove val: " << val << endl;
	_Remove(root, val);
}

void RBTree::_Remove(Node* N, int val){ 
	while (nullptr != N) { // 4 注意循环条件
		if(N->val == val) break;
		N = N->val > val ? N->left : N->right;
	}
	if(N == nullptr) return;

	if (N->left != nullptr || N->right != nullptr) { // 5 这样的||方式会让下面的代码简洁很多
		Node* M = (N->left != nullptr) ? maxValueNode(N->left) : maxValueNode(N->right);
		N->val = M->val;
		_Remove(M, M->val);
	}
	else {
		Node* P = N->parent;
		if (N->color == RED) { // 6 记得红色直接删除，自然推出else的黑色情况
			if (P->left == N) {
				P->left = nullptr;
			}
			else {
				P->right = nullptr;
			}
		}
		else {
			if (P == nullptr) {
				root = nullptr;
				return;
			}

			if (P->left == N) {
				fixRemoveRBTree(P, P->left);
				P->left = nullptr;
			}
			else {
				fixRemoveRBTree(P, P->right);
				P->right = nullptr;
			}
		}
	}
}


void RBTree::fixRemoveRBTree(Node*P, Node* N) {
	Node* W = nullptr;
	while (N != root && getColor(N) == BLACK) { // 9 注意理解循环条件
		if (N == P->left) {
			W = P->right;
			if (getColor(W) == RED) {
				swap(P->color, W->color);
				rotateLeft(P);
				W = P->right;
			}

			if (getColor(W->left) == BLACK && getColor(W->right) == BLACK) {
				cout << "a2" << endl;
				int pColor = P->color;
				P->color = BLACK;
				W->color = RED;
				N = P;

				if (pColor == RED) break;
			}

			if (getColor(W->left) == RED && getColor(W->right) == BLACK) {
				swap(W->color, W->left->color);
				rotateRight(W);
			}

			if (getColor(W->right) == RED) {
				W->right->color = W->color;
				W->color = P->color;
				P->color = BLACK;
				rotateLeft(P);
				break;
			}
		}
		else {
			W = P->left;
			if (W->color == RED) {
				swap(P->color, W->color);
				rotateRight(P);
				W = P->left;
			}

			if (getColor(W->right) == BLACK && getColor(W->left) == BLACK) {
				int pColor = P->color;
				P->color = BLACK;
				W->color = RED;
				N = P;

				if (pColor == RED) break;
			}

			if (getColor(W->right) == RED && getColor(W->left) == BLACK) {
				swap(W->color, W->right->color);
				rotateLeft(W);
			}

			if (getColor(W->left) == RED) {
				W->left->color = W->color;
				W->color = P->color;
				P->color = BLACK;
				rotateRight(P);
				break;
			}
		}
		P = N->parent; // 10 让循环继续下去有意义
	}

	root->color = BLACK;
}


RBTree::Node* RBTree::minValueNode(Node*& node) {
	Node* t = node;
	while (t->left != nullptr) {
		t = t->left;
	}
	return t;
}

RBTree::Node* RBTree::maxValueNode(Node*& node) {
	Node* t = node;
	while (t->right != nullptr) {
		t = t->right;
	}
	return t;
}
