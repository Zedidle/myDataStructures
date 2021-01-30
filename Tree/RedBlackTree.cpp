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
		//ptr->right->parent = R;
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

	if (nullptr == *N) {
		(*N) = node;
		(*N)->parent = P;
	}

	fixInsertRBTree(*N);
}

void RBTree::fixInsertRBTree(Node* N) {
	Node* P = N->parent, *PP = nullptr, *Uncle = nullptr;

	while (P != nullptr && P->parent !=nullptr) {
		if(P->color == BLACK) break;
		PP = P->parent;
		Uncle = PP->left == P ? PP->right : PP->left;

		// 因此，导致双红冲突时，只有两种状况：
		if ((Uncle == nullptr) || (Uncle->color == BLACK)) {  // 1，叔叔结点为空或为黑色，旋转调整之后直接终结；
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

}



void RBTree::fixRemoveRBTree(Node*& node) {
	
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