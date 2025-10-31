#include "Header.h"
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <cmath>

// kernel pentru a calcula mișcarea boizilor
__global__ void kernel (Boid* boizi, Boid* boizi_noi, int numar_boizi) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i >= numar_boizi) return;

	// def parametrii pentru reguli
    float aliniere_x = 0, aliniere_y = 0;
    float coeziune_x = 0, coeziune_y = 0;
    float separare_x = 0, separare_y = 0;
    int numar_aliniere = 0, numar_coeziune = 0, numar_separare = 0;

	// parcurgem boizii pentru a aplica regulile de aliniere, coeziune si separare
    for (int j = 0; j < numar_boizi; ++j) {
        if (i == j) continue;

        float dx = boizi[j].pozitie_x - boizi[i].pozitie_x;
        float dy = boizi[j].pozitie_y - boizi[i].pozitie_y;
        float distanta_patrat = dx * dx + dy * dy;

		// reguli de aliniere, coeziune si separare
        if (distanta_patrat < RAZA_ALINIERE * RAZA_ALINIERE) {
            aliniere_x += boizi[j].viteza_x;
            aliniere_y += boizi[j].viteza_y;
            numar_aliniere++;
        }
        if (distanta_patrat < RAZA_COEZUNE * RAZA_COEZUNE) {
            coeziune_x += boizi[j].pozitie_x;
            coeziune_y += boizi[j].pozitie_y;
            numar_coeziune++;
        }
        if (distanta_patrat < RAZA_SEPARARE * RAZA_SEPARARE) {
            separare_x -= dx;
            separare_y -= dy;
            numar_separare++;
        }
    }

	// actualizăm viteza și poziția boidului
    Boid boid_nou = boizi[i];

    // aliniere
    if (numar_aliniere > 0) {
        aliniere_x /= numar_aliniere;
        aliniere_y /= numar_aliniere;
        float lungime = sqrtf(aliniere_x * aliniere_x + aliniere_y * aliniere_y);
        if (lungime > 0) {
            aliniere_x = aliniere_x / lungime * VITEZA_MAXIMA;
            aliniere_y = aliniere_y / lungime * VITEZA_MAXIMA;
        }
        boid_nou.viteza_x += aliniere_x * GREUTATE_ALINIERE;
        boid_nou.viteza_y += aliniere_y * GREUTATE_ALINIERE;
    }

    // coeziune
    if (numar_coeziune > 0) {
        coeziune_x /= numar_coeziune;
        coeziune_y /= numar_coeziune;
        float dx = coeziune_x - boizi[i].pozitie_x;
        float dy = coeziune_y - boizi[i].pozitie_y;
        float lungime = sqrtf(dx * dx + dy * dy);
        if (lungime > 0) {
            dx = dx / lungime * VITEZA_MAXIMA;
            dy = dy / lungime * VITEZA_MAXIMA;
        }
        boid_nou.viteza_x += dx * GREUTATE_COEZUNE;
        boid_nou.viteza_y += dy * GREUTATE_COEZUNE;
    }

    // separare
    if (numar_separare > 0) {
        separare_x /= numar_separare;
        separare_y /= numar_separare;
        float lungime = sqrtf(separare_x * separare_x + separare_y * separare_y);
        if (lungime > 0) {
            separare_x = separare_x / lungime * VITEZA_MAXIMA;
            separare_y = separare_y / lungime * VITEZA_MAXIMA;
        }
        boid_nou.viteza_x += separare_x * GREUTATE_SEPARARE;
        boid_nou.viteza_y += separare_y * GREUTATE_SEPARARE;
    }

    // limitam viteza
    float viteza = sqrtf(boid_nou.viteza_x * boid_nou.viteza_x + boid_nou.viteza_y * boid_nou.viteza_y);
    if (viteza > VITEZA_MAXIMA) {
        boid_nou.viteza_x = (boid_nou.viteza_x / viteza) * VITEZA_MAXIMA;
        boid_nou.viteza_y = (boid_nou.viteza_y / viteza) * VITEZA_MAXIMA;
    }

    // actualizam pozitia
    boid_nou.pozitie_x += boid_nou.viteza_x;
    boid_nou.pozitie_y += boid_nou.viteza_y;

    boizi_noi[i] = boid_nou;
}

void cuda(vector<Boid>& boizi, int nr_iteratii) {
    Boid* d_boizi, * d_boizi_noi;
    int numar_boizi = static_cast<int>(boizi.size());
    size_t size = numar_boizi * sizeof(Boid);

    // alocam mem pe GPU
    cudaMalloc(&d_boizi, size);
    cudaMalloc(&d_boizi_noi, size);

	// copiem datele de pe CPU pe GPU
    cudaMemcpy(d_boizi, boizi.data(), size, cudaMemcpyHostToDevice);

	// def dimensiuni grid si bloc
    int blockSize = 256;
    int gridSize = (numar_boizi + blockSize - 1) / blockSize;

	// rulam kernel-ul pentru nr de ii specificat
    for (int i = 0; i < nr_iteratii; ++i) {
        kernel << <gridSize, blockSize >> > (d_boizi, d_boizi_noi, numar_boizi);
        cudaDeviceSynchronize();

		// coperim rezultatele de la GPU inapoi pe GPU
        cudaMemcpy(d_boizi, d_boizi_noi, size, cudaMemcpyDeviceToDevice);
    }

    cudaMemcpy(boizi.data(), d_boizi, size, cudaMemcpyDeviceToHost);

	// eliberam memoria GPU
    cudaFree(d_boizi);
    cudaFree(d_boizi_noi);
}