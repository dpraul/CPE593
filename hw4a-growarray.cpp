#include<iostream>
#include<fstream>
#include<sstream>

using namespace std;

class GrowArray {
private:
	int * p;
	int used;
	int size;
	
	void grow(int offset) {  // O(n)
		/** Multiplies array size by 2.
			offset - indeces to shift new array (useful for addFront)
		 **/
		size = size * 2;
		
		int * temp = p;
		p = new int[size];
		
		for (int i = 0; i < used; ++i) {  // O(n)
			p[i + offset] = temp[i];
		}
		delete [] temp;
	}
	
	void grow() {
		grow(0);
	}
public:
	GrowArray(int initialSize) {
		used = 0;
		size = initialSize;
		p = new int[size];
		
	}
	GrowArray() {
		used = 0;
		size = 1;
		p = new int[size];
	}
	
	~GrowArray() {
		delete [] p;
	}
	
	void addBack(int v) {
		if (used + 1 > size) {
			grow();
		}
		p[used] = v;
		++used;
		//cout << ", " << used << ", " << size << ", ";
	}
	
	void addFront(int v) {
		if (used + 1 > size) {
			grow(1);  // shift by 1 and double size
		}
		else {  // shift by 1
			for (int i = used - 1; i >= 0; --i) {  // O(n)
				p[i + 1] = p[i];
			}
		}
		
		p[0] = v;
		++used;
		//cout << used << ", " << size << ": ";
	}
	
	void removeFront() {
		for (int i = 0; i < used - 1; ++i) {  // O(n)
			p[i] = p[i + 1];
		}
		
		--used;
	}
	
	void removeBack() {
		p[used - 1] = 0;
		--used;
	}
	
	int get(int i) {
		return p[i];
	}
	
	int length() const {
		return used;
	}

	friend ostream& operator << (ostream& s, const GrowArray& list) {
		for (int i = 0; i < list.length(); i++) {
			s << list.p[i] << " ";
		}
		return s;
	}
};

int main(int argc, char *argv[]) {
	string filename;
	if (argc == 2) {  // Get filename from args, if available.
		filename = argv[1];
	}
	else {  // Otherwise, prompt for filename.
		cout << "Enter filename: ";
		cin >> filename;
	}
	
	GrowArray a;
	
	string line, choice;
	int input, i;
	istringstream linestream;
	
	ifstream file;
	file.open(filename);
	
	if (file.is_open()) {
		while (!file.eof()) {
			getline(input, line);
			linestream(line);
			linestream >> choice;
			if (choice == "ADD_FRONT") {
				while (linestream >> input) {
					a.addFront(input);
				}
			}
			else if (choice ==  "ADD_BACK") {
				while (linestream >> input) {
					a.addBack(input);
				}
			}
			else if (choice == "REMOVE_FRONT") {
				linestream >> input;
				for (i = 0; i < input; i++) {
					a.removeFront();
				}
			}
			else if (choice == "REMOVE_BACK") {
				linestream >> input;
				for (i = 0; i < input; i++) {
					a.removeBack();
				}
			}
			else if (choice == "OUTPUT") {
				cout << a << endl;
			}
			else {
				cout << "BAD INPUT";
				break;
			}
		}
	}
}