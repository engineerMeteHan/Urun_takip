#ifndef SATIS_H_INCLUDED
#define SATIS_H_INCLUDED

class SATIS {

    private:
        /* Nesne yerel deðiþkenleri */
        int fatura_no;
        char satis_tarihi[6];
        int satis_miktari;
        float birim_satis_fiyati;
        SATIS *sonraki;

    public:
        /* Nesne yaratma metodu */
        SATIS(int,char*,int,float);

        /* Getter Metodlar */
        int faturaNoOku();
        char *tarihOku();
        int miktarOku();
        float birimFiyatOku();
        SATIS *sonrakiOku();

        /* Setter Metodlar */
        void sonrakiYaz(SATIS*);

};

#endif // SATIS_H_INCLUDED


