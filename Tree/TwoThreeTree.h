//author: Zi Hao(Leo) Zhang

#pragma once

#include <stdexcept>
#include <iostream>
using namespace std;
#include <string>
#include <vector>

#define MAX 255
//#define MAX 32766
//#define MAX 32765
#define MIN -1


class TwoThreeTree
{
	class Node
	{
	public:
		Node(int val); // constructor for creating leaf node

		int mval; // 中值，临时作用
		int lval; // 左值
		int rval; // 右值
		int num; // 当前有效 value 数

		Node* parent; // parent of the node
		Node* fchild; // first child of the node
		Node* schild; // second child of the node
		Node* tchild; // Third child of the node

		void showVal();

		bool isLeaf();
		void makeChilds();
		void upLeft(); // 吸收第1棵子树，当 num == 1 时有效;
		void upRight(); // 吸收第2棵子树，当 num == 1 时有效；
		void downLeft(); // 下放左边
		void downRight(); // 下放左边
		void cutMid(); // 从中间切开

	};

public:
	TwoThreeTree();

	~TwoThreeTree();

	Node* root;

	int Find(int val);

	int Insert(int val); // insert a node into the tree, if inserted returns true, if already existed, returns false

	int Remove(int val); // remove the value from the tree, if removed sucesssfully, return true, else return false

	int Selection(int k); // return the k smallest element in the tree'

	Node* minValueNode(Node* node);


	void Display() {
		printf("\n");
		int size = 0;
		if (root != nullptr)
			Display(root, 1, 0, size);
		else
			printf("Empty");
		cout << endl << "size: " << size << endl << endl;
		printf("\n");
	}

	void Display(Node* const& cur, int depth, int state, int& size) {  // state: 1 -> left, 2 -> mid, 3 -> right, 0 -> root
		if (cur == nullptr) return;
		Display(cur->tchild, depth + 1, 3, size);
		Display(cur->schild, depth + 1, 2, size);
		for (int i = 0; i < depth; i++)
			printf("    ");
		size = size + 1;
		cout << "[" << cur->lval ;
		if (cur->rval != MAX) {
			cout << ", " << cur->rval;
			size = size + 1;
		}
		cout << "]" << endl;
		Display(cur->fchild, depth + 1, 1, size);
	}


private:
	int _Remove(Node*& node, int val); // remove the value from the tree, if removed sucesssfully, return true, else return false

};