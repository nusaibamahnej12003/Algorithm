#include<bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin>>t;
    int p=1;
    while(t--)
    {
       int n,l;
       cin>>n;
       vector<int> arr(n);
      
       
       for(int i=0;i<n;i++)
       {
        cin>>arr[i];
       }
        int m=arr[0];
       for(int i=0;i<n;i++)
       {
         if(m<arr[i])
         {
            m=arr[i];
            l=i;
         }
       }
       int j=l;
       int ans=0;
       for(j;j>=0;j--)
       {
        if(n==1) ans=1;
        else if(arr[j]>arr[j-1] && arr[j-1]<=arr[j-2])
        {
            ans=j+1;
           if(ans==2 && arr[0]<arr[1])
           {
            ans=1;
           }
           break;
        }
     }
     if(ans==0)
     {
            cout<<"Case "<<p<<":"<<" "<<"Humanity is doomed!"<<endl;
     }
    else
    cout<<"Case "<<p<<":"<<" "<<ans<<endl;
    p++;
    }
}





