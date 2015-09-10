#include<iostream>
#include<math.h>  // for sqrt
#include<stdlib.h>  // for strtol
#include<vector>

using namespace std;

int main(int argc, char *argv[]) {
	unsigned long long min, max;
	
	if (argc == 3) {  // If available, get numbers from arg string -- only works for ints
		min = strtol(argv[1], NULL, 10);  // a
		max = strtol(argv[2], NULL, 10);  // b
	}
	else {  // Else, have user enter in.
		cout << "requirements: a < b < 10^14" << endl;
		cout << "Enter a (min): ";
		cin >> min;
		cout << "Enter b (max): ";
		cin >> max;
	}
	cout << "a = " << min << ", b = " << max << endl;

	// Assure the entered values fit the spec.
	if (min >= max) {
		cout << "b must be larger than a" << endl;
		return 0;
	}

	vector<bool> composite(max + 1, false);
	unsigned long long i, j;
	// Manually set 0 and 1 to composite
	composite[0] = true;
	composite[1] = true;

	// Set all even numbers to composite
	//!! In testing, this turned out to be slower than checking whether
	//!! the number was even during each loop, so it was commented out
	//for (i = 4; i <= max; i += 2) {
	//	composite[i] = true;
	//}
	// Use Erotosthenes sieve to mark remaining numbers.
	for (i = 3; i <= (int)sqrt(max); i += 2) {
		if (!composite[i] && i % 2 != 0) {
			for (j = i * i; j <= max; j += (i * 2)) {
				composite[j] = true;
			}
		}
	}

	// Count primes from min to max
	unsigned long long count = 0;
	// 2 is the only prime even though it's even, so include if needed
	if (min <= 2) {
		count++;
	}
	for (i = min; i <= max; i++) {
		if (!composite[i] && i % 2 != 0) {
			count++;
		}
	}
	cout << "Primes: " << count;
}