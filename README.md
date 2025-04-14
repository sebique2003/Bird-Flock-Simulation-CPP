# 🌀 Bird Flock Simulation  - Proiect (Secvențial vs. OpenMP vs. CUDA)

> 📚 Proiect realizat în cadrul cursului de Programare Paralelă, Universitatea Transilvania Brașov.

## 📌 Descriere Proiect

#### Acest proiect implementează Algoritmul Boids pentru simularea comportamentului de grup al păsărilor, folosind trei metode:
  - 🔹 **Secvential** - implementare simplă, pe un singur thread
  - ⚙️ **OpenMP** - paralelizare pe CPU, utilizând mai multe fire de execuție
  - 🚀 **CUDA** - paralelizare pe GPU, maximizând performanța prin procesare masiv paralelă


## 🧠 Algoritmul Boids

### Simularea urmărește 3 reguli de bază:

#### 1.  **Aliniere** - fiecare boid tinde să se alinieze cu direcția de deplasare a vecinilor
#### 2.  **Coeziune** - fiecare boid tinde să se apropie de centrul de masă al vecinilor
#### 3.  **Separare** - fiecare boid tinde să evite coliziunile cu vecinii foarte apropiați

## 🐢 Implementare Secvențială

### 🔄 Pași principali:

#### 1. Fiecare boid analizează poziția și viteza tuturor celorlalți boizi.
#### 2. Aplică cele 3 reguli de mișcare:
  - **Aliniere**
  - **Coeziune**
  - **Separare**
#### 3. Se actualizează viteza și poziția fiecărui boid.
#### 4. Se repetă pașii pentru fiecare iterație a simulării.

### 🔍 Cod
```cpp
for (int pas = 0; pas < nr_iteratii; ++pas) {
    for (int i = 0; i < boizi.size(); i++) {
        // calculează influențele vecinilor
        // aplică aliniere, coeziune, separare
        // actualizează poziția și viteza
    }
}
```

## ⚙️ Paralelizarea cu OpenMP

OpenMP permite distribuirea calculelor între mai multe nuclee ale procesorului, accelerând simularea.

### 🧠 Ideea de bază:
Fiecare thread procesează un subset de boizi, calculând regulile de mișcare independent.

### 🔍 Cod
```cpp
#pragma omp parallel for
for (int i = 0; i < static_cast<int>(boizi.size()); i++) {
    // Calculăm influențele vecinilor
    // Aplicăm cele 3 reguli de bază: aliniere, coeziune, separare
    // Limităm viteza și actualizăm poziția
}
```

## ⚡ Paralelizarea cu CUDA

CUDA este o tehnologie dezvoltată de NVIDIA care permite rularea codului pe GPU. Este extrem de eficientă pentru calcule paralele de mari dimensiuni.

### 🧠 Ideea de bază:
Fiecare boid este procesat de un thread CUDA. Fiecare thread GPU calculează regulile de mișcare pentru un singur boid.

### 🔍 Cod
```cpp
__global__ void kernel(Boid* boizi, Boid* boizi_noi, int numar_boizi) {
    // 1. Calculăm influențele vecinilor pentru fiecare boid
    // 2. Aplicăm regulile de aliniere, coeziune și separare
    // 3. Actualizăm viteza și poziția fiecărui boid
}
```
```cpp
void cuda(vector<Boid>& boizi, int nr_iteratii) {
    // 1. Alocăm și copiem datele pe GPU
    // 2. Rulăm kernel-ul pe GPU pentru fiecare iterație
    // 3. Copiem rezultatele înapoi pe CPU și eliberăm memoria GPU
```

## 🧪 Test Performanță

### Test realizat pe un sistem cu:
- CPU: Intel Core i5-9300H (4 nuclee, până la 4.1 GHz).
- GPU: NVIDIA GeForce GTX 1650 4GB GDDR5.

### Exemplu de performanță:
| **Nr.  boizi**     | **Nr.  iteratii** | **Secvențial** | **OpenMP** | **CUDA** |
|--------------------|-------------------|----------------|------------|----------|
| 50                 | 25                | 0.004 sec      | 0.001 sec  | 0.044 sec|
| 500                | 100               | 0.729 sec      | 0.299 sec  | 1.260 sec|
| 1000               | 150               | 3.956 sec      | 1.586 sec  | 0.561 sec|
| 5000               | 200               | 128.367 sec    | 53.623 sec | 2.602 sec|

### 📊 Observații:
- Pentru un număr mare de boizi (ex: 1000+), CUDA oferă cele mai bune performanțe.
- OpenMP este o soluție intermediară foarte bună, ușor de implementat.
- Secvențialul este util doar pentru testare sau un număr mic de boizi.

 ## 🛠 Cum să rulezi?

### 1. Clonează repository-ul
 ```bash
git clone https://github.com/sebique2003/Bird-Flock-Simulation-CPP
cd Bird-Flock-Simulation-CPP
```
### 2. Compilare

Asigură-te că ai:
- Un compilator C++ (ex: g++)
- Suport pentru OpenMP (opțional, pentru paralelizare pe CPU)
- CUDA Toolkit instalat (opțional, pentru paralelizare pe GPU)
  
Apoi compilează:
```bash
make all
```

### 3. Rulare
```bash
./bird_flock_simulation
```

> Proiect realizat de [Iordache Sebastian-Ionut] © 2025





