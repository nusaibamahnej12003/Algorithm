#include<bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        vector<int> arr(n);
        for(int i=0;i<n;i++)
        {
            cin>>arr[i];
        }
        vector<int> narr(100000,0);
        for(int i=0;i<n;i++)
        {
            narr[arr[i]]++;
        }
        int count=0;
        for(int i=0;i<100000;i++)
        {
            if(narr[i]!=0)count++;
        }
        sort(arr.begin(),arr.end());
        int ans;
        for(int i=0;i<n;i++)
        {
            if(arr[i]>=count){ans=arr[i];break;}
        }
        cout<<ans<<endl;
    }  
}