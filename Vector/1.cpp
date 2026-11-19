#include<bits/stdc++.h>
using namespace std;
int main()
{
    vector<int> vec;
    int n;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        int x;
        cin>>x;
        vec.push_back(x);
    }
    //vec.pop_back();
    vec.insert(vec.begin()+2,100);
    vec.erase(vec.begin()+1,vec.begin()+2);//pos 2 k delete korte 2 ar ager position and 2 positinon;
    for(int x:vec) 
    {
        cout<<x<<" ";
    }
    cout << endl;
    //cout<<vec.size()<<endl;




    return 0;
}

