#include<bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin>>t;
    int p=1;
    while(t--)
    {
        int n,l,s;
        cin>>n;
        int arr[n];
        for(int i=0;i<n;i++)
        {
            cin>>arr[i];
        }
        int maxx=arr[0];
        for(int i=0;i<n;i++)
       {
         if(maxx<arr[i])
         {
            maxx=arr[i];
            l=i;
         }
       }
        int minn=arr[0];
        for(int i=0;i<n;i++)
       {
         if(m<arr[i])
         {
            minn=arr[i];
            s=i;
         }
       }

       for(int k=s;k<=l;k++)
       {
         
       }
}
}




