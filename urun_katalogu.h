#ifndef URUN_KATALOGU_H_INCLUDED
#define URUN_KATALOGU_H_INCLUDED

#include <iostream>
#include <conio.h>
#include <string.h>

#include "Satis.h"
#include "Urun.h"
#include "Urun_Katalogu.h"

using namespace std;
class URUNKATALOGU {

    private:
        URUN* hashTablosu[100];
        int hash(int);
    public:
        URUNKATALOGU();
        int UrunVarMi(int);
        URUN* UrunAdres(int);
        void UrunEkle(URUN *);
        /* int parametresi stok alt limittir. Parametresiz �a��r�l�rsa t�m �r�nler listelenir. */
        void UrunleriListele(int=-1);
        void tumUrunTopSatis();

        void satilmayanlariListele(char *);

        int UrunSil(int);

};

#endif // URUN_KATALOGU_H_INCLUDED

URUN::URUN(int a,char b[20],float c,int d) {
    /* Nesne yarat�l�rken veriler yerli yerine yerle�tirilir. */
    int sayac;

    urun_kodu = a;
    for (sayac=0;sayac<20;sayac++) {
        urun_adi[sayac] = b[sayac];
    }
    birim_alis_fiyati = c;
    stok_miktari = d;
    link = NULL;
}

int URUN::kodOku() {
    return urun_kodu;
}

char* URUN::adOku() {
    return urun_adi;
}

float URUN::alisFiyatiOku() {
    return birim_alis_fiyati;
}

int URUN::stokMiktariOku() {
    return stok_miktari;
}

URUN* URUN::sonrakiOku() {
    return sonraki;
}

SATIS* URUN::linkOku() {
    return link;
}

void URUN::alisFiyatiYaz(float a) {
    birim_alis_fiyati = a;
}

void URUN::stokMiktariYaz(int a) {
    stok_miktari = a;
}

void URUN::sonrakiYaz(URUN *a) {
    sonraki = a;
}

void URUN::linkYaz(SATIS *a) {
    link = a;
}

void URUN::UrunYaz(int ayrinti) {
    if (ayrinti == -1) {
        printf("%9d %20s %12d %17.2f\n",urun_kodu,urun_adi,stok_miktari,birim_alis_fiyati);
    } else {
        printf("*** Urun Bilgileri ***\n");
        printf("Urun kodu        : %d\n",urun_kodu);
        printf("Urun adi         : %s\n",urun_adi);
        printf("Stok miktari     : %1d\n",stok_miktari);
        printf("Birim alis fiyati: %.2f\n\n",birim_alis_fiyati);
    }
}

int URUN::satisEkle(SATIS *adres) {

    /* Bu metod �dev 3'deki fonskiyonumun nesneli
       hale d�n��t�r�lm�� halidir.
       �dev 3 teslim edildikten sonra kaynak kodunu
       �nternet'te yay�mlad���m i�in ba�kalar� taraf�ndan
       kullan�l�yor olabilir.

       Bu y�zden ba�ka bir �devde bu koda benzer bir kod
       kullan�l�yor olabilir.

       �dev 3'�n Internet'teki konumu:
        https://ubenzer.com/odev-3-baglacli-listeler/
       */

    SATIS *gezinti;
    SATIS *onceki;

    /* Durum 1: Daha �nce sat�� eklenmemi� olabilir. */

    if (link == NULL) { /* daha �nce �r�n eklemesi yap�lmam��. hemen ekliyoruz. */
        adres->sonrakiYaz(NULL);
        link = adres;
    } else {

        /* Durum 2: Yeni eklenen sat�� �imdiye kadarkilerin en b�y��� olabilir ki
           �r�nler k�sm�nda de�i�iklik gerekir. */
        if(strncmp(adres->tarihOku(),link->tarihOku(),6)>0) {
            adres->sonrakiYaz(link);
            link = adres;
        } else {
            /* Durum 3: Yeni eklenen herhangi bir arada ya da en sonda olabilir. */
            gezinti = link; /* Gezintiye ilk kayd�n adresini ata */

            do  { /* Son kayda kadar */

                if(strncmp(adres->tarihOku(),gezinti->tarihOku(),6) > 0) {

                    adres->sonrakiYaz(gezinti);
                    onceki->sonrakiYaz(adres);
                    return 0;
                }

                onceki = gezinti;
                gezinti = gezinti->sonrakiOku();

            } while (gezinti != NULL);

            adres->sonrakiYaz(gezinti);
            onceki->sonrakiYaz(adres);
       }
    }
    return 0;
}

void URUN::SatislariListele() {

    SATIS *gezinti;
    char *tarih;

    printf("\n");
    printf("FATURA NO SATIS TARIHI SATIS MIKTARI BIRIM SATIS FIYATI\n");
    printf("--------- ------------ ------------- ------------------\n");

    if (link == NULL) { /* heheee ��kertemezsiniz */
        printf("(satis kaydi yok)\n");
    } else {
        gezinti = link;
        while (gezinti != NULL) {
            tarih = gezinti->tarihOku(); /* dizi sonunda NULL olamd���ndan bu �ekilde okunmazsa sorun ��kar�yor. */
            printf("   %6d       %c%c%c%c%c%c %13d %18.4f \n",gezinti->faturaNoOku(),tarih[0],tarih[1],tarih[2],tarih[3],tarih[4],tarih[5],gezinti->miktarOku(),gezinti->birimFiyatOku());
            gezinti = gezinti->sonrakiOku();
       }
    }
}

int URUN::satisSil(int fatno) {

    /* Dikkat: Bu metot bir �r�ne ait sat��lardaki t�m
       fatura numaralar�n�n farkl� olaca�� �ng�r�lerek
       yaz�lm��t�r.                                     */

    SATIS *gezinti;
    SATIS *onceki;

    /* Durum 1: Liste zaten bo� olablir. */
    if (link == NULL) {
        return -1;
    } else {
        /* Durum 2: Silinecek kay�t ilk kay�t olabiir ki
           �r�nler k�sm�nda de�i�iklik gerekir. */
        if(fatno == link->faturaNoOku()) {

            gezinti = link;
            link = link->sonrakiOku();
            delete (gezinti);

        } else {
            /* Durum 3: Silinecek herhangi bir arada ya da en sonda olabilir. */
            gezinti = link; /* Gezintiye ilk kayd�n adresini ata */

            /* Burada onceki = gezinti'ye ihtiyac�m yok, ��nk� do while'daki �art ilk
            giri�te KES�NL�KLE sa�lanmayacak. */

            do  { /* Son kayda kadar */

                if(fatno == gezinti->faturaNoOku()) {

                    onceki->sonrakiYaz(gezinti->sonrakiOku());
                    delete (gezinti);
                    return 0;
                }

                onceki = gezinti;
                gezinti = gezinti->sonrakiOku();

            } while (gezinti != NULL);

            /* Buraya kadar geldiyse silinecek eleman bulunamam��t�r. */
            return -1;
       }
    }
    return 0;

}

#endif // URUN_KATALOGU_H_INCLUDED
