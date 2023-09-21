#include <iostream>
#include <conio.h>

#include "Satis.h"
#include "Urun.h"
#include "Urun_Katalogu.h"

using namespace std;

URUNKATALOGU::URUNKATALOGU() {
    /* Nesne yaratýlýrken tüm kayýtlar NULL'u
       göstersin, sonra sakatlýk çýkmasýn. */
    int sayac;
    for (sayac = 0;sayac<100;sayac++) {
        hashTablosu[sayac] = NULL;
    }
}

int URUNKATALOGU::UrunVarMi(int urun_kodu) {

    /* 1: Ürün var
       0: Ürün yok */

    URUN *guncel;

    guncel = hashTablosu[hash(urun_kodu)];

    while(guncel != NULL) { /* Kayýtlar bitene kadar */

        if (guncel->kodOku() == urun_kodu) {
            return 1;
        }

        guncel = guncel->sonrakiOku(); /* Bir sonraki kayýda bak. */
    }

    return 0; /* Eðer buraya geldiyse eþleþme yok demektir. */
}

URUN* URUNKATALOGU::UrunAdres(int urun_kodu) {

    /* Geriye ürünün adresini gönderir. */

    URUN *guncel;

    guncel = hashTablosu[hash(urun_kodu)];

    while(guncel != NULL) { /* Kayýtlar bitene kadar */

        if (guncel->kodOku() == urun_kodu) {
            return guncel;
        }

        guncel = guncel->sonrakiOku(); /* Bir sonraki kayýda uçalým. */
    }

    return NULL; /* Eðer buraya geldiyse bir sakatlýk var demektir, ama gelmez. :) */
}

void URUNKATALOGU::UrunEkle(URUN *YeniUrun) {

    URUN *gecici;

    /* Eðer HashTablosu zaten boþsa yerleþtirip geçelim.
       Yok eðer doluysa baðlantýlarý da ayarlayalým.  */
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

            /* Satýþlarla ilgili gerekli hesaplamalarý yapalým */
            satis_urun = 0;
            ciro_urun = 0L;

            if (guncel->linkOku() != NULL) { /* heheee çökertemezsiniz */
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

            guncel = guncel->sonrakiOku(); /* Bir sonraki kayýda uçalým. */

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

            if (guncel->linkOku() != NULL) { /* heheee çökertemezsiniz */
                gezinti = guncel->linkOku();
                if(strncmp(gezinti->tarihOku(),tarih_limit,6)<0) {
                    printf("%9d %20s\n",guncel->kodOku(),guncel->adOku());
                }
            } else { /* Hiç satýþ yapýlmamýþ */
                printf("%9d %20s\n",guncel->kodOku(),guncel->adOku());
            }

            guncel = guncel->sonrakiOku(); /* Bir sonraki kayýda uçalým. */
        }
    }

    printf("------------------------------\n");


}

int URUNKATALOGU::UrunSil(int girdi) {

    /* Bu metotta satýþlar silinirken satissil metodu
       çaðýrýlabilirdi. Ancak bu metot fatura numarasý
       verilen satýþý sildikten sonra tüm baðlantýlarý
       da teker teker ayarlayacaktýr. Halbuki toptan
       tüm satýþlarý sileðimizden bu ayarlamalarý yapmak
       etkin olmayacaktýr.                            */

    SATIS *sil_konum;
    SATIS *gecici;
    URUN *gecici2;
    URUN *dolas;

    /* Ürüne baðlý satýþlarý silelim */
    sil_konum = UrunAdres(girdi)->linkOku();
    while(sil_konum!=NULL) {
        gecici = sil_konum;;
        sil_konum = sil_konum->sonrakiOku();
        delete (gecici);
    }

    /* Silmeden önce hashtablosu ya da baðlantýlarda gerekli
       hödöleri ayarlamalýyýz.                            */

    if (hashTablosu[hash(girdi)] == UrunAdres(girdi)) {
    /* Durum 1: Ürün Hash tablosuna baðlý ilk ürün. */

        /* Ayrýntýlý bilgi için commenti kaldýrýn. */
        printf("Urun hash tablosunda.\n");

        gecici2 = hashTablosu[hash(girdi)];
        hashTablosu[hash(girdi)] = hashTablosu[hash(girdi)]->sonrakiOku();
        delete (gecici2);

        return 0; /* Ýþlem tamam, gidiyorum ben. */

    }

    if (hashTablosu[hash(girdi)]->sonrakiOku() == UrunAdres(girdi)) {
    /* Durum 2: Ürün hash tablosundaki ilk ürüne baðlý ikinci ürün. */

        /* Ayrýntýlý bilgi için commenti kaldýrýn. */
        printf("Urun hash tablosundan hemen sonra.\n");

        gecici2 = hashTablosu[hash(girdi)]->sonrakiOku();
        hashTablosu[hash(girdi)]->sonrakiYaz(UrunAdres(girdi)->sonrakiOku());
        delete (gecici2);

        return 0;

    }

    /* Durum 3: Ürün baþka diyarlarda. */

    /* Ayrýntýlý bilgi için commenti kaldýrýn. */
    printf("Urun aralarda bir yerlerde.\n");

    dolas = hashTablosu[hash(girdi)]->sonrakiOku();

    /* Silinecek üründen bir önceki ürünü bulalým. */
    while (dolas->sonrakiOku() != UrunAdres(girdi)) {
            dolas = dolas->sonrakiOku();
    }

    /* Buraya gelince silinecek üründen bir önecki ürünün
       bellek adresi dolas olur. */

    gecici2 = UrunAdres(girdi);
    dolas->sonrakiYaz(UrunAdres(girdi)->sonrakiOku());
    delete (gecici2);

    return 0;

}
