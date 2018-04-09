#include <iostream>
#include <stack>

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
	void preorder(node *);
	void postorder(node *);
	void erase(node *);
	node* clone(node *);
	void copy(node *);
	node* getRoot();
	void preorder_nr(node *);
	void inorder_nr(node *);
	void postorder_nr(node *);

};

void tree::create() {
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
		cout << "\nl or r " << endl;
		char ch;
		cin >> ch;
		if (ch == 'l')
			root->left = insert(root->left, data);
		else if (ch == 'r')
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

void tree::preorder(node *root) {
	if (root) {
		cout << root->data << "  ";
		preorder(root->left);
		preorder(root->right);
	}
}

void tree::postorder(node *root) {
	if (root) {
		postorder(root->left);
		postorder(root->right);
		cout << root->data << "  ";
	}
}

node* tree::getRoot() {
	return root;
}

node* tree::clone(node *root) {
	if (root == NULL)
		return root;
	node *temp = new node;
	temp->data = root->data;
	temp->left = clone(root->left);
	temp->right = clone(root->right);
	return temp;
}

void tree::copy(node *root) {
	this->root = clone(root);
}

void tree::erase(node *root) {
	if (root == NULL)
		return;
	erase(root->left);
	erase(root->right);
	delete root;
}

void tree::preorder_nr(node *root) {
	stack<node *> s;
	while (1) {
		while (root) {
			cout << root->data << " ";
			s.push(root);
			root = root->left;
		}

		if (s.empty())
			break;
		root = s.top();
		s.pop();
		root = root->right;
	}
}

void tree::inorder_nr(node *root) {
	stack<node *> s;
	while (1) {
		while (root) {
			s.push(root);
			root = root->left;
		}

		if (s.empty())
			break;
		root = s.top();
		cout << root->data << " ";
		s.pop();
		root = root->right;
	}
}

void tree::postorder_nr(node *root) {
	stack<node *> s;
	node *previous = NULL;

	do {
		while (root) {
			s.push(root);
			root = root->left;
		}
		while (!root && !s.empty()) {
			root = s.top();
			if (!root->right || root->right == previous) {
				cout << root->data << " ";
				s.pop();
				previous = root;
				root = NULL;
			} else
				root = root->right;
		}
	} while (!s.empty());
}

int main() {
	tree t1;
	t1.create();
	cout << "\n...copying tree into t2..." << endl;
	tree t2;
	t2.copy(t1.getRoot());
	cout << "\n...erasing tree t1..." << endl;
	t1.erase(t1.getRoot());

	char cont;
	int ch;
	while (1) {
		cout
				<< "\n1.preorder\n2.postorder\n3.inorder\n4.preorder_nr\n5.postorder_nr\n6.inorder_nr"
				<< endl;
		cin >> ch;

		switch (ch) {
		case 1:
			t2.preorder(t2.getRoot());
			break;
		case 2:
			t2.postorder(t2.getRoot());
			break;
		case 3:
			t2.inorder(t2.getRoot());
			break;
		case 4:
			t2.preorder_nr(t2.getRoot());
			break;
		case 5:
			t2.postorder_nr(t2.getRoot());
			break;
		case 6:
			t2.inorder_nr(t2.getRoot());
			break;
		default:
			cout << "\nInvalid Entry" << endl;
		}
		cout << "continue??" << endl;
		cin >> cont;
		if(cont == 'n')
			break;
	}
	return 0;
}
