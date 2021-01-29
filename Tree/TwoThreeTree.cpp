#include <stdexcept>
#include <iostream>
using namespace std;
#include <string>

#include "TwoThreeTree.h"

TwoThreeTree::Node::Node(int val){
	parent = nullptr;
	fchild = nullptr;
	schild = nullptr;
	tchild = nullptr;

	lval = val;
	mval = rval = MAX;
	num = 1;
}

void TwoThreeTree::Node::showVal()
{
	cout << "[" << lval;
	if (rval != MAX) {
		cout << ", " << rval;
	}
	cout << "]" << endl;
}

bool TwoThreeTree::Node::isLeaf() {
	return fchild == nullptr && schild == nullptr && tchild == nullptr;
}

void TwoThreeTree::Node::makeChilds() {
	if (num < 3) return;
	if (mval < lval) {
		swap(mval, lval);
	}
	else if (mval > rval) {
		swap(mval, rval);
	}
	fchild = new Node(lval);
	schild = new Node(rval);
	fchild->parent = this;
	schild->parent = this;
	lval = mval;
	mval = rval = MAX;
	num = 1;
}

void TwoThreeTree::Node::upLeft() {
	if(num != 1) return;
	rval = lval;
	tchild = schild;

	Node *F = fchild;
	lval = F->lval;
	fchild = F->fchild;
	schild = F->schild;
	if (fchild != nullptr) fchild->parent = this;
	if (schild != nullptr) schild->parent = this;
	num = 2;
	delete F;
}
void TwoThreeTree::Node::upRight() {
	if (num != 1) return;
	Node *S = schild;
	rval = S->lval;
	schild = S->fchild;
	tchild = S->schild;
	if (schild != nullptr) schild->parent = this;
	if (tchild != nullptr) tchild->parent = this;
	num = 2;
	delete S;
}
void TwoThreeTree::Node::downLeft() {
	if (num != 2) return;
	Node* L = new Node(lval);
	L->parent = this;
	L->fchild = fchild;
	L->schild = schild;
	if (L->fchild != nullptr) L->fchild->parent = L;
	if (L->schild != nullptr) L->schild->parent = L;

	fchild = L;
	schild = tchild;
	tchild = nullptr; // 这样会释放调 tchild, 导致外部对tchild的引用出错
	lval = rval;
	rval = MAX;
	num = 1;
}
void TwoThreeTree::Node::downRight() {
	if (num != 2) return;
	Node* R = new Node(rval);
	R->parent = this;
	R->fchild = schild;
	R->schild = tchild;
	if(R->fchild != nullptr) R->fchild->parent = R;
	if(R->schild != nullptr) R->schild->parent = R;

	schild = R;
	tchild = nullptr;
	rval = MAX;
	num = 1;
}
void TwoThreeTree::Node::cutMid() {
	if (num != 2) return;
	Node* L = new Node(lval);
	Node* R = new Node(rval);
	Node* S = schild;
	L->fchild = fchild;
	L->schild = S->fchild;
	R->fchild = S->schild;
	R->schild = tchild;
	tchild = nullptr;

	if (L->fchild != nullptr) L->fchild->parent = L;
	if (L->schild != nullptr) L->schild->parent = L;
	if (R->fchild != nullptr) R->fchild->parent = R;
	if (R->schild != nullptr) R->schild->parent = R;

	lval = S->lval;
	rval = MAX;
	fchild = L;
	schild = R;
	fchild->parent = this;
	schild->parent = this;

	delete S;
	num = 1;
}









TwoThreeTree::TwoThreeTree(){
	root = nullptr;
}

TwoThreeTree:: ~TwoThreeTree(){
	//removeall(root);
	root = nullptr;
}

int TwoThreeTree::Find(int val) {
	return 0;
}

int TwoThreeTree::Insert(int val) {
	if(val <= MIN || val >= MAX) return -1;

	if (root == nullptr) {
		root = new Node(val);
		return 1;
	}
	//cout << endl << "ins: " << val << endl;
	Node** N = &root;
	Node* P = nullptr;
	while ((*N) != nullptr) {
		if ((*N)->isLeaf()) {
			if ((*N)->num == 1) {
				(*N)->rval = val;
				if ((*N)->rval < (*N)->lval) {
					swap((*N)->rval, (*N)->lval);
				}
			}
			else {
				(*N)->mval = val;
			}
			(*N)->num ++;
			break;
		}

		P = *N;
		if ((*N)->num == 2 && val > (*N)->rval) {
			N = &((*N)->tchild);
			continue;
		}
		N = val < (*N)->lval ? &((*N)->fchild) : &((*N)->schild);
	}

	(*N)->parent = P;

	if( (*N)->num < 3) return 1;
	(*N)->makeChilds();

	while(P != nullptr){
		//Display();
		//cout << "P: ";
		//P->showVal();
		//cout << "N: ";
		//(*N)->showVal();
		if (P->num == 1) {
			if (P->fchild == *N){
				P->upLeft();
			}
			else if (P->schild == *N){
				P->upRight();
			}
			break;
		}

		if (P->fchild == *N) {
			P->downRight();
		}
		else if (P->schild == *N) {
			P->cutMid();
		}
		else if (P->tchild == *N) {
			P->downLeft();
		}

		Node* T = P;
		N = &T;
		P = P->parent;
	}
	return 1;
}

