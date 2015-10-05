#include<iostream>
#include<fstream>
#include<stdlib.h>

using namespace std;

int binarySearch(int x[], int target, int length) {
	int i = 0, j = length, guess, iter = 0;
	/* Optimization disabled for prompt.
	if (target > x[length - 1] || target < x[0]) {
		cout << "NOT FOUND 0";
	}*/
	while (i <= j) {
		++ iter;
		guess = (i + j) / 2;
		if (x[guess] == target) {
			cout << guess << " " << iter << endl;
			return guess;
		}
		if (x[guess] > target) {
			j = guess - 1;
		}
		else if (x[guess] < target) {
			i = guess + 1;
		}
	}
	cout << "NOT FOUND " << iter << endl;
	return -1;
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
	
	int * x;
	int cases, length, target, i = 0, result, k = 0;
	
	ifstream file;
	file.open(filename);
	
	string temp; // Put in stuff we don't need
	if (file.is_open()) {
		file >> temp; // the string "Cases:"
		file >> cases;  // Number of cases. We won't use this since we can dete.
		k = 0;
		while (!file.eof() && k < cases) {  // Go through each case.
			file >> length; // First line, number of elements
			x = new int[length];
			for (i = 0; i < length; i++) { // Second line is list of elements
				file >> x[i];
			}
			file >> target; // Third line is number to search.
			binarySearch(x, target, length);
			++ k;
		}
	}
}