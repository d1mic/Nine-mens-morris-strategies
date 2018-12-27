#include "pravila.h"
#include "heuristike.h"


//proverava da li je igrac odigrao legalan potez u prvoj fazi igre
//legalanPotezPrvaFaza vraca 101 ako nije legaln potez
//vraca 1 ako si napravio micu pa sad imas i drugi deo poteza u kome jedes
//vraca 0 ako si samo imao jedan potez i on je ok
int legalanPotezPrvaFaza(int tabla[24], int igracNaPotezu, int potez)  {
    if (potez < 0 || potez > 23 || tabla[potez] != 0)
        return 101;
    else
        return zatvorenaMicaPrvaFaza(tabla, igracNaPotezu, potez);
}



//mora mu se proslediti potez (tj. pozicija) na kojoj se stvarno nalazi protivnikova figura
//vraca 0 ako moze da se odnese ta figura, vraca 1 ako ne moze da se odnese ta figura
int legalnoNosenje(int tabla[24], int igracNaPotezu, int pozicija) {
  int brojac;
  int indikator = 0;

  for (brojac = 0; brojac < 24; brojac++)
    if(tabla[brojac] == -igracNaPotezu && uMici(tabla, brojac)) {
      indikator = 1;
      break;
    }

  if (indikator == 1 && uMici(tabla, pozicija))
    return 1;

  return 0;
  /*
  znaci ako postoji bilo koja koja nije u mici a ta koju ti hoces da ondeses jeste u mici ne moze ta
  ako ta koju hoces nije u mici mozes da nosis
  ako je indikator ostao 0, dakle sve protivnikove figure su u micama, mozes da nosis i tu iako je u mici
  */
}

/*
 *   za svaku mogucu poziciju vraca niz sa potezima na koje moze da se odigra
 *   dok se ne dodje do -101. treba mu proslediti niz int potezi[4] = {-101, -101, -101, -101}
 *   -101 je da ne bih pomesao sa -1 kao negativan igrac na toj poziciji
 */
void moguciPoteziDrugaFaza(int tabla[24], int pozicija, int potezi[4]) {
    switch (pozicija) {
        case 0:
            if (tabla[1] == 0)
                potezi[0] = 1;
            if (tabla[9] == 0)
                potezi[1] = 9;
        break;

        case 1:
            if (tabla[0] == 0)
                potezi[0] = 0;
            if (tabla[4] == 0)
                potezi[1] = 4;
            if (tabla[2] == 0)
                potezi[2] = 2;
        break;

        case 2:
            if (tabla[1] == 0)
                potezi[0] = 1;
            if (tabla[14] == 0)
                potezi[1] = 14;
        break;

        case 3:
            if (tabla[10] == 0)
                potezi[0] = 10;
            if (tabla[4] == 0)
                potezi[1] = 4;
        break;

        case 4:
            if (tabla[1] == 0)
                potezi[0] = 1;
            if (tabla[3] == 0)
                potezi[1] = 3;
            if (tabla[7] == 0)
                potezi[2] = 7;
            if (tabla[5] == 0)
                potezi[3] = 5;
        break;

        case 5:
            if (tabla[4] == 0)
                potezi[0] = 4;
            if (tabla[13] == 0)
                potezi[1] = 13;
        break;

        case 6:
            if (tabla[11] == 0)
                potezi[0] = 11;
            if (tabla[7] == 0)
                potezi[1] = 7;
        break;

        case 7:
            if (tabla[6] == 0)
                potezi[0] = 6;
            if (tabla[4] == 0)
                potezi[1] = 4;
            if (tabla[8] == 0)
                potezi[2] = 8;
        break;

        case 8:
            if (tabla[7] == 0)
                potezi[0] = 7;
            if (tabla[12] == 0)
                potezi[1] = 12;
        break;

        case 9:
            if (tabla[0] == 0)
                potezi[0] = 0;
            if (tabla[10] == 0)
                potezi[1] = 10;
            if (tabla[21] == 0)
                potezi[2] = 21;
        break;

        case 10:
            if (tabla[9] == 0)
                potezi[0] = 9;
            if (tabla[3] == 0)
                potezi[1] = 3;
            if (tabla[18] == 0)
                potezi[2] = 18;
            if (tabla[11] == 0)
                potezi[3] = 11;
        break;

        case 11:
            if (tabla[10] == 0)
                potezi[0] = 10;
            if (tabla[6] == 0)
                potezi[1] = 6;
            if (tabla[15] == 0)
                potezi[2] = 15;
        break;

        case 12:
            if (tabla[8] == 0)
                potezi[0] = 8;
            if (tabla[17] == 0)
                potezi[1] = 17;
            if (tabla[13] == 0)
                potezi[2] = 13;
        break;


        case 13:
            if (tabla[12] == 0)
                potezi[0] = 12;
            if (tabla[5] == 0)
                potezi[1] = 5;
            if (tabla[20] == 0)
                potezi[2] = 20;
            if (tabla[14] == 0)
                potezi[3] = 14;
        break;


        case 14:
            if (tabla[13] == 0)
                potezi[0] = 13;
            if (tabla[2] == 0)
                potezi[1] = 2;
            if (tabla[23] == 0)
                potezi[2] = 23;
        break;


        case 15:
            if (tabla[11] == 0)
                potezi[0] = 11;
            if (tabla[16] == 0)
                potezi[1] = 16;
        break;


        case 16:
            if (tabla[15] == 0)
                potezi[0] = 15;
            if (tabla[19] == 0)
                potezi[1] = 19;
            if (tabla[17] == 0)
                potezi[2] = 17;
        break;


        case 17:
            if (tabla[16] == 0)
                potezi[0] = 16;
            if (tabla[12] == 0)
                potezi[1] = 12;
        break;


        case 18:
            if (tabla[10] == 0)
                potezi[0] = 10;
            if (tabla[19] == 0)
                potezi[1] = 19;
        break;


        case 19:
            if (tabla[18] == 0)
                potezi[0] = 18;
            if (tabla[16] == 0)
                potezi[1] = 16;
            if (tabla[20] == 0)
                potezi[2] = 20;
            if (tabla[22] == 0)
                potezi[3] = 22;
        break;


        case 20:
            if (tabla[19] == 0)
                potezi[0] = 19;
            if (tabla[13] == 0)
                potezi[1] = 13;
        break;


        case 21:
            if (tabla[9] == 0)
                potezi[0] = 9;
            if (tabla[22] == 0)
                potezi[1] = 22;
        break;


        case 22:
            if (tabla[21] == 0)
                potezi[0] = 21;
            if (tabla[19] == 0)
                potezi[1] = 19;
            if (tabla[23] == 0)
                potezi[2] = 23;
        break;


        case 23:
            if (tabla[22] == 0)
                potezi[0] = 22;
            if (tabla[14] == 0)
                potezi[1] = 14;
        break;
    }
};
