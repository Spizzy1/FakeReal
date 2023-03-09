// FakeReal.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <bitset>
#include <sstream>
#include <vector>
#include <Windows.h>

using namespace std;

string intToFake(int input) {
    string s = std::to_string(input);
    string resultString = "";
    for (int i = 0; i < s.length(); i++) {
        string binary = std::bitset<8>(((int)(s[i])) - 48).to_string();
        string finalResult = "";
        bool stopRemoving = false;
        for (int j = 0; j < binary.length(); j++) {
            if (binary[j] == '0' && (stopRemoving)) {
                finalResult += "fake";
            }
            else if (binary[j] == '1')
            {
                stopRemoving = true;
                finalResult += "real";
            }
            else if (binary.find('1') == string::npos) {
                finalResult += "fake";
                break;
            }
        }
        resultString += finalResult;
        if (i+1 != s.length()) {
            resultString += ' ';
        }
    }
    return resultString;
}
char intToLetter(int input) {
    return(input + 65) + (7 * (input >= 25));
}
int charToInt(char input) {
    return ((int)input) - 65 - (7 * (input >= 97));
}
int fakeToInt(string input) {
    int currentDigit = 0;
    int totalNumber = 0;
    for (int i = 0; i < input.length(); i++) {
        char currentLtr = tolower(input[i]);
        if (input[i] == ' ') {
            totalNumber *= 10;
            totalNumber += currentDigit;
            currentDigit = 0;
        }
        else {
            if (i + 4 <= input.length()) {
                string check;
                for (int j = 0; j < 4; j++) {
                    check += (char)(tolower(input[i + j]));
                }
                if (check == "real") {
                    currentDigit *= 2;
                    currentDigit += 1;
                    i += 3;
                }
                else if (check == "fake") {
                    currentDigit *= 2;

                    i += 3;
                }
            }
        }
    }
    totalNumber *= 10;
    totalNumber += currentDigit;
    return totalNumber;

}
vector<string> split(string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

string CompileTo(string input) {
    string finalString = "";
    for (int i = 0; i < input.length(); i++) {
        if (input[i] == ' ') {
            finalString += "not";
        }
        else {
            finalString += intToFake(charToInt(input[i]));
        }
        finalString += "yes";
    }
    return finalString;
}
string CompileFrom(string input) {
    string finalString = "";
    vector<string> words = split(input, "not");
    for (int i = 0; i < words.size(); i++) {
        vector<string> letters = split(words[i], "yes");
        for (int j = 0; j < letters.size(); j++) {
            if (letters[j] != "") {
                finalString += intToLetter(fakeToInt(letters[j]));
            }
        }
        if (i + 1 != words.size()) {
            finalString += ' ';
        }
    }
    return finalString;
}
bool again() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 10);
    cout << endl << "again?" << endl;
    string question;
    SetConsoleTextAttribute(hConsole, 15);
    std::getline(std::cin, question);
    if (question == "yes") {
        return true;
    }
    else {
        return false;
    }
}
int main()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    start:
    system("CLS");
    cout << flush;
    SetConsoleTextAttribute(hConsole, 10);
    std::cout << "Welcome to the fakereal compiler\n";
    std::string value;
    std::cout << "Type "; 
    SetConsoleTextAttribute(hConsole, 12);
    cout << "in ";
    SetConsoleTextAttribute(hConsole, 10);
    cout << "or "; 
    SetConsoleTextAttribute(hConsole, 12);
    cout << "out ";
    SetConsoleTextAttribute(hConsole, 10);
    cout << "to compile message into or out of fakereal\n";
    SetConsoleTextAttribute(hConsole, 10);
    std::cout << "command: ";
    SetConsoleTextAttribute(hConsole, 15);
    std::getline(std::cin, value);
    if (value == "in") {
        string encode;
        SetConsoleTextAttribute(hConsole, 10);
        cout << "Input to encode: ";
        SetConsoleTextAttribute(hConsole, 15);
        std::getline(std::cin, encode);
        SetConsoleTextAttribute(hConsole, 10);
        std::cout << endl << "Output: ";
        SetConsoleTextAttribute(hConsole, 15);
        cout << CompileTo(encode) << endl;
        if (again()) { goto start; }
    }
    else if (value == "out") {
        string decode;
        SetConsoleTextAttribute(hConsole, 10);
        cout << "Input to decode: ";
        SetConsoleTextAttribute(hConsole, 15);
        std::getline(std::cin, decode);
        std::cout << endl << "Output: ";
        SetConsoleTextAttribute(hConsole, 15);
        cout << CompileFrom(decode) << endl;
        if (again()) { goto start; }
    }
    else {
        cout << "WRONG COMMAND";
        goto start;
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
