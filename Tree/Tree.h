//  Created by Kadir Emre Oto on 06.08.2018.

#include <stdexcept>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "ThreadTree.h"
#include "Heap.h"
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
	TwoThreeTree newtree;
	string test;
	int integerStart = 0;
	int integer = 0;
	string cap = "";
	string operation = ""; //type of operation
	int value = 0; //The value used for the operation
	int temp;

	ifstream inFile;
	inFile.open("Tree/input.txt", ios::in);
	if (!inFile.is_open())
	{
		cout << "打开文件失败" << endl;
		return;
	}
	ofstream OutFile("Tree/output.txt");
	getline(inFile, test);

	for (int i = 0; i < test.length(); i++) // reading the integers on the first line of input.txt
	{
		if (test[i] == ',')
		{
			cap = test.substr(integerStart, i - integerStart);
			integer = stoi(cap);
			integerStart = i + 1;
			newtree.Insert(integer);
		}
	}

	cap = test.substr(integerStart, test.length() - integerStart);
	integer = stoi(cap);
	newtree.Insert(integer);

	while (inFile >> operation >> value) // reading operations and corresponding values
	{
		if (operation == "Insert")
		{
			OutFile << "inserted at position: " << newtree.Insert(value) << endl;
		}

		else if (operation == "Find")
		{
			temp = newtree.Find(value);

			if (temp == 0)
			{
				OutFile << "Not Found" << endl;
			}

			else if (temp > 0)
			{
				OutFile << "Found: " << value << " is the " << temp << " element of the list" << endl;
			}
		}

		else if (operation == "Delete")
		{
			temp = newtree.Delete(value);
			OutFile << value << " is the " << temp << " element of the list, deleted" << endl;
		}
		else if (operation == "Selection")
		{
			temp = newtree.Selection(value);
			OutFile << "The " << value << "th element in the tree is " << temp << endl;
		}
	}


	vector<int> print; // putting every leaf node into a vector and output them to the output file
	newtree.printTree(print);

	OutFile << endl << "The leaf nodes of the tree:" << endl;
	for (int i = 0; i < print.size(); i++)
	{
		OutFile << print[i] << " ";
	}


	inFile.close();
	OutFile.close();
}

void TwoThreeFourTest() {
	
}


void RBTest() {
	RBTree rbTree1, rbTree2;
	int datas[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	for (int d : datas) {
		rbTree1.insertValue(d);
	}

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
	//ThreadTree_Test();
	//TreeHead::Test();
	//AVLTest();
	//TwoThreeTest();
	//TwoThreeFourTest();
	RBTest();

	//Huffman::Test();
}