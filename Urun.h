/******************************************************************************
 ** Metehan GENCER - https://www.linkedin.com/in/metehan-gen%C3%A7er-733770134/
                   - https://github.com/engineerMeteHan

    Project Name : Ürün Takip Yazýlýmý
    Date         : 01/09/2021
    Version      : V 0.2
    File Name    : urun.h
******************************************************************************/

#ifndef URUN_H_INCLUDED
#define URUN_H_INCLUDED

class URUN {

    private:
        // Object local variables
        int urun_kodu;
        char urun_adi[20];
        float birim_alis_fiyati;
        int stok_miktari;
        URUN *sonraki;
        SATIS *link;

    public:
        // Object creation method
        URUN(int, char*,float,int=0);

        // Getter Methods
        int kodOku();
        char *adOku();
        float alisFiyatiOku();
        int stokMiktariOku();
        URUN *sonrakiOku();
        SATIS *linkOku();

        // Setter Methods
        void alisFiyatiYaz(float);
        void stokMiktariYaz(int);
        void sonrakiYaz(URUN *);
        void linkYaz(SATIS *);

        // Screen printing
        void UrunYaz(int=-1);
        void SatislariListele();

        // Adding sales information to the product
        int satisEkle(SATIS *);
        int satisSil(int);

};

#endif // URUN_H_INCLUDED
