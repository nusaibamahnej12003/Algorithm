//Vacation problem of AtCoder
#include<bits/stdc++.h>
using namespace std ;
const int i=100000;
const int j=3;
int dp[i][j];
int arr[i][j];
int fun(int i,int j)
{
    if(i==0) return arr[i][j];
    if(dp[i][j]!=-1)return dp[i][j];
    int maxx=0;
    for(int k=0;k<3;k++)
    {
        if(k==j)continue;
         maxx=max(arr[i][j]+fun(i-1,k),maxx);  
    }
     return dp[i][j]=maxx;
}
int main()
{
    
    memset(dp,-1,sizeof(dp));
    int n;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<3;j++)
        {
            cin>>arr[i][j];
        }
    }

    int ans =max({fun(n-1,0),fun(n-1,1),fun(n-1,2)});
    cout<<ans<<endl;
}


