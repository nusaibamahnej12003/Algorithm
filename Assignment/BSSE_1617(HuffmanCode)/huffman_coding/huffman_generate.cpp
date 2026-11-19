#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
using namespace std;

struct N{
    char c; int f; N *l,*r;
    N(char c,int f){this->c=c;this->f=f;l=r=NULL;}
};

struct C{ bool operator()(N* a,N* b){return a->f>b->f;} };

void g(N* r,string s,unordered_map<char,string>& m){
    if(!r) return;
     if(!r->l && !r->r) m[r->c]=s;
      g(r->l,s+"0",m);
      g(r->r,s+"1",m);
}

N* b(unordered_map<char,int>& f){
    priority_queue<N*,vector<N*>,C> q;
    for(auto p:f) q.push(new N(p.first,p.second));
    while(q.size()>1){
         N* l=q.top();q.pop();
        N* r=q.top();q.pop();
        N* n=new N('\0',l->f+r->f);
          n->l=l;n->r=r;
          q.push(n);
    }
    return q.top();
}

int main(){
    ifstream i("input.txt");
      string t((istreambuf_iterator<char>(i)),istreambuf_iterator<char>());
      i.close();

    unordered_map<char,int> f;
    for(char c:t) f[c]++;

    N* r=b(f);

      unordered_map<char,string> m;
      g(r,"",m);

    ofstream o("codes.txt");
      for(auto p:m) o<<(int)p.first<<" "<<p.second<<"\n";
      o.close();
  
    cout<<"Done\n";
}
