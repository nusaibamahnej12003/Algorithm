#include<iostream>
#include<vector>
using namespace std;
int main(){
    vector<int>v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
     v.push_back(40);
    v.push_back(50);
    v.push_back(100);
    

    cout<<v[0]<<endl;
    cout<<v[1]<<endl;
    cout<<v.at(2)<<endl;
    cout<<v.size()<<endl;
    cout<<v.front()<<endl;
    cout<<v.back()<<endl;
    if(v.empty())cout<<"Empty"<<endl;
    else cout<<"NOT Empty"<<endl;
    v.pop_back();
    v.erase(v.begin()+2);//v.erase(v.begin()+1,v.end());
    for(int i=0;i<v.size();i++)
        {
            cout<<v[i]<<" ";
        }
        cout<<endl;
    v.insert(v.begin()+1,100);
    for(int i=0;i<v.size();i++)
        {
            cout<<v[i]<<" ";
        }

}