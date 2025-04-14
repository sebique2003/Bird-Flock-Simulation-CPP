#include "Header.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <iomanip>

using namespace std;
using namespace chrono;

void labelProiect() {
    cout << "=======================================\n";
    cout << "        BIRD FLOCK SIMULATION\n";
    cout << "=======================================\n";
    cout << " Universitatea Transilvania din Brasov\n";
    cout << " Specializare: Tehnologia Informatiei\n";
    cout << " Student: Iordache Sebastian-Ionut\n";
    cout << " Grupa: 4LF321B\n";
    cout << " Curs: Programare Paralela\n";
    cout << "=======================================\n";
    cout << "    Secvential vs OpenMP vs CUDA\n";
    cout << "=======================================\n\n";
}

int main() {
	// eticheta proiect
    labelProiect();

	// initializare variabile
    int numar_boizi, nr_iteratii;
    vector<Boid> boizi;

    cout << "------------------------------------------------\n";
	// afisare nr pasari
    cout << "Introduceti numarul de boids (pasari): ";
    cin >> numar_boizi;

	// generare random pentru pozitie si viteza
    srand(static_cast<unsigned>(time(nullptr)));
    boizi.resize(numar_boizi);
    for (int i = 0; i < numar_boizi; ++i) {
        boizi[i].pozitie_x = static_cast<float>(rand() % 100);
        boizi[i].pozitie_y = static_cast<float>(rand() % 100);
        boizi[i].viteza_x = static_cast<float>(rand() % 200 - 100) / 50.0f;
        boizi[i].viteza_y = static_cast<float>(rand() % 200 - 100) / 50.0f;
    }

	// afisare nr iteratii
    cout << "Introduceti numarul de iteratii (miscari): ";
    cin >> nr_iteratii;
    cout << "------------------------------------------------\n";

    while (true) {
        cout << "\n=================== MENIU PRINCIPAL ===================\n";
        cout << " 1. Secvential\n";
		cout << " 2. OpenMP\n";
		cout << " 3. CUDA\n";
        cout << " 4. Compara metodele (Secvential / OpenMP / CUDA)\n";
        cout << " 5. Exit\n";
        cout << "=======================================================\n";
        cout << " Alegeti optiunea (1 - 5): ";

        int optiune;
        cin >> optiune;

        switch (optiune) {
		    // secvential
        case 1: 
        {
            cout << "\n>>> Rulare simulare secvential...\n";
            auto startTime = high_resolution_clock::now();
            secvential(boizi, nr_iteratii);
            auto endTime = high_resolution_clock::now();

            duration<double> duration_sec = endTime - startTime;
            cout << fixed << setprecision(3);
            cout << "\n### Timp de executie (Secvential): " << duration_sec.count() << " secunde\n";
            break;
        }
		    // OpenMP
        case 2: 
        {
            cout << "\n>>> Rulare simulare OpenMP...\n";
            auto startTimeOMP = high_resolution_clock::now();
            openmp(boizi, nr_iteratii);
            auto endTimeOMP = high_resolution_clock::now();
            duration<double> duration_omp = endTimeOMP - startTimeOMP;
            cout << fixed << setprecision(3);
            cout << "\n### Timp de executie (OpenMP): " << duration_omp.count() << " secunde\n";
            break;
        }
		case 3:
		    // CUDA
        {
			cout << "\n>>> Rulare simulare CUDA...\n";
			auto startTimeCUDA = high_resolution_clock::now();
			cuda(boizi, nr_iteratii);
			auto endTimeCUDA = high_resolution_clock::now();
			duration<double> duration_cuda = endTimeCUDA - startTimeCUDA;
			cout << fixed << setprecision(3);
			cout << "\n### Timp de executie (CUDA): " << duration_cuda.count() << " secunde\n";
			break;
		}
		case 4:
		    // comparare metode
        {
			cout << "\n>>> Comparare timp executie pentru toate cele trei metode...\n";
			auto startTimeComp = high_resolution_clock::now();
            compareMethods(boizi, nr_iteratii);
			auto endTimeComp = high_resolution_clock::now();
			duration<double> duration_comp = endTimeComp - startTimeComp;
			break;
		}
        case 5:
            cout << "\n>>> Iesire din program...\n";
            return 0;
        default:
            cout << "\n>>> Optiune invalida! Incearca din nou.\n";
        }
    }

    return 0;
}
