#ifndef URUN_H_INCLUDED
#define URUN_H_INCLUDED

class URUN {

    private:
        /* Nesne yerel de�i�kenleri */
        int urun_kodu;
        char urun_adi[20];
        float birim_alis_fiyati;
        int stok_miktari;
        URUN *sonraki;
        SATIS *link;

    public:
        /* Nesne yaratma metodu */
        URUN(int, char*,float,int=0);

        /* Getter Metodlar */
        int kodOku();
        char *adOku();
        float alisFiyatiOku();
        int stokMiktariOku();
        URUN *sonrakiOku();
        SATIS *linkOku();

        /* Setter Metodlar */
        void alisFiyatiYaz(float);
        void stokMiktariYaz(int);
        void sonrakiYaz(URUN *);
        void linkYaz(SATIS *);

        /* Ekrana Yazd�rma */
        void UrunYaz(int=-1);
        void SatislariListele();

        /* Satis Bilgisini �r�ne ��leme */
        int satisEkle(SATIS *);

        /* Sat�� BilgileriniHavaya U�urma */
        int satisSil(int);

};

#endif // URUN_H_INCLUDED
