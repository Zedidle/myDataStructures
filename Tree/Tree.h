//  Created by Kadir Emre Oto on 06.08.2018.

#include <stdexcept>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "numeric"

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
	vector<short> random_datas(MAX);
	iota(random_datas.begin(), random_datas.end(), MIN+1);
	//for (auto d : random_datas) cout << d <<" "; cout << endl;
	random_shuffle(random_datas.begin(), random_datas.end());
	//for (auto d : random_datas) cout << d << " "; cout << endl;

	int right_datas[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 ,15 ,16 ,17, 56, 43, 23, 65, 87, 26, 87, 66, 54};
	int mid_datas[] = { 2,5,7,10,11,1,6,12,8};
	int left_datas[] = {14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

	//for (int d : right_datas) {
	//	ttTree.Insert(d);
	//	ttTree.Display();
	//}

	//for (int d : mid_datas) {
	//	ttTree.Insert(d);
	//	ttTree.Display();
	//}

	//for (int d : left_datas) {
	//	ttTree.Insert(d);
	//	ttTree.Display();
	//}


	for (int d : random_datas) {
		ttTree.Insert(d);
		//ttTree.Display();
	}

	// ============================================== Test ===================================================
	ttTree.Display();
	for (int d : random_datas) {
		ttTree.Remove(d);
		//ttTree.Display();
	}
	ttTree.Display();
}

void TwoThreeFourTest() {
	TTF_Tree::Test();
}




void RBTest() {
	vector<short> random_datas(32);
	iota(random_datas.begin(), random_datas.end(), MIN + 1);
	random_shuffle(random_datas.begin(), random_datas.end());
	for (auto d : random_datas) cout << d << " "; cout << endl;


	RBTree rbTree1, rbTree2;
	for (int d : random_datas) {
		rbTree1.Insert(d);
		//rbTree1.Display();
	}
	rbTree1.Display();
	for (int d : random_datas) {
		rbTree1.Remove(d);
		rbTree1.Display();
	}


	//rbTree1.Display();
}



void TreeTest() {
	//BinaryTree::Test();
	//ThreadTree_Test();
	//AVLTest();
	//TwoThreeTest();
	//TwoThreeFourTest();
	RBTest();
	//Huffman::Test();
}