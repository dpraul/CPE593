#include<iostream>

using namespace std;

class HashMapLinearProbing {
private:
	/**
	 * Internal data
	 **/
	int * data;
	int * histogram;
	unsigned int size;
	unsigned int used;
	
	
	/**
	 * Hashing
	 **/
	
	unsigned int hash (unsigned short value) {
		return (unsigned int)fnv1a(value) % (unsigned int)size;
	}
	
	// FNV-1a hashing from http://create.stephan-brumme.com/fnv-hash/
	// default values recommended by http://isthe.com/chongo/tech/comp/fnv/
	const static long PRIME = 0x01000193;  //   16777619
	const static long SEED  = 0x811C9DC5;  // 2166136261
	/// hash a single byte
	long fnv1a(unsigned char oneByte, long hash = SEED)
	{
		return (oneByte ^ hash) * PRIME;
	}
	
	/// hash a short (two bytes)
	long fnv1a(unsigned short twoBytes, long hash = SEED)
	{
		const unsigned char* ptr = (const unsigned char*) &twoBytes;
		hash = fnv1a(*ptr++, hash);
		return fnv1a(*ptr  , hash);
	}
	
	/// hash a 32 bit integer (four bytes)
	long fnv1a(unsigned long fourBytes, long hash = SEED)
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
		newHistogram();
		
		for(int i = 0; i < originalSize; ++i) {
			if (temp[i] != 0) {
				_add_after_check(temp[i]);
			}
		}
		delete [] temp;
	}
	
	void _add_after_check(int v) {
		unsigned int i = hash(v);
		unsigned int tries = 1;
		while (data[i] != 0) { // probe linearly
			// since used always < size, there is always space.
			if (i >= size) {
				i = 0;
			}
			else {
				++i;
			}
			++tries;
		}
		data[i] = v;
		
		if (tries >= NUM_BINS - 1) {
			tries = NUM_BINS - 1;
		}
		++histogram[tries];
				
		used++;
	}
	/**
	 * Analysis
	 **/
	 
	const static unsigned int NUM_BINS = 52;
	 
	void newHistogram() {
		delete [] histogram;
		histogram = new int[NUM_BINS];
		for (int i = 0; i < NUM_BINS; i++) {
			histogram[i] = 0;
		}
	}

public:
	HashMapLinearProbing(int initialSize = 4) {
		used = 0;
		size = initialSize * 2;
		data = new int[size];
		for (int i = 0; i < size; i++) {
			data[i] = 0;
		}
		newHistogram();
	}
	
	~HashMapLinearProbing() {
		delete [] data;
		delete [] histogram;
	}
	
	void add(int v) {
		if ((used + 1) > (size / 2)) {
			grow();
		}
		_add_after_check(v);
	}
	
	void displayHistogram() {
		cout << "TRIES\t| COUNT" << endl;
		cout << "empty\t- " << (size - used) << endl;
        for (int i = 1; i < NUM_BINS - 1; ++i) {
            cout << i << "\t- " << histogram[i] << endl;
        }
		cout << ">" << NUM_BINS - 1 << "\t-" << histogram[NUM_BINS - 1];
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
	m.displayHistogram();
}