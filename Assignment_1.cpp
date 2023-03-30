using namespace std;
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

struct Word {
	string name;
	string type;
	string definition;
};
void TextFileReader(string file);
void searchWord();
void threeZZZFinder();
void addWord();
void inputCheck(int value);
string capitalRemover(string word);
string typeConverter(string type);
string definitionSeperator(string definition);
vector<Word> Dictionary;
bool loadedDictionary = false;
int main()
{

	string dictionarynameInput;
	cout << "Hi!! Input the name for the dictionary you want to load." << endl;
	string dictionaryName = "dictionary_2023S1.txt";
	
	while (loadedDictionary == false) {
		cin >> dictionarynameInput;
		if (dictionaryName.compare(dictionarynameInput) == 0 || dictionarynameInput.length() >= 4 && dictionarynameInput.substr(dictionarynameInput.length() - 4) == ".txt") {
			cout << "Loading dictionary....." << endl << endl;
			TextFileReader(dictionarynameInput);
			
		}
		else {
			cout << "No Dictionary loaded" << endl << "Please try again!!!" << endl;

		}
	}
	
	bool loopingMenu = true;
	int inputOption;
	while (loopingMenu) {
		cout << "Enter '1' to search for a word in the dictionary" << endl;
		cout << "Enter '2' to print all the words from the dictonary that contains more than three 'z' letters" << endl;
		cout << "Enter '3' to add a word to the dictionary" << endl;
		cout << "Enter '4' to Exit program" << endl;

		cin >> inputOption;
		inputCheck(inputOption);

		switch (inputOption) {
		case 1: 
			searchWord();
			break;
		case 2:
			threeZZZFinder();
			break;
		case 3: 
			addWord();
			break;
		case 4:
			loopingMenu = false;
			break;
		}

	}

}
void TextFileReader(string fileName) {
	
	cout << "Wait few seconds" << endl;
	try {
		string wordLine;
		ifstream readFile;
		int count = 1;
		readFile.open(fileName);
		if (readFile.is_open()) {
			while (!readFile.eof()) {

				getline(readFile, wordLine);
				size_t startWord = wordLine.find("<word>");

				if (startWord != string::npos) {
					Word input;

					getline(readFile, wordLine);
					input.name = wordLine;

					getline(readFile, wordLine);
					input.definition = wordLine;

					getline(readFile, wordLine);
					input.type = wordLine;

					Dictionary.push_back(input);
					cout << count << endl;
					count++;
				}
			}
			readFile.close();
			loadedDictionary = true;
			cout << "Dictionary has been loaded" << endl << endl;
		}
		else {
			cout << "unable to open file" << endl<<"Try Again!"<<endl;
		}

	}
	catch (exception ex) {
		cout << "Something went wrong!!!" <<ex.what()<< endl;
	}

}
void inputCheck(int input) {
	bool correctInput = false;

	while (correctInput == false) {

		if (input < 5 && input >0) {
			correctInput = true;

		}
		else {
			cout << "Please input the correct number corrosponding to the option you want to choose!!!" << endl<<endl;
			cin.clear();
			cin.ignore();
			cin >> input;
		}
	}
}
void searchWord() {
	string searchedWord;

	cout <<endl<<endl<< "What word are your searching for?"<<endl;
	cin >> searchedWord;
	searchedWord = capitalRemover(searchedWord);
	bool  foundWord = false;
	for(auto word : Dictionary) {
		if (word.name.compare(searchedWord) == 0) {
			string type = typeConverter(word.type);
			string definition = definitionSeperator(word.definition);
			cout << endl <<"Search Result: "<<endl<< "Word: " << word.name << endl << "Type: " << type << endl << "Definitions: " <<endl<< definition << endl << endl;
			foundWord = true;
			break;
		}
		
	}
	if (foundWord == false) {
	
		cout << endl << "Word '" << searchedWord << "' cound not be found in the dictionary" << endl << endl;
	
	}

}
void threeZZZFinder() {
	cout << "threeZZZFinder" << endl;
}
void addWord() {
	cout << "addWord" << endl;
}
string capitalRemover(string word) {
	string lowerWord;
	for (char w : word) {
		lowerWord += tolower(w);
	}
	return lowerWord;
}
string typeConverter(string type) {
	if (type == "n") {
		type = "[name]";
	}
	else if(type == "v") {
		type = "[verb]";
	}
	else if (type == "adv") {
		type = "[adverb]";
	}
	else if (type == "adj") {
		type = "[adjective]";
	}
	else if (type == "prep") {
		type = "[preposition]";
	}
	else if (type == "misc") {
		type = "[miscellaneous]";
	}
	else if (type == "pn") {
		type = "[proper noun]";
	}
	else {
		type = "[noun and verb]";
	}
	return type;
}
string definitionSeperator(string definition) {
	istringstream iss(definition);
	string meanings;
	string newDefinition;
	while (getline(iss, meanings, ';')) {		
			newDefinition += "- " + meanings + "\n";
	}
	return newDefinition;

}