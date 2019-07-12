# microbench
Extremely Simple Microbenchmarks

To build X86 binaries,  
```shell
make
```

To build ARM binaries,
```shell
make ARM
```

To build RISCV binaries,
```shell
make RISCV
```

To build X86, ARM, and RISCV binaries,
```shell
make all
```

To set the path to X86 compiler, change `$CC_X86` in `make.config` file.  
To set the path to ARM compiler, change `$CC_ARM` in `make.config` file.  
To set the path to RISCV compiler, change `$CC_RISCV` in `make.config` file.  

The binaries are named `bench.X86`, `bench.ARM`, and `bench.RISCV` on each subdirectory.
