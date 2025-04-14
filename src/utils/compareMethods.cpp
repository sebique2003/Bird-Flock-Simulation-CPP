//#include "Header.h"
//#include <iostream>
//#include <chrono>
//
//using namespace std;
//using namespace chrono;
//
//void compare_execution_times(const vector<Boid>& boids, int num_steps) {
//    cout << "\nComparare timpi de execuție pentru cele 3 metode de simulare:\n";
//
//    // Timp pentru secvențial
//    auto start_time = high_resolution_clock::now();
//    simulate_boids_sequential(boids, num_steps);
//    auto end_time = high_resolution_clock::now();
//    auto duration = duration_cast<milliseconds>(end_time - start_time);
//    cout << "Timp secvențial: " << duration.count() / 1000.0 << " secunde\n";
//
//    // Timp pentru OpenMP
//    start_time = high_resolution_clock::now();
//    simulate_boids_omp(boids, num_steps);
//    end_time = high_resolution_clock::now();
//    duration = duration_cast<milliseconds>(end_time - start_time);
//    cout << "Timp OpenMP: " << duration.count() / 1000.0 << " secunde\n";
//
//    // Timp pentru CUDA
//    start_time = high_resolution_clock::now();
//    simulate_boids_cuda(boids, num_steps);
//    end_time = high_resolution_clock::now();
//    duration = duration_cast<milliseconds>(end_time - start_time);
//    cout << "Timp CUDA: " << duration.count() / 1000.0 << " secunde\n";
//}
