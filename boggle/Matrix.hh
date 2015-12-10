#ifndef MATRIX_HH_
#define MATRIX_HH_

#include<iostream>

using namespace std;

class Matrix {
private:
	char * m;
	int rows, cols;
public:
	Matrix(int r, int c) : rows(r), cols(c) {
		m = new char[rows * cols];
		
	}
	~Matrix() {
		delete [] m;
	}
	
	char get(int i) {
		return m[i];
	}
	
	void set(int i, char x) {
		m[i] = x;
	}
	
	char get(int r, int c) {

		return m[r * cols + c];
	}
	
	void set(int r, int c, char x) {
		m[r * cols + c] = x;
	}

	friend ostream& operator << (ostream& s, Matrix& mat) {
		for (int i = 0; i < mat.rows; i++) {
			for (int j = 0; j < mat.cols; j++) {
				s << mat.get(i, j) << " ";
			}
			s << endl;
		}
		return s;
	}
};	

#endif