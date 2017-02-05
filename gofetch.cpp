#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <list>

using namespace std;

const int BUFF = 50; //bytes

int main(int argc, char* argv[]){
	//open file, fetch a string
	//segment it into words
	//store only the unique ones
	//keep going until eof
	//tada, a set of unique words

	if(argc != 2){
		cout << "Error! 1" << endl;
		exit(-1);
	}

	//open file named in argument
	ifstream inf(argv[1]);
	if(!inf){
		cout << "Error! 2" << endl;
		exit(-2);
	}

	//put the words into a linked list
	list<string> index;
	while(inf){//inf has something

		string item;
		inf >> item; //gets a word (delimited by whitespace)
		index.push_back(item);
//		cout << item << endl;
	}

	index.sort();
	index.unique();

	//print the words
	list<string>::const_iterator it = index.begin();
	list<string>::const_iterator end = index.end();
	for( ;it != end; it++)
		cout << *it << endl;
}
