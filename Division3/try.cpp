#include<bits/stdc++.h>
using namespace std;
int main()
{
    string s;
    string n="";
    cin>>s;
    
    for(int i=0;i<s.length();)
    {
      if(s.substr(i,3)=="WUB")
      {
        if(!n.empty())n+=' ';
        i+=3;
      }
      else
      {
        n+=s[i];
        i++;
      }
    }
    cout<<n<<endl;
}