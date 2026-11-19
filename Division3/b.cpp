#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,m;
    cin>>n>>m;
    int arr[m];
    for(int i=0;i<m;i++)
     {
       cin>>arr[i];
     }
   sort(arr,arr+m);
   int min=1000;
   int d=0;
   for(int i=0;i<m-n+1;i++)
     {
       d=arr[i+n-1]-arr[i];
       if(min>d)
       {
        min=d;
        d=0;
       }
     }
  cout<<min<<endl;

}