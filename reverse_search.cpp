#include<bits/stdc++.h>

using namespace std;

struct node{
    node * children[54];
    bool isEndOfWord;
	int num;
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
		new_node->num = -1;
		return new_node;
    }

    void insert(string key, int num){
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
		temp->num = num;
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
			return temp->num;
		}else{
			return -1;
		}
        
    }

    void reverseSearch(node* current_node,char str[],int level, int num){
        if(current_node->isEndOfWord && current_node->num == num ){
            str[level] = '\0';
            cout<<str<<endl;
        }
        for(int i=0;i<54;i++){
            if(current_node->children[i]){
				if(i>=0 && i<=25){
                	str[level] = i + 'a';
				}else if(i>=26 && i<=51){
					str[level] = (i-26) + 'A';
				}else if(i == 52){
					str[level] = '\'';
				}else{
					str[level] = '-';
				}
                reverseSearch(current_node->children[i], str, level+1, num);
            }
        }
    }

    void display(node* current_node,char str[],int level){
        if(current_node->isEndOfWord){
            str[level] = '\0';
            cout<<str<<" - "<< current_node->num <<endl;
        }
        for(int i=0;i<26;i++){
            if(current_node->children[i]){
                str[level] = i + 'a';
                display(current_node->children[i],str,level+1);
            }
        }
    }

};

int main(int argc, char** argv) 
{ 
	
	ifstream csv_file(argv[1]);

	if(!csv_file.is_open()) cout<< "Unable to open file" << endl;
	
	trie t1;

	string word;
	string freq;
    int num = 0;
	while(csv_file.peek()!=EOF){

		getline(csv_file, word, ',');
		getline(csv_file, freq, '\n');

		t1.insert(word, num);

        num++;
	}
    int searchFor;
    cin>>searchFor;
    char str[t1.max_string_length];
    t1.reverseSearch(t1.root, str, 0, searchFor);

	return 0; 
} 
