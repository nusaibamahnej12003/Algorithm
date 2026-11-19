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
    int a,b,flag=0;
    
    int d;
        for(int i=0;i<n;i++)
        {
            for(int j=i+1;j<n;j++)
            {
              d=arr[j]%arr[i];
              if(d%2==0)
              {
                flag=1;
                a=arr[i];
                b=arr[j];
                break;
              }  
              if(flag==1)break;
            }
        }
    if(flag==1)cout<<a<<" "<<b<<" "<<endl;
    else cout<<"-1"<<endl;
  }
}