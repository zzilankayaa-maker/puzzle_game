#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<time.h>

int cozumu_bul(int *t) {
    int kopya[9];
    int baslangic_mesafe = 0, bas_p9 = -1;

    // Kendi dizini korumak için kopyasını alıyoruz ve başlangıç durumunu ölçüyoruz
    for(int i = 0; i < 9; i++) {
        kopya[i] = t[i];
        if(kopya[i] == 9) bas_p9 = i;
        else baslangic_mesafe += abs(i/3 - (kopya[i]-1)/3) + abs(i%3 - (kopya[i]-1)%3);
    }

    if(baslangic_mesafe == 0) return 0; // Zaten çözülmüş gelmişse

    int sinir = baslangic_mesafe;
    int yon[] = {-3, 3, -1, 1}; // Yukarı (0), Aşağı (1), Sol (2), Sağ (3)

    // Arama sınırını 60 hamleye kadar kendi kendine genişletir (Bulmaca genelde max 31'de biter)
    while(sinir <= 60) {
        // Fonksiyon içinde kendi hafıza yığınımızı (stack) yaratıyoruz
        int tahta[60][9], p9[60], g[60], yon_idx[60];
        int f_min = 999;

        // Yığının en altı (Derinlik 0 / Başlangıç noktası)
        for(int i = 0; i < 9; i++) tahta[0][i] = kopya[i];
        p9[0] = bas_p9;
        g[0] = 0;
        yon_idx[0] = 0;

        int top = 0; // Stack (yığın) işaretçisi

        while(top >= 0) {
            // Eğer o anki durum için 4 yönü de denediysek bir geri dön (Backtrack)
            if (yon_idx[top] == 4) {
                top--; 
                continue;
            }

            int i = yon_idx[top]++; // Denenecek yönü seç ve sayacı artır
            int onceki_yon = (top > 0) ? (yon_idx[top-1] - 1) : -1;
            int pos = p9[top];

            // 1. Kural: Tahta dışına çıkmayı engelle
            if ((i==0 && pos<3) || (i==1 && pos>5) || (i==2 && pos%3==0) || (i==3 && pos%3==2)) continue;
            
            // 2. Kural: Bir önceki hamlenin tam tersini yapıp kısır döngüye girmeyi engelle
            if (onceki_yon != -1 && i == (onceki_yon ^ 1)) continue;

            // Kurallardan geçtik, hamleyi yapıp stack'e (yeni derinliğe) ekle
            int hedef = pos + yon[i];
            top++;
            for(int j = 0; j < 9; j++) tahta[top][j] = tahta[top-1][j];
            
            tahta[top][pos] = tahta[top][hedef];
            tahta[top][hedef] = 9;
            p9[top] = hedef;
            g[top] = g[top-1] + 1; // Hamle sayısını artır
            yon_idx[top] = 0;      // Yeni durum için yönleri baştan (0'dan) denemeye başla

            // Yeni durumun hedef matrise olan mesafesini ölç
            int h = 0;
            for(int j = 0; j < 9; j++) {
                if(tahta[top][j] != 9) {
                    h += abs(j/3 - (tahta[top][j]-1)/3) + abs(j%3 - (tahta[top][j]-1)%3);
                }
            }

            if (h == 0) return g[top]; // Tam çözümü buldu! Direkt hamle sayısını döndür.

            // Mevcut hamle sayısı (g) + Kalan tahmini mesafe (h)
            int f = g[top] + h;
            
            // Eğer belirlediğimiz derinlik sınırını aştıysak bu koldan gitmeyi bırak
            if (f > sinir) {
                if (f < f_min) f_min = f; // Bir sonraki tur için sınırı ne kadar artırmamız gerektiğini not al
                top--; // Sınırı aştı, bu koldan çık (pop)
            }
        }
        
        if (f_min == 999) return -1; // Hiçbir çıkış yolu yoksa (Teorik olarak imkansız dizilim)
        sinir = f_min; // Döngü bitince arama sınırını genişlet ve tekrar daha derine dal
    }
    return -1; // 60 hamle sınırını geçtiyse pes et
}


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


void oyun(int acilacak)//oyunun ana kısmı bu ilk for sayıyı yan yana kaydettiğimiz için onu tekrar açıyor(burayı tahminen ibrahim anlatır karıştırma kısmına dahil sayılır)
{
    int baslangic=clock();
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


   int enKisa=cozumu_bul(&islevsel2[0][0]);



char girdi;//burası ana başlangıç burada tanımlamalar yapılıyor
int takip1=2;//takip yıldızın nerede olduğunu gösteriyor 2 tane var çünkü 2 boyutlu dizi
int takip2=2;
int gecici;
int hata=0;

printf("\n\n*'i hareket ettirmek icin w,a,s,d tuslarini kullanabilrisiniz.\nBaslamak entere basin\n\n");//baslangıç mesajı
scanf("%c");// enter tuşuna basılana kadar oyunu anlık bekletiyor

system("cls");//ekranı temizliyor


printf("En kisa cozum = %d\n\n",enKisa);


printf("\n");
for(int i=0;i<3;i++)//ekrana oyun alanını 3 e 3 yazdırıyor
    {
     for(int j=0;j<3;j++)
        {
            if(islevsel2[i][j]!=9)
            printf("[%d] ",islevsel2[i][j]);
            else
            printf("[*] ");
        }
        printf("\n");       
    }//alttaki while oyun doğru şekle geldimi diye kontrol ediyor doğru durumda değilse whileye giriyor
   while(!(islevsel2[0][0]==1 && islevsel2[0][1]==2 && islevsel2[0][2]==3 && islevsel2[1][0]==4 && islevsel2[1][1]==5 && islevsel2[1][2]==6 && islevsel2[2][0]==7 && islevsel2[2][1]==8))
   {
        
        scanf(" %c",&girdi);//oyuncudan giridi alıyor
        
        if(girdi =='w'&&takip1-1<3&&takip1-1>=0&&takip2<3&&takip2>=0)//bu if else iflerin tamamı giridinin ne olduğunu anlamak için eğer geçersiz hamle yaparsa else e giriyor
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
        else//daha sonra hata mesajı verebilmesi için bir değişkeni bire eşitliyor
        hata=1;

        system("cls");//ekranı temizler

        if(hata)
        {
            hata=0;//yukarda eğer hata 1 oldu ise hata mesajı veriyor bunu burada yapmamızın sebebi üsste tüm herşey temizlensede hata mesajının bir süre daha kalması
            printf("En kisa cozum = %d\nyanlis hamle farkli bir girdi giriniz\n\n",enKisa);
        }
        
 
        else
        printf("En kisa cozum = %d\n\n\n",enKisa);

        for(int i=0;i<3;i++)//tekrar ekrana oyunun hamle yaplmış yeni kısmını yazdırıyor
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
   int bitis=clock();
   float sure=(float)bitis-baslangic;
   printf("Oyun suresi = %.3f\n",(sure)/1000);
   return;
}


int main()
{
    int karar=1;
        while(karar)
        {
            oyun(karistirma());

            printf("Oyun bitti!!\n\nCikmak icin 0 i tekrar oynamak icin 1 i girin\n");
            scanf("%d",&karar);

            while(!(karar==0||karar==1))
            {
                printf("yanlis girdi girdiniz tekrar deneyin");
                scanf("%d",karar);
            }
            
        }
       return 0;
}