#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// Node of Huffman Tree
struct Node {
    char ch;
    int freq;
    Node *left, *right;

    Node(char c, int f) {
        ch = c;
        freq = f;
        left = right = NULL;
    }
};

// Comparator for Min Heap
struct compare {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq; // Min heap
    }
};

// Print Huffman Codes
void printCodes(Node* root, string code) {
    if (!root) return;

    // Leaf node → contains character
    if (!root->left && !root->right) {
        cout << root->ch << " : " << code << endl;
    }

    printCodes(root->left, code + "0");
    printCodes(root->right, code + "1");
}

int main() {
    vector<char> chars = {'a','b','c','d','e','f'};
    vector<int> freq  = {5, 9, 12, 13, 16, 45};

    priority_queue<Node*, vector<Node*>, compare> pq;

    // Step 1: Create leaf nodes
    for (int i = 0; i < chars.size(); i++) {
        pq.push(new Node(chars[i], freq[i]));
    }

    // Step 2: Build Huffman Tree
    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* newNode = new Node('$', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;

        pq.push(newNode);
    }

    Node* root = pq.top();

    // Step 3: Print codes
    cout << "Huffman Codes:\n";
    printCodes(root, "");

    return 0;
}
