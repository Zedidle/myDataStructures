//  Created by Kadir Emre Oto on 06.08.2018.

#include "AVLTreeNode.h"

template <class T>
AVLTreeNode<T>::AVLTreeNode(T value) : value(value) {
	count = 1;
	height = 1;

	left = nullptr;
	right = nullptr;
}

template <class T>
void AVLTreeNode<T>::updateValues() {
	// count 等于 两个子节点的count相加 + 加上根结点自己；
	count = (left != nullptr ? left->count : 0) + (right != nullptr ? right->count : 0) + 1;

	// height 等于两个子节点里最高的 + 自身结点的1个高度；
	height = std::max(left != nullptr ? left->height : 0, right != nullptr ? right->height : 0) + 1;
}

template <class T>
int AVLTreeNode<T>::balanceFactor() {
	// 计算平衡因子：左子树高度 - 右子树高度
	return (left != nullptr ? left->height : 0) - (right != nullptr ? right->height : 0);
}

template <class T>
AVLTreeNode<T>* AVLTreeNode<T>::left_rotate() {
	AVLTreeNode<T>* R = right;
	right = R->left;
	R->left = this;
	this->updateValues();
	R->updateValues();
	return R;
}

template <class T>
AVLTreeNode<T>* AVLTreeNode<T>::right_rotate() {
	AVLTreeNode<T>* L = left;
	left = L->right;
	L->right = this;
	this->updateValues();
	L->updateValues();
	return L;
}

template class AVLTreeNode<int>;
template class AVLTreeNode<short>;
template class AVLTreeNode<long>;
template class AVLTreeNode<long long>;
template class AVLTreeNode<std::string>;
