#include<iostream>

using namespace std;

int power(int a, int n) {
	int product = 1;
	while (n > 0) {
		if (n % 2 != 0) {
			product = product * a;
		}
		a = a * a;
		n = n / 2;
	}
	return product;
}

int power_mod(int a, int n, int m) {
	int product = 1;
	while (n > 0) {
		if (n % 2 != 0) {
			product = (product * a) % m;
		}
		a = (a * a) % m;
		n = n / 2;
		cout << "p: " << product << ", a: " << a << ", n: " << n << endl;
	}
	return product;
}

int main(int argc, char *argv[]) {
	cout << power_mod(2, 36, 37) << endl;
}