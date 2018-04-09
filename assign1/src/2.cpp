#include <iostream>

using namespace std;

class node {
	int data;
	node *left;
	node *right;
public:
	node() {
		data = 0;
		left = right = NULL;
	}
	friend class tree;
};

class tree {
	node *root;
public:
	tree() {
		root = NULL;
	}
	void create();
	node* insert(node *, int);
	void inorder(node *);
	int height(node *);
	int findmin(node *);
	void mirror(node *);
	void swap(node **, node **);
	node* search(node *, int);
	node* getRoot();

};

void tree::create() {
	int flag = 0;
	while (1) {
		cout << "\nEnter data" << endl;
		int data;
		cin >> data;
			root = insert(root, data);
		cout << "\ncontinue?" << endl;
		char ch;
		cin >> ch;
		if (ch == 'n')
			break;
	}
}

node* tree::insert(node *root, int data) {
	if (root == NULL) {
		root = new node;
		root->data = data;
	} else {
		if (data < root->data)
			root->left = insert(root->left, data);
		else if (data > root->data)
			root->right = insert(root->right, data);
	}
	return root;
}

void tree::inorder(node *root) {
	if (root) {
		inorder(root->left);
		cout << root->data << "  ";
		inorder(root->right);
	}
}

int tree::height(node *root) {
	int leftheight, rightheight;

	if (root == NULL)
		return 0;
	else {
		leftheight = height(root->left);
		rightheight = height(root->right);

		if (leftheight > rightheight)
			return (leftheight + 1);
		else
			return (rightheight + 1);
	}
}

int tree::findmin(node *root) {
	if(!root)
		return 0;
	else if(root->left==NULL)
		return root->data;
	else
		return findmin(root->left);
}

void tree::mirror(node *root) {
	if (root) {
		mirror(root->left);
		mirror(root->right);
		swap(&root->left, &root->right);
	}
}

void tree::swap(node **left, node **right) {
	node *temp = *left;
	*left = *right;
	*right = temp;
}

node* tree::search(node *root, int data) {
	if (root == NULL)
		return NULL;
	if (data < root->data)
		return search(root->left, data);
	else if (data > root->data)
		return search(root->right, data);
	return root;
}

node* tree::getRoot() {
	return root;
}

int main() {
	tree t;
	t.create();
	t.inorder(t.getRoot());

	while (1) {
		cout
				<< "\n i. Insert new node\nii. Find number of nodes in longest path\niii. Minimum data value found in the tree\niv. Change a tree so that the roles of the left and right pointers are swapped atevery node\nv. Search a value\nvi. Display"
				<< endl;
		cout << "\nEnter choice" << endl;
		int ch;
		cin >> ch;

		switch (ch) {
		case 1:
			int data;
			cout << "\nenter data" << endl;
			cin >> data;
			t.insert(t.getRoot(), data);
			break;
		case 2:
			cout << "\nnumber of nodes in longest path: "
					<< t.height(t.getRoot()) << endl;
			break;
		case 3:
			cout << "\nMinimum data value found in the tree:  "
					<< t.findmin(t.getRoot());
			break;
		case 4:
			t.mirror(t.getRoot());
			break;
		case 5:
			cout << "\nEnter element to search" << endl;
			int element;
			cin >> element;
			if (t.search(t.getRoot(), element)!=NULL)
				cout << "\nElement found" << endl;
			else
				cout << "\nElement not found" << endl;
			break;
		case 6:
			t.inorder(t.getRoot());
			break;
		default:
			cout << "\nInvalid entry" << endl;
		}

		cout << "\ncontinue?" << endl;
		char cont;
		cin >> cont;
		if (cont == 'n')
			break;
	}
	return 0;
}

