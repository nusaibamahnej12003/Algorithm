#include <bits/stdc++.h>
 #include<cmath>
 #include <string>
using namespace std;
void deleteElement(int arr[], int& size, int index) {
    if (index >= 0 && index < size) {
        for (int i = index; i < size - 1; ++i) {
            arr[i] = arr[i + 1];
        }
        size--;
    }
}
int main()
{
    int n,car=0,p=0,so=0;
    cin>>n;
    int s[n];
    int size=n;
    for(int i=0;i<n;i++)
    {
        cin>>s[i];
    }
    sort(s, s + n);
       for(int i=0;i<n;i++)
{
                        if(s[i]==1)
                        {
                                    for(int j=i;j<n;j++)
                                    {
                                        if(s[j]==3){car++; deleteElement(s, size,j);p=1;break;}
                                    }
                                     if(p==0)
                                        {
                                        for(int j=i;j<n;j++)
                                        {
                                            if(s[j]==2)
                                            {for(int k=j+1;k<n;k++)
                                                {
                                                    if(s[k]==1){car++; deleteElement(s, size,j);deleteElement(s, size,k);p=1;break;}
                                                      else
                                                  { car++; deleteElement(s, size,j);p=1;break;}
                                                }
                                           }
                                        } 
                                        }
                                if(p==0)
                                    {
                                        for(int j=i;j<n;j++)
                                    {
                            
                                    if(n%4==0){car=n/4;}
                                    else {car=(n/4)+1;}
                                    so=1;
                                    }
                                    }
                                    p=0;
                                if(so==1)break; 
                        }
    if(s[i]==2)
    {
        
        
           for(int j=i+1;j<n;j++)
        {
            if(s[j]==2){car++; deleteElement(s, size,j);p=1;break;}
        } 
        
        if(p==0)
        {
            for(int j=i;j<n;j++)
        {
            if(s[j]==1){
                for(int k=j+1;k<n;k++)
                {
                    if(s[k]==1){car++; deleteElement(s, size,j);deleteElement(s, size,k);p=1;break;}
                    else
                 { car++; deleteElement(s, size,j);p=1;break;}
                }
                
                
        }
        }
        p=0;
    }
    if(so==1)break;
}
}
for(int i=0;i<size;i++){
    if(s[i]==3||s[i]==4){car++;}
}
cout<<car;
}