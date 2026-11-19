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
        int i=0;
        int p=arr[0];
        int ans=0;
        while(i<n)
        {
          if(arr[i]<p)ans++;
          else{
            p=arr[i];
          }
          i++;
        }
        cout<<ans<<endl;
    }
}