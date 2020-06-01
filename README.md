## Compile and run:

### serial
Compile:
```Bash
$ g++ -o serial serial.cpp
```
Run:
```Bash
$ ./serial
```

### mpi
Compile:
```Bash
$ mpic++ -o mpi mpi.cpp
```
Run:
```Bash
$ mpiexec -n <number of processes> ./mpi
```

### omp
Compile:
```Bash
$ g++ -fopenmp -o omp omp.cpp
```
Run:
```Bash
$ ./omp <number of threads>
```
