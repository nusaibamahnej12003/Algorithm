#include<bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n,a,b;
        cin>>n>>a>>b;
        if(a==0 && b==0)
        {
             cout<<"YES"<<endl;
            for(int i=1;i<=n;i++)cout<<i<<" ";
            cout<<endl;
            for(int i=1;i<=n;i++)cout<<i<<" ";
            cout<<endl;

        }
        else if(a+b>n || a==0 || b==0)cout<<"NO"<<endl;
        else if(a+b<n)
        {
            int p=n-(a+b);
            cout<<"YES"<<endl;
            for(int i=1;i<=n;i++)cout<<i<<" ";
            cout<<endl;
            for(int i=a+1;i<=n-p;i++)cout<<i<<" ";
            for(int i=1;i<=a;i++)cout<<i<<" ";
            for(int i=n-p+1;i<=n;i++)cout<<i<<" ";
            cout<<endl;
            
        }
        else{
            cout<<"YES"<<endl;
            for(int i=1;i<=n;i++)cout<<i<<" ";
            cout<<endl;
            for(int i=a+1;i<=n;i++)cout<<i<<" ";
            for(int i=1;i<=a;i++)cout<<i<<" ";
            cout<<endl;
        }
    }
}