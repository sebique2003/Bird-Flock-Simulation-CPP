#ifndef BOIDS_H
#define BOIDS_H

#include <vector>
using namespace std;

// constante comportament boizi / pasari
#define RAZA_ALINIERE 20.0f       // raza pentru regula de aliniere
#define RAZA_COEZUNE 20.0f        // raza pentru regula de coeziune
#define RAZA_SEPARARE 10.0f       // raza pentru regula de separare

#define VITEZA_MAXIMA 2.0f        // viteza max
#define GREUTATE_ALINIERE 1.0f    // imp alinierii
#define GREUTATE_COEZUNE 1.0f     // imp coeziunii
#define GREUTATE_SEPARARE 1.5f    // imp separarii

// structura pentru un boid (PASARE)
struct Boid {
    float pozitie_x, pozitie_y;   // poz curenta
    float viteza_x, viteza_y;     // viteza curenta
};

// fct secvential
void secvential(vector<Boid>& boizi, int nr_iteratii);
// fct OpenMP
void openmp(vector<Boid>& boizi, int nr_iteratii);
// fct CUDA
void cuda(vector<Boid>& boizi, int numar_pasi);
// fct pentru compararea timpilor de executie
void compareMethods(vector<Boid>& boids, int nr_iteratii);

#endif