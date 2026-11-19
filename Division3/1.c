#include<stdio.h>
void deleteElement(int arr[], int *size, int index) {
    if (index >= 0 && index < *size) {
        for (int i = index; i < *size - 1; ++i) {
            arr[i] = arr[i + 1];
        }
        (*size)--; 
    }
}

void bubblesort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
int main()
{
    int n,car=0,p=0,count=0,c=0,c1=0,c2=0;
scanf("%d",&n);
    int s[n];
    int size=n;
    for(int i=0;i<n;i++)
    {
        scanf("%d",&s[i]);
    }
    bubblesort(s,n);
    for(int i=0;i<size;i++)
      {
                if(s[i]==1)
                {
                    for(int j=i+1;j<size;j++)
                    {
                        if(s[j]==3)car++;deleteElement(s,&size,j);deleteElement(s,&size,i);p=1;break;
                    }
                    if(p==0)
                    {
                       for(int j=i+1;j<size;j++)
                       {
                         if(s[j]==2){
                                      for(int k=i+1;k<j;k++)
                                    {
                                        if(s[k]==1)
                                        {
                                            car++;deleteElement(s,&size,i);deleteElement(s,&size,j);deleteElement(s,&size,k);p=1;break;
                                        }
                                    }
                                    if(p==0)
                                    {
                                        car++;deleteElement(s,&size,j);deleteElement(s,&size,i);p=1;break;
                                    }
                                 }
                       } 

                    }
                }
    }
    for(int i=0;i<size;i++)
    {
        printf("%d ",s[i]);
    }
    for(int i=0;i<size;i++)
    {
        if(s[i]==1)c1++;
        if(s[i]==2)c2++;
        if(s[i]==3)car++;
        if(s[i]==4)car++;
    }
    if(c1%4==0)car+=(c1/4);
    else if(c1%4!=0)car+=(c1/4)+1;
     if(c2%2==0)car+=(c2/2);
    else if(c2%2!=0)car+=(c2/2)+1;
printf("%d",car);
}