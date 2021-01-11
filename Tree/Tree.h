//  Created by Kadir Emre Oto on 06.08.2018.

#include <iostream>
#include "AVL/AVLTree.h"
#include "Heap/Heap.h"


void AVLTest() {
	AVLTree<std::string> tree;

	tree.insert("Emre");
	tree.insert("KEO");
	tree.insert("Kadir");
	tree.insert("Oto");
	tree.insert("Oto0");
	tree.insert("kisd");
	tree.insert("Ofdg");
	tree.insert("sdf0");
	tree.insert("d2wgf");
	tree.insert("b000");
	tree.insert("jgm4");
	tree.insert("vmda");
	tree.insert("flam");
	tree.insert("0kd");

	tree.display();
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