using namespace std;
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

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
vector<Word> Dictionary;
int main()
{

	string dictionarynameInput;
	cout << "Hi!! Input the name for the dictionary you want to load." << endl;
	string dictionaryName = "dictionary_2023S1.txt";
	bool loadedDictionary = false;
	while (loadedDictionary == false) {
		cin >> dictionarynameInput;
		if (dictionaryName.compare(dictionarynameInput) == 0) {
			cout << "Loading dictionary....." << endl << endl;
			TextFileReader(dictionarynameInput);
		}
		else {
			cout << "Dictionary not loaded" << endl << "Incorrect Dictionary name!!!" << endl << "Please try again!!!" << endl;

		}
	}
	cout << "Dictionary has been loaded";
	bool endLoop = false;
	int inputOption;
	while (endLoop == false) {
		cout << "Enter '1' to search for a work in the dictionary" << endl;
		cout << "Enter '2' to print all the works from the dictonary that contain more than three 'z' characters" << endl;
		cout << "Enter '3' to add a word to the dictionary" << endl;
		cout << "Enter '4' to Exit program" << endl;

		cin >> inputOption;
		inputCheck(inputOption);

		switch (inputOption) {
		case 1: searchWord();
		case 2:threeZZZFinder();
		case 3: addWord();
		case 4: break;
		}

	}

}
void TextFileReader(string fileName) {
	string wordLine;

	try {
		ifstream readFile(fileName);
		int count = 0;
		if (readFile.is_open()) {
			while (!readFile.eof()) {

				getline(readFile, wordLine);
				size_t startWord = wordLine.find("<word>");
				if (startWord != string::npos) {
					Word input;

					getline(readFile, wordLine);
					input.name = wordLine;
					getline(readFile, wordLine);
					input.type = wordLine;
					getline(readFile, wordLine);
					input.definition = wordLine;


					Dictionary.push_back(input);
					cout << count << endl;
					count++;
				}
			}
			readFile.close();
		}
		else {
			cout << "unable to open file" << endl;
		}

	}
	catch (exception ex) {
		cout << "caught an exception" << endl;
	}

}
void inputCheck(int input) {
	bool correctInput = false;
	while (correctInput == false) {
		if (cin >> input || input < 5 || input >0) {
			correctInput = true;

		}
		else {
			cout << "Please input the correct number corrosponding to the option you want to choose" << endl;
			cin.clear();
			cin.ignore();
		}
	}
}
void searchWord() {

}
void threeZZZFinder() {

}
void addWord() {

}