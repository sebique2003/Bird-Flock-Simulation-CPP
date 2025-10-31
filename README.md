# 🌀 Bird Flock Simulation  - Project (Sequential vs. OpenMP vs. CUDA)

> 📚 Project developed for the Parallel Programming course, Transilvania University of Brașov.

## 📌 Project Description

#### This project implements the Boids Algorithm to simulate bird flocking behavior, using three approaches:
  - 🔹 **Sequential** - simple implementation, single-threaded
  - ⚙️ **OpenMP** - CPU parallelization using multiple threads
  - 🚀 **CUDA** - GPU parallelization, maximizing performance through massive parallel processing

## 🧠 Boids Algorithm

### The simulation follows 3 basic rules:

#### 1.  **Alignment** - each boid tends to align with the direction of nearby neighbors
#### 2.  **Cohesion** - each boid tends to move towards the center of mass of nearby neighbors
#### 3.  **Separation** - each boid tries to avoid collisions with very close neighbors

## 🐢 Sequential Implementation

### 🔄 Main Steps:

#### 1. Each boid analyzes the position and velocity of all other boids.
#### 2. Applies the 3 movement rules:
  - **Alignment**
  - **Cohesion**
  - **Separation**
#### 3. Updates the velocity and position of each boid.
#### 4. Repeats the steps for each simulation iteration.

### 🔍 Code
```cpp
for (int step = 0; step < num_iterations; ++step) {
    for (int i = 0; i < boids.size(); i++) {
        // calculate neighbor influences
        // apply alignment, cohesion, separation
        // update position and velocity
    }
}
```

## ⚙️ Parallelization with OpenMP

OpenMP allows distributing computations across multiple CPU cores, speeding up the simulation.

### 🧠 Basic Idea:
Each thread processes a subset of boids, independently calculating movement rules.

### 🔍 Code
```cpp
#pragma omp parallel for
for (int i = 0; i < static_cast<int>(boids.size()); i++) {
    // Calculate neighbor influences
    // Apply the 3 basic rules: alignment, cohesion, separation
    // Limit velocity and update position
}
```

## ⚡ Parallelization with CUDA

CUDA is a technology developed by NVIDIA that enables running code on the GPU. It is extremely efficient for large-scale parallel computations.

### 🧠 Basic Idea:
Each boid is processed by a CUDA thread. Each GPU thread computes movement rules for a single boid.

### 🔍 Code
```cpp
__global__ void kernel(Boid* boids, Boid* new_boids, int num_boids) {
    // 1. Calculate neighbor influences for each boid
    // 2. Apply alignment, cohesion and separation rules
    // 3. Update velocity and position for each boid
}
```
```cpp
void cuda(vector<Boid>& boids, int num_iterations) {
    // 1. Allocate and copy data to GPU
    // 2. Run the kernel on GPU for each iteration
    // 3. Copy results back to CPU and free GPU memory
```

## 🧪 Performance Test

### Test performed on a system with:
- CPU: Intel Core i5-9300H (4 cores, up to 4.1 GHz).
- GPU: NVIDIA GeForce GTX 1650 4GB GDDR5.

### Example performance:
| **Nr. boids**     | **Nr. iterations** | **Sequential** | **OpenMP** | **CUDA** |
|-------------------|-------------------|----------------|------------|----------|
| 50                | 25                | 0.004 sec      | 0.001 sec  | 0.044 sec|
| 500               | 100               | 0.729 sec      | 0.299 sec  | 1.260 sec|
| 1000              | 150               | 3.956 sec      | 1.586 sec  | 0.561 sec|
| 5000              | 200               | 128.367 sec    | 53.623 sec | 2.602 sec|

### 📊 Observations:
- For a large number of boids (e.g., 1000+), CUDA provides the best performance.
- OpenMP is a very good intermediate solution, easy to implement.
- Sequential is only useful for testing or a small number of boids.

 ## 🛠 How to Run?

### 1. Clone the repository
 ```bash
git clone https://github.com/sebique2003/Bird-Flock-Simulation-CPP
cd Bird-Flock-Simulation-CPP
```
### 2. Compile

Make sure you have:
- A C++ compiler (e.g., g++)
- OpenMP support (optional, for CPU parallelization)
- CUDA Toolkit installed (optional, for GPU parallelization)
  
Then compile:
```bash
make all
```

### 3. Run
```bash
./bird_flock_simulation
```

> Project developed by [Iordache Sebastian-Ionut] © 2025
