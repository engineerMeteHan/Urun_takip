#include <iostream>
#include <conio.h>

#include "Satis.cpp"
#include "Urun.cpp"
#include "Urun_Katalogu.cpp"

using namespace std;

void beklet() {
    /* Bu fonksiyonun tek amaci kullaniciyi bir tusa basana kadar
       bekletmek, ve sonra ekrani silmektir. */
    printf("\nDevam etmek icin bir tusa basin.");
    getch();
    system ("cls");
}

int main() {

    /* Acilis yazilari BASLANGICI */
    printf("Metehan GENCER\n");
    printf("01 - 09 - 2021\n");
    printf("Erciyes Universitesi Mühendislik Fakultesi\n");
    printf("https://www.linkedin.com/in/metehan-gen%C3%A7er-733770134/");
    printf("PROJE: Nesneye Dayali Programlama\n");
    printf("Surum: 0.2\n\n");
    /* Acilis yazilari SONU */

    int sag_serbest=-1;
    char secenek;

    int sayac;

    int girdi;
    char girdi2[20];
    float girdi3;
    int girdi4;
    char girdi5[6];
    int girdi6;

    /* Girdi degiskenleri main fonksiyonun her bir yerinde
       farkli farkli bir sürü amaçla kullanýldýðý için
       özel isimler vermedim. */

    /* Ürün Kataloðu nesnesi yarat */
   URUNKATALOGU dizin;

    /* Ana döngü */
    while (sag_serbest==-1) {

        /* menu BASLANGICI */
        printf("*** Menu *** \n\n");
        printf("1. Yeni bir urunun eklenmesi \n");
        printf("2. Bir urunun birim alis fiyatinin ve stok miktarinin guncellenmesi \n");
        printf("3. Bir urune iliskin satis eklenmesi \n");
        printf("4. Bir urune iliskin satisin silinmesi \n");
        printf("5. Bir urunun silinmesi \n");
        printf("6. Bir urunun bilgilerinin ve o urunden yapilan tum satislarin listelenmesi \n");
        printf("7. Belirli bir tarihten bugune hic satis yapilmayan urunlerin listelenmesi\n");
        printf("8. Tum urunlerin listelenmesi \n");
        printf("9. Belirli bir stok miktarinin altinda urunlerin listelenmesi \n");
        printf("0. Tum urunlerden yapilan toplam satislarin listelenmesi \n");
        printf("C. Cikis \n");

        printf("Lutfen istediginiz islemin numarasini giriniz.\n");
        /*menu BITIMI */

        secenek=getch();
        system ("cls");

        /* secenek getche ile alýndýðý için ASCII koduna göre switch yapýsýna sokulabilir. */
        switch(secenek) {
            case 49: //1
                system ("cls");
                printf("Yeni bir urun kodu giriniz: ");
                scanf("%d",&girdi);
                system ("cls");

                switch (dizin.UrunVarMi(girdi)) {

                   case 0: /* Yaþasýn doðru girmiþler. */

                        for (sayac=0;sayac<20;sayac++) {
                            girdi2[sayac] = 0;
                        }

                        while (girdi2[0] == 0) {
                            fflush(stdin);
                            printf("Yeni urunun adini giriniz: ");
                            gets(girdi2);
                        }

                        printf("Urunun alis fiyatini giriniz: ");
                        scanf("%f",&girdi3);

                        printf("Urunun stok durumunu giriniz: ");
                        scanf("%d",&girdi4);

                        dizin.UrunEkle(new URUN(girdi,girdi2,girdi3,girdi4));
                        printf("Islem tamam. ;)\n");

                        break;
                    case 1:
                        printf("Girdiginiz urun kodu daha once alinmis.\n");
                        break;
                }
                beklet();
                break;
            case 50: //2
                system ("cls");
                printf("Duzenlenecek urun kodunu giriniz: ");
                scanf("%d",&girdi);
                system ("cls");

                switch (dizin.UrunVarMi(girdi)) {

                    case 1: /* Yaþasýn doðru girmiþler. */

                        printf("Urunun yeni alis fiyatini giriniz: ");
                        scanf("%f",&girdi3);

                        printf("Urunun yeni stok durumunu giriniz: ");
                        scanf("%d",&girdi4);

                        dizin.UrunAdres(girdi)->alisFiyatiYaz(girdi3);
                        dizin.UrunAdres(girdi)->stokMiktariYaz(girdi4);

                        printf("Islem tamam. ;)\n");
                        break;

                    case 0:
                        printf("Aradiginiz urune su anda ulasilamiyor.\n");
                        printf("Lutfen, daha sonra tekrar deneyin.\n");
                        printf("The URUN you have called cannot be reached at the moment.\n");
                        printf("Please try again later.\n");
                        break;
                }
                beklet();
                break;
            case 51: //3
                system ("cls");
                printf("Satis eklenecek urun kodunu giriniz: ");
                scanf("%d",&girdi);
                system ("cls");

                switch (dizin.UrunVarMi(girdi)) {

                    case 1: /* Evet var. */

                        printf("Fatura no giriniz: ");
                        scanf("%d",&girdi4);

                        for (sayac=0;sayac<6;sayac++) {
                            girdi5[sayac] = 0;
                        }

                        while (girdi5[0] == 0) {
                            fflush(stdin);
                            /* Ödevin asýl amacýnýn tarihlerle deðil de
                               nesnelerle uðraþmak olduðu bilindiðinden
                               2000 öncesi yýllar için sýralama sorunu
                               ihmal edildi.
                            */
                            printf("Satis tarihini giriniz (YYAAGG): ");
                            gets(girdi5);
                        }

                        printf("Urunun satis miktarini giriniz: ");
                        scanf("%d",&girdi6);

                        printf("Birim satis fiyatini giriniz: ");
                        scanf("%f",&girdi3);

                        dizin.UrunAdres(girdi)->satisEkle(new SATIS(girdi4,girdi5,girdi6,girdi3));
                        printf("Islem tamam.");
                        break;

                    case 0: /* Hayýr, yok */
                        printf("Boyle bir urun yok.");
                        break;
                }
                beklet();
                break;
            case 52: //4
                system ("cls");
                printf("Satis silinecek urunun kodunu giriniz: ");
                scanf("%d",&girdi);
                system ("cls");

                switch (dizin.UrunVarMi(girdi)) {

                    case 1: /* Yaþasýn doðru girmiþler. */

                        system ("cls");
                        printf("Silinecek satisin fatura nosu: ");
                        scanf("%d",&girdi4);
                        system ("cls");

                        switch (dizin.UrunAdres(girdi)->satisSil(girdi4)) {

                            case -1:
                                printf("Silinmesi istenen fatura numarasina rastlanamadi.\n");
                                break;
                            case 0:
                                printf("Sildim bile.");
                                break;
                        }


                        break;
                    case 0:
                        printf("Boyle bir urun yok ki. :)\n");
                        break;
               }

                beklet();
                break;
            case 53: //5
                system ("cls");
                printf("Silinecek urun kodunu giriniz: ");
                scanf("%d",&girdi);
                system ("cls");

                switch (dizin.UrunVarMi(girdi)) {

                    case 1: /* Yaþasýn doðru girmiþler. */

                        dizin.UrunSil(girdi);
                        printf("Sildim bile.");
                        break;
                    case 0:
                        printf("Boyle bir urun zaten yok ki. :)\n");
                        break;
                }
                beklet();
                break;
            case 54: //6
                system ("cls");
                printf("Satislari listelenecek urun kodunu giriniz: ");
                scanf("%d",&girdi);
                system ("cls");

                switch (dizin.UrunVarMi(girdi)) {

                    case 1: /* Yaþasýn doðru girmiþler. */

                        dizin.UrunAdres(girdi)->UrunYaz(1); /* Ürün bilgileri getirilir. */
                        dizin.UrunAdres(girdi)->SatislariListele(); /* Satis bilgileri ekrana yazilir. */
                        break;
                    case 0:
                        printf("Aradiginiz urune su anda ulasilamiyor.\n");
                        printf("Lutfen, daha sonra tekrar deneyin.\n");
                        printf("The URUN you have called cannot be reached at the moment.\n");
                        printf("Please try again later.\n");
                        break;
                }

                beklet();
                break;
            case 55: //7

                for (sayac=0;sayac<6;sayac++) {
                    girdi5[sayac] = 0;
                }

                while (girdi5[0] == 0) {
                    fflush(stdin);
                    /* Ödevin asýl amacýnýn tarihlerle deðil de
                       nesnelerle uðraþmak olduðu bilindiðinden
                       2000 öncesi yýllar için sýralama sorunu
                       ihmal edildi.
                    */
                    printf("Ne zamandan beri? (YYAAGG): ");
                    gets(girdi5);
                }

                dizin.satilmayanlariListele(girdi5);
                beklet();
                break;
            case 56: //8
                dizin.UrunleriListele();

                beklet();
                break;
            case 57: //9
                girdi = -1;
                system("cls");
                printf("Kactan kucuk olsun istiyorsunuz? ");
                scanf("%d",&girdi);
                system("cls");

                dizin.UrunleriListele(girdi);

                beklet();
                break;
            case 48: // 0
                dizin.tumUrunTopSatis();
                beklet();
                break;
            case 99: //c
            case 67: //C
                /* E e H h ve disinda girdi kabul etmeyen cikmak istiyor musunuz sorusu BASLANGICI */
                do {
                    printf ("\nCidden cikmak istiyor musunuz? (E/H) ");
                    secenek = getche();
                    if (secenek == 'E' || secenek == 'e') {
                        sag_serbest = 0;
                        secenek = 'H';
                    }
                } while (secenek != 'H' && secenek != 'h');
                /* E e H h ve disinda girdi kabul etmeyen cikmak istiyor musunuz sorusu SONU */
                system ("cls");
                break;
            default:
                /* Elleri yanlis tusa basan kullanicilar icin yazilan bolum BASLANGICI */
                printf("Bir zahmet 1'den 9'a kadar bir secim yapin.");
                beklet();
                /* Elleri yanlis tusa basan kullanicilar icin yazilan bolum SONU */
                break;
        }
    }

    printf("O halde hoscakalin. :)\n\n\n");
    return 0;
}
