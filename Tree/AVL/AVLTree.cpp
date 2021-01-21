//  Created by Kadir Emre Oto on 06.08.2018.

#include "AVLTree.h"
#include "queue"
using namespace std;

template <class T>
AVLTree<T>::AVLTree() {
	root = nullptr;
	_size = 0;
}

template <class T>
AVLTree<T>::~AVLTree() {
	clear();
}

template <class T>
void AVLTree<T>::clear() { // 按独立层删除
	queue<AVLTreeNode<T>*> stack;
	if(root == nullptr) return;
	stack.push(root);

	while (!stack.empty()) {
		AVLTreeNode<T>* node = stack.front();
		stack.pop();

		if (node->left != nullptr) stack.push(node->left);
		if (node->right != nullptr) stack.push(node->right);
		_size--;
		delete node;
	}
	root = nullptr;
}

template <class T>
void AVLTree<T>::insert(T value) {
	vector<AVLTreeNode<T>**> path;
	AVLTreeNode<T>** node = &root;
	while ((*node) != nullptr) {
		path.push_back(node);
		if ((*node)->value > value) {
			node = &((*node)->left);
		}
		else {
			node = &((*node)->right);
		}
	}
	*node = new AVLTreeNode<T>(value);
	path.push_back(node);
	balance(path);
	_size ++ ;
}

/*	erase 的步骤：
	1.	确定删除点 I 并设左右子树分别为 IL, IR；
	2.	判断 IL 和 IR 的状态：
			1）都为空，可直接删除 I ；
			2）IR 为空：可直接删除 I ，并让IL代替自己；
			3）IR 不为空：找到 IR 中的最小左结点 S， 还有如下情况：
				① 若 S 不存在，则让 IR替换掉I；
				② 否则，设S的右结点为SR（没有左节点）、S的父节点为SP，则SP的左节点为SR； 然后将S替换掉I；  
*/
template <class T>
void AVLTree<T>::erase(T value) {
	AVLTreeNode<T>** I = &root;
	vector<AVLTreeNode<T>**> path;
	while (*I != nullptr and (*I)->value != value) {
		path.push_back(I);
		if ((*I)->value > value) {
			I = &((*I)->left);
		}
		else {
			I = &((*I)->right);
		}
	}

	if(*I == nullptr) return;
	int index = path.size();

	AVLTreeNode<T> *IL = (*I)->left, *IR = (*I)->right;

	if (IL == nullptr && IR == nullptr) {
		delete *I;
		*I = nullptr;
	}
	else if (IR == nullptr) {
		AVLTreeNode<T>* toRemove = *I;
		(*I) = (*I)->left;
		delete toRemove;
	}
	else {
		path.push_back(I);

		AVLTreeNode<T>** S = &IR;
		while ((*S)->left != nullptr) {
			path.push_back(S);
			S = &((*S)->left);
		}

		if (*S == IR) {
			(*S)->left = (*I)->left;
			AVLTreeNode<T>* toRemove = *I;
			*I = *S;
			delete toRemove;
		}
		else {
			AVLTreeNode<T>* p = *path.back(), *s = *S;

			p->left = (*S)->right;
			s->left = (*I)->left;
			s->right = (*I)->right;

			delete *I;
			*I = s;
			path[index] = &(s->right);
		}
	}
	IL = IR = nullptr;
	delete IL, IR, I;

	balance(path);
	_size --;
}

template <class T>
void AVLTree<T>::balance(vector<AVLTreeNode<T>**> path) {
	reverse(path.begin(), path.end());
	
	for (auto node : path) {
		(*node)->updateValues();

		if ((*node)->balanceFactor() >= 2) {
			if ((*node)->left->balanceFactor() > 0) {  // LL
				*node = (*node)->right_rotate();
			}
			else {  // LR
				(*node)->left = (*node)->left->left_rotate();
				*node = (*node)->right_rotate();
			}
		}
		else if ((*node)->balanceFactor() <= -2) {
			if ((*node)->right->balanceFactor() < 0) { // RR
				*node = (*node)->left_rotate();
			}
			else {  // RL
				(*node)->right = (*node)->right->right_rotate();
				*node = (*node)->left_rotate();
			}
		}

	}
}

template <class T>
bool AVLTree<T>::empty() const {
	return _size == 0;
}

template <class T>
int AVLTree<T>::size() const {
	return _size;
}

template <class T>
int AVLTree<T>::find(T value) const {
	AVLTreeNode<T>* direct = root;
	int idx = 0;

	while (direct != nullptr and direct->value != value) {
		if (direct->value > value)
			direct = direct->left;
		else {
			idx += (direct->left ? direct->left->count : 0) + 1;
			direct = direct->right;
		}
	}

	if (direct == nullptr)
		return -1;

	else
		return idx + (direct->left ? direct->left->count : 0);
}

template <class T>
int AVLTree<T>::upper_bound(T value) const {
	AVLTreeNode<T>* direct = root;
	int idx = 0;

	while (direct != nullptr) {
		if (direct->value > value)
			direct = direct->left;
		else {
			idx += (direct->left ? direct->left->count : 0) + 1;
			direct = direct->right;
		}
	}

	return idx;
}

template <class T>
int AVLTree<T>::lower_bound(T value) const {
	AVLTreeNode<T>* direct = root;
	int idx = 0;

	while (direct != nullptr) {
		if (direct->value >= value)
			direct = direct->left;
		else {
			idx += (direct->left ? direct->left->count : 0) + 1;
			direct = direct->right;
		}
	}

	return idx;
}

template <class T>
const T& AVLTree<T>::find_min() const {
	AVLTreeNode<T>* cur = root;

	while (cur->left != nullptr)
		cur = cur->left;

	return cur->value;
}

template <class T>
const T& AVLTree<T>::find_max() const {
	AVLTreeNode<T>* cur = root;

	while (cur->right != nullptr)
		cur = cur->right;

	return cur->value;
}

template <class T>
const T& AVLTree<T>::operator[](std::size_t idx) const {
	AVLTreeNode<T>* cur = root;
	int left = cur->left != nullptr ? cur->left->count : 0;

	while (left != idx) {
		if (left < idx) {
			idx -= left + 1;

			cur = cur->right;
			left = cur->left != nullptr ? cur->left->count : 0;
		}

		else {
			cur = cur->left;
			left = cur->left != nullptr ? cur->left->count : 0;
		}
	}

	return cur->value;
}

template <class T>
void AVLTree<T>::display() {
	printf("\n");
	if (root != nullptr)
		display(root);
	else
		printf("Empty");
	printf("\n");
}

template <class T>
void AVLTree<T>::display(AVLTreeNode<T>* cur, int depth, int state) {  // state: 1 -> left, 2 -> right , 0 -> root
	if (cur->left)
		display(cur->left, depth + 1, 1);

	for (int i = 0; i < depth; i++)
		printf("     ");

	if (state == 1) // left
		printf("┌───");
	else if (state == 2)  // right
		printf("└───");

	std::cout << "[" << cur->value << "] - (" << cur->count << ", " << cur->height << ")" << std::endl;

	if (cur->right)
		display(cur->right, depth + 1, 2);
}


template class AVLTree<int>;
template class AVLTree<short>;
template class AVLTree<long>;
template class AVLTree<long long>;
template class AVLTree<std::string>;
