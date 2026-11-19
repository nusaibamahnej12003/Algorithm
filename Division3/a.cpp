#include <bits/stdc++.h>
using namespace std;

int main() {
  int p=-1;
  int n;
  cin>>n;
   string s;
   cin>>s;
   int freq[26]={0};
  transform(s.begin(),s.end(),s.begin(), ::tolower);
  for(int i=0;i<n;i++)
  if(s[i]>='a'&& s[i]<='z')
  {
    freq[s[i]-'a']++;
  }
  for(int i=0;i<26;i++)
  {
    if(freq[i]==0)
    {
      p=1;
    }
  }
  if(p==1)cout<<"NO";
  else cout<<"YES";
}
