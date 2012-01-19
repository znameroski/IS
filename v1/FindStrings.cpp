/*
 * FindStrings.cpp
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


struct trie {

    typedef map<char, trie *> child;
    child child_map;
    trie() :child_map(map<char, trie*>()) {}

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
    /*
    void print() {
        	trie *pNode = this;
        	string str = "";
        	for (child::const_iterator itr = pNode->child_map.begin(); itr != pNode->child_map.end(); ++itr) {
        		char letter = (*itr).first;
        		 if(letter == '\0'){
        			 cout << endl;
        			 str.clear();
        		 }else{
        			 cout << letter << ' ';
        			 str += letter;
        		 }
        		trie *node;
        		node = pNode->child_map[letter];
        		if(!(node->child_map.empty())){
        			print_aux(node, str);
        		}else{
        	   		str.clear();
        		}
        	}
        }
        void print_aux(trie * node, string& str){
        	if(node == NULL){
        		return;
        	}
        	for ( child::const_iterator itr = node->child_map.begin(); itr != node->child_map.end(); ++itr) {
        		char letter = (*itr).first;

        	    if(letter == '\0'){
        	    	cout << endl;
        	    	str.clear();
        	    }else{
        	    	//cout << letter << ' ';
        	    	str += letter;
        	    	cout << str << ' ';
        	    }
        	    trie * aux_node;
        	    aux_node = node->child_map[letter];
        	    if(!(aux_node->child_map.empty())){
        	    	print_aux(aux_node, str);
        	    	//str = str.substr(0, (str.size() - 1));
        	    }
        	    else{
        	   		//str.clear();
        	   		for(int i = 1; i < str.size(); i++){
        	   		   cout << str.substr(i) << ' ';
        	   		}
        	   		str = str.substr(0, str.size() - 1);
        	    }
        	}
        }
        */
    void enum_substrings(vector<string>& substrings) {
    	trie *parent = this;
    	string str = "";
    	for (child::const_iterator itr = parent->child_map.begin(); itr != parent->child_map.end(); ++itr) {
    		char ch = (*itr).first;
    		/*
    		 if(ch == '\0'){
    			 str.clear();
    		 }else{
    		 */
    			 str += ch;
    			 substrings.push_back(str);
    		 //}
    		trie *node;
    		node = parent->child_map[ch];
    		if(!(node->child_map.empty())){
    			enum_substrings_aux(node, str);
    		}else{
    	   		str.clear();

    		}
    	}

    }
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
    	   		//str.clear();
    	    }
    	}
    	str.clear();
    }
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

trie trie;
/**
 * Conducts behavior described in "Find Strings" problem
 */
int main (){



	int n,q;
	//cin >> n;

	ifstream myfile1("test1"); //file
	string n_string; //file
	getline (myfile1, n_string); //file
	n = atoi(n_string.c_str()); //file






	if((n < 1) || (n > 50)){
		cout << "INVALID";  //1<=n<=50
		return 0;
	}
	string mystr;
	for(int i = 0; i < n; i++){

		//cin >> mystr;
		getline (myfile1, mystr); //file

		if((mystr.length() > 2000) || (mystr.length() < 1)){
			cout << "INVALID";  //1<=mi<=2000
			return 0;
		}
		else{
			trie.insert(mystr);
		}

	}
	//trie.print();
	trie.enum_substrings(substrings);
	sort(substrings.begin(), substrings.end());
	it = unique(substrings.begin(), substrings.end());
	substrings.resize(it - substrings.begin());
	//print_elements(substrings);

	//cin >> q;

	string q_string; //file
	getline (myfile1, q_string); //file
	q = atoi(q_string.c_str()); //file


	if((q < 1) || (q > 500)){
		cout << "INVALID";  //1<=q<=500
		return 0;
	}
	else{
		int myk;
		string mystr;
		string k_string; //file
		for(int i = 0; i < q; i++){

			//cin >> myk;

			getline (myfile1, k_string); //file
			myk = atoi(k_string.c_str()); //file


			if(myk > substrings.size() || ((myk > 1000000000) || (myk < 1))){
				kstrings.push_back("INVALID"); //1<=k<=1000000000
			}
			else{
				kstrings.push_back(substrings[myk - 1]);
			}
		}
		print_elements(kstrings);
	}


	myfile1.close();
	return 0;
}
