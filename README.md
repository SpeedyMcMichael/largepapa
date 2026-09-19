# largepapa
a kernel for UEFI-compatible machines (leverages limine)

## deps:

* GNU Make

* xorriso (iso creation)

* preferably gcc

* qemu (or real hardware if you want)

* curl

## build instructions

MAKE COMMANDS:
```sh
make clean
```
- cleans dir

```sh
make 
```
- compiles into keebler ELF

ISO CREATION:

```sh
$ ./iso.sh
```

_PLEASE_ RUN ISO CREATION UTIL AFTER MAKE

Either flash onto external HDD via dd/rufus/balena or boot with qemu

## plans (not in sequential order)

* add MMU logic

* add and flesh out userland

* add syscall table

* port ksh and tcc probably

* add mandoc support + man pages 

* shitpost in the kernel source
