#include<iostream>
using namespace std;
int main()
{
    int n,sum=0;
    cin>>n;
    int array[n];
    for(int i=0;i<n;i++)
    {
        cin>>array[i];
    }

    for(int i=0;i<n;i=i+2)
    {
        sum=sum+array[i];
    }
    cout<<sum;

}