int TwoThreeTree::Remove(int val) {
	if (root == nullptr || val <= MIN || val >= MAX) return -1;
	cout << "Remove val:" << val << endl;
	return _Remove(root, val);
}

int TwoThreeTree::_Remove(Node*& node, int val) {
	Node** N = &node;
	Node* P = nullptr;

	while ((*N) != nullptr) {
		P = (*N)->parent;
		if ((*N)->num == 2 && val > (*N)->rval) {
			N = &((*N)->tchild);
		}
		else if (val > (*N)->lval && val < (*N) -> rval) {
			N = &((*N)->schild);
		}
		else if (val < (*N)->lval) {
			N = &((*N)->fchild);
		}
		else {

			if ((*N)->isLeaf()) {
				if ((*N)->num == 2) {
					if ((*N)->lval == val) { // 删除右值
						(*N)->lval = (*N)->rval;
						(*N)->rval = MAX;
					}
					else if ((*N)->rval == val) {
						(*N)->rval = MAX;
					}
					(*N)->num = 1;
				}
				else if ((*N)->lval == val) { 	
					if ((*N) == root) {
						root = nullptr;
						break;
					}

					if (P->num == 2){
						if (P->tchild == *N) {
							if (P->schild->num == 1) {
								P->tchild = nullptr;
								P->downRight();
								P->schild->upLeft();
							}
							else {
								(*N)->lval = P->rval;
								P->rval = P->schild->rval;
								P->schild->rval = MAX;
								P->schild->num = 1;
							}
						}
						else  if(P->fchild == *N) { // N 是 P 的第一个结点
							if (P->schild->num == 1) {
								P->fchild = nullptr;
								P->downLeft();
								P->fchild->upRight();
							}
							else {
								(*N)->lval = P->lval;
								P->lval = P->schild->lval;
								P->schild->lval = P->schild->rval;
								P->schild->rval = MAX;
								P->schild->num = 1;
							}}
						else if (P->schild == *N) { // N 是 P 的第二个结点
							if (P->fchild->num == 1) {
								P->schild = nullptr;
								P->downLeft();
								P->fchild->upLeft();
							}
							else {
								(*N)->lval = P->lval;
								P->lval = P->fchild->rval;
								P->fchild->rval = MAX;
								P->fchild->num = 1;
							}
						}
					}else if (P->num == 1) {
						if (P->fchild == *N) { // N 是 P 的第一个结点
							if (P->schild->num == 1) {
								P->fchild = nullptr;
								P->upRight();
							}
							else {
								(*N)->lval = P->lval;
								P->lval = P->schild->lval;
								P->schild->lval = P->schild->rval;
								P->schild->rval = MAX;
								P->schild->num = 1;
							}
						}
						else if (P->schild == *N) { // N 是 P 的第二个结点
							if (P->fchild->num == 1) {
								P->schild = nullptr;
								P->upLeft();
							}
							else {
								(*N)->lval = P->lval;
								P->lval = P->fchild->rval;
								P->fchild->rval = MAX;
								P->fchild->num = 1;
							}
						}
					}
					Node* PP = P->parent;
					if (PP != nullptr) {
						if (PP->num == 2) {
							if (PP->fchild == P) {
								PP->downLeft();
								P->upRight();
							}
							else if (PP->schild == P) {
								PP->downRight();
								P->upRight();
							}
							else if (PP->tchild == P) {
								PP->downRight();
								P->upLeft();
							}
						}
						else if (PP->num == 1) {
							if (PP->fchild == P) {
								PP->upRight();
							}
							else if (PP->schild == P) {
								PP->upLeft();
							}
						}
					}
				}
			}
			else { // 非叶子结点
				cout << "no-leaf " << endl;
				if ((*N)->lval == val) {
					Node* M = minValueNode((*N)->schild);
					(*N)->lval = M->lval;
					_Remove(M, M->lval);
				}
				else {
					Node* M = minValueNode((*N)->tchild);
					(*N)->rval = M->lval;
					_Remove(M, M->lval);
				}
			}

			break;
		}
	}

	return 1;
}

int TwoThreeTree::Selection(int k) {
	return 1;
}

TwoThreeTree::Node* TwoThreeTree::minValueNode(Node* node)
{
	if( node == nullptr ) return nullptr;
	if (node->fchild != nullptr) {
		node = node->fchild;
	}
	return node;
}
