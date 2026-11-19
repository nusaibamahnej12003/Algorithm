#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;
int main()
{
    int n,k,s=0,step[10000];
    cin>>n>>k;
    vector<int> h(n);
    for(int i=0;i<n;i++)
    {
      cin>>h[i];
    }
    vector<int> dp(n,0);
    dp[0]=0;
    for(int i=1;i<n;i++)
    {
        for(int j=1;j<=k;j++){
          step[s++]=(i>=j)?dp[i-j]+abs(h[i]-h[i-j]):INT16_MAX;
          dp[i]=*min_element(step,step+s);
        }
        s=0;
    }
    cout<<dp[n-1];

}