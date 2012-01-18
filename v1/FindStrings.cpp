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




struct trie_node_t {

    typedef map<char, trie_node_t *> child_node_t;
    child_node_t m_childMap;
    trie_node_t() :m_childMap(map<char, trie_node_t*>()) {}

    void insert( string& word ) {
        trie_node_t *pNode = this;
        for ( string::const_iterator itr = word.begin(); itr != word.end(); ++itr) {
            char letter = *itr;
            if ( pNode->m_childMap.find(letter) == pNode->m_childMap.end()){
                pNode->m_childMap[letter] = new trie_node_t();
            }
            pNode = pNode->m_childMap[letter];
        }
    }
    /*oid display()
    {
        preorder_display(root);
    }

    void preorder_display(trie_node_t* t)
    {
        if(t == NULL)
            return;

        cout << "iterating :: " << t->character << " :: " << t->eow << " :: " << t->prefixes << endl;

        for(int i=0;i<26;i++)
        {
            if(t->edge[i] != NULL)
                preorder_display(t->edge[i]);
        }
    }
    */
    void print() {
    	trie_node_t *pNode = this;
    	string str = "";
    	for ( child_node_t::const_iterator itr = pNode->m_childMap.begin(); itr != pNode->m_childMap.end(); ++itr) {
    		char letter = (*itr).first;
    		 if(letter == '\0'){
    			 cout << endl;
    			 str.clear();
    		 }else{
    			 cout << letter << ' ';
    			 str += letter;
    		 }
    		trie_node_t *node;
    		node = pNode->m_childMap[letter];
    		if(!(node->m_childMap.empty())){
    			print_aux(node, str);
    		}else{
    	   		cout << ' ';
    	   		str.clear();
    		}
    	}
    }
    void print_aux(trie_node_t * node, string& str){
    	if(node == NULL){
    		return;
    	}
    	for ( child_node_t::const_iterator itr = node->m_childMap.begin(); itr != node->m_childMap.end(); ++itr) {
    		char letter = (*itr).first;

    	    if(letter == '\0'){
    	    	cout << endl;
    	    	str.clear();
    	    }else{
    	    	//cout << letter << ' ';
    	    	str += letter;
    	    	cout << str << ' ';
    	    }
    	    trie_node_t * aux_node;
    	    aux_node = node->m_childMap[letter];
    	    if(!(aux_node->m_childMap.empty())){
    	    	print_aux(aux_node, str);
    	    }
    	    else{
    	   		cout << ' ';
    	   		str.clear();
    	    }
    	}
    }
};
/**
 * Print all elements in an array
 */
void PRINT_ELEMENTS (const vector<string>& coll) //file
{
	vector<string>::const_iterator pos;


    for (pos=coll.begin(); pos!=coll.end(); ++pos) {
        //cout << *pos << endl;
    	cout << *pos << endl; //file
    }
    //cout << endl;
    cout << endl; //file
}

vector<string> substrings;
vector<string> kstrings;
vector<string>::iterator it;
trie_node_t trie;
/**
 * Conducts behavior described in "Find Strings" problem
 */
int main (){
	cout << "START MAIN \n";

	ifstream myfile1("test2"); //file
	//ofstream myfile2("output"); //file

	cout << "START\n";
	int n,q;

	//cin >> n;
	//myfile1 >> n; //file
	string n_string; //file
	getline (myfile1, n_string); //file
	n = atoi(n_string.c_str()); //file
	cout << "GOT N: " << n << endl;



	if((n < 1) || (n > 50)){
		cout << "INVALID";  //1<=n<=50
		//myfile2 << "INVALID"; //file
		return 0;
	}
	string mystr;
	for(int i = 0; i < n; i++){
		//myfile2 << "START 1ST FOR\n";

		//cin >> mystr;
		//myfile1 >> mystr; //file
		getline (myfile1, mystr); //file

		if((mystr.length() > 2000) || (mystr.length() < 1)){
			cout << "INVALID";  //1<=mi<=2000
			//myfile2 << "INVALID"; //file
			return 0;
		}
		else{
			//myfile2 << "START 1ST IF\n";
			/*
			if(mystr.length() == 1){
				substrings.push_back(mystr);
			}
			else{
			*/
				//string str;
				cout << i << endl;
				trie.insert(mystr);
				//substrings.push_back(str);
				trie.print();
				/*
				for(int j = 0; j < mystr.length(); j++){
					//myfile2 << "START 1ST NESTED FOR\n";
					for(int k = j + 1; k <= mystr.length(); k++){
						//myfile2 << "START 2ND NESTED FOR\n";
						str = mystr.substr(j, k);
						substrings.push_back(str);
					}
				}
				*/
				/*
				 * vector<string>* all_possible(const string& original) {

 	 	 	 	 	 	 f vector<string> *result = new vector<string>;
 	 	 	 	 	 ize(it - substrings.begin());
	//cin >> q;	 for (string::iterator iter_outer = original.begin();    iter_outer != original.end(); ++iter_outer)
  	  	  	  	  	  	  for (string::iterator iter_inter = iter_outer; iter_inner != original.end(); ++iter_inter)
  	  	  	  	  	  	  result -> push_back(string(iter_outer, iter_inner));
  	  	  	  	  	  	 return result;
					}
				 */

			//}

		}

	}
	/*
	//myfile2 << "START SORT\n";
	sort(substrings.begin(), substrings.end());

	//myfile2 << "START UNIQUE\n";
	it = unique(substrings.begin(), substrings.end());
	substrings.res
	//myfile1 >> q; //file
	string q_string; //file
	getline (myfile1, q_string); //file
	q = atoi(q_string.c_str()); //file

	myfile2 << "GOT Q: " << q << endl;

	if((q < 1) || (q > 500)){
		//cout << "INVALID";  //1<=q<=500
		myfile2 << "INVALID"; //file
		return 0;
	}
	else{
		//myfile2 << "START 2ND IF\n";
		int myk;
		string mystr;
		string k_string; //file
		for(int i = 0; i < q; i++){
			//myfile2 << "START 3RD FOR\n";
			//cin >> myk;
			//myfile1 >> myk; //file

			getline (myfile1, k_string); //file
			myk = atoi(k_string.c_str()); //file

			if(myk > substrings.size() || ((myk > 1000000000) || (myk < 1))){
				kstrings.push_back("INVALID"); //1<=k<=1000000000
			}
			else{

				kstrings.push_back(substrings[myk - 1]);
			}

		}
		myfile2 << "START PRINT ELEMENTS\n";
		//PRINT_ELEMENTS(kstrings);
		//PRINT_ELEMENTS(kstrings); //file
	}
	*/
	cout<< "START FILE CLOSURE\n";
	myfile1.close();
	//myfile2.close();
	cout << "END\n";
	return 0;
}
