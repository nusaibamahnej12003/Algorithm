#include<bits/stdc++.h>
using namespace std;
int main()
{
   int t;
   cin>>t;
   while(t--)
   {
    int n;
    cin>>n;
    vector<int> arr(n);
    unordered_set<int> st;
    arr[0]=1;
    st.insert(arr[0]);
    for(int i=1;i<n;i++)
        {
          if(i%2!=0){arr[i]=arr[i-1]*2;}
          else 
          {
            if(i==2)arr[i]=3;
            else{
            if(st.count(arr[i-2]+1)) arr[i]=arr[i-2]+2;
            else arr[i]=arr[i-2]+1;
          }
        }
        st.insert(arr[i]);
        }

        for(int i=0;i<n;i++)cout<<arr[i]<<" ";
        cout<<endl;

    }
   
}