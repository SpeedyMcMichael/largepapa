#ifndef PANIC_H
#define PANIC_H

#include <stdint.h>
#include <stdarg.h>

struct cpu_state {
	uint64_t r15, r14, r13, r12, r11, r10, r9, r8;		// scratch registers (r12-r15 are callee-saved and im lowk gay)
	uint64_t rbp, rdi, rsi, rdx, rcx, rbx, rax;		// standard amd64 regs
	uint64_t int_no, err_code;				// interrupt num + errno
	uint64_t rip, cs, rflags, rsp, ss;			// misc regs
}

__attribute__((noreturn)) void panic(const char *msg);
__attribute__((noreturn)) void panic_regs(const char *msg, struct cpu_state *r);

#endif
