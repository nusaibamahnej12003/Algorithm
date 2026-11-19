#include <iostream>
#include <fstream>
#include <unordered_map>
using namespace std;

int main(){
    unordered_map<char,string> codeMap;

    ifstream codeFile("codes.txt");
    int asciiValue;
    string code;

    while(codeFile >> asciiValue >> code)
        codeMap[(char)asciiValue] = code;

    codeFile.close();

    ifstream inputFile("input.txt");
    string text((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
    inputFile.close();

    string encodedText = "";

    for(char ch : text)
        encodedText += codeMap[ch];

    ofstream compressedFile("compressed.txt");
    compressedFile << encodedText;
    compressedFile.close();

    cout << "Done\n";
}