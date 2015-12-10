#ifndef BITVEC_HH_
#define BITVEC_HH_

#include<cstdint>
#include<iostream>

using namespace std;

class Bitvec {
private:
	uint64_t * bits;
	uint32_t size;
	uint32_t bitCount;
	
public:
	Bitvec(uint32_t length, bool zero = true) : size((length + 63) / 64), bitCount(length) {
		bits = new uint64_t[size];
		setAll(!zero);
	}
	
	Bitvec(const Bitvec& other) : bits(other.bits), size(other.size), bitCount(other.bitCount) {}
	
	~Bitvec() {
		delete [] bits;
	}
	
	void set(uint32_t i) {
		bits[i / 64] |= (1 << (i & 63));
	}
	
	void clear(uint32_t i) {
		bits[i / 64] &= ~(1 << (i & 63));
	}
	
	bool test(uint32_t i) {
		return (bits[i/64] & (1 << (i & 63))) != 0;
	}
	
	void setAll(bool v = true) {
		for (int i = 0; i < size; ++i) {
			if (v) {
				bits[i] = 0xFFFFFFFFFFFFFFFF;
			}
			else {
				bits[i] = 0;
			}
		}
	}
	
	friend ostream& operator << (ostream& s, Bitvec& b) {
		for (int i = 0; i < b.bitCount; ++i) {
			cout << b.test(i);
		}
		return s;
	}
};

#endif