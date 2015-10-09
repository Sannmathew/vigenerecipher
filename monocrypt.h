#ifndef MONOCRYPT_H
#define MONOCRYPT_H

#include "Monocrypt.h"
class MonoCrypt {
private: 
	int option;
	int keyNumber;				// get rid of variables that don't need to be private
	int keyNumberRotate;
	string keyPhrase;
	vector<char> keyPhraseChar;
	vector<char> keyPhraseCharConvert;
	vector<char> message;
	char ch;
	vector<char> messageConvert;
	char alphabet[26]; 
	char vigSquare[26][26];
	char letter;
	vector<char> convertText;
public:
	MonoCrypt();
	void selectCrypt();
	void inputKeys();
	void inputMessage();
	void vigenereSquare();
	void printSquare();
	void letterConvert(char);
	void cryptMessage();
};

#endif