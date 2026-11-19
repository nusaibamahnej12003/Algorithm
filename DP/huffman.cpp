#include <iostream>
#include <string>
#include <queue>
#include <map>

using namespace std;

// হাফম্যান ট্রির নোড স্ট্রাকচার
struct Node {
    char ch;
    int freq;
    Node *left, *right;

    Node(char c, int f) {
        ch = c;
        freq = f;
        left = right = nullptr;
    }
};

// মিন-হিপের জন্য কম্পারেটর
struct compare {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};

// --- মেইন ডিকোডিং ফাংশন ---
string decodeString(Node* root, string encodedStr) {
    string decodedResult = "";
    Node* current = root;

    for (int i = 0; i < encodedStr.length(); i++) {
        // যদি বিট ০ হয় বামে যাও, ১ হলে ডানে যাও
        if (encodedStr[i] == '0')
            current = current->left;
        else
            current = current->right;

        // লিফ নোডে পৌঁছালে (যে নোডের ডানে বামে কেউ নেই)
        if (!current->left && !current->right) {
            decodedResult += current->ch;
            current = root; // আবার রুট থেকে শুরু করো
        }
    }
    return decodedResult;
}

void buildTreeAndDecode(string text, string binaryToDecode) {
    // ১. ফ্রিকোয়েন্সি বের করা (ট্রি বানানোর জন্য এটি দরকার)
    map<char, int> freq;
    for (char c : text) freq[c]++;

    // ২. মিন-হিপে নোডগুলো পুশ করা
    priority_queue<Node*, vector<Node*>, compare> pq;
    for (auto pair : freq) {
        pq.push(new Node(pair.first, pair.second));
    }

    // ৩. হাফম্যান ট্রি তৈরি করা
    while (pq.size() != 1) {
        Node *left = pq.top(); pq.pop();
        Node *right = pq.top(); pq.pop();
        Node *parent = new Node('$', left->freq + right->freq);
        parent->left = left;
        parent->right = right;
        pq.push(parent);
    }

    Node* root = pq.top();

    // ৪. ডিকোডিং কল করা
    string result = decodeString(root, binaryToDecode);
    
    cout << "Given Binary String: " << binaryToDecode << endl;
    cout << "Decoded Original Text: " << result << endl;
}

int main() {
    // ল্যাব এক্সামে হয়তো তোমাকে একটা স্যাম্পল টেক্সট দিবে ট্রি বানানোর জন্য
    // এবং একটা বাইনারি স্ট্রিং দিবে ডিকোড করার জন্য।
    string sampleText = "abbcccdddd"; 
    string binaryString = "110111111001010100"; // ধরো এটি দেওয়া আছে

    cout << "Building tree from sample text: " << sampleText << endl;
    buildTreeAndDecode(sampleText, binaryString);

    return 0;
}