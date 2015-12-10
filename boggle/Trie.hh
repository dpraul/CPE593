#ifndef TRIE_HH_
#define TRIE_HH_

#include<fstream>
#include<sstream>

using namespace std;

class Trie {
private:
	class Node {
	public:
		Node * next[26];
		bool isWord;

		Node() {
			for (int i = 0; i < 26; i++) {
				next[i] = nullptr;
			}
		}
	};
	Node * root;
	
	Node * getNode(const string s) {
		Node * p = root;
		int l = 0;
		for (int i = 0; i < s.size(); ++i) {
			l = (int) tolower(s[i]) - 97;
			if (p->next[l] == nullptr) {
				return nullptr;
			}
			p = p->next[l];
		}
		
		return p;
	}
	
public:
	Trie(string dict_filename = "") {
		root = new Node;

		if (!dict_filename.empty()) {
			loadDict(dict_filename);
		}
	}

	~Trie() {
		delete[] root;
	}
	
	void add(const string s) {
		if (s.empty()) {
			return;
		}
		
		Node * p = root;
		
		int l = 0;
		for (int i = 0; i < s.size(); ++i) {
			l = (int) tolower(s[i]) - 97;
			if (l > 25 || l < 0) {
				return;
			}
			if (p->next[l] == nullptr) {
				p->next[l] = new Node;
			}
			p = p->next[l];
		}
		
		p->isWord = true;
	}
	
	void loadDict(const string dict_filename) {
		ifstream file;
		file.open(dict_filename);
		
		string line_temp, word;
		
		if (file.good()) {
			while(getline(file, line_temp)) {
				istringstream line(line_temp);
				line >> word;
				add(word);
			}
		}
	}
	
	bool contains(const string s) {
		if (s.empty()) {
			return false;
		}
		Node * p = getNode(s);
		bool isWord;
		if (p == nullptr) {
			isWord = false;
		}
		else {
			isWord = p->isWord;
		}
		
		return isWord;
	}
	
	bool containsPrefix(const string s) {
		if (s.empty()) {
			return false;
		}

		return getNode(s) != nullptr;
	}

};

#endif