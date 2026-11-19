#include <iostream>
#include <fstream>
#include <unordered_map>
using namespace std;

int main(){
    unordered_map<char,string> m;
       ifstream c("codes.txt");
    int x; string s;
       while(c>>x>>s) m[(char)x]=s;
    c.close();

    ifstream i("input.txt");
       string t((istreambuf_iterator<char>(i)),istreambuf_iterator<char>());
    i.close();

    string e="";
      for(char ch:t) e+=m[ch];
      ofstream o("compressed.txt");
    o<<e;
    o.close();

    cout<<"Done\n";
}
