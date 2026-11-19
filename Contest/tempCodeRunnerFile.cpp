/*#include<bits/stdc++.h>
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
    int a=arr[0],flag=0;
    for(int i=0;i<n;i++)
    {
        if(arr[i]!=a)flag=1;
    }
    if(flag==0)cout<<"1"<<endl;
    else if(flag==1){
            int ans=0,count=0;
            int brr[n];
            for(int i=0;i<n-1;i++)
            {
                int p=arr[i+1]-arr[i];
                if(p==1)count++;
                if(p>1)ans++;

            }
            int tt=ans+(count/2)+1;
            cout<<tt<<endl;

             }

  }
}*/

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

    vector<int> arr(n+1);
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
    }
    for(int i=0;i<n;i++)
    {
      if(arr[i]==arr[i+1]||arr[i]+1==arr[i+1])
      {
        arr.erase(arr.begin()+i);
        n--;
      }
    }
    int count=0;
    arr[n]=-1;
    for(int i=0;i<n;i++)
    {
        if(arr[i]==arr[i+1])continue;
        else
        {
            count++;
        }
    }
    cout<<count<<endl;
    
     }

  }
