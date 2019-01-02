#include "heuristike.h"
#include "pravila.h"
#include "alphabeta.h"

#include <iostream>




//slicno kao za max
int min(int tabla[24], int alpha, int beta, int poslednjiPotezPozitivnog, int poslednjiPotezNegativnog,
        int dubina, int brojPoteza, int koef[19]) {


    int pobeda;
    int rezultat[4] = {0, 0, 0, 0};
    brojBlokiranih(tabla, rezultat);

    int minimalnaVrednost = 32000;
    int vrednost = 0;
    int brojac;

    if (rezultat[3] == 2 || rezultat[3] == rezultat[1])
        pobeda = 1;
    else
        if (rezultat[2] == 2 || rezultat[2] == rezultat[0])
            pobeda = -1;
        else
            pobeda = 0;

    if (brojPoteza < 18) {
        //jos uvek je prva faza igre

        if (dubina == 0) {
            //izlaz iz rekurzije
            int dvaITriKonf[2] = {0, 0};
            brojDvaITriKonfiguracija(tabla, dvaITriKonf);


            //sto je negativni u boljoj poziciji to je vrednost povratne vrednosti manja
            //zbog toga oduzimamo vrednost ako je upravo zatvorio micu u poslednjem potezu
            return (koef[0] * (poslednjiPotezNegativnog + poslednjiPotezPozitivnog)) + (koef[1] * brojFiguraUMicamaPrvaFaza(tabla)) +
                   (koef[2] * (rezultat[0] - rezultat[1])) + (koef[3] * (rezultat[2] - rezultat[3])) +
                   (koef[4] * dvaITriKonf[0]) + (koef[5] * dvaITriKonf[1]) + (koef[6] * sloboda(tabla));
        }

        //jos uvek ne izlazimo iz rekurzije vec gledamo koji je najbolji potez za negativnog
        for (brojac = 0; brojac < 24; brojac++) {
            if (tabla[brojac] == 0) {
                tabla[brojac] = -1; //posto smo u min-u znamo da je negativni na potezu

                if (uMici(tabla, brojac)) {
                    poslednjiPotezNegativnog = 1;
                    int j;

                    for (j = 0; j < 24; j++) {
                        if (tabla[j] == 1 && !legalnoNosenje(tabla, -1, j)) {
                            tabla[j] = 0; //skidamo protivnikovu figuru
                            vrednost = max(tabla, alpha, beta, nullptr, poslednjiPotezPozitivnog,
                                           poslednjiPotezNegativnog, dubina - 1, brojPoteza + 1, koef);
                            tabla[j] = 1; //vracamo kako je bilo posle evaluacije tog poteza
                            if (vrednost < minimalnaVrednost)
                                minimalnaVrednost = vrednost;
                            if (minimalnaVrednost <= alpha) {
                                tabla[brojac] = 0;
                                return minimalnaVrednost;
                            }
                            if(minimalnaVrednost < beta)
                                beta = minimalnaVrednost;
                        }
                    }

                }
                else {
                    //odigrani potez nije napravio micu
                    poslednjiPotezNegativnog = 0;
                    vrednost = max(tabla, alpha, beta, nullptr, poslednjiPotezPozitivnog,
                                   poslednjiPotezNegativnog, dubina - 1, brojPoteza + 1, koef);
                    if (vrednost < minimalnaVrednost)
                        minimalnaVrednost = vrednost;
                    if (minimalnaVrednost <= alpha) {
                        tabla[brojac] = 0;
                        return minimalnaVrednost;
                    }
                    if (minimalnaVrednost < beta)
                        beta = minimalnaVrednost;
                }
                tabla[brojac] = 0;
            }
        }      
        return minimalnaVrednost;
    }
    else {

        if (dubina == 0 || pobeda != 0) {
            if (rezultat[2] > 3 && rezultat[3] > 3) {
                //evaluacija prema heuristikama za drugu fazu igre
                int brMicaIOtvorenih[3] = {0, 0, 0};
                miceIOtvoreneMice(tabla, brMicaIOtvorenih);

                return (koef[7] * (poslednjiPotezNegativnog + poslednjiPotezPozitivnog)) +
                       (koef[8] * brMicaIOtvorenih[0]) + (koef[9] * (rezultat[0] - rezultat[1])) +
                       (koef[10] * (rezultat[2] - rezultat[3])) + (koef[11] * brMicaIOtvorenih[1]) +
                       (koef[12] * brMicaIOtvorenih[2]) + (koef[13] * sloboda(tabla)) + (koef[14] * pobeda);
            }
            else {
                //evaluacija prema heuristikama za trecu fazu igre
                int dvaITriKonf[2] = {0, 0};
                brojDvaITriKonfiguracija(tabla, dvaITriKonf);

                return (koef[15] * dvaITriKonf[0]) + (koef[16] * dvaITriKonf[1]) + (koef[17] * (poslednjiPotezNegativnog + poslednjiPotezPozitivnog)) +
                       (koef[18] * pobeda);
            }
        }

        //jos uvek se ne izlazi iz rekurzije vec igramo neki od poteza
        if (rezultat[3] > 3) {
            //negativni ima vise od 3 figure i igra po pravilima druge faze
            for (brojac = 0; brojac < 24; brojac++) {
                if (tabla[brojac] == -1) {
                    //nasli smo negativnu figuru i gledamo na koju poziciju mozemo da je odigramo
                    int potezi[4] = {-101, -101, -101, -101};
                    moguciPoteziDrugaFaza(tabla, brojac, potezi);
                    int j;
                    for (j = 0; j < 4; j++)
                        if (potezi[j] != -101) {
                            //igramo sa brojac na potezi[j]
                            tabla[brojac] = 0;
                            tabla[potezi[j]] = -1;

                            if (uMici(tabla, potezi[j])) {
                                poslednjiPotezNegativnog = 1;
                                int k;
                                for (k = 0; k < 24; k++) {
                                    if (tabla[k] == 1 && !legalnoNosenje(tabla, -1, k)) {
                                        tabla[k] = 0;
                                        vrednost = max(tabla, alpha, beta, nullptr, poslednjiPotezPozitivnog,
                                                       poslednjiPotezNegativnog, dubina - 1, brojPoteza + 1, koef);
                                        tabla[k] = 1; //vracamo kako je bilo posle evaluacije tog poteza
                                        if (vrednost < minimalnaVrednost)
                                            minimalnaVrednost = vrednost;
                                        if (minimalnaVrednost <= alpha) {
                                            tabla[potezi[j]] = 0;
                                            tabla[brojac] = -1;
                                            return minimalnaVrednost;
                                        }
                                        if(minimalnaVrednost < beta)
                                            beta = minimalnaVrednost;
                                    }
                                }
                            }
                            else {
                                //kad odigramo sa brojac na potezi[j] ne pravimo micu
                                poslednjiPotezNegativnog = 0;
                                vrednost = max(tabla, alpha, beta, nullptr, poslednjiPotezPozitivnog,
                                               poslednjiPotezNegativnog, dubina - 1, brojPoteza + 1, koef);
                                if (vrednost < minimalnaVrednost)
                                    minimalnaVrednost = vrednost;
                                if (minimalnaVrednost <= alpha) {
                                    tabla[potezi[j]] = 0;
                                    tabla[brojac] = -1;
                                    return minimalnaVrednost;
                                }
                                if(minimalnaVrednost < beta)
                                    beta = minimalnaVrednost;
                            }
                            tabla[potezi[j]] = 0;
                            tabla[brojac] = -1;
                        }
                }
            }
            return minimalnaVrednost;
        }
        else {
            //negativni ima 3 figure i igra po pravilima trece faze
            for (brojac = 0; brojac < 24; brojac++) {
                if (tabla[brojac] == -1) {
                    int j;
                    for (j = 0; j < 24; j++) {
                        if (tabla[j] == 0) {
                            //mozemo da skocimo na poziciju j jer je slobodna
                            tabla[brojac] = 0;
                            tabla[j] = -1;

                            if (uMici(tabla, j)) {
                                //upravo smo skokom na j zatvorili mici
                                poslednjiPotezNegativnog = 1;
                                int k;
                                for (k = 0; k < 24; k++) {
                                    if (tabla[k] == 1 && legalnoNosenje(tabla, -1, k)) {
                                        tabla[k] = 0;
                                        vrednost = max(tabla, alpha, beta, nullptr, poslednjiPotezPozitivnog,
                                                       poslednjiPotezNegativnog, dubina - 1, brojPoteza + 1, koef);
                                        tabla[k] = 1;
                                        if (vrednost < minimalnaVrednost)
                                            minimalnaVrednost = vrednost;
                                        if (minimalnaVrednost <= alpha) {
                                            tabla[j] = 0;
                                            tabla[brojac] = -1;
                                            return minimalnaVrednost;
                                        }
                                        if(minimalnaVrednost < beta)
                                            beta = minimalnaVrednost;
                                    }
                                }
                            }
                            else {
                                //skokom na j ne pravimo micu
                                poslednjiPotezNegativnog = 0;
                                vrednost = max(tabla, alpha, beta, nullptr, poslednjiPotezPozitivnog,
                                               poslednjiPotezNegativnog, dubina - 1, brojPoteza + 1, koef);
                                if (vrednost < minimalnaVrednost)
                                    minimalnaVrednost = vrednost;
                                if (minimalnaVrednost <= alpha) {
                                    tabla[j] = 0;
                                    tabla[brojac] = -1;
                                    return minimalnaVrednost;
                                }
                                if(minimalnaVrednost < beta)
                                    beta = minimalnaVrednost;
                            }
                            tabla[j] = 0;
                            tabla[brojac] = -1;
                        }
                    }
                }
            }
            return minimalnaVrednost;
        }
    }
}


