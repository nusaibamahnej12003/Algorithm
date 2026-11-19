#include<iostream>
#include<string>
using namespace std;
int main()
{
     string s;
     cin>>s;
     int len=s.length();
     int p=0;
     for(char i='a';i<='z';i++)
     {

        for(int j=0;j<=len-1;j++)
         {
           size_t pos=s.find(i,j);
           if(pos== string::npos)
          {
            p++;
          }
        }
        if(p==len)
        {
            cout<<i;
            break;
        }
        p=0;
    }

}