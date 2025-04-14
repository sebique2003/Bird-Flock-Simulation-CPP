#include "Header.h"
#include <iostream>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

void compareMethods(vector<Boid>& boids, int nr_iteratii) {
	// copiem vectorul de boizi pentru fiecare metoda
    vector<Boid> boizi_secvential = boids;
    vector<Boid> boizi_openmp = boids;
    vector<Boid> boizi_cuda = boids;

    cout << fixed << setprecision(3);

    // secvential
    auto start_time = high_resolution_clock::now();
    secvential(boizi_secvential, nr_iteratii);
    auto end_time = high_resolution_clock::now();
    duration<double> duration_sec = end_time - start_time;
    cout << "\n### Timp de executie (Secvential): " << duration_sec.count() << " secunde\n";

    // openmp
    start_time = high_resolution_clock::now();
    openmp(boizi_openmp, nr_iteratii);
    end_time = high_resolution_clock::now();
    duration<double> duration_omp = end_time - start_time;
    cout << "\n### Timp de executie (OpenMP): " << duration_omp.count() << " secunde\n";

    // cuda
    start_time = high_resolution_clock::now();
    cuda(boizi_cuda, nr_iteratii);
    end_time = high_resolution_clock::now();
    duration<double> duration_cuda = end_time - start_time;
    cout << "\n### Timp de executie (CUDA): " << duration_cuda.count() << " secunde\n";
}
