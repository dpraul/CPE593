#include<iostream>
#include<fstream>
#include<stdlib.h> // rand

using namespace std;

void print_arr(int x[], int length) {
	for (int i = 0; i < length; ++i) {
		cout << x[i] << ' ';
	}
	cout << endl;
}


void quicksort(int x[], int left, int right) {
	int i = left,
		j = right,
		tmp,
		pivot = x[rand() % (right + 1)];
	cout << pivot << ' ' << left << ' ' << right << endl;
	print_arr(x, right + 1);
	while (i <= j) {
		while (x[i] < pivot) {
			++i;
		}
		while (x[j] > pivot) {
			--j;
		}
		if (i <= j) {
			// swap i and j
			tmp = x[i];
			x[i] = x[j];
			x[j] = tmp;
			++i;
			--j;
		}
	}
	
	if (left < j) {
		quicksort(x, left, j);
	}
	if (i > right) {
		quicksort(x, i, right);
	}
}

int main(int argc, char *argv[]) {
	char *filename;
	if (argc == 1) {
		filename = argv[1];
	}
	else {
		cout << "Enter filename: ";
		cin >> filename;
	}
	ifstream file;
	string line;
	
	int length;
	string arr;
	file.open(filename);
	if (file.is_open()) {
		fstream(getline(file, line), length);
		getline(file, arr);
	}
	cout << length;
	cout << arr;
	//int x[] {9, 2, 5, 4, 11, 3, 1, 3, 5, 6, 7, 2, 8};
	//cout << sizeof(x) << endl;
	//print_arr(x, sizeof(x));
	//quicksort(x, 0, sizeof(x) - 1);
	//print_arr(x);
}