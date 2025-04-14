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
    cout << "\tBIRD FLOCK SIMULATION\n";
    cout << "=======================================\n";
    cout << "Universitatea Transilvania din Brasov\n";
    cout << "Specializare: Tehnologia Informatiei\n";
    cout << "Student: Iordache Sebastian-Ionut\n";
    cout << "Grupa: 4LF321B\n";
    cout << "Curs: Programare Paralela\n";
    cout << "=======================================\n";
    cout << "\Secvential vs OpenMP vs CUDA\n";
    cout << "=======================================\n\n";
}

int main() {
    labelProiect();

    int numar_boizi, numar_pasi;
    vector<Boid> boizi;

    cout << "-------------------------------------------\n";
    cout << "Introduceti numarul de pasari: ";
    cin >> numar_boizi;

    srand(static_cast<unsigned>(time(nullptr)));
    boizi.resize(numar_boizi);
    for (int i = 0; i < numar_boizi; ++i) {
        boizi[i].pozitie_x = rand() % 100;
        boizi[i].pozitie_y = rand() % 100;
        boizi[i].viteza_x = static_cast<float>(rand() % 200 - 100) / 50.0f;
        boizi[i].viteza_y = static_cast<float>(rand() % 200 - 100) / 50.0f;
    }

    cout << "Introduceti numarul de iteratii: ";
    cin >> numar_pasi;
    cout << "-------------------------------------------\n";

    while (true) {
        cout << "\n=================== MENIU PRINCIPAL ===================\n";
        cout << " 1. Secvential\n";
        cout << " 2. Compara metodele (Secvential / OpenMP / CUDA)\n";
        cout << " 3. Exit\n";
        cout << "=======================================================\n";
        cout << " Alegeti optiunea (1 - 3): ";

        int optiune;
        cin >> optiune;

        switch (optiune) {
        case 1: {
            cout << "\n>>> Rulare simulare secventiala...\n";
            auto startTime = high_resolution_clock::now();
            simuleaza_boizi_secvential(boizi, numar_pasi);
            auto endTime = high_resolution_clock::now();

            duration<double> duration_sec = endTime - startTime;
            cout << std::fixed << setprecision(3);
            cout << "\n### Timp de executie (Secvential): " << duration_sec.count() << " secunde\n";
            break;
        }
        case 2:
            cout << "\n>>> Comparatie intre metode...\n";
            cout << ">>> Functionalitatea va fi implementata ulterior.\n";
            break;
        case 3:
            cout << "\n>>> Iesire din program...\n";
            return 0;
        default:
            cout << "\n>>> Optiune invalida! Incearca din nou.\n";
        }
    }

    return 0;
}
