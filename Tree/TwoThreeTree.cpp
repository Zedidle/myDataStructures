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
	fchild->parent = this;
	schild->parent = this;
	num = 2;
	delete F;
}
void TwoThreeTree::Node::upRight() {
	if (num != 1) return;
	Node *S = schild;
	rval = S->lval;
	schild = S->fchild;
	tchild = S->schild;
	schild->parent = this;
	tchild->parent = this;
	num = 2;
	delete S;
}
void TwoThreeTree::Node::downLeft() {
	if (num != 2) return;
	Node* L = new Node(lval);
	L->parent = this;
	L->fchild = fchild;
	L->schild = schild;
	fchild = L;
	schild = tchild;
	tchild = nullptr;
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

	L->fchild->parent = L;
	L->schild->parent = L;
	R->fchild->parent = R;
	R->schild->parent = R;
	

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
	if (root == nullptr) {
		root = new Node(val);
		return 1;
	}
	cout << endl << "ins: " << val << endl;
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
		N = val > (*N)->lval ? &((*N)->schild) : &((*N)->fchild);
	}

	(*N)->parent = P;

	if( (*N)->num < 3) return 1;
	(*N)->makeChilds();
	Display();

	while(P != nullptr){
		//cout << endl << " > " << endl;
		//cout << "P: ";
		//P->showVal();
		//cout << "N: ";
		//(*N)->showVal();
		if (P->num == 1) {
			if (P->fchild == *N){ // N 作为 P 的左结点
				//cout << "upLeft" << endl;
				P->upLeft();
			}
			else if (P->schild == *N){
				//cout << "upRight" << endl;
				P->upRight();
			}
			break;
		}
		else if (P->num == 2) {
			if (P->fchild == *N) {
				//cout << "downRight" << endl;
				P->downRight();
			}
			else if (P->schild == *N) {
				//cout << "cutMid" << endl;
				P->cutMid();
			}
			else if (P->tchild == *N) {
				//cout << "downLeft" << endl;
				P->downLeft();
			}
		}

		P = P->parent;
		N = &((*N)->parent);
	}
	return 1;
}

int TwoThreeTree::Delete(int val) {
	return 0;
}

int TwoThreeTree::Selection(int k) {
	return 0;
}
