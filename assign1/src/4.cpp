#include <iostream>
#include <cstdlib>
#include <string.h>
#include <string>

#define MAX 10

using namespace std;

class PhoneBook {
	string name;
	string number;
public:
	PhoneBook() {
		name = "---";
		number = "---";
	}
	friend class HashTable;
};

class HashTable {
	PhoneBook Hash[MAX];
public:
	int insert(string, string);
	int getKey(string);
	int hashFunction(int);
	void find(string);
	void display() {
		for (int i = 0; i < MAX; i++)
			cout << Hash[i].name << "\t" << Hash[i].number << endl;
	}
};

int HashTable::getKey(string key) {
	char keyCharArray[key.length()];
	strcpy(keyCharArray, key.c_str());
	int newKey;
	for (unsigned int i = 0; i < key.length(); i++) {
		newKey += int(keyCharArray[i]);
	}
	return newKey;
}

int HashTable::hashFunction(int key) {
	int location = key % MAX;
	return location;
}

int HashTable::insert(string key, string number) {
	int newKey = getKey(key);
	int loc = hashFunction(newKey);
	int flag = 0;

	for (int i = loc;; i = (i + 1) % MAX) {
		if (Hash[i].name == "---") {
			Hash[i].name = key;
			Hash[i].number = number;
			flag++;
		}
		if (i == loc) {
			cout << "\nallocation failed" << endl;
			break;
		}
	}
	return flag;
}

void HashTable::find(string key) {
	int newKey = getKey(key);
	int loc = hashFunction(newKey);

	for (int i = loc;; i = (i + 1) % MAX) {
		if (Hash[i].name == key) {
			cout << "Phone Number: " << Hash[i].number << endl;
			break;
		}
		if (i == loc) {
			cout << "Person doesn't exist" << endl;
			break;
		}
	}
}

int main() {
	HashTable t;
	char choice;
	while (1) {
		cout << "\na.insert\nb.find\nc.display\nd.exit" << endl;
		cout << "Enter choice" << endl;
		cin >> choice;

		switch (choice) {
		case 'a': {
			string Name;
			string Number;
			cout << "\nEnter name and number" << endl;
			cin >> Name;
			cin >> Number;
			t.insert(Name, Number);
			break;
		}
		case 'b': {
			string Name;
			cout << "\nEnter name of the client" << endl;
			cin >> Name;
			t.find(Name);
			break;
		}
		case 'c':
			t.display();
			break;
		case 'd':
			exit(0);
		}
	}
	return 0;
}


