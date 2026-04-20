#include<stdio.h>
#include<stdlib.h>
#include<time.h>
      
int karistirma()
{
    int sayilar[25]={0,0,0,0,0,0,1,2,3,0,0,4,5,6,0,0,7,8,9,0,0,0,0,0,0};
    int islevsel[9]={6,7,8,11,12,13,16,17};
    int a,b,s,i;

    srand(time(NULL));

    int degistirmeS=rand() %(20-1+1)+5;
    degistirmeS=degistirmeS*2;

    for(i=0;i<degistirmeS;i++)
    {
        
        a=rand() %(8-1+1)+0;
        b=rand() %(8-1+1)+0;
        if(a!=b)
        {
            s=islevsel[a];
            islevsel[a]=islevsel[b];
            islevsel[b]=s;
        }
        else
        i--;

        
    }
    
    for(i=0;i<8;i++)
    {
        
        printf("[%d] ",sayilar[islevsel[i]]);
        if(i%3==2)
        printf("\n");
    }
    return islevsel[0];
    //bu biraz daha ham yapılan fonksiyonlara göre ayarız.
}
