#include<iostream>

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
		
		int* temp = p;
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
	
	GrowArray() {
		int len = 0,
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
	}
	
	void addFront(int v) {
		if (used + 1 > size) {
			grow(1);  // shift by 1 and double size
		}
		else {  // shift by 1
			int* temp = p;
			p = new int[size];
			
			for (int i = 0; i < used; ++i) {  // O(n)
				p[i + 1] = temp[i];
			}
			delete [] temp;
		}
		
		p[used] = v;
		++used;
	}
	
	void removeFront() {		
		for (int i = 0; i < used - 1; ++i) {  // O(n)
			p[i] = temp[i + 1];
		}
		
		--used;
	}
	
	void removeBack() {
		p[used] = 0;
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
			s << list.p[i] << ' ';
		}
		return s;
	}
}