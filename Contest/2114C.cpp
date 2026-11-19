
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
 
    vector<int> arr(n+1);
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
    }
    for(int i=0;i<n;i++)
    {
        if(arr[i]==arr[i+1])
        {
            arr.erase(arr.begin()+(i));
            n--;
            i--;
        }
    }
    for(int i=0;i<n-1;i++)
    {
        int p=arr[i];
        if(arr[i+1]-arr[i]==1)
        {
            arr.erase(arr.begin()+(i+1));
            n--;
            i--;
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
 
  }*/
#include <bits/stdc++.h>

using namespace std;

void solve(int tc){
    int n;
    cin >> n;
    int last = -1, ans = 0;
    for(int i = 0; i < n; ++i){
        int a;
        cin >> a;
        if(a - last > 1){
            ans++;
            last = a;
        }
    }
    cout << ans;
}

bool multi = true;

signed main() {
    int t = 1;
    if (multi)cin >> t;
    for (int i = 1; i <= t; ++i) {
        solve(i);
        cout << "\n";
    }
    return 0;
}