# hpec2023
An example to demonstrate the timelord algorithm

### Description
The following is a synthetic benchmark that involves a series of BSP (Bulk Synchronous Parallel) iterations.

During each iteration, it busy-waits for a specific duration determined according to a Poisson Distribution.


### How to compile
```
./build.sh
```

### How to use
```
LD_PRELOAD=<path/to/libtimelord_wrapper.so> mpirun <arguments> <program>
```
By default, this will be under ./build
