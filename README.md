# largepapa
a kernel for UEFI-compatible machines (leverages limine)

## deps:

* GNU Make

* xorriso (iso creation)

* preferably gcc

* qemu (or real hardware if you want)

## build instructions

MAKE COMMANDS:

`make clean` - cleans dir

`make` - compiles into bzimage

ISO CREATION:

`chmod +x iso.sh`

`./iso.sh`

_PLEASE_ RUN ISO CREATION UTIL AFTER MAKE

Either flash onto external HDD via dd/rufus/balena or boot with qemu
