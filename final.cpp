#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <time.h>

// g++ final.cpp 

using namespace std;
int Quiz(int quiz, vector<string> w, vector<string> m);
int main(int argc, char *argv[]) {
	// string filePath = "test1.txt";
	string filePath;
	cout << "Welcome to 'Quiz yourself'" << endl;
	cout << "Please input the file(.txt) name : ";
	cin >> filePath;
 	
	vector<string> word;
	vector<string> mean;

	// read File
	char* token;
	ifstream file(filePath);
	if(file.is_open() ){
		string line;
		while(getline(file, line)){
			istringstream iss(line);
			string token;
			int s = 0;	// s = 0 이면 첫번째 token(word), 1 이면 두번째 token(mean)
			while(getline(iss, token, ',')) {
				token.erase(remove(token.begin(), token.end(), ' '), token.end()); // 공백 제거
				if(s == 0) word.push_back(token);
				else mean.push_back(token);	
				s++;
			}
		}
		file.close();
	}
	else {	// file open error
		cout << "There is no file named '" << filePath << "'\n";
		return 0;
	}
	
	int opt;	// option
	while(true) {
		// menu
		cout << "\n** MENU ** \n";
		cout << "1. QUIZ" << endl;
		cout << "2. List all words" << endl;
		cout << "3. Add a word" << endl;
		cout << "4. Delete a word" << endl;
		cout << "5. Modify a word" << endl;
		cout << "0. Save and quit" << endl;

		cout << "Please input the number of menu > ";
		cin >> opt;

		if(opt == 0) {
			// 모두 txt에 새로 저장하고 끄기 
			ofstream writeFile;
			writeFile.open(filePath);
			if(writeFile.is_open() ){	
				for(int i=0; i<word.size(); i++) {
					writeFile << word.at(i) << "," << mean.at(i) << "\n";
				}
			}
			writeFile.close();
			cout << "\nSave in " << filePath << "\n";
			cout << "Thank you *^^*\n";
			break;
		}
		else if(opt == 1) {	// 1번 quiz 옵션
			int number_of_quiz = 0;
			cout << "\nInput the number of questions  > ";
			cin >> number_of_quiz;
			Quiz(number_of_quiz, word, mean);
		}
		else if(opt == 2) {	// 2번 list 옵션
			cout << "\nThis is the list of words in file\n\n";
			for(int i=0; i<word.size(); i++) {
				cout << "word # " << i+1 << " " << word.at(i) << " - " << mean.at(i) << endl;
			}	
		}
		else if(opt == 3) {	// 3번 add 옵션
			string w_add;	// word add
			string m_add;	
			cout << "Input the word > ";
			cin >> w_add;
			cout << "Input the meaning of the word > ";
			cin >> m_add;

			string add_chose;	 
			cout << "word : " << w_add << " / meaning : " << m_add << " (ADD : 1, CANCEL : anything except 1) > ";
			cin >> add_chose;
			if(add_chose == "1") {	// add
				word.push_back(w_add);
				mean.push_back(m_add);
				cout << " > Add success!" << endl;	// Indicates 'Add' has worked successfully.
			}
			else {	// add cancel
				cout << " > Add cancel.." << endl;
			}
		}
		else if(opt == 4) {	// 4번 delete 옵션
			int del_idx = 0;
			cout << "Input the word index you want to delete > ";
			cin >> del_idx;
			del_idx--;			// because index starts at 0

			string del_chose;
			cout << "word : " << word.at(del_idx) << " / meaning : " << mean.at(del_idx) << " (DELETE : 1, CANCEL : anything except 1) > ";
			cin >> del_chose;
			if(del_chose == "1") {	// delete
				word.erase(word.begin() + del_idx);
				mean.erase(mean.begin() + del_idx);
				cout << " > Delete success!" << endl;	// Indicates 'Delete' has worked successfully.
			}	
			else {	// delete cancel
				cout << " > Delete cancel.." << endl;
			}
		}
		else if(opt == 5) {	// 5번 modify 옵션
			int mod_idx = 0;
			cout << "Input the word index you want to modify > ";
			cin >> mod_idx;
			mod_idx--;			// because index starts at 0

			if(mod_idx > word.size() || mod_idx < 0) {
				cout << "Index out of range\n"; 
				break;
			}
			cout << "word : " << word.at(mod_idx) << " / meaning : " << mean.at(mod_idx) << endl;

			string mod_word, mod_mean;
			cout << "\nInput the new word > ";
			cin >> mod_word;
			cout << "Input the new mean > ";
			cin >> mod_mean;
			
			string mod_chose;
			cout << "word : " << mod_word << " / meaning : " << mod_mean << " (MODIFY : 1, CANCEL : anything except 1) > ";
			cin >> mod_chose;
			if(mod_chose == "1") {	// modify
				word.at(mod_idx) = mod_word;
				mean.at(mod_idx) = mod_mean;
				cout << " > Modify success!" << endl;	// Indicates 'Modify' has worked successfully.
			}	
			else {	// modify cancel
				cout << " > Modify cancel.." << endl;
			}
		}	
	}
	return 0;
}

int Quiz(int quiz, vector<string> w, vector<string> m) {
	int correct = 0;	// 정답 개수
	string answer;
	int len = w.size();
	srand(time(NULL));

	// user choose word(ex English) test or meaning(native language) test.
	int type;
	cout << "choose test type (1: word test, 2: meaning test) > ";
	cin >> type;
	cout << endl;
	// word test
	if (type == 1) {
		for(int i=1; i<=quiz; i++) {	
			int idx = rand()%len;	// make random number (== index of word list)

			cout << "Q" << i << ". Write the word that corresponds to [" << m.at(idx) << "] : ";
			cin >> answer;
			if(answer == w.at(idx)) {	// if the user input correct answer, count the score (Number of times the user answers correctly)
				correct++;
			}
			else {	// show correct answer if the user input incorrect answer!
				cout << "	*Q" << i << " -> wrong !! (right answer : " << w.at(idx) << ")" << endl;
			}
		}
	}
	// meaning test
	else if(type == 2) {
		for(int i=1; i<=quiz; i++) {
			int idx = rand()%len;	// make random number (== index of word list)

			cout << "Q" << i << ". Write the meaning of the [" << w.at(idx) << "] : ";
			cin >> answer;
			if(answer == m.at(idx)) {	// if the user input correct answer, count the score (Number of times the user answers correctly)
				correct++;
			}
			else {	// show correct answer if the user input incorrect answer!
				cout << "	*Q" << i << " -> wrong !! (correct answer : " << m.at(idx) << ")" << endl;
			}
		}
	}
	cout << "\nYour score is " << correct << "/" << quiz << " *^^*";	// show score
	cout << endl;
	return 0;
}