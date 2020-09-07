#include<bits/stdc++.h>

using namespace std;

struct node{
    node * children[54];
    bool isEndOfWord;
	int frequency;
}; 

struct trie{
    node* root;
    int max_string_length;
    trie(){
        root = getNode();
        max_string_length = 0;
    }
    node * getNode(){
        node* new_node=new node();
        for(int i=0;i<54;i++){
            new_node->children[i] = NULL;
        }
        new_node->isEndOfWord = false;
		new_node->frequency = -1;
		return new_node;
    }

    void insert(string key, int freq){
        node * temp = root;
        int index;
        for(int i=0;i<key.length();i++){

            if(key[i] >= 'a' && key[i] <= 'z'){
				index = key[i] - 'a';
			}else if(key[i] >= 'A' && key[i] <= 'Z'){
				index = key[i] - 'A';
				index+=26;
			}else if(key[i] == '\''){
				index = 52;
			}else if(key[i] == '-' ){
				index = 53;
			}
			
            if(temp->children[index] == NULL){
                temp->children[index] = getNode();
            }
            temp = temp->children[index];
        }
        temp->isEndOfWord = true;
		temp->frequency = freq;
        if(max_string_length > key.length()){
            max_string_length = key.length();
        }
    }

    int search(string key){
        node * temp = root;
        int index;
        for(int i=0;i<key.length();i++){
            if(key[i] >= 'a' && key[i] <= 'z'){
				index = key[i] - 'a';
			}else if(key[i] >= 'A' && key[i] <= 'Z'){
				index = key[i] - 'A';
				index+=26;
			}else if(key[i] == '\''){
				index = 52;
			}else if(key[i] == '-' ){
				index = 53;
			}
            if(temp->children[index]==NULL){
                return -1;
            }
            temp = temp->children[index];
        }

		if(temp != NULL && temp->isEndOfWord){
			return temp->frequency;
		}else{
			return -1;
		}
        
    }

};

void searchWord(trie t1) {
	string word;
	cin>>word;
	int ans = t1.search(word); 
	if(ans != -1){
		cout<<"YES, "<< ans<<endl;
	}else{
		cout<<"No"<<endl;
	}
}


int main(int argc, char** argv) 
{ 	
	ifstream csv_file(argv[1]);

	if(!csv_file.is_open()) cout<< "Unable to open file" << endl;
	
	trie t1;

	string word;
	string freq;

	while(csv_file.peek()!=EOF){

		getline(csv_file, word, ',');
		getline(csv_file, freq, '\n');

		t1.insert(word, stoi(freq));
	}
	// int level = 0;
	// char str[t1.max_string_length];
	// t1.display(t1.root,str,level);

	searchWord(t1);


	return 0; 
} 
