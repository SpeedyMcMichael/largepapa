// largepapa implementation of panic(9) (geometry dash rule 34)

#include "panic.h" 
#include "io.h"

static volatile int panicking;

static void out(const char *s) {
	print_serial(s);
}
