#include <bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        string s;
        cin >> s;
        int arr[n]={0};
        int j=0;
        if(n==1 || n==0)
        {
            cout<<"0"<<endl;
            cout<<endl;
        }
        else
        {

            for(int i=0;i<n;i++)
            {
                if(s[i]=='0'){arr[j++]=i;}
            }
        
        cout<<j<<endl;
        for(int k=0;k<j;k++)
        {
            cout<<arr[k]+1<<" ";
        }
        cout<<endl;
    }
}
}
