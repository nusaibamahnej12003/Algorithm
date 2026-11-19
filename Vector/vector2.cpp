#include<iostream>
#include<vector>
#include <algorithm>
using namespace std;
int main()
{
    vector<int>v1;
    vector<int>v2;

    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(3);
    v1.push_back(1);
    v1.push_back(55);

    v2.push_back(100);
    v2.push_back(200);
    swap(v1,v2);
    //v1.swap(v2);
    sort(v2.begin(),v2.end());
    for(int i=0;i<v2.size();i++)
        {
            cout<<v2[i]<<" ";
        }
        cout<<endl;
    reverse(v2.begin(),v2.end());
    for(int i=0;i<v2.size();i++)
        {
            cout<<v2[i]<<" ";
        }
        
    

}