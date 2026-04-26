#include<stdio.h>
#include<time.h>
#include<stdlib.h>
      
int karistirma()//karıştırma yapmak için kendi bulduğum yönetem burayı ben anlatırım 
{
    int islevsel[8]={1,2,3,4,5,6,7,8};
    int a,b,s,i;
    int son=0;

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

for(int i=0;i<8;i++)
{
        son+=islevsel[i];
        son*=10;
}
son+=9;
return son;
}


void oyun(int acilacak)//oyunun 
{
    int islevsel2[3][3];
    int a=100000000;

   for(int i=0;i<3;i++)
   {
    for(int j=0;j<3;j++)
    {
        islevsel2[i][j]=acilacak/a;
        acilacak%=(a);
        a/=10;
    } 
   }

char girdi;
int takip1=2;
int takip2=2;
int gecici;
int takipTut1;
int takipTut2;
int hata=0;

printf("\n\nOyun basladi *'i hareket ettirmek icin w,a,s,d tuslarini kullanabilrisiniz.\nBaslamak entere basin\n\n");
scanf("%c");
system("cls");
printf("\n\n");
for(int i=0;i<3;i++)
    {
     for(int j=0;j<3;j++)
        {
            if(islevsel2[i][j]!=9)
            printf("[%d] ",islevsel2[i][j]);
            else
            printf("[*] ");
        }
        printf("\n");       
    }
   while(!(islevsel2[0][0]==1 && islevsel2[0][1]==2 && islevsel2[0][2]==3 && islevsel2[1][0]==4 && islevsel2[1][1]==5 && islevsel2[1][2]==6 && islevsel2[2][0]==7 && islevsel2[2][1]==8))
   {
        
        scanf(" %c",&girdi);
        takipTut1=takip1;
        takipTut2=takip2;


        if(girdi =='w'&&takip1-1<3&&takip1-1>=0&&takip2<3&&takip2>=0)
        {
            takip1-=1;
            gecici=islevsel2[takip1+1][takip2];
            islevsel2[takip1+1][takip2]=islevsel2[takip1][takip2];
            islevsel2[takip1][takip2]=gecici;
            
        }
        else if(girdi =='s'&&takip1+1<3&&takip1+1>=0&&takip2<3&&takip2>=0)
        {
            takip1+=1;
            gecici=islevsel2[takip1-1][takip2];
            islevsel2[takip1-1][takip2]=islevsel2[takip1][takip2];
            islevsel2[takip1][takip2]=gecici;
            
        }
        else if(girdi =='a'&&takip1<3&&takip1>=0&&takip2-1<3&&takip2-1>=0)
        {
            takip2-=1;
            gecici=islevsel2[takip1][takip2+1];
            islevsel2[takip1][takip2+1]=islevsel2[takip1][takip2];
            islevsel2[takip1][takip2]=gecici;
            
        }
        else if(girdi =='d'&&takip1<3&&takip1>=0&&takip2+1<3&&takip2+1>=0)
        {
            takip2+=1;
            gecici=islevsel2[takip1][takip2-1];
            islevsel2[takip1][takip2-1]=islevsel2[takip1][takip2];
            islevsel2[takip1][takip2]=gecici;
            
        }
        else
        hata=1;

        system("cls");

        if(hata)
        printf("yanlis hamle farkli bir girdi giriniz\n\n");
 
        else
        printf("\n\n");

        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
                {
                    if(islevsel2[i][j]!=9)
                    printf("[%d] ",islevsel2[i][j]);
                    else
                    printf("[*] ");
                }
        printf("\n");       
        }

   }
   return;
}


int main()
{
    int karar=1;
        while(karar)
        {
            oyun(karistirma());

            printf("Oyun bitti!!\n\nCikmak icin 0 i tekrar oynamak icin 1 i girin\n");
            scanf("%d",karar);

            while(!(karar==0||karar==1))
            {
                printf("yanlis girdi girdiniz tekrar deneyin");
                scanf("%d",karar);
            }
            
        }
       return 0;
}