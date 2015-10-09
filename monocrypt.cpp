#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>
using namespace std;
#include "Monocrypt.h"

MonoCrypt::MonoCrypt() {
	char temporary[] = {'A', 'B', 'C', 'D','E', 'F', 'G', 'H','I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
	for (int i = 0; i < 26; i++) {
		alphabet[i] = temporary[i];
	}
}

void MonoCrypt::selectCrypt() {
	option = -1;
	while (option < 0) {
		cout << "Will you be 1) encrypting or 2) decrypting today? (Please pick a number)" << endl;
		cin >> option;
		if (cin.fail()) {
			cout << "Error" << endl;
 		}
	}
	if (option == 1 || option == 2){
		MonoCrypt();		// is it okay to call of these in the functions instead of the main?
		inputKeys();
		inputMessage();
		vigenereSquare(); 
		//printSquare(); //prints out what the vigenere cipher looks like
		cryptMessage();
	}
}

void MonoCrypt::inputKeys() {
	keyNumber = -1;
	while (keyNumber < 0) {
		if (option == 1) {
			cout << "Please input a number that is 0 or greater. This will determine how many letters the first alphabet will be shifted to the left." << endl;
			cin >> keyNumber;
		}
		else {
			cout << "Please input the key number." << endl;
			cin >> keyNumber;
		}
		if (cin.fail()) {
			cout << "Error" << endl;
 		}
	}
	keyNumber = (keyNumber) % 26;
	keyNumberRotate = keyNumber;
	
	if (option ==1) {
		cout << "Please input a phrase less than 26 letters. " <<
			 "This will determine which alphabets to use to encrypt the message." << endl;
	}
	else if (option == 2) {
		cout << "Please input the key phrase." << endl;
	}
	
	cin >> keyPhrase;
	int keylength = keyPhrase.length();
	
	for (int i=0; i < keylength; i++) {
		keyPhraseChar.push_back(keyPhrase[i]);
	}
	/*
	// This function prints and makes sure 
	// the keyPhrase is converted into a character list.
	for (int i=0; i < keylength; i++) {
		cout << keyPhraseChar[i] << endl;
	}
	*/
	
	for (int i = 0; i < keylength; i++) {
		letterConvert(keyPhraseChar[i]);
		keyPhraseCharConvert.push_back(convertText[i]);
	}
	convertText.clear();
}

void MonoCrypt::inputMessage() {
	ifstream inCryptFile("crypt.txt"); //make this 1 argument instead NO NAME
	
	if(!inCryptFile)
		cout << "Something shitty just happened" << endl;
	
	while (inCryptFile >> noskipws >> ch) {
		message.push_back(ch);
	}
	inCryptFile.close();
}

void MonoCrypt::vigenereSquare(){
	for(int j = 0; j < 26; j++) {
		for (int i = 0; i < 26; i++) {
			vigSquare[j][i] = alphabet[keyNumberRotate];
			keyNumberRotate = (keyNumberRotate + 1) % 26;
		}
		keyNumber = (keyNumber+1) % 26;
		keyNumberRotate = keyNumber;
	}
}

void MonoCrypt::printSquare() {
	for (int j = 0; j < 26; j++) {
		for (int i = 0; i < 26; i++) {
			cout << vigSquare[j][i] << " ";
		}
		cout << endl;
	}
}

void MonoCrypt::cryptMessage() {
	if (option == 1) 
		cout << "Encrypted Message: ";
	else
		cout << "Decrypted Message: ";
	int messageSize;
	int messageLetterPlace; 
	int keyPhraseLetterPlace;
	messageSize = message.size();
	ofstream outCryptFile ("crypt.txt");
	for (int i = 0; i < messageSize; i++ ) {
		letterConvert(message[i]);
	}
	/*
	// prints out the tidied up text
	for (int i = 0; i < x; i++ ) {
		cout << convertText[i] << " ";
	} 
	*/
	int convertTextSize = convertText.size();
	for (int i = 0; i < convertTextSize; i++ ) {
		messageConvert.push_back(convertText[i]);
	}
	
	int place = 0;
	for (int i = 0; i < messageConvert.size(); i++ ) {
		for (int h = 0; h < 26; h++ ) {
			if (vigSquare[h][0] == keyPhraseCharConvert[place])
				keyPhraseLetterPlace = h;
		}
		place = (place +1) % keyPhraseCharConvert.size();
		for (int j = 0; j < 26; j++) {
			if (option == 1) {
				if (alphabet[j]==messageConvert[i]) 
					messageLetterPlace = j;
			}
			else {
				if (vigSquare[keyPhraseLetterPlace][j]==messageConvert[i])
					messageLetterPlace = j;
			}
		}
		
		if (option == 1) {
			cout << vigSquare[messageLetterPlace][keyPhraseLetterPlace] << " "; //output a file & phrase?
			outCryptFile << vigSquare[messageLetterPlace][keyPhraseLetterPlace] << " ";
		} 
		else {
			cout << alphabet[messageLetterPlace] << " ";
			outCryptFile << alphabet[messageLetterPlace] << " ";
		}
	}
	cout << endl;
	outCryptFile.close();
}

void  MonoCrypt::letterConvert(char letter) {
	switch (letter) {
	  case 'A':
	  case 'a':
	    convertText.push_back('A');
	    break;
  	  case 'B':
	  case 'b':
  	    convertText.push_back('B');
  	    break;
  	  case 'C':
	  case 'c':
  	    convertText.push_back('C');
  	    break;
  	  case 'D':
	  case 'd':
  	    convertText.push_back('D');
  	    break;
  	  case 'E':
	  case 'e': 
  	    convertText.push_back('E');
  	    break;
  	  case 'F':
	  case 'f':
  	    convertText.push_back('F');
  	    break;
  	  case 'G':
	  case 'g':
  	    convertText.push_back('G');
  	    break;
  	  case 'H':
	  case 'h':
  	    convertText.push_back('H');
  	    break;
  	  case 'I':
	  case 'i':
  	    convertText.push_back('I');
  	    break;
  	  case 'J':
	  case 'j':
  	    convertText.push_back('J');
  	    break;
  	  case 'K':
	  case 'k':
  	    convertText.push_back('K');
  	    break;
  	  case 'L':
	  case 'l':
  	    convertText.push_back('L');
  	    break;
  	  case 'M':
	  case 'm':
  	    convertText.push_back('M');
  	    break;
  	  case 'N':
	  case 'n':
  	    convertText.push_back('N');
  	    break;
  	  case 'O':
	  case 'o':
  	    convertText.push_back('O');
  	    break;
  	  case 'P':
	  case 'p':
  	    convertText.push_back('P');
  	    break;
  	  case 'Q':
	  case 'q':
  	    convertText.push_back('Q');
  	    break;
  	  case 'R':
	  case 'r':
  	    convertText.push_back('R');
  	    break;
  	  case 'S':
	  case 's':
  	    convertText.push_back('S');
  	    break;
  	  case 'T':
	  case 't':
  	    convertText.push_back('T');
  	    break;
  	  case 'U':
	  case 'u':
  	    convertText.push_back('U');
  	    break;
  	  case 'V':
	  case 'v':
  	    convertText.push_back('V');
  	    break;
  	  case 'W':
	  case 'w':
  	    convertText.push_back('W');
  	    break;
  	  case 'X':
	  case 'x': 
  	    convertText.push_back('X');
  	    break;
  	  case 'Y':
	  case 'y':
  	    convertText.push_back('Y');
  	    break;
  	  case 'Z':
	  case 'z':
  	    convertText.push_back('Z');
  	    break;
	  }
}