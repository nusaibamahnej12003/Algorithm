#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;
int main()
{
    int n;
    cin>>n;
    vector<int> h(n);
    for(int i=0;i<n;i++)
    {
      cin>>h[i];
    }
    vector<int> dp(n,0);
    dp[0]=0;
    for(int i=1;i<n;i++)
    {
        int one=dp[i-1]+abs(h[i]-h[i-1]);
        int two=(i>1)?dp[i-2]+abs(h[i]-h[i-2]):INT16_MAX;
        dp[i]=min(one,two);
    }
    cout<<dp[n-1];

}