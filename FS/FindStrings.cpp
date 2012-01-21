/*
 * FindStrings.cpp
 *
 * This is my first time attempting to write a program in C++. This program
 * takes a user-defined number of strings and enumerates all unique substrings
 * of each string. Next, the program takes a user-defined number of indexes
 * and prints out each substring at each given index. If a given index
 * is out of range, the program prints and error message.
 *
 *  Created on: Jan 12, 2012
 *      Author: Peter
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <map>

using namespace std;

vector<string> substrings;
vector<string> kstrings;
vector<string>::iterator it;

/**
 * Trie recursive data structure for storing strings.
 */
struct trie {

    typedef map<char, trie *> child;
    child child_map;
    trie() :child_map(map<char, trie*>()) {}

    /**
     * Inserts a string into a trie.
     */
    void insert(string& word) {
        trie *parent = this;
        for (string::const_iterator itr = word.begin(); itr != word.end(); ++itr) {
            char ch = *itr;
            if (parent->child_map.find(ch) == parent->child_map.end()){
                parent->child_map[ch] = new trie();
            }
            parent = parent->child_map[ch];
        }
    }

    /**
     * This function recursively enumerates all unique substrings
     * of all strings stored in a trie. Each substring is directly
     * inserted into the global substring array.
     */
    void enum_substrings(vector<string>& substrings) {
    	trie *parent = this;
    	string str = "";
    	for (child::const_iterator itr = parent->child_map.begin(); itr != parent->child_map.end(); ++itr) {

    		char ch = (*itr).first;
    		str += ch;
    		substrings.push_back(str);

    		trie *node;
    		node = parent->child_map[ch];

    		if(!(node->child_map.empty())){
    			enum_substrings_aux(node, str);
    		}else{
    	   		str.clear();
    		}
    	}

    }

    /**
     * Recursive auxiliary function for enumerate substrings function.
     */
    void enum_substrings_aux(trie * node, string& str){
    	if(node == NULL){
    		return;
    	}
    	for (child::const_iterator itr = node->child_map.begin(); itr != node->child_map.end(); ++itr) {

    		char ch = (*itr).first;


    	    if(ch == '\0'){
    	    	str.clear();
    	    }else{
    	    	str += ch;
    	    	substrings.push_back(str);
    	    }


    	    trie * aux_node;
    	    aux_node = node->child_map[ch];

    	    if(!(aux_node->child_map.empty())){
    	    	enum_substrings_aux(aux_node, str);
    	    }
    	    else{

    	   		for(int i = 1; i < str.size(); i++){
    	   			substrings.push_back(str.substr(i));
    	   		}

    	   		str = str.substr(0, str.size() - 1);
    	    }
    	} //end for
    	str.clear();
    } //end enum_substrings_aux
};


/**
 * Print all elements in an array
 */
void print_elements(const vector<string>& coll)
{
	vector<string>::const_iterator pos;

    for (pos=coll.begin(); pos!=coll.end(); ++pos) {
    	cout << *pos << endl;
    }
    cout << endl;
}


trie trie; //global trie


/**
 * Conducts behavior described in "Find Strings" problem
 */
int main (){

	int n,q;
	cin >> n; //get n


	if((n < 1) || (n > 50)){
		cout << "INVALID";  //1<=n<=50
		return 0;
	}
	string mystr;
	for(int i = 0; i < n; i++){

		cin >> mystr; //get string

		if((mystr.length() > 2000) || (mystr.length() < 1)){
			cout << "INVALID";  //1<=mi<=2000
			return 0;
		}
		else{
			trie.insert(mystr);
		}

	}

	trie.enum_substrings(substrings);
	sort(substrings.begin(), substrings.end());
	it = unique(substrings.begin(), substrings.end());
	substrings.resize(it - substrings.begin());


	cin >> q; //get q


	if((q < 1) || (q > 500)){
		cout << "INVALID";  //1<=q<=500
		return 0;
	}
	else{
		int myk;
		for(int i = 0; i < q; i++){

			cin >> myk; //get substring index

			if(myk > substrings.size() || ((myk > 1000000000) || (myk < 1))){
				kstrings.push_back("INVALID"); //1<=k<=1000000000
			}
			else{
				kstrings.push_back(substrings[myk - 1]);
			}
		}
		print_elements(kstrings);
	}

	return 0;
}
