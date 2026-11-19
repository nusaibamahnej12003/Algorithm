#include<bits/stdc++.h>
using namespace std;
int main()
{
int t;
cin>>t;
while(t--)
{
    long long int n,arr[100],t=-1,x=-1,y=-1;
    cin>>n;
    long long  int s,p=0,a,b,c,d;
    a=b=c=d=pow(10,18);
    while(n!=0)
    {
     s = n%10;
     arr[++t]=s;
     n=n/10;
     p++;
    }
   for(int i=0;i<p;i++)
   {
        if(arr[i]==0&&x==-1)
        {
          for(int j=i+1;j<p;j++)
            {
              if(arr[j]==0)
              {a=j-1;
               x=0;
               break;}
          
              if(arr[j]==5)
              {b=j-1;
               x=0;
               break;}
            
            }
        }
       if(arr[i]==5&&y==-1)
        {
          for(int j=i+1;j<p;j++)
           {
            if(arr[j]==2)
             {c=j-1;
             y=0;
             break;}
            if(arr[j]==7)
             {d=j-1;
             y=0;
           break;}
          
          }  
        }
   }
   long long int minimum=min({a,b,c,d});
   cout<<minimum<<endl;
}
}