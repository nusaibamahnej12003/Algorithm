#include <iostream>
#include <fstream>
#include <unordered_map>
using namespace std;

int main(){
     unordered_map<string,char> m;
      ifstream c("codes.txt");
          int x; string s;
        while(c>>x>>s) m[s]=(char)x;
    c.close();

      ifstream i("compressed.txt");
      string e;
         i>>e;
    i.close();

    string cur="",d="";
      for(char b:e){
          cur+=b;
            if(m.count(cur)){
             d+=m[cur];
             cur="";
        }
    }

     ofstream o("decompressed.txt");
        o<<d;
      o.close();

    cout<<"Done\n";
}
