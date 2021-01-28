#include "bits/stdc++.h"
//#include "iostream"
#include "RedBlackTree.h"
using namespace std;

RBTree::Node::Node(int data) {
	this->data = data;
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

RBTree::Node* RBTree::insertBST(Node*& root, Node*& ptr) {
	if (root == nullptr)
		return ptr;
	if (ptr->data < root->data) {
		root->left = insertBST(root->left, ptr);
		root->left->parent = root;
	}
	else if (ptr->data > root->data) {
		root->right = insertBST(root->right, ptr);
		root->right->parent = root;
	}
	return root;
}

void RBTree::insertValue(int n) {
	Node* node = new Node(n);
	root = insertBST(root, node);

	insertBST(root, node);
	fixInsertRBTree(node);
}

void RBTree::rotateLeft(Node*& ptr) {
	Node* R = ptr->right;
	ptr->right = R->left;
	if (ptr->right != nullptr) {
		ptr->right->parent = R;
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

void RBTree::fixInsertRBTree(Node*& ptr) {
	Node* p = nullptr;
	Node* gp = nullptr;
	Node* uncle = nullptr;

	while (ptr != root && getColor(ptr) == RED && getColor(ptr->parent) == RED) {
		p = ptr->parent;
		gp = p->parent;
		if (p == gp->left) {
			uncle = gp->right;
			if (getColor(uncle) == RED) {
				setColor(uncle, BLACK);
				setColor(p, BLACK);
				setColor(gp, RED);
				ptr = gp;
			}
			else {
				if (ptr == p->right) {
					rotateLeft(p);
					ptr = p;
					p = ptr->parent;
				}
				rotateRight(gp);
				setColor(gp, RED);
				setColor(p, BLACK);
				ptr = p;
			}
		}
		else if(p == gp->right){
			uncle = gp->left;
			if (getColor(uncle) == RED) {
				setColor(uncle, BLACK);
				setColor(p, BLACK);
				setColor(gp, RED);
				ptr = gp;
			}
			else {
				if (ptr == p->left) {
					rotateRight(p);
					ptr = p;
					p = ptr->parent;
				}
				rotateLeft(gp);
				setColor(gp, RED);
				setColor(p, BLACK);
				ptr = p;
			}
		}
	}
	setColor(root, BLACK);
}

void RBTree::fixDeleteRBTree(Node*& node) {
	if(node == nullptr) return;
	if(node == root){
		root = nullptr;
		return;
	}

	if (getColor(node) == RED || getColor(node->left) == RED || getColor(node->right) == RED) {
		Node* child = node->left != nullptr ? node->left : node->right;

		if (node == node->parent->left) {
			node->parent->left = child;
			if(child != nullptr) child->parent = node->parent;
			setColor(child, BLACK);
			delete(node);
		}
		else {
			node->parent->right = child;
			if(child != nullptr) child->parent = node->parent;
			setColor(child, BLACK);
			delete(node);
		}
	}
	else {
		Node* sibling = nullptr;
		Node* parent = nullptr;
		Node* ptr = node;
		setColor(ptr, DOUBLE_BLACK);
		while (ptr != root && getColor(ptr) == DOUBLE_BLACK) {
			parent = ptr->parent;
			if (ptr == parent->left) {
				sibling = parent->right;
				if (getColor(sibling) == RED) {
					// 由于自己是黑色被删除了，则要把兄弟结点的红色往上提一级
					setColor(sibling, BLACK);
					setColor(parent, RED); 
					rotateLeft(parent); // 再左旋保持平衡
				}
				else {
					if (getColor(sibling->left) == BLACK && getColor((sibling->right)) == BLACK){
						setColor(sibling, RED);
						if (getColor(parent) == RED) {
							setColor(parent, BLACK);
						}
						else {
							setColor(parent, DOUBLE_BLACK); 
						}
						ptr = parent;
					}
					else {
						if (getColor(sibling->right) == BLACK) {
							setColor(sibling->left, BLACK);
							setColor(sibling, RED);
							rotateRight(sibling);
							sibling = parent->right;
						}
						setColor(sibling, parent->color);
						setColor(parent, BLACK);
						setColor(sibling->right, BLACK);
						rotateLeft(parent);
						break;
					}
				}
			}
			else {
				sibling = parent->left;
				if (getColor(sibling) == RED) {
					setColor(sibling, BLACK);
					setColor(parent, RED);
					rotateRight(parent);
				}
				else {
					if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
						setColor(sibling, RED);
						if (getColor(parent) == RED) {
							setColor(parent, BLACK);
						}
						else {
							setColor(parent, DOUBLE_BLACK); 
						}
						ptr = parent;
					}
					else {
						if (getColor(sibling->left) == BLACK) {
							setColor(sibling->right, BLACK);
							setColor(sibling, RED);
							rotateLeft(sibling);
							sibling = parent->left;
						}
						setColor(sibling, parent->color);
						setColor(parent, BLACK);
						setColor(sibling->left, BLACK);
						rotateRight(parent);
						break;
					}
				}
			}
		}
		if (node == node->parent->left) {
			node->parent->left = nullptr;
		}
		else {
			node->parent->right = nullptr;
		}
		delete(node);
		setColor(root, BLACK);
	}
}

RBTree::Node* RBTree::deleteBST(Node*& root, int data) {
	if(root == nullptr) return root;
	if(data > root->data) return deleteBST(root->right, data);
	if(data < root->data) return deleteBST(root->left, data);
	if(root->left == nullptr || root->right == nullptr) return root;
	
	Node* temp = minValueNode(root->right);
	root->data = temp->data;
	return deleteBST(root->right, temp->data);
}

void RBTree::deleteValue(int data) {
	Node* node = deleteBST(root, data);
	fixDeleteRBTree(node);
}

void RBTree::inorderBST(Node*& ptr) {
	if (ptr == nullptr)
		return;

	inorderBST(ptr->left);
	cout << ptr->data << " " << ptr->color << endl;
	inorderBST(ptr->right);
}

void RBTree::inorder() {
	inorderBST(root);
}

void RBTree::preorderBST(Node*& ptr) {
	if (ptr == nullptr)
		return;

	cout << ptr->data << " " << ptr->color << endl;
	preorderBST(ptr->left);
	preorderBST(ptr->right);
}

void RBTree::preorder() {
	preorderBST(root);
	cout << "-------" << endl;
}

RBTree::Node* RBTree::minValueNode(Node*& node) {

	Node* ptr = node;

	while (ptr->left != nullptr)
		ptr = ptr->left;

	return ptr;
}

RBTree::Node* RBTree::maxValueNode(Node*& node) {
	Node* ptr = node;

	while (ptr->right != nullptr)
		ptr = ptr->right;

	return ptr;
}

int RBTree::getBlackHeight(Node* node) {
	int blackheight = 0;
	while (node != nullptr) {
		if (getColor(node) == BLACK)
			blackheight++;
		node = node->left;
	}
	return blackheight;
}

// Test case 1 : 5 2 9 1 6 8 0 20 30 35 40 50 0
// Test case 2 : 3 0 5 0
// Test case 3 : 2 1 3 0 8 9 4 5 0

void RBTree::merge(RBTree rbTree2) {
	int temp;
	Node* c, * temp_ptr = nullptr;
	Node* root1 = root;
	Node* root2 = rbTree2.root;
	int initialblackheight1 = getBlackHeight(root1);
	int initialblackheight2 = getBlackHeight(root2);
	if (initialblackheight1 > initialblackheight2) {
		c = maxValueNode(root1);
		temp = c->data;
		deleteValue(c->data);
		root1 = root;
	}
	else if (initialblackheight2 > initialblackheight1) {
		c = minValueNode(root2);
		temp = c->data;
		rbTree2.deleteValue(c->data);
		root2 = rbTree2.root;
	}
	else {
		c = minValueNode(root2);
		temp = c->data;
		rbTree2.deleteValue(c->data);
		root2 = rbTree2.root;
		if (initialblackheight1 != getBlackHeight(root2)) {
			rbTree2.insertValue(c->data);
			root2 = rbTree2.root;
			c = maxValueNode(root1);
			temp = c->data;
			deleteValue(c->data);
			root1 = root;
		}
	}
	setColor(c, RED);
	int finalblackheight1 = getBlackHeight(root1);
	int finalblackheight2 = getBlackHeight(root2);
	if (finalblackheight1 == finalblackheight2) {
		c->left = root1;
		root1->parent = c;
		c->right = root2;
		root2->parent = c;
		setColor(c, BLACK);
		c->data = temp;
		root = c;
	}
	else if (finalblackheight2 > finalblackheight1) {
		Node* ptr = root2;
		while (finalblackheight1 != getBlackHeight(ptr)) {
			temp_ptr = ptr;
			ptr = ptr->left;
		}
		Node* ptr_parent;
		if (ptr == nullptr)
			ptr_parent = temp_ptr;
		else
			ptr_parent = ptr->parent;
		c->left = root1;
		if (root1 != nullptr)
			root1->parent = c;
		c->right = ptr;
		if (ptr != nullptr)
			ptr->parent = c;
		ptr_parent->left = c;
		c->parent = ptr_parent;
		if (getColor(ptr_parent) == RED) {
			fixInsertRBTree(c);
		}
		else if (getColor(ptr) == RED) {
			fixInsertRBTree(ptr);
		}
		c->data = temp;
		root = root2;
	}
	else {
		Node* ptr = root1;
		while (finalblackheight2 != getBlackHeight(ptr)) {
			ptr = ptr->right;
		}
		Node* ptr_parent = ptr->parent;
		c->right = root2;
		root2->parent = c;
		c->left = ptr;
		ptr->parent = c;
		ptr_parent->right = c;
		c->parent = ptr_parent;
		if (getColor(ptr_parent) == RED) {
			fixInsertRBTree(c);
		}
		else if (getColor(ptr) == RED) {
			fixInsertRBTree(ptr);
		}
		c->data = temp;
		root = root1;
	}
	return;
}