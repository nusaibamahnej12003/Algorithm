//House robbing 2 
#include<bits/stdc++.h>
using namespace std ;
const int N=1e5+10;
int dp[N],kp[N];
vector<int> arr(N);

int fun(int n)
{
    if(n==0)return arr[0];
    if(n==1)return max(arr[0],arr[1]);
    if(dp[n]!=-1)return dp[n];
    else{
     int maxx=INT_MIN;
     dp[n] = max(fun(n-1), arr[n] + fun(n-2));

      return dp[n];
}

}
int main()
{
    memset(dp,-1,sizeof(dp));
    int n;
    cin>>n;
    int p;
    p=n;
    for(int i=0;i<n;i++)cin>>arr[i];
    
    int a=fun(n-2);
    cout<<a<<endl;

    memset(dp,-1,sizeof(dp));
    arr.erase(arr.begin());
    int b=fun(n-1);
    cout<<b<<endl;
    int ans=max(a,b);
    cout<<ans<<endl;
 }

