#include <iostream>
#include <fstream>

using namespace std;

class student {
	long int rno;
	string name;
	string address;
	string division;
public:
	void getdata();
	void display();
	long int getroll();
};

void student::getdata() {
	cout << "\nEnter roll no." << endl;
	cin >> rno;
	cout << "\nEnter name" << endl;
	cin >> name;
	cout << "\nEnter division" << endl;
	cin >> division;
	cout << "\nEnter address" << endl;
	cin >> address;
}

void student::display() {
	cout << "\nroll no.: " << rno << endl;
	cout << "name: " << name << endl;
	cout << "division: " << division << endl;
	cout << "address: " << address << endl;
}

long int student::getroll() {
	return rno;
}

class database {
	student s;
public:
	void write();
	void display_records();
	void modify();
	void delete_record();
	void search();
};

void database::write() {
	ofstream fout;

	fout.open("stud.txt", ios::app);
	char cont;
	while (1) {
		s.getdata();
		fout.write((char*) &s, sizeof(s));
		cout << "Do you want to add more students ?" << endl;
		cin >> cont;
		if (cont == 'n')
			break;
	}
	fout.close();
}

void database::display_records() {
	int count = 1;
	ifstream fin;
	fin.open("stud.txt");
	cout << "\nStudent Records" << endl;
	while (fin.read((char*) &s, sizeof(s))) {
		cout << "\nRecord number: " << count;
		s.display();
		count++;
	}
	fin.close();
}

void database::delete_record() {
	cout << "\nEnter the roll no. to delete" << endl;
	long int todelete;
	cin >> todelete;

	ifstream fin;
	fin.open("stud.txt");

	ofstream fout;
	fout.open("temp.txt");

	while (fin.read((char*) &s, sizeof(s))) {
		if (s.getroll() != todelete)
			fout.write((char*) &s, sizeof(s));
	}
	remove("stud.txt");
	rename("temp.txt", "stud.txt");
}

void database::modify() {
	cout << "\nEnter the roll no. to modify" << endl;
	long int tomodify;
	cin >> tomodify;

	ifstream fin;
	fin.open("stud.txt");

	ofstream fout;
	fout.open("temp.txt");

	int flag = 0;
	while (fin.read((char*) &s, sizeof(s))) {
		if (s.getroll() != tomodify)
			fout.write((char*) &s, sizeof(s));
		else {
			flag++;
			student d;
			d.getdata();
			fout.write((char*) &d, sizeof(d));
		}
	}
	if(!flag)
		cout << "\nRecord not found" << endl;
	remove("stud.txt");
	rename("temp.txt", "stud.txt");
}

void database::search() {
	cout << "\nEnter the roll no. to search" << endl;
	long int tosearch;
	cin >> tosearch;

	ifstream fin;
	fin.open("stud.txt");

	int flag = 0;
	while(fin.read((char*) &s, sizeof(s))) {
		if(s.getroll()==tosearch) {
			cout << "\nRecord found" << endl;
			s.display();
			flag++;
		}
	}
	if(!flag)
		cout << "\nRecord not found" << endl;
	fin.close();
}

int main() {
	database d;
	char cont;
	int ch;
	while(1) {
		cout << "\n1.write\n2.display\n3.modify\n4.search\n5.delete\n";
		cin >> ch;

		switch(ch) {
		case 1:
			d.write();
			break;
		case 2:
			d.display_records();
			break;
		case 3:
			d.modify();
			break;
		case 4:
			d.search();
			break;
		case 5:
			d.delete_record();
			break;
		default:
			cout << "Invalid choice" <<endl;
		}

		cout << "continue??" << endl;
		cin >> cont;
		if(cont=='n')
			break;
	}
	return 0;
}



