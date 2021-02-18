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

void RBTree::rotateLeft(Node*& ptr) {
	Node* N = ptr->right;
	ptr->right = N->left;
	if(ptr->right) ptr->right->parent = ptr;
	N->left = ptr;
	N->parent = ptr->parent;
	if (!ptr->parent) {
		root = N;
	}
	else if (ptr->parent->right == ptr) {
		ptr->parent->right = N;
	}
	else {
		ptr->parent->left = N;
	}
	ptr->parent = N;
}

void RBTree::rotateRight(Node*& ptr) {
	Node* N = ptr->left;
	ptr->left = N->right;
	if (ptr->left) ptr->left->parent = ptr;

	N->right = ptr;
	N->parent = ptr->parent;

	if (!N->parent) {
		root = N;
	}
	else if (ptr == ptr->parent->right) {
		ptr->parent->right = N;
	}
	else {
		ptr->parent->left = N;
	}

	ptr->parent = N;
}



void RBTree::Insert(int val) { // 3	整个insert 都要注意细节以及循环
	if (root == nullptr) {
		root = new Node(val);
		root->color = BLACK;
		return;
	}
	Node** N = &root;
	Node* P = nullptr;
	while ((*N) != nullptr) {
		P = (*N);
		N = val > (*N)->val ? &((*N)->right) : &((*N)->left);
	}
	(*N) = new Node(val);
	(*N)->parent = P;

	if (P->color == RED) {
		fixInsertRBTree((*N));
	}
}

void RBTree::fixInsertRBTree(Node* N) {
	Node* PP = nullptr, * P = N->parent, *Uncle = nullptr;
	while (getColor(P) == RED && P->parent) {
		PP = P->parent;
		Uncle = PP->left == P ? PP->right : PP->left;
		if (getColor(Uncle) == BLACK) {
			swap(PP->color, P->color); // 换色以保持平衡
			if (P == PP->left) {
				if (N == P->right) {
					swap(P->color, N->color); // 换色以保持平衡
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

		setColor(P, BLACK);
		setColor(Uncle, BLACK);
		setColor(PP, RED);
		N = PP;
		P = N->parent;
	}
}


void RBTree::Remove(int val) {
	cout << "Remove val: " << val << endl;
	_Remove(root, val);
}

void RBTree::_Remove(Node* N, int val){ 
	while (N) {
		if(val == N->val) break;
		N = N->val < val ? N->right : N->left;
	}

	if(N == nullptr) return;

	if (N->left || N->right) {
		Node* M = N->left ? maxValueNode(N->left) : minValueNode(N->right);
		N->val = M->val;
		_Remove(M, M->val);
	}
	else {
		Node* P = N->parent;
		if (P == nullptr) {
			root = nullptr;
			return;
		}
		if (getColor(N) == BLACK) {
			fixRemoveRBTree(P, N);
		}
		if (N == P->left) {
			P->left = nullptr;
		}
		else {
			P->right = nullptr;
		}
	}

}


void RBTree::fixRemoveRBTree(Node*P, Node* N) {
	Node* Bro = nullptr;
	while (N != root && getColor(N) == BLACK) {  // 循环条件：只有当N为黑时，才可能破坏平衡
		if (N == P->left) {
			Bro = P->right;
			if (Bro->color == RED) {
				swap(Bro->color, P->color);
				rotateLeft(P);
				Bro = P->right;
			}

			if(getColor(Bro->left) == BLACK && getColor(Bro->right) == BLACK){
				int pColor = P->color;
				setColor(P, BLACK);
				setColor(Bro, RED);
				N = P;
				if(pColor == RED) break;
			}

			if (getColor(Bro->right) == BLACK && getColor(Bro->left) == RED) {
				swap(Bro->left->color, Bro->color);
				rotateRight(Bro);
				Bro = P->right;
			}

			if (getColor(Bro->right) == RED) {
				Bro->right->color = BLACK;  // 因为要将Bro的黑移到另一边，因此补一个黑
				swap(Bro->color, P->color);
				rotateLeft(P);
				break;
			}
		}
		else {
			Bro = P->left;
			if (Bro->color == RED) {
				swap(Bro->color, P->color);
				rotateRight(P);
				Bro = P->left;
			}

			if (getColor(Bro->left) == BLACK && getColor(Bro->right) == BLACK) {
				int pColor = P->color;
				setColor(P, BLACK);
				setColor(Bro, RED);
				N = P;
				if (pColor == RED) break;
			}

			if (getColor(Bro->left) == BLACK && getColor(Bro->right) == RED) {
				swap(Bro->right->color, Bro->color);
				rotateLeft(Bro);
				Bro = P->left;
			}

			if (getColor(Bro->left) == RED) {
				Bro->left->color = BLACK;
				swap(Bro->color, P->color);
				rotateRight(P);
				break;
			}
		}


		P = N->parent;
	}
	root->color = BLACK;
}


