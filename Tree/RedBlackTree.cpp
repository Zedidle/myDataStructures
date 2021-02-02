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
	if (node == nullptr)
		return BLACK;

	return node->color;
}

void RBTree::setColor(Node*& node, int color) {
	if (node == nullptr) return;
	node->color = color;
}




void RBTree::rotateLeft(Node*& ptr) {
	Node* R = ptr->right;
	ptr->right = R->left;
	if (ptr->right != nullptr) {
		ptr->right->parent = ptr;
	}
	R->parent = ptr->parent;
	R->left = ptr;

	if (R->parent == nullptr) {
		root = R;
	}
	else if (ptr->parent->left == ptr) {
		ptr->parent->left = R;
	}
	else if (ptr->parent->right == ptr) {
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
	L->parent = ptr->parent;
	L->right = ptr;
	if (L->parent == nullptr) {
		root = L;
	}
	else if (ptr->parent->left == ptr) {
		ptr->parent->left = L;
	}
	else if (ptr->parent->right == ptr) {
		ptr->parent->right = L;
	}

	ptr->parent = L;
}


void RBTree::Transplant(Node* N, Node* T)
{	
	if (N->parent == nullptr) {
		root = T;
	}
	else if(N == N->parent->left){
		N->parent->left = T;
	}
	else {
		N->parent->right = T;
	}
	if (T != nullptr) {
		T->parent = N->parent;
	}
}


void RBTree::Insert(int val) {
	//cout << "ins val:" << val << endl;
	Node* node = new Node(val);
	Node* P = nullptr;
	Node** N = &root;

	if ((*N) == nullptr) {
		(*N) = node;
		setColor(node, BLACK);
		return;
	}

	while (nullptr != *N) {
		if((*N)->val == val) return; // 已经有值了，直接退出
		P = *N;
		N = (*N)->val > val ? &((*N)->left) : &((*N)->right);
	}

	(*N) = node;
	(*N)->parent = P;

	fixInsertRBTree(*N);
}

void RBTree::fixInsertRBTree(Node* N) {
	Node* P = N->parent, *PP = nullptr, *Uncle = nullptr;

	while (P != nullptr && P->parent !=nullptr) {
		if(P->color == BLACK) break;
		PP = P->parent;
		Uncle = PP->left == P ? PP->right : PP->left;

		// 因此，导致双红冲突时，只有两种状况：
		if (getColor(Uncle) == BLACK) {  // 1，叔叔结点为空或为黑色，旋转调整之后直接终结；
			if (PP->left == Uncle) {
				if (P->left == N) {
					swap(PP->color, N->color);
					rotateRight(P);
				}
				rotateLeft(PP);
			}
			else {
				if (P->right == N) {
					swap(PP->color, N->color);
					rotateLeft(P);
				}
				rotateRight(PP);
			}
			swap(PP->color, P->color);
			break;
		}

		// 2. 叔叔结点为红色，直接将红色提级，进入下一轮循环；
		setColor(PP, RED);
		setColor(P, BLACK);
		setColor(Uncle, BLACK);
		N = PP;
		P = PP->parent;
	}

	setColor(root, BLACK);
}





void RBTree::Remove(int val) {
	cout << "Remove val: " << val << endl;
	_Remove(root, val);
}

void RBTree::_Remove(Node* z, int val){
	// 找到对应值的结点
	while (z != nullptr) {
		if (z->val == val) break;
		z = z->val < val ? z->right : z->left;
	}
	if (z == nullptr) return; // 找不到则跳出

	Node* y = nullptr;
	if (z->left) {
		y = maxValueNode(z->left);
		z->val = y->val;
		_Remove(y, y->val);
	}
	else if (z->right) {
		y = minValueNode(z->right);
		z->val = y->val;
		_Remove(y, y->val);
	}
	else{
		Node* p = z-> parent;
		if (z->color == RED) {
			if (p->left == z) {
				p->left = nullptr;
			}
			else {
				p->right = nullptr;
			}
		}
		else {
			if (p == nullptr) {
				root = nullptr;
				return;
			}

			if (p->left == z) {
				fixRemoveRBTree(p, p->left);
				p->left = nullptr;
			}
			else {
				fixRemoveRBTree(p, p->right);
				p->right = nullptr;
			}
		}
	}
}


void RBTree::fixRemoveRBTree(Node*P, Node* N) {
	Node* W = nullptr;
	while (N != root && getColor(N) == BLACK) {
		//Display();
		if (N == P->left) {
			cout << "toLeft" << endl;
			W = P->right;
			// ① W是红色，必定有黑色子结点，所以可以交换P 和 W的颜色，然后P左旋；
			if (getColor(W) == RED) {
				cout << "a1" << endl;
				swap(P->color, W->color);
				rotateLeft(P);
				W = P->right;
			}

			if (getColor(W->left) == BLACK && getColor(W->right) == BLACK) { // ②
				cout << "a2.1" << endl;
				int pColor = P->color;
				P->color = BLACK;
				W->color = RED;
				N = P;
				if (pColor == RED) break;
			}
			else {
				cout << "a33" << endl;
				// ③ RL: W 为黑色, WL 为红色, 交换W 及 WL的颜色，然后把W右旋，再刷新W；
				if (getColor(W->left) == RED && getColor(W->right) == BLACK) {
					cout << "a3" << endl;
					W->left->color = P->color;
					P->color = BLACK;
					rotateRight(W);
					rotateLeft(P);
				}else if (getColor(W->right) == RED) { // ④ RR:  WR 为红色，将W的颜色给WR，P的颜色给W；然后P左旋
					cout << "a4" << endl;
					W->right->color = W->color;
					W->color = P->color;
					P->color = BLACK;
					rotateLeft(P);
				}
				break;
			}
		}
		else {
			cout << "toRight" << endl;
			W = P->left;
			// ① 
			if (getColor(W) == RED) {
				cout << "b1" << endl;
				swap(P->color, W->color);
				rotateRight(P);
				W = P->left;
			}

			if (getColor(W->left) == BLACK && getColor(W->right) == BLACK) { // ②
				cout << "b2.1" << endl;
				int pColor = P->color;
				P->color = BLACK;
				W->color = RED;
				N = P;
				if(pColor == RED) break;
			}
			else {
				cout << "b33" << endl;
				// ③
				if (getColor(W->right) == RED && getColor(W->left) == BLACK) {
					cout << "b3" << endl;
					W->right->color = P->color;
					P->color = BLACK;
					rotateLeft(W);
					rotateRight(P);
				}else if (getColor(W->left) == RED) { // ④
  					cout << "b4" << endl;
					W->left->color = W->color;
					W->color = P->color;
					P->color = BLACK;
					rotateRight(P);
				}
				break;
			}
		}
		P = N->parent;
	}
	root->color = BLACK;
}


RBTree::Node* RBTree::minValueNode(Node*& node) {
	Node* ptr = node;

	while (ptr->left != nullptr) {
		ptr = ptr->left;
	}

	return ptr;
}

RBTree::Node* RBTree::maxValueNode(Node*& node) {
	Node* ptr = node;

	while (ptr->right != nullptr) {
		ptr = ptr->right;
	}

	return ptr;
}

int RBTree::getBlackHeight(Node* node) { // 获得以当前结点为根节点的树的黑高
	int blackheight = 0;
	while (node != nullptr) {
		if (getColor(node) == BLACK) {
			blackheight++;
		}
		node = node->left;
	}
	return blackheight;
}



void RBTree::Merge(RBTree rbTree2) {

}



