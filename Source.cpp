#include <iostream>
#include <string>
using namespace std;

string alphabetstr = "ABCDEFGHIKLMNOPQRSTUVWXYZ", keystr = "";
char matrix[5][5];
char* encrypted = new char[600];
char* decrypted = new char[600];

void formatStrings(string& str, int x)
{
	string formatOne = "", formatTwo = "";
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
	for (int i = 0; i < str.length(); i++)
	{
		formatOne += toupper(str[i]);
	}
	if (x == 2)
	{
		for (int i = 0; i < formatOne.length(); i = i + 2)
		{
			if (formatOne[i] == formatOne[i + 1])
			{
				formatOne.insert(i + 1, "X");
			}
		}

		for (int i = 0; i < formatOne.length(); i = i + 2)
		{
			if (alphabetstr.find(formatOne[i]) != string::npos && alphabetstr.find(formatOne[i + 1]) != string::npos)
				formatTwo = formatTwo + formatOne[i] + formatOne[i + 1] + " ";
			else if (alphabetstr.find(formatOne[i]) != string::npos && alphabetstr.find(formatOne[i + 1]) == string::npos)
				formatTwo = formatTwo + formatOne[i];
		}

		if (alphabetstr.find(formatTwo[formatTwo.length() - 2]) == string::npos)
		{
			formatTwo += "X";
		}

		str = formatTwo;
	}
	else if (x == 1) {
		str = formatOne;
	}
}

string newalphabetstr(string key)
{
	formatStrings(key, 1);
	string newstr = key + alphabetstr;
	for (int i = 0; i < newstr.length(); i++)
	{
		char currentChar = newstr[i];
		bool deleted = false;
		while (!deleted)
		{
			int pos = newstr.find(currentChar, i + 1);
			if (pos != -1)
			{
				newstr.erase(pos, 1);
			}
			else if (pos == -1)
			{
				deleted = true;
			}
		}
	}
	return newstr;
}

void createMatrix(string key)
{
	keystr = newalphabetstr(key);
	int k = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			matrix[i][j] = keystr[k];
			k++;
		}
	}
}

void findCharacters(char ch, int& x, int& y)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (matrix[i][j] == ch)
			{
				x = i;
				y = j;
				break;
			}
		}
		if (x >= 0 && y >= 0)
			break;
	}
}

void fillZero()
{
	for (int i = 0; i < 600; i++)
	{
		encrypted[i] = 0;
		decrypted[i] = 0;
	}
}

