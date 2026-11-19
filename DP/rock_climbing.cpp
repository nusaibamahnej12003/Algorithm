#include<bits/stdc++.h>
using namespace std;
const int m=4,n=5;
int arr[m][n];
int dp[m][n];

int rock(int m,int n)
{
   if (n < 0 || n >= 5) return 100000;
   if(m==0)  return arr[0][n];
   if(dp[m][n]!=-1) return dp[m][n];
   else  dp[m][n]= arr[m][n]+min(rock(m-1,n-1),(min(rock(m-1,n),rock(m-1,n+1))));
   return dp[m][n]; 
}
int main()
{
    memset(dp,-1,sizeof(dp));
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
       {
         cin>>arr[i][j];
       }
    }
    for(int k=0;k<n;k++)
    { 
        cout<<rock(m-1,k)<<endl;
    }

}
