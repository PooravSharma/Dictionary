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

int wordCount;
void TextFileReader(string file);
void searchWord();
void threeZZZFinder();
void addWord();
int inputCheck(int value);
string capitalRemover(string word);
string typeConverter(string type);
string definitionSeperator(string definition);
void TextFileWriter(string newFileName);
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
		cout << endl << "Enter '1' to search for a word in the dictionary" << endl;
		cout << "Enter '2' to print all the words from the dictonary that contains more than three 'z' letters" << endl;
		cout << "Enter '3' to add a word to the dictionary" << endl;
		cout << "Enter '4' to Exit program" << endl;

		
		cin>>inputOption;
		inputOption = inputCheck(inputOption);
		
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
			wordCount = count;
		}
		else {
			cout << "unable to open file" << endl << "Try Again!" << endl;
		}

	}
	catch (exception ex) {
		cout << "Something went wrong!!!" << ex.what() << endl;
	}

}

int inputCheck(int input) {
	bool correctInput = false;
	
	while (correctInput == false) {
			
		if (input < 5 && input >0) {
			correctInput = true;
			break;
		}			
		else {
			cin.clear();
			cin.ignore();
			cout << "Please input the correct number corrosponding to the option you want to choose!!!" << endl << endl;
			
			
		}
		cin >> input;
	}
	
	return input;
}
void searchWord() {
	string searchedWord;

	cout << endl << endl << "What word are your searching for?" << endl;
	cin >> searchedWord;
	searchedWord = capitalRemover(searchedWord);
	bool  foundWord = false;
	for (auto word : Dictionary) {
		if (word.name.compare(searchedWord) == 0) {
			string type = typeConverter(word.type);
			string definition = definitionSeperator(word.definition);
			cout << endl << "Search Result: " << endl << "Word: " << word.name << endl << "Type: " << type << endl << "Definitions: " << endl << definition << endl << endl;
			foundWord = true;
			break;
		}

	}
	if (foundWord == false) {

		cout << endl << "Word '" << searchedWord << "' cound not be found in the dictionary" << endl << endl;

	}

}
void threeZZZFinder() {
	cout << endl << "Finding words that has more than three 'z'...;" << endl;

	for (auto word : Dictionary) {
		int zCounter = 0;
		zCounter = count(word.name.begin(), word.name.end(), 'z');
		if (zCounter > 3) {
			cout << endl << word.name << endl;
		}
	}
}
void addWord() {

	Word newWord;
	int typeOptionInput;
	cout << endl << "What is the name of the word you want to add to the dictionary?" << endl;
	cin >> newWord.name;
	newWord.name = capitalRemover(newWord.name);
	for (auto word : Dictionary) {
		if (word.name.compare(newWord.name) == 0) {
			cout << "That word already exists in the dictionary!!!" << endl;
			return;
		}
	}

	cout << endl << "What type of word is it?" << endl;
	cout << "Enter '1' for Noun" << endl << "Enter '2' for Verb" << endl << "Enter '3' for Adverb" << endl << "Enter '4' for Adjective" << endl;
	cout << "Enter '5' for Preposition" << endl << "Enter '6' for Miscellaneous" << endl << "Enter '7' for Proper Noun" << endl << "Enter '8' for Noun and Verb" << endl;
	
	bool correctInput = false;

	while (correctInput == false) {
		cin >> typeOptionInput;
		if (typeOptionInput < 9 && typeOptionInput >0) {
			correctInput = true;

		}
		else {
			cin.clear();
			cin.ignore();
			cout << "Please input the correct number corrosponding to the option you want to choose!!!" << endl << endl;


		}

	}
	switch (typeOptionInput) {
	case 1:
		newWord.type = "n";
		break;
	case 2:
		newWord.type = "v";
		break;
	case 3:
		newWord.type = "adv";
		break;
	case 4:
		newWord.type = "adj";
		break;
	case 5:
		newWord.type = "prep";
		break;
	case 6:
		newWord.type = "misc";
		break;
	case 7:
		newWord.type = "pn";
		break;
	case 8:
		newWord.type = "nandv";
		break;

	}

	bool definitionRecieved = false;
	cout <<"What is the definition of the word?" << endl;
	getline(cin, newWord.definition);
	while (definitionRecieved == false) {
		getline(cin, newWord.definition);
		if (cin.fail()||newWord.definition.empty()) {
			cin.clear();
			cin.ignore();
			cout << "Input definition again"<<endl;
			continue;
		}
		break;
	}
	Dictionary.push_back(newWord);

	string newDictionaryFileName;
	bool correctnewName = false;

	cout << endl << "Which file do you want to save the updated Dictionary to?" << endl;

	while (correctnewName == false) {


		cin >> newDictionaryFileName;
		if (newDictionaryFileName.length() >= 4 && newDictionaryFileName.substr(newDictionaryFileName.length() - 4) == ".txt") {
			correctnewName = true;
			TextFileWriter(newDictionaryFileName);
		}
		else {
			cout << endl << "Please provide a valid file name to save the updated Dictionary into." << endl << endl;
		}
	}
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
		type = "[noun]";
	}
	else if (type == "v") {
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
void TextFileWriter(string newFileName) {

	cout << "Wait few seconds..." << endl << "Saving dictionary..." << endl;
	try {
		string wordLine;
		ofstream writeFile;
		int count = wordCount + 1;
		writeFile.open(newFileName);
		if (writeFile.is_open()) {
			writeFile << "2023 - S1 dictionary contains " << count << " words" << endl << endl;
			for (auto word : Dictionary) {
				writeFile << "<word>" << endl;

				writeFile << word.name << endl;
				writeFile << word.definition << endl;
				writeFile << word.type << endl;

				writeFile << "</word>" << endl;
			}

			writeFile.close();
			cout << "Dictionary has been saved" << endl << endl;
		}
		else {
			cout << "unable to open file" << endl << "Try Again!" << endl;
		}

	}
	catch (exception ex) {
		cout << "Something went wrong!!!" << ex.what() << endl;
	}
}