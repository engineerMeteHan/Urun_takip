/******************************************************************************
 ** Metehan GENCER - https://www.linkedin.com/in/metehan-gen%C3%A7er-733770134/
                   - https://github.com/engineerMeteHan

    Project Name : Ürün Takip Yazılımı
    Date         : 01/09/2021
    Version      : V 0.2
    File Name    : urun_katalogu.h
******************************************************************************/

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
        // The stock with int parameter is the lower limit. If called without parameters, all products are listed.
        void UrunleriListele(int=-1);
        void tumUrunTopSatis();

        void satilmayanlariListele(char *);

        int UrunSil(int);

};

#endif // URUN_KATALOGU_H_INCLUDED

URUN::URUN(int a,char b[20],float c,int d) {
    // When the object is created, the data is placed in its place
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

    SATIS *gezinti;
    SATIS *onceki;

    // Case 1: Sales may not have been added before

    if (link == NULL) { // No product has been added before. We add it immediately.
        adres->sonrakiYaz(NULL);
        link = adres;
    } else {

        // Case 2: The newly added sale may be the largest ever, requiring changes to the products section.
        if(strncmp(adres->tarihOku(),link->tarihOku(),6)>0) {
            adres->sonrakiYaz(link);
            link = adres;
        } else {
            // Case 3: The newly added can be any in between or at the end.
            gezinti = link; // Assign the address of the first record to gezinti

            do  { // Until the last recording

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

    if (link == NULL) {
        printf("(satis kaydi yok)\n");
    } else {
        gezinti = link;
        while (gezinti != NULL) {
            tarih = gezinti->tarihOku(); // Since there is no NULL at the end of the array, it causes problems if it is not read this way.
            printf("   %6d       %c%c%c%c%c%c %13d %18.4f \n",gezinti->faturaNoOku(),tarih[0],tarih[1],tarih[2],tarih[3],tarih[4],tarih[5],gezinti->miktarOku(),gezinti->birimFiyatOku());
            gezinti = gezinti->sonrakiOku();
       }
    }
}

int URUN::satisSil(int fatno) {

    /* Attention: This method was written with the
       expectation that all invoice numbers for sales
       of a product will be different. */

    SATIS *gezinti;
    SATIS *onceki;

    // Case 1: The list may already be empty
    if (link == NULL) {
        return -1;
    } else {
        // Case 2: The record to be deleted may be the first record that requires changes in the products section.
        if(fatno == link->faturaNoOku()) {

            gezinti = link;
            link = link->sonrakiOku();
            delete (gezinti);

        } else {
            // Case 3: To be deleted can be any intermediate or last.
            gezinti = link; // Assign the address of the first record to the navigation.

            do  { /* Son kayda kadar */

                if(fatno == gezinti->faturaNoOku()) {

                    onceki->sonrakiYaz(gezinti->sonrakiOku());
                    delete (gezinti);
                    return 0;
                }

                onceki = gezinti;
                gezinti = gezinti->sonrakiOku();

            } while (gezinti != NULL);

            // If þt has come this far, no element to be deleted has been found
            return -1;
       }
    }
    return 0;

}

#endif // URUN_KATALOGU_H_INCLUDED
