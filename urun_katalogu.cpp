#include <iostream>
#include <conio.h>

#include "Satis.h"
#include "Urun.h"
#include "Urun_Katalogu.h"

using namespace std;

URUNKATALOGU::URUNKATALOGU() {
    /* All records should show NULL while the object
       is being created, so that no problems arise later. */
    int sayac;
    for (sayac = 0;sayac<100;sayac++) {
        hashTablosu[sayac] = NULL;
    }
}

int URUNKATALOGU::UrunVarMi(int urun_kodu) {

    // 1: There is product
    // 0: No product

    URUN *guncel;

    guncel = hashTablosu[hash(urun_kodu)];

    while(guncel != NULL) { // Until registration ends.

        if (guncel->kodOku() == urun_kodu) {
            return 1;
        }

        guncel = guncel->sonrakiOku();  // Look at the next entry
    }

    return 0; // If it landed here, it means there is no match
}

URUN* URUNKATALOGU::UrunAdres(int urun_kodu) {

    // It shows the address of the product

    URUN *guncel;

    guncel = hashTablosu[hash(urun_kodu)];

    while(guncel != NULL) { // Until registration ends

        if (guncel->kodOku() == urun_kodu) {
            return guncel;
        }

        guncel = guncel->sonrakiOku(); // Look at the next entry
    }

    return NULL; // If it comes here, there is a problem, but it does not come
}

void URUNKATALOGU::UrunEkle(URUN *YeniUrun) {

    URUN *gecici;

    /* If the HashTable is already empty,
       let's insert it and pass. No, if it is full,
       let's adjust the connections. */

    gecici = hashTablosu[hash(YeniUrun->kodOku())];

    hashTablosu[hash(YeniUrun->kodOku())] = YeniUrun;
    YeniUrun->sonrakiYaz(gecici);

}

int URUNKATALOGU::hash(int urun_kodu) {
    return (urun_kodu % 100);
}

void URUNKATALOGU::UrunleriListele(int stok_limit) {

    int sayac;
    URUN *guncel;

    printf("Urun Kodu        Urun Adi      Stok Miktari Bilim Alis Fiyati\n");
    printf("--------- -------------------- ------------ -----------------\n");

    for (sayac=0;sayac<100;sayac++) {
        guncel = hashTablosu[sayac];

        while (guncel != NULL) {
            if (stok_limit == -1 || guncel->stokMiktariOku() < stok_limit) {
                guncel->UrunYaz();
            }
            guncel = guncel->sonrakiOku();
        }
    }
}

void URUNKATALOGU::tumUrunTopSatis() {

    int sayac;
    int satis_urun;
    int satis_top=0;
    float ciro_urun;
    float ciro_top=0L;
    URUN *guncel;
    SATIS *gezinti;

    printf("Urun Kodu      Urun Adi        Toplam Satis Miktari Toplam Ciro\n");
    printf("--------- -------------------- -------------------- -----------\n");

    for (sayac=0;sayac<100;sayac++) {
        guncel = hashTablosu[sayac];

        while (guncel != NULL) {

            // Let's make the necessary calculations regarding sales
            satis_urun = 0;
            ciro_urun = 0L;

            if (guncel->linkOku() != NULL) {/
                gezinti = guncel->linkOku();
                while (gezinti != NULL) {
                    satis_urun += gezinti->miktarOku();
                    ciro_urun += gezinti->miktarOku() * gezinti->birimFiyatOku();

                    gezinti = gezinti->sonrakiOku();
               }
            }

            printf("%9d %20s %20d %11.4f\n",guncel->kodOku(),guncel->adOku(),satis_urun,ciro_urun);

            ciro_top += ciro_urun;
            satis_top += satis_urun;

            guncel = guncel->sonrakiOku(); // Look at the next entry

        }
    }

    printf("---------------------------------------------------------------\n");
    printf("Toplam:                      %22d %11.4f\n",satis_top,ciro_top);
}

void URUNKATALOGU::satilmayanlariListele(char *tarih_limit) {

    int sayac;
    URUN *guncel;
    SATIS *gezinti;

    printf("Urun Kodu      Urun Adi       \n");
    printf("--------- --------------------\n");

    for (sayac=0;sayac<100;sayac++) {
        guncel = hashTablosu[sayac];

        while (guncel != NULL) {

            if (guncel->linkOku() != NULL) {
                gezinti = guncel->linkOku();
                if(strncmp(gezinti->tarihOku(),tarih_limit,6)<0) {
                    printf("%9d %20s\n",guncel->kodOku(),guncel->adOku());
                }
            } else { // No sales were made
                printf("%9d %20s\n",guncel->kodOku(),guncel->adOku());
            }

            guncel = guncel->sonrakiOku(); // Look at the next entry
        }
    }

    printf("------------------------------\n");


}

int URUNKATALOGU::UrunSil(int girdi) {

    /* In this method, the sales method could be
       called while deleting sales. However,
       this method will adjust all connections one by one
       after deleting the sale with the invoice number.
       However, making these adjustments as we delete
       all wholesale sales will not be effective. */

    SATIS *sil_konum;
    SATIS *gecici;
    URUN *gecici2;
    URUN *dolas;

    // Let's delete product-related sales
    sil_konum = UrunAdres(girdi)->linkOku();
    while(sil_konum!=NULL) {
        gecici = sil_konum;;
        sil_konum = sil_konum->sonrakiOku();
        delete (gecici);
    }

    // Before deleting, we must set the necessary statuses in the hashtable or connections.

    if (hashTablosu[hash(girdi)] == UrunAdres(girdi)) {
    // Case 1: The first product connected to the product hashtable.

        // Remove comment for details
        printf("Urun hash tablosunda.\n");

        gecici2 = hashTablosu[hash(girdi)];
        hashTablosu[hash(girdi)] = hashTablosu[hash(girdi)]->sonrakiOku();
        delete (gecici2);

        return 0; // The process is complete

    }

    if (hashTablosu[hash(girdi)]->sonrakiOku() == UrunAdres(girdi)) {
    // Case 2: Second product linked to first product in product hashtable

        // Remove comment for details
        printf("Urun hash tablosundan hemen sonra.\n");

        gecici2 = hashTablosu[hash(girdi)]->sonrakiOku();
        hashTablosu[hash(girdi)]->sonrakiYaz(UrunAdres(girdi)->sonrakiOku());
        delete (gecici2);

        return 0;

    }

    // The product is elsewhere

    // Remove comment for detail
    printf("Urun aralarda bir yerlerde.\n");

    dolas = hashTablosu[hash(girdi)]->sonrakiOku();

    // Let's find the product before the product to be deleted
    while (dolas->sonrakiOku() != UrunAdres(girdi)) {
            dolas = dolas->sonrakiOku();
    }

    /* When it comes here, the memory address of the
       product before the product to be deleted is browsed */

    gecici2 = UrunAdres(girdi);
    dolas->sonrakiYaz(UrunAdres(girdi)->sonrakiOku());
    delete (gecici2);

    return 0;

}
