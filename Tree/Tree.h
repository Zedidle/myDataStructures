//  Created by Kadir Emre Oto on 06.08.2018.

#include <stdexcept>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "BinaryTree.h"

#include "ThreadTree.h"
#include "AVL/AVLTree.h"
#include "TwoThreeTree.h"
#include "TwoThreeFourTree.h"
#include "RedBlackTree.h"
#include "HuffmanTree.h"

using namespace std;


void AVLTest() {
	AVLTree<string> tree;
	vector<string> elements = { "Emre" , "KEO", "Kadir", "Oto", "Oto0", "kisd", "Ofdg", "sdf0", "d2wgf" };
	for (auto e : elements) {
		tree.insert(e);
	}
	tree.display();
	//tree.clear();
	vector<string> elements2 = { "Emre" , "KEO", "Kadir" };
	for (auto e : elements2) {
		
		cout << endl << "erase: " << e << endl;
		tree.erase(e);
		tree.display();
	}
	//tree.display();
}


void TwoThreeTest() {
	TwoThreeTree ttTree;
	int right_datas[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 ,15 ,16 ,17, 56,43,23,65,87,26,87,65,54};
	int mid_datas[] = { 2,5,7,10,11,1,6,12,8};
	int left_datas[] = {14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

	//for (int d : right_datas) {
	//	ttTree.Insert(d);
	//	ttTree.Display();
	//}

	for (int d : mid_datas) {
		ttTree.Insert(d);
		//ttTree.Display();
	}

	//for (int d : left_datas) {
	//	ttTree.Insert(d);
	//	ttTree.Display();
	//}


	ttTree.Display();
	for (int d : mid_datas) {
		ttTree.Remove(d);
		ttTree.Display();
	}

}

void TwoThreeFourTest() {
	TTF_Tree::Test();
}


void RBTest() {
	RBTree rbTree1, rbTree2;
	int datas[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	for (int d : datas) {
		rbTree1.insertValue(d);
	}

	rbTree1.preorder();
	
	rbTree1.deleteValue(5);
	cout << endl;
	rbTree1.preorder();


	//cin >> data;
	//while (data != 0)
	//{
	//	rbTree2.insertValue(data);
	//	cin >> data;
	//}

	//rbTree2.preorder();

	//rbTree1.merge(rbTree2);
	//rbTree1.preorder();
}

void TreeTest() {
	
	//BinaryTree::Test();

	//ThreadTree_Test();
	//AVLTest();
	TwoThreeTest();
	//TwoThreeFourTest();
	//RBTest();
	//Huffman::Test();
}