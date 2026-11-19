#include<bits/stdc++.h>
using namespace std;
void cycle(int V,vector<vector<int>> adj[])
{
   stack<int> s;
   vector<int> flag(V,-1);
   s.push(0);
   flag[0]=0;
   int f=0;
   while(!s.empty())
   {
     int v=s.top();
     if(adj[v].empty()) {s.pop();flag[v]=1;}

     for(auto u:adj[v])
     {
       int U=u[0];
       if(flag[U]==0)
       {
        cout<<"there have cycle ("<<v<<" to "<<U<<")"<<endl;
        f=1;
        break;
       }
       if(flag[U]!=-1)continue;
       s.push(U);
       flag[U]=0;
     }
   }
   if(f==0)cout<<"There have no cycle"<<endl;

}

int main()
{
    int V=5;
    vector<vector<int>> adj[V];
    adj[0].push_back({1});
    adj[0].push_back({2});

    adj[1].push_back({3});
    adj[1].push_back({2});

    adj[3].push_back({4});

    adj[4].push_back({1});

    cycle(V,adj);
    return 0;

}