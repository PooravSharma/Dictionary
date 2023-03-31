using namespace std;
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
// All the variables created are named accordingly. The names clearly tell use they purpose and use 

//Created a 'Word' struct to hold each word, with fields : name(string) The word in the dictionary, type(string), definition(string)

struct Word {
	string name;
	string type;
	string definition;
};
// I like having my functions below the main. It is what i am used to from java and c# programming. I find it easier and it makes me double check the function i make when i declare it at the top.
#pragma region Declared Methods


void TextFileReader(string file);
void searchWord();
void threeZZZFinder();
void addWord();
int inputCheck(int value);
string capitalRemover(string word);
string typeConverter(string type);
string definitionSeperator(string definition);
void TextFileWriter(string newFileName);

#pragma endregion
// Vector of Words called Dictionary.
//used to keep track of new words added to the dictionary 
int wordCount;
vector<Word> Dictionary;
static bool loadedDictionary = false;
int main()
{
	//Task 01 Load and Parse a dictionary file.First ask the user to either enter the file name or use the ‘default’ file, that being dictionary_2023S1.txt, provided with this assignment(See Appendix at the end of this document for file layout).Your program will load the information for each word(name, type and definition) from the file into a new instance of a Word struct (details of this struct provided after description of tasks) and add this instance to a STL vector of Words called Dictionary.

	string dictionarynameInput;
	cout << "Hi!! Input the name for the dictionary you want to load." << endl;
	string dictionaryName = "dictionary_2023S1.txt";

	while (loadedDictionary == false) {
		cin >> dictionarynameInput;
		if (dictionaryName.compare(dictionarynameInput) == 0 || dictionarynameInput.length() >= 4 && dictionarynameInput.substr(dictionarynameInput.length() - 4) == ".txt") {
			cout << "Loading dictionary....." << endl << endl;
			TextFileReader(dictionarynameInput);

		}
		// If no dictionary is loaded the task should just print ‘No dictionary loaded’ and return to the menu
		else {
			cout << "No Dictionary loaded" << endl << "Please try again!!!" << endl;

		}
	}

	bool loopingMenu = true;
	int inputOption;
	while (loopingMenu) {
		cout << endl << "Enter '1' to search for a word in the dictionary" << endl;
		cout << "Enter '2' to print all the words from the dictonary that contains more than three 'z' letters" << endl;
		cout << "Enter '3' to add a word to the dictionary and save updated dictionary" << endl;
		cout << "Enter '4' to Exit program" << endl;


		cin >> inputOption;
		inputOption = inputCheck(inputOption);

		switch (inputOption) {
		case 1:
			//Task 02 method
			searchWord();
			break;
		case 2:
			//Task 03 methon 
			moreZZZFinder();
			break;
		case 3:
			//Task 04 method
			addWord();
			break;
		case 4:
			//to exit the menu loop and end he program
			loopingMenu = false;
			break;
		}

	}

}
// I made a region for the mentods created so that the who code looks more tidy 
#pragma region Methods
// file reader function used to read the dictionary from the text file into the dictionary vector where contants word struct with name, type and definition.

void TextFileReader(string fileName) {

	cout << "Wait few seconds" << endl;
	//used try and catch to prevent system error from stopping the program
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
					//had to switch the order of the definiton and type element because the definition is printed above the type. 
					getline(readFile, wordLine);
					input.definition = wordLine;

					getline(readFile, wordLine);
					input.type = wordLine;

					Dictionary.push_back(input);
					cout << count << endl;
					count++;
				}
			}
			//closed the file after use and changes the booles loaded dictionary to true so that the program can continue to the menu 
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
// madee this option input checker to check user input. it will repeatedly ask the user for input until they input the correct options
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

// Task 02 Prompt the user to enter a word.If that exact word is in the dictionary, print the word’s name, followed on the line directly below by the word type using the scheme in Table 1, and on the line below the type print the word’s definition. 
void searchWord() {
	string searchedWord;

	cout << endl << endl << "What word are your searching for?" << endl;
	cin >> searchedWord;
	// I made a function that lowers all the string letters so that there is no problem due to capital letter when comparing words
	searchedWord = capitalRemover(searchedWord);
	bool  foundWord = false;
	// uded for loop to go through the vector and try and find the word the user wants.
	for (auto word : Dictionary) {
		if (word.name.compare(searchedWord) == 0) {
			// i used two function I created to make sure the displayed type is shown as per the requirement of the second task, 
			string type = typeConverter(word.type);
			// i aslo desided to seperate the definitions becasue if there were multiple for one word. 
			string definition = definitionSeperator(word.definition);
			cout << endl << "Search Result: " << endl << "Word: " << word.name << endl << "Type: " << type << endl << "Definitions: " << endl << definition << endl << endl;
			foundWord = true;
			break;
		}

	}
	//If the word is not in the dictionary print ‘word not found.’
	if (foundWord == false) {

		cout << endl << "Word '" << searchedWord << "' cound not be found in the dictionary" << endl << endl;

	}

}
//Task 03 Find(and print to the screen) all words that contain more than three ‘z’ characters in them.

