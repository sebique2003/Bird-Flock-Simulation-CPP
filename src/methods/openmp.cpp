#include "Header.h"
#include <cmath>
#include <iostream>
#include <omp.h>

using namespace std;

void openmp(vector<Boid>& boizi, int nr_iteratii) {
    omp_set_num_threads(4);
    // parcurgem fiecare i al simularii
    for (int i = 0; i < nr_iteratii; ++i) {
        // cream o copie a boizilor pentru a nu afecta calculul curent
        vector<Boid> boizi_noi = boizi;

        // paralelizam procesarea fiecarui boid
        #pragma omp parallel for
        for (int i = 0; i < static_cast<int>(boizi.size()); i++) {
            // var pt regulile de baza
            float aliniere_x = 0, aliniere_y = 0;
            float coeziune_x = 0, coeziune_y = 0;
            float separare_x = 0, separare_y = 0;
            int numar_aliniere = 0, numar_coeziune = 0, numar_separare = 0;

            // calculam vecinii si regulile pt fiecare boid
            for (size_t j = 0; j < boizi.size(); j++) {
                if (i == j) continue;

                // calculam distanta dintre boidul curent si vecin
                float dx = boizi[j].pozitie_x - boizi[i].pozitie_x;
                float dy = boizi[j].pozitie_y - boizi[i].pozitie_y;
                float distanta_patrat = dx * dx + dy * dy;

                // ALINIERE - ajustam directia dupa vecini
                if (distanta_patrat < RAZA_ALINIERE * RAZA_ALINIERE) {
                    aliniere_x += boizi[j].viteza_x;
                    aliniere_y += boizi[j].viteza_y;
                    numar_aliniere++;
                }

                // COEZUNE - ne indreptam spre centrul grupului
                if (distanta_patrat < RAZA_COEZUNE * RAZA_COEZUNE) {
                    coeziune_x += boizi[j].pozitie_x;
                    coeziune_y += boizi[j].pozitie_y;
                    numar_coeziune++;
                }

                // SEPARARE - evitam vecinii prea apropiati
                if (distanta_patrat < RAZA_SEPARARE * RAZA_SEPARARE) {
                    separare_x -= dx;
                    separare_y -= dy;
                    numar_separare++;
                }
            }

            // ALINIERE
            if (numar_aliniere > 0) {
                aliniere_x /= numar_aliniere;
                aliniere_y /= numar_aliniere;
                float lungime_aliniere = sqrt(aliniere_x * aliniere_x + aliniere_y * aliniere_y);
                if (lungime_aliniere > 0) {
                    aliniere_x = aliniere_x / lungime_aliniere * VITEZA_MAXIMA;
                    aliniere_y = aliniere_y / lungime_aliniere * VITEZA_MAXIMA;
                }
                boizi_noi[i].viteza_x += aliniere_x * GREUTATE_ALINIERE;
                boizi_noi[i].viteza_y += aliniere_y * GREUTATE_ALINIERE;
            }

            // COEZIUNE
            if (numar_coeziune > 0) {
                coeziune_x = coeziune_x / numar_coeziune - boizi[i].pozitie_x;
                coeziune_y = coeziune_y / numar_coeziune - boizi[i].pozitie_y;
                float lungime_coeziune = sqrt(coeziune_x * coeziune_x + coeziune_y * coeziune_y);
                if (lungime_coeziune > 0) {
                    coeziune_x = coeziune_x / lungime_coeziune * VITEZA_MAXIMA;
                    coeziune_y = coeziune_y / lungime_coeziune * VITEZA_MAXIMA;
                }
                boizi_noi[i].viteza_x += coeziune_x * GREUTATE_COEZUNE;
                boizi_noi[i].viteza_y += coeziune_y * GREUTATE_COEZUNE;
            }

            // SEPARARE
            if (numar_separare > 0) {
                separare_x /= numar_separare;
                separare_y /= numar_separare;
                float lungime_separare = sqrt(separare_x * separare_x + separare_y * separare_y);
                if (lungime_separare > 0) {
                    separare_x = separare_x / lungime_separare * VITEZA_MAXIMA;
                    separare_y = separare_y / lungime_separare * VITEZA_MAXIMA;
                }
                boizi_noi[i].viteza_x += separare_x * GREUTATE_SEPARARE;
                boizi_noi[i].viteza_y += separare_y * GREUTATE_SEPARARE;
            }

            // limitam viteza la VITEZA_MAXIMA
            float viteza = sqrt(boizi_noi[i].viteza_x * boizi_noi[i].viteza_x +
                boizi_noi[i].viteza_y * boizi_noi[i].viteza_y);
            if (viteza > VITEZA_MAXIMA) {
                boizi_noi[i].viteza_x = (boizi_noi[i].viteza_x / viteza) * VITEZA_MAXIMA;
                boizi_noi[i].viteza_y = (boizi_noi[i].viteza_y / viteza) * VITEZA_MAXIMA;
            }

            // actualizam poz pe baza vitezei
            boizi_noi[i].pozitie_x += boizi_noi[i].viteza_x;
            boizi_noi[i].pozitie_y += boizi_noi[i].viteza_y;
        }

        // actualizam stare totala a boizilor
        boizi = boizi_noi;
    }
}