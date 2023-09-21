#ifndef SATIS_H_INCLUDED
#define SATIS_H_INCLUDED

class SATIS {

    private:
        // Object local variables
        int fatura_no;
        char satis_tarihi[6];
        int satis_miktari;
        float birim_satis_fiyati;
        SATIS *sonraki;

    public:
        // Object creation method
        SATIS(int,char*,int,float);

        /* Getter Methods */
        int faturaNoOku();
        char *tarihOku();
        int miktarOku();
        float birimFiyatOku();
        SATIS *sonrakiOku();

        /* Setter Methods */
        void sonrakiYaz(SATIS*);

};

#endif // SATIS_H_INCLUDED


