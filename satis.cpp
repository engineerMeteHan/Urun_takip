/******************************************************************************
 ** Metehan GENCER - https://www.linkedin.com/in/metehan-gen%C3%A7er-733770134/
                   - https://github.com/engineerMeteHan

    Project Name : Ürün Takip Yazýlýmý
    Date         : 01/09/2021
    Version      : V 0.2
    File Name    : satis.cpp
******************************************************************************/

#include <iostream>
#include <conio.h>

#include "Satis.h"
#include "Urun.h"
#include "Urun_Katalogu.h"

using namespace std;

SATIS::SATIS(int a,char b[6],int c,float d) {
    // When the object is created, the data is placed in its place.
    int sayac;

    fatura_no = a;

    for (sayac=0;sayac<6;sayac++) {
        satis_tarihi[sayac] = b[sayac];
    }

    satis_miktari = c;
    birim_satis_fiyati = d;

    sonraki = NULL;
}

int SATIS::faturaNoOku() {
    return fatura_no;
}

char* SATIS::tarihOku() {
    return satis_tarihi;
}

int SATIS::miktarOku() {
    return satis_miktari;
}

float SATIS::birimFiyatOku() {
    return birim_satis_fiyati;
}

SATIS* SATIS::sonrakiOku() {
    return sonraki;
}

void SATIS::sonrakiYaz(SATIS* a) {
    sonraki = a;
}