void moreZZZFinder() {

	cout << endl << "Finding words that has more than three 'z'...;" << endl;
	// again used the for loop to got throught all the word name and count the number of z it has. I then used a if statement which states that any word with more than three counts of z letter need to be printed 
	// I wamted to used the same function but the function is a return type and it only allows parameter loaded
	for (auto word : Dictionary) {
		int zCounter = 0;
		zCounter = count(word.name.begin(), word.name.end(), 'z');
		if (zCounter > 3) {
			cout << endl << word.name << endl;
		}
	}
}

// Task 04 Add a word to the dictionary. Allow the user to enter the name, type and definition of a word. If the word is already in the dictionary, the program should print ‘error: word exists, elevated privileges required to edit existing words’. If the word is not in the dictionary, and providing a valid ‘type’ is entered – create a corresponding Word struct instance and add it to the Dictionary STL vector.
void addWord() {
	// I create new Variable where i can store the users new word. Before continueing on I used a for loop and the comapre method to check if there is already a same word in the dictionary. if there is one then then I inform them and take them back to the menu.
	Word newWord;
	int typeOptionInput;
	cout << endl << "What is the name of the word you want to add to the dictionary?" << endl;
	cin >> newWord.name;
	//used the capital remover fucntion to lower the letter so that even if the user used capital letter i doesn't affect the comparing process
	newWord.name = capitalRemover(newWord.name);
	for (auto word : Dictionary) {
		if (word.name.compare(newWord.name) == 0) {
			cout << "That word already exists in the dictionary!!!" << endl;
			return;
		}
	}
	// I make a multiple choice option using a switch case to insure that i can store the type of the word similar to how the orginal dictionary format
	cout << endl << "What type of word is it?" << endl;
	cout << "Enter '1' for Noun" << endl << "Enter '2' for Verb" << endl << "Enter '3' for Adverb" << endl << "Enter '4' for Adjective" << endl;
	cout << "Enter '5' for Preposition" << endl << "Enter '6' for Miscellaneous" << endl << "Enter '7' for Proper Noun" << endl << "Enter '8' for Noun and Verb" << endl;

	bool correctInput = false;
	// used the same function as input checker but the only difference is that the upper limit is extented to 8 because there is more options of word type to choose from.
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
	// I when throughth the dictionary and could not find what noun and verb type are written i decided to just make one up. this will not affect the output later on because is used the else statemnt to show case any noun and verb type letters  
	case 8:
		newWord.type = "nandv";
		break;

	}
	// askes for definiton of the word. the used can add multiple one as long as they seperate them using a semicolon(';')
	bool definitionRecieved = false;
	cout << "What is the definition of the word?" << endl;
	getline(cin, newWord.definition);
	while (definitionRecieved == false) {
		getline(cin, newWord.definition);
		if (cin.fail() || newWord.definition.empty()) {
			cin.clear();
			cin.ignore();
			cout << "Input definition again" << endl;
			continue;
		}
		break;
	}
	// new word added to the vector
	Dictionary.push_back(newWord);

	string newDictionaryFileName;
	bool correctnewName = false;

	//Following the successful addition of the word, save the Dictionary to a new file(file name specified by the user), in the same format as the original dictionary file(so that it can be read using Task 01).
	cout << endl << "Which file do you want to save the updated Dictionary to?" << endl;
	// used this method to ensure the user names the new file correctily using the correct format at the end
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
//function used to remove capital letters from words
string capitalRemover(string word) {
	string lowerWord;
	for (char w : word) {
		lowerWord += tolower(w);
	}
	return lowerWord;
}
// converts the dictionary format of word type to the ones the second task is asking for. 
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

//I used this function to seperate different definition and cleanly display it
string definitionSeperator(string definition) {
	istringstream iss(definition);
	string meanings;
	string newDefinition;
	while (getline(iss, meanings, ';')) {
		newDefinition += "- " + meanings + "\n";
	}
	return newDefinition;

}

// this function is used to create a new txt file that contains the updated dictionary. 
void TextFileWriter(string newFileName) {

	cout << "Wait few seconds..." << endl << "Saving dictionary..." << endl;
	try {
		string wordLine;
		ofstream writeFile;
		int count = wordCount + 1;
		writeFile.open(newFileName);
		if (writeFile.is_open()) {
			// The orginal dictionary text file had this sentence at the beginning along with the number of words it contains. i augusted the word count accordingly and write the sentance into the txt file
			// Attention to detail is key 
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
#pragma endregion