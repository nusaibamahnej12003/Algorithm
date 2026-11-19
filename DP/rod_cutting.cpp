/*#include<bits/stdc++.h>
using namespace std;
int n=10;
vector<int> arr(n);
const int N=1e5+10;
int dp[N];
int rodcutting(int n)
{
    if(n==0)return 0;
    if(n==1)return arr[0];

    if(dp[n]!=-1)return dp[n];
   int maximum=INT_MIN;
   for(int i=1;i<=n/2;i++)
   {
    maximum=max({maximum,rodcutting(i)+rodcutting(n-i),arr[n-1]});
   }
   return dp[n]=maximum;
}
int main()
{
   memset(dp,-1,sizeof(dp));
   arr={1,5,8,9,10,12,17,20,24,30};
   int rodlength;
   cin>>rodlength;
   int ans = rodcutting(rodlength);
   cout<<ans<<endl;
}*/
#include<bits/stdc++.h>
using namespace std;
int n=10;
vector<int> arr(n);
const int N=1e5+10;
int dp[N];
int rodcutting(int n)
{
    if(n==0)return 0;

    if(dp[n]!=-1)return dp[n];
    int maximum=INT_MIN;
        for(int i=1;i<=n;i++)
        {
            maximum=max(maximum,arr[i-1]+rodcutting(n-i));
        }
    dp[n]=maximum;
    return dp[n];
}

int main()
{
   memset(dp,-1,sizeof(dp));
   arr={1,5,8,9,10,12,17,20,24,30};
   int rodlength;   
   cin>>rodlength;
   int ans = rodcutting(rodlength);
   cout<<ans<<endl;
}