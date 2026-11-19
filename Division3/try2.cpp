#include<bits/stdc++.h>
using namespace std;
int main()
{
    string str;
    string s="";
    getline(cin,str);
    int j;
    for(int i=0;i<str.length();i++)
    {
     if(str[i]>='a'&&str[i]<='z')
      {
        s+=str[i];
      }
    }
    int n[26]={0};
    for(j=0;j<s.length();j++)
    {
        n[s[j]-'a']++;
    }
    int p=0;
    for(int k=0;k<26;k++)
    {
        if(n[k]> 0)
        {p++;}
    }
    cout<<p<<endl;

}