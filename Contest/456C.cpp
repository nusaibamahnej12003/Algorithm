#include<bits/stdc++.h>
using namespace std;
int  main()
{
   long long n;
   cin>>n;
 vector<long long> arr(n);
for(long long i=0;i<n;i++)
{
  cin>>arr[i];
}
long long m=*max_element(arr.begin(),arr.end());
vector<long long> cnt(m+1,0);
for(long long x:arr)
{
  cnt[x]++;
}
vector<long long> ans(m+1,0);
ans[0]=0;
ans[1]=cnt[1];
for(long long i=2;i<=m;i++)
{
   ans[i]=max(ans[i-1],ans[i-2]+cnt[i]*i);
}
cout<<ans[m];
}