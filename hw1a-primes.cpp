#include<iostream>
#include<stdlib.h>  // for strtol

using namespace std;

const int TABLE_LEN = 1000000;

int main(int argc, char *argv[]) {
	if (argc != 3) {
		cout << "usage: " << argv[0] << " <a> <b>" << endl;
		cout << "where a < b <= 10^14 and b - a < 10^9";
		return 0;
	}

	int min = strtol(argv[1], NULL, 10);  // a
	int max = strtol(argv[2], NULL, 10);  // b
	if (min >= max) {
		cout << "usage: " << argv[0] << " <a> <b>" << endl;
		cout << "where a < b <= 10^14 and b - a < 10^9";
		return 0;
	}

	bool not_prime[TABLE_LEN] = { false };

	long i, j;

	for (i = 2; i <= max; i ++) {
		if (!not_prime[i - 1]) {
			for (j = i * i; j <= max; j += 2 * i) {
				not_prime[j - 1] = true;
			}
		}
	}

	long count = 0;
	for (i = min; i <= max; i += 2) {
		if (!not_prime[i - 1]) {
			count++;
		}
	}

	cout << count;
}