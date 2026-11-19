#include<iostream>
#include <string>
using namespace std;
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        string s;
        cin>>s;
         char q=s[1];
         int p = q-'0';
         for(char c='a';c<='h';++c)
        {
            if(s[0]==c)continue;
            else cout<<c<<s[1]<<endl;
            
        }
        for(int i=1;i<=8;++i)
        {
           
            if(p==i){continue;}
             cout<<s[0]<<i<<endl;
        }
       
    }
}