/*
 * set.cpp
 *
 *  Created on: 28-Feb-2018
 *      Author: shubham
 */

/*PROBLEM STATEMENT:

 To Create ADT that implements the SET concept.
 a. Add (new Element) – place a value into the set
 b. Remove (element) Remove the value.
 c. Contains (element) Return true if element is in collection.
 d. Size () return number of values in collection
 e. iterator () Return an iterator used to loop over collection.
 f. intersection of two sets.
 g. Union of two sets
 h. Difference between two sets
 i. Subset */

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

template<class T>
class SET {
	vector<T> v;
public:
	void Create();
	void Add(T);
	void Display();
	void Remove(T);
	void Contains(T);
	void Size();
	void Intersection(vector<T>);

};

template<class T>
void SET<T>::Create() {
	cout << "\nEnter the no. of elements to add" << endl;
	int size;
	cin >> size;

	cout << "\nEnter the elements" << endl;
	T x;
	for (int i = 0; i < size; i++) {
		cin >> x;
		v.push_back(x);
	}
}

template<class T>
void SET<T>::Display() {
	cout << "\n";
	for (unsigned int i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}
	cout << "\n";
}

template<class T>
void SET<T>::Remove(T x) {
	vector<int>::iterator it;

	for(unsigned int i=0;i<v.size();i++){
		if(x==v[i]){
			v.erase(v.begin()+i);
			return;
		}
	}
		cout << "Element not present" << endl;
		return;
}

template<class T>
void SET<T>::Contains(T x) {
	vector<int>::iterator it;
	//it = search(v.begin(), v.end(), v, v.size());

	if (it != v.end()) {
		cout << "\nElement found at position " << (it - v.begin()) << '\n';
	} else
		cout << "Element not found\n";
}

template<class T>
void SET<T>::Size() {
	cout << "Size of set is : " << v.size() << endl;
}

template<class T>
void SET<T>::Intersection(vector<T>v2) {
	vector<T>x(this->v.size()+v2.size());
	vector<int>::iterator it;
	 it=set_intersection (v, v+v.size(), v2, v2+v.size(), x.begin());

	  x.resize(it-x.begin());

	  cout << "The intersection has " << (x.size()) << " elements:\n";
	  for (it=x.begin(); it!=x.end(); it++)
	    cout << ' ' << *it;
	  cout << '\n';
}


int main() {
	SET<int> s1;
	char cont;
	do {
	cout<<"a. Add (new Element) – place a value into the set\nb. Remove (element) Remove the value.\nc. Contains (element) Return true if element is in collection.\nd. Size () return number of values in collection\ne. iterator () Return an iterator used to loop over collection.\nf. intersection of two sets.\ng. Union of two sets\nh. Difference between two sets\ni. Subset\n";
	cout << "Enter choice" << endl;
	char choice;
	cin >> choice;

	switch(choice){
	case 'a':
		s1.Create();
		break;
	case 'b':
		cout << "Enter the element to be removed" << endl;
		int remov;
		cin >> remov;
		s1.Remove(remov);
		s1.Display();
		break;
	case 'c':
		cout << "Enter the element to find" << endl;
		int find;
		s1.Contains(find);
		break;
	case 'd':
		s1.Size();
		break;
	case 'e':
		break;
	case 'f':
		cout << "Enter another set" << endl;
		SET<int>s2;
		s2.Create();

		break;
	}
	cout << "Do you want to continue";
	cin >> cont;
	}while(cont=='y');
	return 0;
}

