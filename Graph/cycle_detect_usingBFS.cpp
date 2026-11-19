#include<bits/stdc++.h>
using namespace std;
void cycle(int V,vector<int> adj[])
{
   queue<int> q;
   vector<int> flag(V,-1);
   q.push(0);
   flag[0]=0;
   int f=0;
   while(!q.empty())
   {
     int v=q.front();
     q.pop();
     flag[v]=1;

     for(int U:adj[v])
     {
       if(flag[U]==0)
       {
        cout<<"there have cycle ("<<v<<" to "<<U<<")"<<endl;
        f=1;
       }
       if(flag[U]!=-1)continue;
       q.push(U);
       flag[U]=0;
     }
   }
   if(f==0)cout<<"There have no cycle"<<endl;

}

int main()
{
    int V=5;
    vector<int> adj[V];
    adj[0].push_back(1);
    adj[0].push_back(2);

    adj[1].push_back(3);
    adj[1].push_back(4);
    adj[1].push_back(0);

    adj[2].push_back(0);

    adj[3].push_back(1);
    adj[3].push_back(4);

    adj[4].push_back(3);
    adj[4].push_back(4);

    cycle(V,adj);
    return 0;

}