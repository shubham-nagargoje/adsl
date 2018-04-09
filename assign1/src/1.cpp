#include <iostream>
#include <vector>

using namespace std;

template<class T>
class SET {
	vector<T> v;
public:
	void insert();
	void display();
	void contains();
	void remove();
	void subset();
	void intersection();
	void unionSet();
	void size();
};

template<class T>
void SET<T>::insert() {
	cout << "\nHow many elements" << endl;
	int num;
	cin >> num;

	for (int i = 0; i < num; i++) {
		cout << "\nEnter the element" << endl;
		T element;
		cin >> element;

		int flag = 0; //For not accepting duplicates
		for (unsigned int i = 0; i < v.size(); i++) {
			if (element == v[i])
				flag = 1;
		}
		if (flag == 1) {
			cout << "\nElement already present.Enter another element" << endl;
			num++;
			continue;
		} else
			v.push_back(element);
	}
}

template<class T>
void SET<T>::display() {
	for (unsigned int i = 0; i < v.size(); i++)
		cout << v[i] << "  ";
	cout << "\n";
}

template<class T>
void SET<T>::contains() {
	cout << "\nEnter the element to find" << endl;
	T element;
	cin >> element;

	for (unsigned int i = 0; i < v.size(); i++) {
		if (v[i] == element) {
			cout << "\nElement found at position " << i + 1;
			break;
		}

	}
	cout << "\nElement not found" << endl;
}

template<class T>
void SET<T>::remove() {
	cout << "\nEnter the element to delete" << endl;
	T element;
	cin >> element;

	for (unsigned int i = 0; i < v.size(); i++) {
		if (element == v[i]) {
			v.erase(v.begin() + i);
			return;
		}
	}
	cout << "\nElement not present" << endl;
}

template<class T>
void SET<T>::size() {
	cout << "\nSize is :" << v.size() << endl;
}

template<class T>
void SET<T>::subset() {
	SET<T> newSet;
	newSet.insert();

	int count;
	for (unsigned int i = 0; i < newSet.v.size(); i++) {
		for (unsigned int j = 0; j < v.size(); j++) {
			if (newSet.v[i] == v[j])
				count++;
		}
	}
	if (count == newSet.v.size())
		cout << "\nEntered set is a subset of 1st set" << endl;
	else
		cout << "\nNot a subset" << endl;
}

template<class T>
void SET<T>::unionSet() {
	SET<T> newSet;
	newSet.insert();

	SET<T> uniSet;
	for (unsigned int i = 0; i < v.size(); i++)
		uniSet.v.push_back(v[i]);

	for (unsigned int i = 0; i < newSet.v.size(); i++)
		uniSet.v.push_back(newSet.v[i]);

	cout << "The union has " << (uniSet.v.size()) << " elements:\n";
	uniSet.display();
}

template<class T>
void SET<T>::intersection() {
	SET<T> newSet;
	newSet.insert();

	SET<T> interSet;

	for (unsigned int i = 0; i < v.size(); i++)
		for (unsigned int j = 0; j < newSet.v.size(); j++) {
			if (v[i] == newSet.v[j])
				interSet.v.push_back(v[i]);
		}
	cout << "The intersection has " << (interSet.v.size()) << " elements:\n";
	interSet.display();
}

int main() {
	SET<int> s;
	char cont;
	do {
		cout
				<< "\na.insert\nb.display\nc.contains\nd.remove\ne.subset\nf.intersection\ng.unionSet\nh.size"
				<< endl;
		cout << "Enter choice" << endl;
		char ch;
		cin >> ch;

		switch (ch) {
		case 'a':
			s.insert();
			break;
		case 'b':
			s.display();
			break;
		case 'c':
			s.contains();
			break;
		case 'd':
			s.remove();
			break;
		case 'e':
			s.subset();
			break;
		case 'f':
			s.intersection();
			break;
		case 'g':
			s.unionSet();
			break;
		case 'h':
			s.size();
			break;
		}
		cout << "continue?" << endl;
		cin >> cont;
	} while (cont == 'y');

	return 0;
}


