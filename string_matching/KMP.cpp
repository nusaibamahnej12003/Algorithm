#include <iostream>
#include <string>
#include <vector>
using namespace std;

void constructLps(string &pat, vector<int> &lps) {

    // len stores the length of longest prefix which
    // is also a suffix for the previous index
    int len = 0;

    // lps[0] is always 0
    lps[0] = 0;

    int i = 1;
    while (i < pat.length()) {

        // If characters match, increment the size of lps
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        }

        // If there is a mismatch
        else {
            if (len != 0) {

                // Update len to the previous lps value
                // to avoid reduntant comparisons
                len = lps[len - 1];
            }
            else {

                // If no matching prefix found, set lps[i] to 0
                lps[i] = 0;
                i++;
            }
        }
    }
}

vector<int> search(string &pat, string &txt) {
    int n = txt.length();
    int m = pat.length();

    vector<int> lps(m);
    vector<int> res;

    constructLps(pat, lps);

    // Pointers i and j, for traversing
    // the text and pattern
    int i = 0;
    int j = 0;

    while (i < n) {

        // If characters match, move both pointers forward
        if (txt[i] == pat[j]) {
            i++;
            j++;

            // If the entire pattern is matched
            // store the start index in result
            if (j == m) {
                res.push_back(i - j);

                // Use LPS of previous index to
                // skip unnecessary comparisons
                j = lps[j - 1];
            }
        }

        // If there is a mismatch
        else {

            // Use lps value of previous index
            // to avoid redundant comparisons
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
    return res;
}

int main() {
    string txt = "aabaacaadaabaaba";
    string pat = "aaba";

    vector<int> res = search(pat, txt);
    for (int i = 0; i < res.size(); i++)
        cout << res[i] << " ";

    return 0;
}


/*
#include <iostream>
#include <vector>
using namespace std;

void constructLps(vector<int> &pat, vector<int> &lps) {
    int len = 0;
    lps[0] = 0;

    int i = 1;
    while (i < pat.size()) {

        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else {
            if (len != 0) {
                len = lps[len - 1];
            }
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

vector<int> search(vector<int> &pat, vector<int> &txt) {
    int n = txt.size();
    int m = pat.size();

    vector<int> lps(m);
    vector<int> res;

    constructLps(pat, lps);

    int i = 0; // text pointer
    int j = 0; // pattern pointer

    while (i < n) {

        if (txt[i] == pat[j]) {
            i++;
            j++;

            if (j == m) {
                res.push_back(i - j);
                j = lps[j - 1];
            }
        }
        else {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }

    return res;
}

int main() {

    // binary text: 11010011
    vector<int> txt = {1,1,0,1,0,0,1,1};

    // pattern: 1101
    vector<int> pat = {1,1,0,1};

    vector<int> res = search(pat, txt);

    for (int i = 0; i < res.size(); i++)
        cout << res[i] << " ";

    return 0;
}*/

//pechano question 
/*

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// কমন ফাংশন: LPS (Longest Prefix Suffix) অ্যারে তৈরি করা
vector<int> computeLPS(string pattern) {
    int m = pattern.length();
    vector<int> lps(m);
    int len = 0;
    lps[0] = 0;
    int i = 1;
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) len = lps[len - 1];
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

// ৪ নম্বর সমস্যা: Overlapping Matches গণনা করা
int countOccurrences(string text, string pattern) {
    int n = text.length();
    int m = pattern.length();
    if (m == 0) return 0;

    vector<int> lps = computeLPS(pattern);
    int i = 0, j = 0, count = 0;

    while (i < n) {
        if (text[i] == pattern[j]) {
            i++; j++;
        }
        if (j == m) {
            count++; // একটি ম্যাচ পাওয়া গেল
            j = lps[j - 1]; // ওভারল্যাপ চেক করার জন্য এটাই মেইন ট্রিক
        } else if (i < n && text[i] != pattern[j]) {
            if (j != 0) j = lps[j - 1];
            else i++;
        }
    }
    return count;
}

// ১ নম্বর সমস্যা: String Rotation চেক করা
bool isRotation(string s1, string s2) {
    if (s1.length() != s2.length()) return false;
    string combined = s1 + s1; // s1 কে ডাবল করলে সব পসিবল রোটেশন পাওয়া যায়
    // এখন combined স্ট্রিং এর ভেতর s2 খুঁজবো
    return countOccurrences(combined, s2) > 0;
}

// ২ নম্বর সমস্যা: ক্ষুদ্রতম পুনরাবৃত্তি একক (Smallest Repeating Period)
string findSmallestPeriod(string s) {
    int n = s.length();
    vector<int> lps = computeLPS(s);
    int L = lps[n - 1];
    int k = n - L; // পিরিয়ড এর সম্ভাব্য দৈর্ঘ্য

    // যদি n কে k দিয়ে ভাগ করা যায়, তবে k দৈর্ঘ্যের সাবস্ট্রিংটিই মূল একক
    if (n % k == 0 && L > 0) {
        return s.substr(0, k);
    }
    return s; // অন্যথায় পুরো স্ট্রিং নিজেই একক
}

int main() {
    // --- ৪ নম্বর সমস্যার টেস্ট ---
    string text = "abababa", pat = "aba";
    cout << "1. Overlapping occurrences of 'aba' in 'abababa': " 
         << countOccurrences(text, pat) << endl; // Output: 3

    // --- ১ নম্বর সমস্যার টেস্ট ---
    string s1 = "table", s2 = "bleta";
    cout << "2. Is 'bleta' a rotation of 'table'? " 
         << (isRotation(s1, s2) ? "Yes" : "No") << endl; // Output: Yes

    // --- ২ নম্বর সমস্যার টেস্ট ---
    string s3 = "abcabcabc";
    cout << "3. Smallest repeating unit of 'abcabcabc': " 
         << findSmallestPeriod(s3) << endl; // Output: abc

    return 0;
}

*/