#include<fstream>
#include<sstream>
#include<iostream>

#include "Trie.hh"
#include "Bitvec.hh"

using namespace std;

class Boggle {
private:

	Trie * dict;
	char * board;
	int rows;
	int size;

	int find (int r, int c, Bitvec * checked, string prefix, bool print) {
		string s = prefix + board[getIndex(r, c)];
	
		bool isWord = dict->contains(s);
		if (isWord && print) {  // Print if it exists.
			cout << s << endl;
		}
	
		if (!dict->containsPrefix(s)) {  // No other words with this prefix, no point in checking them.
			return isWord;
		}
		Bitvec * check = new Bitvec((const Bitvec&) checked);
		check->set(getIndex(r, c));
		//cout << r << " " << c << " " << s << " " << checked << endl;
	
		int nextRow;
		int nextCol;
		int count = isWord;
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				if (i == 0 && j == 0)  {  // current word.
					continue;
				}
				nextRow = r + i;
				nextCol = c + j;
				if (nextRow >= rows || nextRow < 0 || nextCol >= rows || nextCol < 0) {
					continue;
				}
			
				if (!check->test(getIndex(nextRow, nextCol))) {
					count += find(nextRow, nextCol, check, s, print); 
				}
			}
		}
	
		return count;
	}

	int getIndex(int r, int c) {
		return r * rows + c;
	}

public:
	
	Boggle(string dict_filename, string board_filename) {
		dict = new Trie(dict_filename);
		loadBoard(board_filename);
	}
	
	~Boggle() {
		delete [] board;
		delete dict;
	}
	
	int findWords(bool print = true) {
		Bitvec * c = new Bitvec(rows * rows);
		int count = find(0, 0, c, "", print);

		return count;
	}
	
	void loadBoard(string board_filename) {
		ifstream file;
		file.open(board_filename);
		
		string line_temp;
		char c;
		
		if (file.good()) {
			file >> rows;
			size = rows * rows;
			
			board = new char[rows * rows];
			
			int i = 0;
			while(!file.eof() && i < size) {
				
				file >> c;
				board[i] = c;

				i++;
			}
			cout << board << endl;
		}
	}
};


int main(int argc, char *argv[]) {
	/*
	string dict_filename;
	string board_filename;
	if (argc == 3) {  // Get files from args, if available.
		dict_filename = argv[1];
		board_filename = argv[2];
	}
	else {  // Otherwise, prompt for files
		cout << "Enter dictionary filename: ";
		cin >> dict_filename;
		cout << "Enter boggle board filename: ";
		cin >> board_filename;
	}
	*/
	
	string dict_filename = "C:\\projects\\CPE593\\boggle\\dictionary.txt";
	string board_filename = "C:\\projects\\CPE593\\boggle\\boggle.dat";
	

	Boggle b(dict_filename, board_filename);
	
	cout << "Count: " << b.findWords();
	cout << "End";
}