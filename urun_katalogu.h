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
        /* int parametresi stok alt limittir. Parametresiz çaðýrýlýrsa tüm ürünler listelenir. */
        void UrunleriListele(int=-1);
        void tumUrunTopSatis();

        void satilmayanlariListele(char *);

        int UrunSil(int);

};

#endif // URUN_KATALOGU_H_INCLUDED

URUN::URUN(int a,char b[20],float c,int d) {
    /* Nesne yaratýlýrken veriler yerli yerine yerleþtirilir. */
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

    /* Bu metod Ödev 3'deki fonskiyonumun nesneli
       hale dönüþtürülmüþ halidir.
       Ödev 3 teslim edildikten sonra kaynak kodunu
       Ýnternet'te yayýmladýðým için baþkalarý tarafýndan
       kullanýlýyor olabilir.

       Bu yüzden baþka bir ödevde bu koda benzer bir kod
       kullanýlýyor olabilir.

       Ödev 3'ün Internet'teki konumu:
        https://ubenzer.com/odev-3-baglacli-listeler/
       */

    SATIS *gezinti;
    SATIS *onceki;

    /* Durum 1: Daha önce satýþ eklenmemiþ olabilir. */

    if (link == NULL) { /* daha önce ürün eklemesi yapýlmamýþ. hemen ekliyoruz. */
        adres->sonrakiYaz(NULL);
        link = adres;
    } else {

        /* Durum 2: Yeni eklenen satýþ þimdiye kadarkilerin en büyüðü olabilir ki
           ürünler kýsmýnda deðiþiklik gerekir. */
        if(strncmp(adres->tarihOku(),link->tarihOku(),6)>0) {
            adres->sonrakiYaz(link);
            link = adres;
        } else {
            /* Durum 3: Yeni eklenen herhangi bir arada ya da en sonda olabilir. */
            gezinti = link; /* Gezintiye ilk kaydýn adresini ata */

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

    if (link == NULL) { /* heheee çökertemezsiniz */
        printf("(satis kaydi yok)\n");
    } else {
        gezinti = link;
        while (gezinti != NULL) {
            tarih = gezinti->tarihOku(); /* dizi sonunda NULL olamdýðýndan bu þekilde okunmazsa sorun çýkarýyor. */
            printf("   %6d       %c%c%c%c%c%c %13d %18.4f \n",gezinti->faturaNoOku(),tarih[0],tarih[1],tarih[2],tarih[3],tarih[4],tarih[5],gezinti->miktarOku(),gezinti->birimFiyatOku());
            gezinti = gezinti->sonrakiOku();
       }
    }
}

int URUN::satisSil(int fatno) {

    /* Dikkat: Bu metot bir ürüne ait satýþlardaki tüm
       fatura numaralarýnýn farklý olacaðý öngörülerek
       yazýlmýþtýr.                                     */

    SATIS *gezinti;
    SATIS *onceki;

    /* Durum 1: Liste zaten boþ olablir. */
    if (link == NULL) {
        return -1;
    } else {
        /* Durum 2: Silinecek kayýt ilk kayýt olabiir ki
           ürünler kýsmýnda deðiþiklik gerekir. */
        if(fatno == link->faturaNoOku()) {

            gezinti = link;
            link = link->sonrakiOku();
            delete (gezinti);

        } else {
            /* Durum 3: Silinecek herhangi bir arada ya da en sonda olabilir. */
            gezinti = link; /* Gezintiye ilk kaydýn adresini ata */

            /* Burada onceki = gezinti'ye ihtiyacým yok, çünkü do while'daki þart ilk
            giriþte KESÝNLÝKLE saðlanmayacak. */

            do  { /* Son kayda kadar */

                if(fatno == gezinti->faturaNoOku()) {

                    onceki->sonrakiYaz(gezinti->sonrakiOku());
                    delete (gezinti);
                    return 0;
                }

                onceki = gezinti;
                gezinti = gezinti->sonrakiOku();

            } while (gezinti != NULL);

            /* Buraya kadar geldiyse silinecek eleman bulunamamýþtýr. */
            return -1;
       }
    }
    return 0;

}

#endif // URUN_KATALOGU_H_INCLUDED
