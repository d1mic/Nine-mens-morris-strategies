#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

#include "heuristike.h"
#include "pravila.h"
#include "alphabeta.h"

#define dubinaStabla 5 //easy = 7, noraml = 8, hard = 9 (ako hoces da cekas do sutra)



int main() {

    int brojIgrca = 0;
    int brojProtivnika = 0;

  /*
    std::cout << "Da li zelite da ucitate podatke iz fajla ili rucno: f/r: ";
    char tipUnosa;
    std::cin >> tipUnosa;

    if (tipUnosa == 'r') {


        int igraci[brojIgrca][19];
        int protivnici[brojProtivnika][19];

        char indIgraci;
        do {
            std::cout << "Unesite broj igraca" << std::endl;
            std::cin >> brojIgrca;
            std::cout << "Uneli ste: " << brojIgrca << " Potvrdite sa y/n" << std::endl;
            std::cin >> indIgraci;
        } while (indIgraci != 'y');


        int i;
        int j;
        char indPojedinacni;

        for (i = 0; i < brojIgrca; i++) {
            do {
                std::cout << "Unesite koeficijente za igraca br: " << i << std::endl;
                for (j = 0; j < 19; j++) {
                    std::cin >> igraci[i][j];
                }
                std::cout << "Uneli ste sledeci vektor: ";
                for (j = 0; j < 19; j++) {
                    std::cout << igraci[i][j] << " ";
                }
                std::cout << "Potvrdite y/n" << std::endl;
                std::cin >> indPojedinacni;
            } while(indPojedinacni != 'y');
            indPojedinacni = 'n';
        }

        brojProtivnika = 0;
        char indProtivnici;

        do {
            std::cout << "Unesite broj protivnika" << std::endl;
            std::cin >> brojProtivnika;
            std::cout << "Uneli ste: " << brojProtivnika << " Potvrdite sa y/n" << std::endl;
            std::cin >> indProtivnici;
        } while (indProtivnici != 'y');

        indPojedinacni = 'n';

        for (i = 0; i < brojProtivnika; i++) {
            do {
                std::cout << "Unesite koeficijente za protivnika br: " << i << std::endl;
                for (j = 0; j < 19; j++) {
                    std::cin >> protivnici[i][j];
                }
                std::cout << "Uneli ste sledeci vektor: ";
                for (j = 0; j < 19; j++) {
                    std::cout << protivnici[i][j] << " ";
                }
                std::cout << "Potvrdite y/n" << std::endl;
                std::cin >> indPojedinacni;
            } while(indPojedinacni != 'y');
            indPojedinacni = 'n';
        }
    }
    else if (tipUnosa == 'f') {
*/


        std::fstream input;
        input.open("unos.txt", std::fstream::in);

        brojIgrca = 0;
        input >> brojIgrca;

        brojProtivnika = 0;
        input >> brojProtivnika;

        int igraci[brojIgrca][19];
        int protivnici[brojProtivnika][19];

        for (int i = 0; i < brojIgrca; i++) {
            for (int j = 0; j < 19; j++) {
                input >> igraci[i][j];
            }
        }

        for (int i = 0; i < brojProtivnika; i++) {
            for (int j = 0; j < 19; j++) {
                input >> protivnici[i][j];
            }
        }





    int tabla[24] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    std::fstream fs;
    fs.open ("rezultat.txt", std::fstream::out);

    int brojacIgraca;
    int brojacProtivnika;

    for (brojacIgraca = 0; brojacIgraca < brojIgrca; brojacIgraca++) {
        int fitnes = 0;
        for (brojacProtivnika = 0; brojacProtivnika < brojProtivnika; brojacProtivnika++) {
            fs << "Pocinje meci izmedju igraca: " << brojacIgraca << " i protivnika: " << brojacProtivnika << std::endl;

            for (int i = 0; i < 24; i++)
                tabla[i] = 0;

            int brojPoteza = 1;
            int dubina = dubinaStabla;
            int fazaIgre = 1;


            srand(time(nullptr));
            int random = std::rand() % 3;

            if (random == 0) {
                tabla[4] = 1;
            }
            if (random == 1) {
                tabla[10] = 1;
            }
            if (random == 2) {
                tabla[19] = 1;
            }
            if (random == 3) {
                tabla[13] = 1;
            }


            int potez[3] = {-1, -1, -1};
            int pobeda = 0;

            while (1) {
                //protivnik je na potezu
                if (brojPoteza == 18)
                    fazaIgre = 2;

                int rezultat[4] = {0, 0, 0, 0};
                brojBlokiranih(tabla, rezultat);

                if (brojPoteza == 2 || brojPoteza == 3 || brojPoteza == 4 || rezultat[2] == 3 || rezultat[3] == 3)
                    dubina = dubinaStabla - 1;
                else {
                    dubina = dubinaStabla;
                }


                int t;
                for (t = 0; t < 24; t++)
                    if (tabla[t] == 1)
                        tabla[t] = -1;
                    else if (tabla[t] == -1)
                             tabla[t] = 1;

                alphabeta(tabla, potez, dubina, brojPoteza, protivnici[brojacProtivnika]);
                //kupimo protivnikov potez i odigravamo ga

                if (potez[1] == -1) {
                    tabla[potez[0]] = 1;
                    if (potez[2] != -1)
                        tabla[potez[2]] = 0;
                }
                else {
                    tabla[potez[0]] = 0;
                    tabla[potez[1]] = 1;
                    if (potez[2] != -1)
                        tabla[potez[2]] = 0;
                }

                brojBlokiranih(tabla, rezultat);


                if (fazaIgre != 1 && (rezultat[3] == 2 || rezultat[3] == rezultat[1]))
                    pobeda = 1;
                else
                    if (fazaIgre != 1 && (rezultat[2] == 2 || rezultat[2] == rezultat[0]))
                        pobeda = -1;
                    else
                        pobeda = 0;


                // ovo je za prvu fazu igre jer iako nije moguce da u prvoj vazi igre
                // neko nekom odnese 7 figura, moguce je da posle postavljanja poslenje figure sve
                // figure ostanu blokirane
               if (rezultat[3] == 9 && rezultat[3] == rezultat[1])
                   pobeda = 1;
               else
                   if (rezultat[2] == 9 && rezultat[2] == rezultat[0])
                       pobeda = -1;


                potez[0] = -1;
                potez[1] = -1;
                potez[2] = -1;

                if(pobeda == 1) {
                    //pobedio je igrac
                    fs << "Pobedio je protivnik. Score: -7"  << std::endl;
                    fitnes -= 7;
                    fs.flush();
                    break;
                }
                if(pobeda == -1) {
                    //pobedio je protivnik
                    fs << "Pobedio je igrac. Score: +7" << std::endl;
                    fitnes += 7;
                    fs.flush();
                    break;
                }


                if (brojPoteza > 45 && (rezultat[2] == rezultat[3])) {
                    fs << "Nereseno. Score: +0" << std::endl;
                    fs.flush();
                    break;
                }

                if (brojPoteza > 85 && (rezultat[2] == rezultat[3])) {
                    fs << "Nereseno. Score: +0 "<< std::endl;
                    fs.flush();
                    break;
                }
                else if (brojPoteza > 85 && (rezultat[2] > rezultat[3])) {
                    fs << "Sudijskom odlukom pobedio je protivnik. Score: -2" << std::endl;
                    fitnes -= 2;
                    fs.flush();
                    break;
                }
                else if (brojPoteza > 85 && (rezultat[2] < rezultat[3])) {
                    fs << "Sudijskom odlukom pobedio je igrac. Score: +2" << std::endl;
                    fitnes += 2;
                    fs.flush();
                    break;
                }



                brojPoteza++;

                if (brojPoteza == 18)
                    fazaIgre = 2;

                if ((brojPoteza >= 18)) {
                    dubina = dubinaStabla + 1;
                }
                else if (brojPoteza == 2 || brojPoteza == 3 || brojPoteza == 4 || brojPoteza == 5)
                    dubina = dubinaStabla - 1;
                else {
                    dubina = dubinaStabla;
                }


                for (t = 0; t < 24; t++)
                    if (tabla[t] == 1)
                        tabla[t] = -1;
                    else if (tabla[t] == -1)
                             tabla[t] = 1;


                //igrac je na potezu
                alphabeta(tabla, potez, dubina, brojPoteza, igraci[brojacIgraca]);
                //kupimo igracev potez i odigravamo ga


                if (potez[1] == -1) {
                    tabla[potez[0]] = 1;
                    if (potez[2] != -1)
                        tabla[potez[2]] = 0;
                }
                else {
                    tabla[potez[0]] = 0;
                    tabla[potez[1]] = 1;
                    if (potez[2] != -1)
                        tabla[potez[2]] = 0;
                }

                int pom;
                for (pom = 0; pom < 4; pom++)
                    rezultat[pom] = 0;
                brojBlokiranih(tabla, rezultat);


                if (fazaIgre != 1 && (rezultat[3] == 2 || rezultat[3] == rezultat[1]))
                    pobeda = 1;
                else
                    if (fazaIgre != 1 && (rezultat[2] == 2 || rezultat[2] == rezultat[0]))
                        pobeda = -1;
                    else
                        pobeda = 0;


                // ovo je za prvu fazu igre jer iako nije moguce da u prvoj vazi igre
                // neko nekom odnese 7 figura, moguce je da posle postavljanja poslenje figure sve
                // figure ostanu blokirane
               if (rezultat[3] == 9 && rezultat[3] == rezultat[1])
                   pobeda = 1;
               else
                   if (rezultat[2] == 9 && rezultat[2] == rezultat[0])
                       pobeda = -1;


                potez[0] = -1;
                potez[1] = -1;
                potez[2] = -1;

                if(pobeda == 1) {
                    //pobedio je igrac
                    fs << "Pobedio je igrac. Score: +7"  << std::endl;
                    fitnes += 7;
                    fs.flush();
                    break;
                }
                if(pobeda == -1) {
                    //pobedio je protivnik
                    fs << "Pobedio je protivnik. Score: -7" << std::endl;
                    fitnes -= 7;
                    fs.flush();
                    break;
                }


                if (brojPoteza > 45 && (rezultat[2] == rezultat[3])) {
                    fs << "Nereseno. Score: +0" << std::endl;
                    fs.flush();
                    break;
                }

                if (brojPoteza > 85 && (rezultat[2] == rezultat[3])) {
                    fs << "Nereseno. Score: +0" << std::endl;
                    fs.flush();
                    break;
                }
                else if (brojPoteza > 85 && (rezultat[2] < rezultat[3])) {
                    fs << "Sudijskom odlukom pobedio je protivnik. Score: -2" << std::endl;
                    fitnes -= 2;
                    fs.flush();
                    break;
                }
                else if (brojPoteza > 85 && (rezultat[2] > rezultat[3])) {
                    fs << "Sudijskom odlukom pobedio je igrac. Score: +2" << std::endl;
                    fitnes += 2;
                    fs.flush();
                    break;
                }

                brojPoteza++;

            }
        }
        fs << "Igrac " << brojacIgraca << " ima fitness: " <<  fitnes << std::endl;
        fs.flush();
    }
    fs.flush();
    fs.close();

    return 0;
}



