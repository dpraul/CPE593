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
	
	if (min % 2 == 0) {  // if min is even, make it an odd number.
		min += 1;
	}

	bool* composite = new bool[(int)sqrt(max) + 1];
	bool* composite_in_range = new bool[max - min + 1];
	unsigned long long sqrt_max = (int)sqrt(max);
	double log_min = log(min * 1.0);
	unsigned long long i, j, next_start;

	// Use Erotosthenes sieve to mark remaining numbers.
	for (i = 3; i <= sqrt_max; i += 2) {
		if (!composite[i]) {
			for (j = i * i; j <= sqrt_max; j += (i * 2)) {
				composite[j] = true;
			}
			next_start = pow(i, (int)(log_min / log(i * 1.0)));
			if (next_start <  i * i) {
				next_start = i * i;
			}
			for (j = next_start; j <= max; j += (i * 2)) {
				if (j >= min) {
					composite_in_range[j - min] = true;
				}
			}
		}
	}
	// count primes recorded in sieve
	unsigned long long count = 0;
	for (i = 0; i < max - min + 1; i += 2) {
		if (!composite_in_range[i]) {
			count++;
		}
	}
	cout << "Primes: " << count;
}