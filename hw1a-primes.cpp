#include<iostream>
#include<math.h>
#include<stdlib.h>  // for strtol

using namespace std;

const long long TABLE_LEN = 100000000000000;

int main(int argc, char *argv[]) {
	unsigned long long min, max;
	/*
	if (argc == 3) {
		min = strtol(argv[1], NULL, 10);  // a
		max = strtol(argv[2], NULL, 10);  // b
	}
	else {
		cout << "Enter a (a < 10^14): ";
		cin >> min;
		cout << "Enter b (a < b < 10^14): ";
		cin >> max;
	}
	*/
	min = 2000000000000;
	max = 2000000100000;
	if (min > max) {
		cout << "b must be larger than a" << endl;
		return 0;
	}

	bool* not_prime = new bool[TABLE_LEN];

	unsigned long long i, j;

	for (i = 2; i <= max; i ++) {
		if (!not_prime[i - 1]) {
			for (j = i * i; j <= max; j += 2 * i) {
				not_prime[j - 1] = true;
			}
		}
	}

	unsigned long long count = 0;
	for (i = min; i <= max; i += 2) {
		if (!not_prime[i - 1]) {
			count++;
		}
	}

	cout << count;
}