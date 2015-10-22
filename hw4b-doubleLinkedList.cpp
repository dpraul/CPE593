#include<fstream>
#include<sstream>
#include<iostream>

using namespace std;

class DoubleLinkedList {
private:
	class Node {
	public:
		int value;
		Node * next;
		Node * prev;
		Node(Node * p, int v, Node * n) {
			value = v;
			next = n;
			prev = p;
		}
	};
	Node * head;
	Node * tail;
public:
	DoubleLinkedList() {
		head = tail = nullptr;
	}
	
	~DoubleLinkedList() {
		Node * temp;
		for (temp = head->next; temp != nullptr; temp = temp->next) {
			delete temp->prev;
		}
	}
	
	void addBack(int v) {
		if (head == nullptr) {
			head = tail = new Node(nullptr, v, nullptr);
		}
		else {
			tail->next = new Node(tail, v, nullptr);
			tail = tail->next;
		}
	}
	
	void addFront(int v) {
		if (head == nullptr) {
			head = tail = new Node(nullptr, v, nullptr);
		}
		else {
			head->prev = new Node(nullptr, v, head);
			head = head->prev;
		}
	}
	
	void removeFront() {
		Node * temp = head;
		head = head->next;
		head->prev = nullptr;
		delete temp;
	}
	
	void removeBack() {
		Node * temp = tail;
		tail = tail->prev;
		tail->next = nullptr;
		delete temp;
	}

	friend ostream& operator << (ostream& s, const DoubleLinkedList& list) {
        Node * temp;
        for (temp = list.head; temp != nullptr; temp = temp->next) {
            s << temp->value << " ";
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
	
	DoubleLinkedList a;
	
	string line_temp, choice;
	int input, i;
	
	ifstream file;
	file.open(filename);
	
	if (file.good()) {
		while (getline(file, line_temp)) {
			istringstream line(line_temp);
			line >> choice;
			if (choice == "ADD_FRONT") {
				while (line >> input) {
					a.addFront(input);
				}
			}
			else if (choice ==  "ADD_BACK") {
				while (line >> input) {
					a.addBack(input);
				}
			}
			else if (choice == "REMOVE_FRONT") {
				line >> input;
				for (i = 0; i < input; ++i) {
					a.removeFront();
				}
			}
			else if (choice == "REMOVE_BACK") {
				line >> input;
				for (i = 0; i < input; ++i) {
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