#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int tahta[3][3];
int bos_satir = 2; //boşluğun pozisyonu
int bos_sutun = 2;
int hamle_sayisi = 0; //kullanıcının kaç hamle yaptığını sayıyoruz

char son_ipucu = 'x'; //son verilen ipucunu tekrar olmasın diye tutuyoruz

//hafıza sisteminde ayno duruma tekrar gitmemek için
int onceki_tahta[3][3]; 
int onceki_var = 0;

void ekran_temizle() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int ayni_mi(int a[3][3], int b[3][3]) {
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(a[i][j] != b[i][j])
                return 0;
    return 1;
}

int manhattan_hesapla() { //puzzleın çözüme ne kadar uzak olduğunu ölçüyoruz
    int toplam = 0;
    for(int i=0;i<3;i++) { //satırı gez
        for(int j=0;j<3;j++) { //sütunları gez
            if(tahta[i][j] != 0) {
                int s = tahta[i][j]; //taşın olması gerektiği yeri buluyoruz.
                int hs = (s-1)/3;
                int ht = (s-1)%3;
                toplam += abs(i-hs)+abs(j-ht); //kaç adım yanlış yerde??
            }
        }
    }
    return toplam;
}

/*daha doğru ipuçları için iki adımlı testi tercih ettik. 
ilk hamle yapılmış gibi 1 hamle daha ileri bakılarak düşünülür */

int iki_adim_test(char yon1) { //tek bir yöni alır ve dener "ne kadar iyi?""
    int en_iyi = 9999; //başta büyük çünkü min manhattan skoru arıyoruz
    char yonler[4] = {'w','s','a','d'};

    int es = bos_satir; //mevcut konumlar
    int et = bos_sutun;

    int ys = es, yt = et; //geçici yeni konumlar

    if(yon1=='w') ys--;
    else if(yon1=='s') ys++;
    else if(yon1=='a') yt--;
    else if(yon1=='d') yt++;

    if(!(ys>=0 && ys<3 && yt>=0 && yt<3)) //eğer duvar dışına çıkıyorsak geçersiz ve kötü skor 
        return 9999;

    int tas = tahta[ys][yt]; //boşluğun gideceği yerdeki sayı alınır

    tahta[es][et] = tas; //hamle gerçekten yapılmış gibi simüle edilir
    tahta[ys][yt] = 0;

    for(int i=0;i<4;i++) { //şimdi bir adım daha ileri bakıyoruz
        int s = ys, t = yt; //yeni boşluk konumu

        if(yonler[i]=='w') s--; //ikinci hamleler
        else if(yonler[i]=='s') s++;
        else if(yonler[i]=='a') t--;
        else if(yonler[i]=='d') t++;

        if(s>=0 && s<3 && t>=0 && t<3) {
            int tas2 = tahta[s][t];

            tahta[ys][yt] = tas2;
            tahta[s][t] = 0;

            int m = manhattan_hesapla();
            if(m < en_iyi) en_iyi = m; //en küçük manhattan=en iyi durum

            tahta[s][t] = tas2; //2.hamleyi geri al
            tahta[ys][yt] = 0;
        }
    }

    tahta[ys][yt] = tas; //her şey esi haline döndürülür
    tahta[es][et] = 0;

    return en_iyi;
}

void tahtayi_yazdir() {
    ekran_temizle();
    
    printf("--- 8-PUZZLE OYUNU ---\n");
    printf("Hamle: %d\n", hamle_sayisi);
    printf("Kalan Uzaklik (Manhattan): %d\n\n", manhattan_hesapla());

    for(int i = 0; i < 3; i++) {
        printf("+----+----+----+\n");
        for(int j = 0; j < 3; j++) {
            if(tahta[i][j] == 0)
                printf("|    ");
            else
                printf("| %2d ", tahta[i][j]);
        }
        printf("|\n");
    }
    printf("+----+----+----+\n\n");

    printf("W/A/S/D: Hareket | H: Ipucu | Q: Cikis\n");
    printf("Hamleniz: ");
}

