#include<iostream>
#include<string>
#include<cmath>
using namespace std;

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        string s;
        cin>>s;
        int flag=0;
        int e=stoi(s);
        for(int i=0;i<=sqrt(e);i++)
        {
          for(int j=0;j<=sqrt(e);j++)
          {
             if((i+j)*(i+j)==e)
             {
                cout<<i<<" "<<j<<endl;
                flag=1;
                break;
             }
          }
            if(flag==1)
                {
                    break;
                }
          
        }
        if(flag!=1)
        {
           
             cout<<-1<<endl;
        }
   
}
}