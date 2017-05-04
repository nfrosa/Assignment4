using namespace std;
#include <iostream> 
#include <string> 
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <vector>
#include <queue>
#include <stack>
 int getNum(char ch) {
	int index;
	int num = (int)ch;
	if (num >= 97 && num <= 122)
		index = num - 97;
	else if (num >= 65 && num <= 90)
		index = num - 65;
	return index;
 };
class TreeNode {
public:
	TreeNode * Parent;
	vector<TreeNode*> children;
	int value = 0;
	char v;
	TreeNode(char val, TreeNode* ParentNode) {
		children.resize(26);
		v = val;
		Parent = ParentNode;	
	}
	TreeNode() {
		children.resize(26);
	}
	void addChild(TreeNode &child) {
		int num = getNum(child.v);
		children.at(num) = &child;
	}
	bool isNull() {
		bool isnull = true;
		for (int i = 0; i < 26; i++) {
			if (children.at(i) != nullptr) {
				isnull = false;
				break;
			}
		}
		return isnull;
	}
	bool isNull(int start,int end) {
		bool isnull = true;
		int i = start;
		int j = end;
		while (i != j) {
			if (children.at(i) != nullptr) {
				isnull = false;
				break;
			}
			i++;
		}
		return isnull;
	}
};

class Tree {
public:
	TreeNode rootnode;
	TreeNode * root = &rootnode;
	Tree() {
	}
	string printArray(TreeNode* rootn, string parents) {
		TreeNode* temp = rootn;
		string str = parents;
		for (int i = 0; i < 26; i++) {
			string tempstring = str;
			if (temp->children.at(i) != nullptr) {
				char curr = temp->children.at(i)->v;
				tempstring = str;
				str.append(1, curr);
				str = printArray(temp->children.at(i), str);
				if (temp->children.at(i)->value > 0) {
					cout << str << ": " << temp->children.at(i)->value << endl;
					//not clearing intermediate characters, doesnt print for the first character
					str = tempstring;
					if (temp->isNull(i, 26)) {
						break;
					}
				} 
				str = tempstring;
			}
		}
		return str;
	}
	void insertWord(vector<string> words) {
		TreeNode * par = root;
		for (int i = 0; i < words.size(); i++) {
			string str = words.at(i);
			par = root;
			if (str.length() > 0) {
				for (int j = 0; j < str.length(); j++) {
					char ch = str.at(j);
					int index = getNum(ch);
					//making a node out of individual characters
					//placeChar will take in the current character and attempt to place it in the array
					//if it can't be placed because it is already present, it won't place and the loop will continue
					if (j == 0) {
						par = root;
					}
					//checking if word is already present
					if (par->children.at(index) != nullptr && par->children.at(index)->value == 1 && j == str.length()-1) {
					}
					//checking if character is already present
					else if (par->children.at(index) != nullptr) {
					}
					else {
						placeChar(ch, par, new TreeNode(ch, par));
					}
					//nu becomes the node for ch, and the parent for the next round
					par = par->children.at(index);
				}
			}
			if (!isblank(par->v)) {
				par->value++;
			}
		}
	}
	void placeChar(char ch,TreeNode *& par, TreeNode* nu) {
		int index = getNum(ch);
		par->addChild(*nu); // does this really work lol
	}
	void decrement(string key) {
		TreeNode * rootptr = root;
		for (int i = 0; i < key.size(); i++) {
			char ch = key.at(i);
			int num = getNum(ch);
			if (rootptr->children.at(num) != nullptr && i == key.size()-1) {
				rootptr->children.at(num)->value--;
			} else if (rootptr->children.at(num) == nullptr){
				break; 
			}
			rootptr = rootptr->children.at(num);
		}
	}
};



int main() {
	string in;
	getline(cin,in);
	if (cin.fail()) {
		return -1;
		cin.clear();
		cin.ignore();
	}
	vector<string> words;
	//putting words in string into a vector
	for (int i = 0; i < in.length(); i++) {
		string word;
		int j = 0;
		while(i < in.length() && !isspace(in.at(i)) ){
			word.append(1,in.at(i));
			j++;
			i++;
		}
		if (word.size() != 0) {
			words.push_back(word);
		}
	}
	Tree trie;
	string blank = "";
	trie.insertWord(words);
	//trie.printArray(trie.root,blank);
	getline(cin, in);
	if (cin.fail()) {
		return -1;
		cin.clear();
		cin.ignore();
	}
	words.clear();
	for (int i = 0; i < in.length(); i++) {
		string word;
		int j = 0;
		while (i < in.length() && !isspace(in.at(i))) {
			word.append(1, in.at(i));
			j++;
			i++;
		}
		if (word.size() != 0) {
			words.push_back(word);
		}
	}
	for (int i = 0; i < words.size(); i++) {
		string str = words.at(i);
		trie.decrement(str);
	}

	trie.printArray(trie.root, blank);
}
