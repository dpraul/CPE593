#include<iostream>

using namespace std;

class HashMapLinearProbing {
private:
	/**
	 * Internal data
	 **/
	int * data;
	int size;
	int used;
	
	
	/**
	 * Hashing algorithm
	 **/
	
	int hash (unsigned short value) {
		return fnv1a(value) % size;
	}
	
	// FNV-1a hashing from http://create.stephan-brumme.com/fnv-hash/
	// default values recommended by http://isthe.com/chongo/tech/comp/fnv/
	const static long Prime = 0x01000193;  //   16777619
	const static long Seed  = 0x811C9DC5;  // 2166136261
	/// hash a single byte
	long fnv1a(unsigned char oneByte, long hash = Seed)
	{
		return (oneByte ^ hash) * Prime;
	}
	
	/// hash a short (two bytes)
	long fnv1a(unsigned short twoBytes, long hash = Seed)
	{
		const unsigned char* ptr = (const unsigned char*) &twoBytes;
		hash = fnv1a(*ptr++, hash);
		return fnv1a(*ptr  , hash);
	}
	
	/// hash a 32 bit integer (four bytes)
	long fnv1a(unsigned long fourBytes, long hash = Seed)
	{
		const unsigned char* ptr = (const unsigned char*) &fourBytes;
		hash = fnv1a(*ptr++, hash);
		hash = fnv1a(*ptr++, hash);
		hash = fnv1a(*ptr++, hash);
		return fnv1a(*ptr  , hash);
	}
	
	/**
	 * Internal functions
	 **/
	
	void grow() {
		int * temp = data;
		int originalSize = size;
		
		size *= 2;
		used = 0;
		data = new int[size];
		
		for (int i = 0; i < size; i++) {
			data[i] = 0;
		}
		
		for(int i = 0; i < originalSize; ++i) {
			if (temp[i] != 0) {
				_add_after_check(temp[i]);
			}
		}
		delete [] temp;
	}
	
	void _add_after_check(int v) {
		int i = hash(v);
		while (data[i] != 0) { // probe linearly
			// since used always < size, there is always space.
			if (i >= size) {
				i = 0;
			}
			else {
				++i;
			}
		}
		data[i] = v;
		used++;
	}

public:
	HashMapLinearProbing(int initialSize = 4) {
		used = 0;
		size = initialSize * 2;
		data = new int[size];
		for (int i = 0; i < size; i++) {
			data[i] = 0;
		}
	}
	
	~HashMapLinearProbing() {
		delete [] data;
	}
	
	void add(int v) {
		if ((used + 1) > (size / 2)) {
			grow();
		}
		_add_after_check(v);
	}
	
	friend ostream& operator << (ostream& s, const HashMapLinearProbing& map) {
        for (int i = 0; i < map.size; ++i) {
            s << map.data[i] << " ";
        }
        return s;
    }
};

int main(int argc, char *argv[]) {
	int n;
	HashMapLinearProbing m;
	cout << "Numbers to input: ";
	cin >> n;
	
	for (int i = 1; i <= n; ++i) {
		m.add(i);
	}
	cout << m;
	//m.displayHistogram();
}