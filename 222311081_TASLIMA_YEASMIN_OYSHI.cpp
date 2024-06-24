#include <bits/stdc++.h>
#include <iostream>
#include <string.h>
using namespace std;

string encrypt(string text, int shift);
string decrypt(string cipher, int shift);

class Tapcode {
public:
    string value;
    string decodedValue;
    string encodedValue;
    bool valueIsSet = false;
    char charList[37];
    int numberList[37];

    Tapcode() {
        int counter = 1;
        int charCounter = 97;

        for (int i = 1; i <= 8; i++) {
            for (int j = 1; j <= 5; j++) {
                numberList[counter] = i * 10 + j;

                if ((charCounter >= 48 && charCounter <= 57) || (charCounter >= 97 && charCounter <= 122)) {
                    charList[counter] = (char)charCounter;
                    counter++;
                    charCounter++;
                }
                if (charCounter > 122) {
                    charCounter = 48;
                }
            }

            charList[0] = ' ';
            numberList[0] = 87;
        }
    }

    void setValue(string value) {
        valueIsSet = true;
        this->value = value;
    }

    string getEncoded() {
        if (!valueIsSet) {
            return "";
        }

        string tempText = value;
        string tempEncodedText = "";

        for (int i = 0; i < tempText.length(); i++) {
            for (int j = 0; j < 37; j++) {
                if (tolower(tempText[i]) == charList[j]) {
                    tempEncodedText += to_string(numberList[j]);
                    numberList[j] = numberList[j];
                }
            }

            encodedValue = tempEncodedText;
        }
        return encodedValue;
    }

    string getDecoded() {
        if (!valueIsSet) {
            return "";
        }

        string tempText = value;
        string tempDecodedText = "";

        for (int i = 0; i < tempText.length(); i += 2) {
            string current = "";
            current += tempText[i];
            current += tempText[i + 1];

            for (int j = 0; j < 37; j++) {
                if (stoi(current) == numberList[j]) {
                    tempDecodedText += charList[j];
                }
            }

            decodedValue = tempDecodedText;
        }

        return decodedValue;
    }
};

int main() {
    cout << "\t\t==============================\n";
    cout << "\t\t|         CIPHER CRAFT        |\n";
    cout << "\t\t==============================\n";
    cout << "\t\t|         MENU OPTIONS:       |\n";
    cout << "\t\t|                             |\n";
    cout << "\t\t|  1. Choose one to encrypt.  |\n";
    cout << "\t\t|  2. Choose two to decrypt.  |\n";
    cout << "\t\t|  3. Alphabets and digits    |\n";
    cout << "\t\t|     only.                   |\n";
    cout << "\t\t==============================\n\n";

    int choice;
    cout << "ENTER YOUR DESIRED CHOICE:\n\n";
    cout << "1. ENCRYPTION.\n";
    cout << "2. DECRYPTION.\n\n";
    cout << "YOU CHOSE:\n\n";
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        string s;
        cout << "\nENTER THE TEXT YOU WANT TO ENCRYPT:\n\n";
        getline(cin, s);
        int len = s.length();
        string cipherText = encrypt(s, len);
        cout << "\nCIPHER TEXT:\n\n" << cipherText << "\n\n";
        Tapcode tCode;
        tCode.setValue(cipherText);
        string encoded = tCode.getEncoded();
        cout << "THE ENCRYPTED TEXT:\n\n" << encoded << "\n\n";
    } else {
        string ciphertext, plaintext;
        cout << "\nENTER THE ENCRYPTED TEXT YOU WANT TO DECRYPT:\n\n";
        getline(cin, ciphertext);
        int shift = ciphertext.length() / 2;
        Tapcode tCode;
        tCode.setValue(ciphertext);
        string numberBack2text = tCode.getDecoded();
        cout << "\nNUMBER BACK TO CIPHER TEXT:\n\n" << numberBack2text << "\n\n";
        plaintext = decrypt(numberBack2text, shift);
        cout << "THE DECRYPTED TEXT:\n\n" << plaintext << "\n\n";
    }

    return 0;
}

string encrypt(string text, int shift) {
    string result = "";

    for (int i = 0; i < text.length(); i++) {
        char c = text[i];

        if (isalpha(c)) {
            c = toupper(c);
            c = (((c - 65) + shift + i) % 26) + 65;
        }

        result += c;
    }

    return result;
}

string decrypt(string cipher, int shift) {
    string result = "";

    for (int i = 0; i < cipher.length(); i++) {
        char c = cipher[i];

        if (isalpha(c)) {
            c = toupper(c);
            c = (((c - 65) - shift + 26 - i) % 26) + 65;
        }

        result += c;
    }

    return result;
}