/*
 * Potez je taj najbolji potez koji engine treba da odigra na kraju. Prosledjujemo dalje i
 * poslednji (tj. upravo) odigrani potez kako bi u sledecem pozivu imali proveru za upravo zatvorenu
 * micu. Ova heuristika se dodaje da bi smo bili sigurni da ce engine otvarati i zatvarati mice
 * Moglo je i bez toga uz dobre koeficijente za broj figura, broj otvorenih i zatvorenih mica ali
 * ovako smo sigurni da se nece desiti da napravi micu i kaze super je ovo i nikad je ne otvori :)
 */
int max(int tabla[24], int alpha, int beta, int potez[3], int poslednjiPotezPozitivnog,
        int poslednjiPotezNegativnog, int dubina, int brojPoteza, int koef[19]) {

    if (brojPoteza == 18 || brojPoteza == 19)
        dubina = dubina + 1;

    if (brojPoteza == 24 || brojPoteza == 25)
        dubina = dubina + 1;

    int pobeda;
    int rezultat[4] = {0, 0, 0, 0};
    brojBlokiranih(tabla, rezultat);


    int maksimalnaVrednost = -32000;
    int vrednost = 0;
    int brojac;


    if (rezultat[3] == 2 || rezultat[3] == rezultat[1])
        pobeda = 1;
    else
        if (rezultat[2] == 2 || rezultat[2] == rezultat[0])
            pobeda = -1;
        else
            pobeda = 0;


    if (brojPoteza < 18) {
        //jos uvek je prva faza igre

        if (dubina == 0) {
            //izlaz iz rekurzije
            int dvaITriKonf[2] = {0, 0};
            brojDvaITriKonfiguracija(tabla, dvaITriKonf);            

            return (koef[0] * (poslednjiPotezPozitivnog + poslednjiPotezNegativnog)) + (koef[1] * brojFiguraUMicamaPrvaFaza(tabla)) +
                   (koef[2] * (rezultat[0] - rezultat[1])) + (koef[3] * (rezultat[2] - rezultat[3])) +
                   (koef[4] * dvaITriKonf[0]) + (koef[5] * dvaITriKonf[1]) + (koef[6] * sloboda(tabla));
        }

        //ako dubina jos uvek nije nula ne izlazimo iz rekurzije vec gledamo
        //koji je najbolji potez koji moze da se odigra iz ove pozicije
        for (brojac = 0; brojac < 24; brojac++) {
            if (tabla[brojac] == 0) {
                tabla[brojac] = 1; //znamo da je pozitivni igrac onaj koji se trudi da maxuje

                if (uMici(tabla, brojac)) {
                    poslednjiPotezPozitivnog = 1;
                    //ako je to sto smo odigrali zatvorilo micu, sada imamo drugi deo poteza gde
                    //nosimo protivnikovu figuru
                    int j;

                    for (j = 0; j < 24; j++) {
                        if (tabla[j] == -1 && !legalnoNosenje(tabla, 1, j)) {
                            tabla[j] = 0; //skidamo protivnikovu figuru
                            vrednost = min(tabla, alpha, beta, poslednjiPotezPozitivnog,
                                           poslednjiPotezNegativnog, dubina - 1, brojPoteza + 1, koef);
                            tabla[j] = -1; //vracamo kako je bilo posle evaluacije tog poteza
                            if (vrednost > maksimalnaVrednost) {
                                maksimalnaVrednost = vrednost;
                                //posto smo nasli bolji potez igramo ga
                                if (potez) {
                                    potez[0] = brojac; //igramo na poziciju brojac
                                    potez[2] = j; //nosimo figuru sa pozicije j
                                }
                            }
                            if (maksimalnaVrednost >= beta) {
                                tabla[brojac] = 0;
                                return maksimalnaVrednost;
                            }
                            if(maksimalnaVrednost > alpha)
                                alpha = maksimalnaVrednost;
                        }
                    }
                }
                else {
                    //ta pozicija na koju se igra ne pravi micu
                    poslednjiPotezPozitivnog = 0;

                    vrednost = min(tabla, alpha, beta, poslednjiPotezPozitivnog,
                                   poslednjiPotezNegativnog, dubina - 1, brojPoteza + 1, koef);
                    if (vrednost > maksimalnaVrednost) {
                        maksimalnaVrednost = vrednost;
                        if (potez) {
                            potez[0] = brojac;
                            potez[2] = -1;
                        }
                    }
                    if (maksimalnaVrednost >= beta) {
                        tabla[brojac] = 0;
                        return maksimalnaVrednost;
                    }
                    if (maksimalnaVrednost > alpha)
                        alpha = maksimalnaVrednost;
                }
                tabla[brojac] = 0;
            }
            //else nije legalan potez jer nije slobodna pozicija
        }
        //izvrteli smo sve kombinacije poteza i nosenja i vracamo maksimalnu vrednost
        return maksimalnaVrednost;
    }
    else {
        //proslo je postavljanje figura

        //izlaz iz rekurzije
        if (dubina == 0 || pobeda != 0) {
            if (rezultat[2] > 3 && rezultat[3] > 3) {
                //druga faza igre
                int brMicaIOtvorenih[3] = {0, 0, 0};
                miceIOtvoreneMice(tabla, brMicaIOtvorenih);

                return (koef[7] * (poslednjiPotezNegativnog + poslednjiPotezPozitivnog)) +
                       (koef[8] * brMicaIOtvorenih[0]) + (koef[9] * (rezultat[0] - rezultat[1])) +
                       (koef[10] * (rezultat[2] - rezultat[3])) + (koef[11] * brMicaIOtvorenih[1]) +
                       (koef[12] * brMicaIOtvorenih[2]) + (koef[13] * sloboda(tabla)) + (koef[14] * pobeda);
            }
            else {
                //treca faza igre
                int dvaITriKonf[2] = {0, 0};
                brojDvaITriKonfiguracija(tabla, dvaITriKonf);

                return (koef[15] * dvaITriKonf[0]) + (koef[16] * dvaITriKonf[1]) + (koef[17] * (poslednjiPotezNegativnog + poslednjiPotezPozitivnog)) +
                       (koef[18] * pobeda);
            }
        }


        //jos uvek se ne izlazi iz rekurzije vec igramo neki od poteza
        if (rezultat[2] > 3) {
            //pozitivni ima vise od 3 figure i igra po pravilima druge faze
            for (brojac = 0; brojac < 24; brojac++) {
                if (tabla[brojac] == 1) {
                    //naisli smo na nasu figuru i gledamo da li mozemo da igramo njome
                    int potezi[4] = {-101, -101, -101, -101};
                    moguciPoteziDrugaFaza(tabla, brojac, potezi);
                    int j;
                    for (j = 0; j < 4; j++)
                        if (potezi[j] != -101) {
                            //imamo poziciju na koju mozemo da odigramo (dakle sa brojac moze na potez[j])
                            tabla[brojac] = 0;
                            tabla[potezi[j]] = 1;

                            if (uMici(tabla, potezi[j])) {
                                poslednjiPotezPozitivnog = 1;
                                int k;
                                for (k = 0; k < 24; k++) {
                                    if (tabla[k] == -1 && !legalnoNosenje(tabla, 1, k)) {
                                        tabla[k] = 0;
                                        vrednost =  min(tabla, alpha, beta, poslednjiPotezPozitivnog,
                                                        poslednjiPotezNegativnog, dubina - 1, brojPoteza + 1, koef);
                                        tabla[k] = -1;
                                        if (vrednost > maksimalnaVrednost) {
                                            maksimalnaVrednost = vrednost;
                                            if (potez) {
                                                potez[0] = brojac;
                                                potez[1] = potezi[j];
                                                potez[2] = k;
                                            }
                                        }
                                        if (maksimalnaVrednost >= beta) {
                                            tabla[potezi[j]] = 0;
                                            tabla[brojac] = 1;
                                            return maksimalnaVrednost;
                                        }
                                        if (maksimalnaVrednost > alpha)
                                            alpha = maksimalnaVrednost;
                                    }
                                }
                            }
                            else {
                                //ta pozicija na koju se igra ne pravi micu
                                poslednjiPotezPozitivnog = 0;

                                vrednost =  min(tabla, alpha, beta, poslednjiPotezPozitivnog,
                                                poslednjiPotezNegativnog, dubina - 1, brojPoteza + 1, koef);
                                if (vrednost > maksimalnaVrednost) {
                                    maksimalnaVrednost = vrednost;
                                    if (potez) {
                                        potez[0] = brojac;
                                        potez[1] = potezi[j];
                                        potez[2] = -1;
                                    }
                                }                               
                                if (maksimalnaVrednost >= beta) {
                                    tabla[potezi[j]] = 0;
                                    tabla[brojac] = 1;                                    
                                    return maksimalnaVrednost;
                                }
                                if (maksimalnaVrednost > alpha)
                                    alpha = maksimalnaVrednost;
                            }
                            tabla[potezi[j]] = 0;
                            tabla[brojac] = 1;
                        }
                }
                //inace nije legalan potez
            }
            //izvrteli smo sve moguce poteze i sad vracamo vrednost
            return maksimalnaVrednost;
        }
        else {
            //pozitivni ima 3 figure i igra po pravilima trece faze
            for (brojac = 0; brojac < 24; brojac++) {
                if (tabla[brojac] == 1) {
                    int j;
                    for (j = 0; j < 24; j++) {
                        if (tabla[j] == 0) {
                            //mozemo da skocimo na tu poziciju
                            tabla[brojac] = 0;
                            tabla[j] = 1;

                            if (uMici(tabla, j)) {
                                poslednjiPotezPozitivnog = 1;
                                int k;
                                for (k = 0; k < 24; k++) {
                                    if (tabla[k] == -1 && !legalnoNosenje(tabla, 1, k)) {
                                        tabla[k] = 0;
                                        vrednost = min(tabla, alpha, beta, poslednjiPotezPozitivnog,
                                                       poslednjiPotezNegativnog, dubina - 1, brojPoteza + 1, koef);
                                        tabla[k] = -1;

                                        if (vrednost > maksimalnaVrednost) {
                                            maksimalnaVrednost = vrednost;
                                            if (potez) {
                                                potez[0] = brojac;
                                                potez[1] = j;
                                                potez[2] = k;
                                            }
                                        }
                                        if (maksimalnaVrednost >= beta) {
                                            tabla[j] = 0;
                                            tabla[brojac] = 1;
                                            return maksimalnaVrednost;
                                        }
                                        if (maksimalnaVrednost > alpha)
                                            alpha = maksimalnaVrednost;
                                    }
                                }
                            }
                            else {
                                //kad sa brojac odigramo na j ne previmo micu
                                poslednjiPotezPozitivnog = 0;
                                vrednost =  min(tabla, alpha, beta, poslednjiPotezPozitivnog,
                                                poslednjiPotezNegativnog, dubina - 1, brojPoteza + 1, koef);
                                if (vrednost > maksimalnaVrednost) {
                                    maksimalnaVrednost = vrednost;
                                    if (potez) {
                                        potez[0] = brojac;
                                        potez[1] = j;
                                        potez[2] = -1;
                                    }
                                }
                                if (maksimalnaVrednost >= beta) {
                                    tabla[j] = 0;
                                    tabla[brojac] = 1;
                                    return maksimalnaVrednost;
                                }
                                if (maksimalnaVrednost > alpha)
                                    alpha = maksimalnaVrednost;
                            }
                            tabla[j] = 0;
                            tabla[brojac] = 1;
                        }
                    }
                }
            }
            return maksimalnaVrednost;
        }
    }
}


void alphabeta(int tabla[24], int potez[3], int dubina, int brojPoteza, int koef[19]) {
    max(tabla, -30000, 30000, potez, -1, -1, dubina, brojPoteza, koef);
}
