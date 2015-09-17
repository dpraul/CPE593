#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<time.h> // time

using namespace std;


void print_arr(int x[], int start, int end) {
	for (int i = start; i < end; ++i) {
		cout << x[i] << ' ';
	}
	cout << endl;
}


void quicksort(int x[], int left, int right) {
	int i = left,
		j = right - 1,
		tmp,
		pivot = x[(rand() % (right - left)) + left];
	if (left >= right) {
		return;
	}
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
		quicksort(x, left, j + 1);
	}
	if (i < right) {
		quicksort(x, j + 1, right);
	}
}


int main(int argc, char *argv[]) {
	string filename;
	if (argc == 2) {  // Get filename from args, if available.
		filename = argv[1];
	}
	else {  // Otherwise, prompt for filename.
		cout << "Enter filename: ";
		cin >> filename;
	}
	srand(time(0)); // seed random number generator
	
	int * x;
	int length, i = 0;
	
	ifstream file;
	file.open(filename);
	
	if (file.is_open()) {
		file >> length;  // First number from file is length
		x = new int[length];
		while (!file.eof()) {  // All following numbers go into array.
			file >> x[i];
			i++;
		}
	}
	cout << "Length: " << length << endl << "Array:  ";
	print_arr(x, 0, length);
	quicksort(x, 0, length);
	cout << "Sorted: ";
	print_arr(x, 0, length);
}