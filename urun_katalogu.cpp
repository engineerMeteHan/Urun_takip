#include <iostream>
#include <conio.h>

#include "Satis.h"
#include "Urun.h"
#include "Urun_Katalogu.h"

using namespace std;

URUNKATALOGU::URUNKATALOGU() {
    /* Nesne yarat�l�rken t�m kay�tlar NULL'u
       g�stersin, sonra sakatl�k ��kmas�n. */
    int sayac;
    for (sayac = 0;sayac<100;sayac++) {
        hashTablosu[sayac] = NULL;
    }
}

int URUNKATALOGU::UrunVarMi(int urun_kodu) {

    /* 1: �r�n var
       0: �r�n yok */

    URUN *guncel;

    guncel = hashTablosu[hash(urun_kodu)];

    while(guncel != NULL) { /* Kay�tlar bitene kadar */

        if (guncel->kodOku() == urun_kodu) {
            return 1;
        }

        guncel = guncel->sonrakiOku(); /* Bir sonraki kay�da bak. */
    }

    return 0; /* E�er buraya geldiyse e�le�me yok demektir. */
}

URUN* URUNKATALOGU::UrunAdres(int urun_kodu) {

    /* Geriye �r�n�n adresini g�nderir. */

    URUN *guncel;

    guncel = hashTablosu[hash(urun_kodu)];

    while(guncel != NULL) { /* Kay�tlar bitene kadar */

        if (guncel->kodOku() == urun_kodu) {
            return guncel;
        }

        guncel = guncel->sonrakiOku(); /* Bir sonraki kay�da u�al�m. */
    }

    return NULL; /* E�er buraya geldiyse bir sakatl�k var demektir, ama gelmez. :) */
}

void URUNKATALOGU::UrunEkle(URUN *YeniUrun) {

    URUN *gecici;

    /* E�er HashTablosu zaten bo�sa yerle�tirip ge�elim.
       Yok e�er doluysa ba�lant�lar� da ayarlayal�m.  */
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

            /* Sat��larla ilgili gerekli hesaplamalar� yapal�m */
            satis_urun = 0;
            ciro_urun = 0L;

            if (guncel->linkOku() != NULL) { /* heheee ��kertemezsiniz */
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

            guncel = guncel->sonrakiOku(); /* Bir sonraki kay�da u�al�m. */

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

            if (guncel->linkOku() != NULL) { /* heheee ��kertemezsiniz */
                gezinti = guncel->linkOku();
                if(strncmp(gezinti->tarihOku(),tarih_limit,6)<0) {
                    printf("%9d %20s\n",guncel->kodOku(),guncel->adOku());
                }
            } else { /* Hi� sat�� yap�lmam�� */
                printf("%9d %20s\n",guncel->kodOku(),guncel->adOku());
            }

            guncel = guncel->sonrakiOku(); /* Bir sonraki kay�da u�al�m. */
        }
    }

    printf("------------------------------\n");


}

int URUNKATALOGU::UrunSil(int girdi) {

    /* Bu metotta sat��lar silinirken satissil metodu
       �a��r�labilirdi. Ancak bu metot fatura numaras�
       verilen sat��� sildikten sonra t�m ba�lant�lar�
       da teker teker ayarlayacakt�r. Halbuki toptan
       t�m sat��lar� sile�imizden bu ayarlamalar� yapmak
       etkin olmayacakt�r.                            */

    SATIS *sil_konum;
    SATIS *gecici;
    URUN *gecici2;
    URUN *dolas;

    /* �r�ne ba�l� sat��lar� silelim */
    sil_konum = UrunAdres(girdi)->linkOku();
    while(sil_konum!=NULL) {
        gecici = sil_konum;;
        sil_konum = sil_konum->sonrakiOku();
        delete (gecici);
    }

    /* Silmeden �nce hashtablosu ya da ba�lant�larda gerekli
       h�d�leri ayarlamal�y�z.                            */

    if (hashTablosu[hash(girdi)] == UrunAdres(girdi)) {
    /* Durum 1: �r�n Hash tablosuna ba�l� ilk �r�n. */

        /* Ayr�nt�l� bilgi i�in commenti kald�r�n. */
        printf("Urun hash tablosunda.\n");

        gecici2 = hashTablosu[hash(girdi)];
        hashTablosu[hash(girdi)] = hashTablosu[hash(girdi)]->sonrakiOku();
        delete (gecici2);

        return 0; /* ��lem tamam, gidiyorum ben. */

    }

    if (hashTablosu[hash(girdi)]->sonrakiOku() == UrunAdres(girdi)) {
    /* Durum 2: �r�n hash tablosundaki ilk �r�ne ba�l� ikinci �r�n. */

        /* Ayr�nt�l� bilgi i�in commenti kald�r�n. */
        printf("Urun hash tablosundan hemen sonra.\n");

        gecici2 = hashTablosu[hash(girdi)]->sonrakiOku();
        hashTablosu[hash(girdi)]->sonrakiYaz(UrunAdres(girdi)->sonrakiOku());
        delete (gecici2);

        return 0;

    }

    /* Durum 3: �r�n ba�ka diyarlarda. */

    /* Ayr�nt�l� bilgi i�in commenti kald�r�n. */
    printf("Urun aralarda bir yerlerde.\n");

    dolas = hashTablosu[hash(girdi)]->sonrakiOku();

    /* Silinecek �r�nden bir �nceki �r�n� bulal�m. */
    while (dolas->sonrakiOku() != UrunAdres(girdi)) {
            dolas = dolas->sonrakiOku();
    }

    /* Buraya gelince silinecek �r�nden bir �necki �r�n�n
       bellek adresi dolas olur. */

    gecici2 = UrunAdres(girdi);
    dolas->sonrakiYaz(UrunAdres(girdi)->sonrakiOku());
    delete (gecici2);

    return 0;

}
