#ifndef RED_BLACK_TREE_RBTREE_H
#define RED_BLACK_TREE_RBTREE_H
using namespace std;
enum Color { RED, BLACK, DOUBLE_BLACK };


#define MAX 255
#define MIN -1

class RBTree
{
private:
	struct Node
	{
		int val;
		int color;
		Node* left, * right, * parent;

		explicit Node(int);

		bool isLeaf() {
			return left == nullptr && right == nullptr;
		}

	};

	Node* root;
protected:
	int getColor(Node*&);
	void setColor(Node*&, int);
	void rotateLeft(Node*&);
	void rotateRight(Node*&);

	void fixInsertRBTree(Node*);
	void fixRemoveRBTree(Node*, Node*);

	Node* minValueNode(Node*&);
	Node* maxValueNode(Node*&);
	int getBlackHeight(Node*);
public:
	RBTree();
	void Insert(int);
	void Remove(int);
	void Merge(RBTree);



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

	void Display(Node* const& cur, int depth, int state, int& size) {  // state: 1 -> left, 2 -> right,  0 -> root
		if (cur == nullptr) return;
		Display(cur->right, depth + 1, 2, size);
		for (int i = 0; i < depth; i++)
			printf("    ");
		size = size + 1;
		if (state == 2) {
			cout << "┌--";
		}
		else if (state == 1) {
			cout << "└--";
		}
		cout << "[" << cur->val;
		if (cur->color == RED) cout << "°";
		cout << "]" << endl;
		Display(cur->left, depth + 1, 1, size);
	}


	private:
		void _Remove(Node* N, int val);
};


#endif //RED_BLACK_TREE_RBTREE_H