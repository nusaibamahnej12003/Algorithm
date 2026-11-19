#include<bits/stdc++.h>
using namespace std ;
const int p=1e5+10;
int dp[p];
int fun(int n)
{
    if(n==0)return 0;
    if(n==1)return 1;
    if(dp[n]!=-1)return dp[n];
    return dp[n]=fun(n-1)+fun(n-2);
}
int main()
{
    memset(dp,-1,sizeof(dp));
    int n;
    cin>>n;
    cout<<fun(n);
}