int hareket_et(char yon) {
    int ys = bos_satir;
    int yt = bos_sutun;

    if(yon=='w'||yon=='W') ys--;
    else if(yon=='s'||yon=='S') ys++;
    else if(yon=='a'||yon=='A') yt--;
    else if(yon=='d'||yon=='D') yt++;
    else return 0;

    if(ys>=0 && ys<3 && yt>=0 && yt<3) {
        tahta[bos_satir][bos_sutun] = tahta[ys][yt];
        tahta[ys][yt] = 0;

        bos_satir = ys;
        bos_sutun = yt;
        return 1;
    }
    return 0;
}
//ters hamle kkontrolü arka arkaya aşağı yukarı hamle yaptırmasın diye
int ters_mi(char a, char b) {
    return (a=='w'&&b=='s')||(a=='s'&&b=='w')||
           (a=='a'&&b=='d')||(a=='d'&&b=='a');
}

void ipucu_ver() {
    char yonler[4] = {'w','s','a','d'};
    char isimler[4][50] = {"Belki de yukari gitmelisin ;)","Belki de asagi gitmelisin ;)","Belki de sola gitmelisin ;) ","Belki de saga gitmelisin ;)"};

    int en_iyi = 9999; //en küçük manhattan araniyor
    int adaylar[4]; //en iyi yönler listesi
    int say = 0;

    for(int i=0;i<4;i++) {

        if(ters_mi(yonler[i], son_ipucu)) continue; //önceki ipucunun tersini verme!!!

        int es = bos_satir; //mevcut konum
        int et = bos_sutun;

        int ys = es, yt = et; //yeni konum

        if(yonler[i]=='w') ys--;
        else if(yonler[i]=='s') ys++;
        else if(yonler[i]=='a') yt--;
        else if(yonler[i]=='d') yt++;

        if(!(ys>=0 && ys<3 && yt>=0 && yt<3)) continue; //duvar dışıysa iptal

        int tas = tahta[ys][yt]; //hareket edecek taşı al

        tahta[es][et] = tas; //puzzle geçici değişir
        tahta[ys][yt] = 0;

        if(onceki_var && ayni_mi(tahta, onceki_tahta)) { //aynı duruma geri dönüyorsa noo
            tahta[ys][yt] = tas;
            tahta[es][et] = 0;
            continue;
        }

        int m = iki_adim_test(yonler[i]);

        tahta[ys][yt] = tas;
        tahta[es][et] = 0;

        if(m < en_iyi) { //daha iyi durum bulunduysa
            en_iyi = m;
            say = 0;
            adaylar[say++] = i; //aday listesine ekle
        }
        else if(m == en_iyi) { //başka aday varsa
            adaylar[say++] = i;
        }
    }

    if(say > 0) {
        int sec = adaylar[rand()%say]; //random en iyi yön seçilşr
        son_ipucu = yonler[sec];

        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                onceki_tahta[i][j] = tahta[i][j]; //memory güncellenir
        onceki_var = 1;

        printf("\nIPUCU: %s\n", isimler[sec]); //kullanıcıya yön gösterilir
        char c; scanf(" %c",&c);
    }
}

void karistir() { //oyun başlamadan puzzle karıştırılır
    int k=1;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            tahta[i][j]=k++;

    tahta[2][2]=0;
    bos_satir=2;
    bos_sutun=2; //boş kutunun konumu kaydedilir

    srand(time(NULL));

    char y[4]={'w','s','a','d'};
    int s=0;

    while(s<20) {
        if(hareket_et(y[rand()%4])) s++;
    }

    hamle_sayisi=0;
}

int main() {
    char g;
    karistir();

    while(1) { //sonsuz oyun döngüsü
        tahtayi_yazdir();

        if(manhattan_hesapla()==0) { //tüm taşlar doğru yerdeyse
            printf("Bitti, TEBRIKLER!!!! %d hamle\n",hamle_sayisi);
            break;
        }

        scanf(" %c",&g);

        if(g=='q'||g=='Q') break;
        else if(g=='h'||g=='H') {
            ipucu_ver();
            continue;
        }

        if(hareket_et(g)) hamle_sayisi++;
    }

    return 0;
}
