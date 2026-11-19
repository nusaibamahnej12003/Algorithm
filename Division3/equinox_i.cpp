/*#include<bits/stdc++.h>
using namespace std;
int main()
{
  int n;
  cin>>n;
  int arr[n];
  for(int i=0;i<n;i++)
  {
    cin>>arr[i];
  }
 int carr[n],cum_sum=0;
 for(int i=0;i<n;i++)
 {
  cum_sum+=arr[i];
   carr[i]=cum_sum;
 }
 for(int i=0;i<n;i++)
 {
cout<<carr[i]<<" ";
}
cout<<endl;
 int maxx=*max_element(carr,carr+n);cout<<maxx<<endl;
 int i=0; 
 int minn=carr[0];
 while(carr[i]!=maxx)
 {
   minn=min(minn,carr[i]);
   i++;
 }
 cout<<minn<<endl;
 int sum;
if(minn>=0||minn==carr[0]){sum=maxx;}
 else{
   sum=maxx-minn;
 } 
 cout<<sum<<endl;
}*/
#include <bits/stdc++.h>
using namespace std;

void maxSubarrayCumulative(vector<int>& arr) {
    int n = arr.size();
    int prefix_sum = 0;
    int min_prefix = 0;  // smallest prefix so far
    int min_sum = INT_MAX;

    int start = 0, end = 0, temp_start = 0;

    for (int i = 0; i < n; i++) {
        prefix_sum += arr[i];

        // check best subarray ending at i
        if (prefix_sum - min_prefix < min_sum) {
            min_sum = prefix_sum - min_prefix;
            start = temp_start;
            end = i;
        }

        // update min_prefix
        if (prefix_sum > min_prefix) {
            min_prefix = prefix_sum;
            temp_start = i + 1; // new start candidate
        }
    }

    cout << "Maximum subarray sum = " << min_sum << endl;
    cout << "Subarray: ";
    for (int i = start; i <= end; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    vector<int> arr = {-2,90,-5 ,-1 ,-2 ,-4 ,-3 ,2 ,-10,57,1};
    maxSubarrayCumulative(arr);
    return 0;
}
