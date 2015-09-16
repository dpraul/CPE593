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
		cout << "requirements: a < b < 10^14, b - a < 10^9" << endl;
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
	
	// Guarantee that min is an odd number.
	if (min % 2 == 0) {
		min += 1;
	}


	unsigned long long sqrt_max = (int)sqrt(max);
	unsigned long long i, j, count = 0;

	// In this case, it is more optimized to do the whole sieve
	if (min <= sqrt_max) {
		bool* composite = new bool[max + 1];

		composite[0] = true;  // 0 is not prime.
		composite[1] = true;  // 1 is not prime.
		composite[2] = false; // 2 is prime.
		for (i = 3; i <= sqrt_max; i += 2) {
			if (!composite[i]) {
				// Create the whole sieve from 3 to max
				for (j = i * i; j <= max; j += (i * 2)) {
					composite[j] = true;
				}
			}
		}

		// Count primes only above min, a.k.a. in composite_in_range
		for (i = min; i <= max; i += 2) {
			if (!composite[i]) {
				++count;
			}
		}

		if (min <= 2) {  // 2 is the only even number that is prime... add it in!
			++count;
		}
	}

	// Otherwise, we can skip all the numbers between sqrt_max and min
	else {
		bool* composite = new bool[(int)sqrt(max) + 1];
		bool* composite_in_range = new bool[max - min + 1];

		for (i = 3; i <= sqrt_max; i += 2) {
			if (!composite[i]) {
				// Create a base sieve from 3 to sqrt_max
				for (j = i * i; j <= sqrt_max; j += (i * 2)) {
					composite[j] = true;
				}
				// ... and also create a sieve from min to max.
				for (j = ((unsigned long long)(min / i) * i) + i; j <= max; j += i) {
					composite_in_range[j - min] = true;
				}
			}
		}

		// Count primes only above min, a.k.a. in composite_in_range
		for (i = 0; i < max - min + 1; i += 2) {
			if (!composite_in_range[i]) {
				++count;
			}
		}
	}
	cout << "Primes: " << count;
}