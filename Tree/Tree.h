//  Created by Kadir Emre Oto on 06.08.2018.

#include <iostream>
#include "AVL/AVLTree.h"
#include "Heap/Heap.h"
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


void TTTest() {

}

void RBTest() {

}

void TreeTest() {
	TreeHead::Test();
	//AVLTest();
	//TTTest();
	//RBTest();
}