char* encrypt(string cleartext)
{
	for (int i = 0; i < cleartext.length(); i = i + 3)
	{
		if (cleartext[i] == 'J')
		{
			cleartext[i] = 'I';
		}
		if (cleartext[i + 1] == 'J')
		{
			cleartext[i + 1] = 'I';
		}
		int firstX = -1, firstY = -1, secondX = -1, secondY = -1;
		findCharacters(cleartext[i], firstX, firstY);
		findCharacters(cleartext[i + 1], secondX, secondY);
		if (firstX != secondX && firstY != secondY)
		{
			encrypted[i] = matrix[firstX][secondY];
			encrypted[i + 1] = matrix[secondX][firstY];
		}
		else if (firstX == secondX && firstY != secondY)
		{
			if (firstY == 4)
			{
				encrypted[i] = matrix[firstX][0];
				encrypted[i + 1] = matrix[firstX][secondY + 1];
			}
			else if (secondY == 4)
			{
				encrypted[i + 1] = matrix[firstX][0];
				encrypted[i] = matrix[firstX][firstY + 1];
			}
			else {
				encrypted[i] = matrix[firstX][firstY + 1];
				encrypted[i + 1] = matrix[firstX][secondY + 1];
			}
		}
		else if (firstX != secondX && firstY == secondY)
		{
			if (firstX == 4)
			{
				encrypted[i] = matrix[0][firstY];
				encrypted[i + 1] = matrix[secondX + 1][firstY];
			}
			else if (secondX == 4)
			{
				encrypted[i + 1] = matrix[0][firstY];
				encrypted[i] = matrix[firstX + 1][firstY];
			}
			else {
				encrypted[i] = matrix[firstX + 1][firstY];
				encrypted[i + 1] = matrix[secondX + 1][firstY];
			}
		}
	}
	return encrypted;
}
char* decrypt(string ciphertext)
{
	for (int i = 0; i < ciphertext.length(); i = i + 2)
	{
		int firstX = -1, firstY = -1, secondX = -1, secondY = -1;
		findCharacters(ciphertext[i], firstX, firstY);
		findCharacters(ciphertext[i + 1], secondX, secondY);
		if (firstX != secondX && firstY != secondY)
		{
			decrypted[i] = matrix[firstX][secondY];
			decrypted[i + 1] = matrix[secondX][firstY];
		}
		else if (firstX == secondX && firstY != secondY)
		{
			if (firstY == 0)
			{
				decrypted[i] = matrix[firstX][4];
				decrypted[i + 1] = matrix[firstX][secondY - 1];
			}
			else if (secondY == 0)
			{
				decrypted[i + 1] = matrix[firstX][4];
				decrypted[i] = matrix[firstX][firstY - 1];
			}
			else {
				decrypted[i] = matrix[firstX][firstY - 1];
				decrypted[i + 1] = matrix[firstX][secondY - 1];
			}
		}
		else if (firstX != secondX && firstY == secondY)
		{
			if (firstX == 0)
			{
				decrypted[i] = matrix[4][firstY];
				decrypted[i + 1] = matrix[secondX - 1][firstY];
			}
			else if (secondX == 0)
			{
				decrypted[i + 1] = matrix[4][firstY];
				decrypted[i] = matrix[firstX - 1][firstY];
			}
			else {
				decrypted[i] = matrix[firstX - 1][firstY];
				decrypted[i + 1] = matrix[secondX - 1][firstY];
			}
		}
	}
	return decrypted;
}

int main()
{
	int choice = 0;
	string userchoice, useranswer, key, keycopy, userchoicecopy;

	while (choice != -1)
	{
		cout << "Enter 1 for Encryption, 2 for Decryption and -1 to exit.\n";
		cin >> choice;
		if (choice == -1)
			continue;
		else if (choice < 1 || choice > 2)
		{
			cout << "Invalid operation\n";
			continue;
		}
	again:
		cout << "Enter key and cleartext/ciphertext.\n";
		getline(cin, key);
		getline(cin, userchoice);
		if (key.length() < 7)
		{
			cout << "Key too small.\n";
			goto again;
		}
		keycopy = key;
		for (int i = 0; i < keycopy.length(); i++)
		{
			formatStrings(keycopy, 1);
			char currentChar = toupper(keycopy[i]);
			int pos = alphabetstr.find(currentChar);
			if (pos == -1)
			{
				cout << "Invalid key2, please input a text containing characters a - z and/or A - Z\n";
				goto again;
			}
		}
		userchoicecopy = userchoice;
		for (int i = 0; i < userchoicecopy.length(); i++)
		{
			formatStrings(userchoicecopy, 1);
			char currentChar = userchoicecopy[i];
			int pos = alphabetstr.find(currentChar);
			if (pos == -1)
			{
				cout << "Invalid text, please input a text containing characters a - z and/or A - Z\n";
				goto again;
			}
		}
		createMatrix(key);
		fillZero();
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				cout << matrix[i][j] << " ";
			}
			cout << endl;
		}
		switch (choice)
		{
		case 1:
			formatStrings(userchoice, 2);
			encrypted = encrypt(userchoice);
			cout << "\nCiphertext:\n";
			for (int i = 0; i < userchoice.length(); i++)
			{
				cout << encrypted[i];
			}
			cout << endl;
			break;
		case 2:
			decrypted = decrypt(userchoice);
			cout << "\nCleartext:\n";
			for (int i = 0; i < userchoice.length(); i++)
			{
				cout << decrypted[i];
			}
			cout << endl;
			break;
		}
	}
}