#include <iostream>
#include <conio.h>

#include "Satis.cpp"
#include "Urun.cpp"
#include "Urun_Katalogu.cpp"

using namespace std;

void beklet() {
    /* The sole purpose of this function is to make the user
       wait until they press a key, and then clear the screen. */
    printf("\nDevam etmek icin bir tusa basin.");
    getch();
    system ("cls");
}

int main() {

    // Information will be written on the screen
    printf("Metehan GENCER\n");
    printf("01 - 09 - 2021\n");
    printf("Erciyes Universitesi Mühendislik Fakultesi\n");
    printf("https://www.linkedin.com/in/metehan-gen%C3%A7er-733770134/");
    printf("PROJE: Nesneye Dayali Programlama\n");
    printf("Surum: 0.2\n\n");
    // End of information

    int sag_serbest=-1;
    char secenek;

    int sayac;

    int girdi;
    char girdi2[20];
    float girdi3;
    int girdi4;
    char girdi5[6];
    int girdi6;

    /* Since the input variables are used for many different
       purposes in each part of the main function,
       I did not give them special names. */

   // Create a Product Catalog object.
   URUNKATALOGU dizin;

    // Main Loop
    while (sag_serbest==-1) {

        // Menu Start
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
        // End of Menu

        secenek=getch();
        system ("cls");

        // Since the option is received via getche, it can be inserted into the switch structure according to the ASCII code.
        switch(secenek) {
            case 49: //1
                system ("cls");
                printf("Yeni bir urun kodu giriniz: ");
                scanf("%d",&girdi);
                system ("cls");

                switch (dizin.UrunVarMi(girdi)) {

                   case 0: // Entered correctly

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

                    case 1: // Entered correctly

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

                    case 1: // Yes there is

                        printf("Fatura no giriniz: ");
                        scanf("%d",&girdi4);

                        for (sayac=0;sayac<6;sayac++) {
                            girdi5[sayac] = 0;
                        }

                        while (girdi5[0] == 0) {
                            fflush(stdin);
                            /* Knowing that the main purpose of the project was
                               to deal with objects, not dates, the sorting problem
                               was neglected for the years before 2000.
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

                    case 0: // No, there is not
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

                    case 1: // Entered correctly

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

                    case 1: // Entered Correctly

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

                    case 1: // Entered Correctly

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
                    /* Since it was known that the main purpose of the project
                       was to deal with objects, not dates, the sorting problem
                       was neglected for the years before 2000.
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

                //It does not accept input other than E e H h and do you want to exit question START
                do {
                    printf ("\nCikmak istiyor musunuz? (E/H) ");
                    secenek = getche();
                    if (secenek == 'E' || secenek == 'e') {
                        sag_serbest = 0;
                        secenek = 'H';
                    }
                } while (secenek != 'H' && secenek != 'h');
                // END of the question Do you want to exit, which does not accept input other than E e H h and.
                system ("cls");
                break;
            default:
                // The section written for users whose hands press the wrong button is the START.
                printf("1'den 9'a kadar bir secim yapin.");
                beklet();
                /* Elleri yanlis tusa basan kullanicilar icin yazilan bolum SONU */
                break;
        }
    }

    printf("O halde hoscakalin. :)\n\n\n");
    return 0;
}
