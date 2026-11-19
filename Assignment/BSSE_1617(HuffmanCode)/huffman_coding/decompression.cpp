#include <iostream>
#include <fstream>
#include <unordered_map>
using namespace std;

int main(){
    unordered_map<string,char> reverseCodeMap;

    ifstream codeFile("codes.txt");
    int asciiValue;
    string code;

    while(codeFile >> asciiValue >> code)
        reverseCodeMap[code] = (char)asciiValue;

    codeFile.close();

    ifstream compressedFile("compressed.txt");
    string encodedText;
    compressedFile >> encodedText;
    compressedFile.close();

    string currentCode = "", decodedText = "";

    for(char bit : encodedText){
        currentCode += bit;
        if(reverseCodeMap.find(currentCode) != reverseCodeMap.end()){
            decodedText += reverseCodeMap[currentCode];
            currentCode = "";
        }
    }

    ofstream outputFile("decompressed.txt");
    outputFile << decodedText;
    outputFile.close();

    cout << "Done\n";
}