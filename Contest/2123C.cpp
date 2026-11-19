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
        for(int i=0;i<n;i++)
        {
            cin>>arr[i];
        }
        int narr[n]={0};
        int m=1000000;
        int mx=-1;
                    for(int i=0;i<n;i++)
                    {
                        if(arr[i]<m)
                        {
                            m=arr[i];
                            narr[i]=1;
                        }
                    }
        
                   for(int j=n-1;j>=0;j++){
                    if(narr[j]!=1){
                        if(arr[j]>mx)
                        {
                            mx=arr[j];
                            narr[j]=1;
                        }  
                    }
                }
                        
              
        for(int i=0;i<n;i++)
        {
            cout<<narr[i];
        }
        cout<<endl;

    }
}