// FUCK YOU INTEL

#ifndef GDT_H
#define GDT_H

#include <stdint.h>

struct gdt_entry {
	uint16_t	limit_low; 	// lower limit i think
	uint16_t	base_low;	// low base val
	uint8_t 	base_middle;	// mid base val
	uint8_t		access;
	uint8_t 	granularity;
	uint8_t		base_high;	// high base val
} __attribute__((packed));

struct gdt_descriptor {
	uint16_t 	limit;
	uint64_t	base;
} __attribute__((packed));

struct tss_entry {
	uint32_t	reserved0;
	uint64_t	rsp0;		// stack pointer for r0 (ring 0) interrupts
	uint64_t	rsp1;
	uint64_t	rsp2;
	uint32_t	reserved1;
	uint32_t	reserved2; 	
	uint64_t	ist[7];		// 7 bowls of wrath, 7 seals, 7 days of creation, and now 7 interrupt stack table pointers
	uint32_t	reserved3;
	uint32_t	reserved4;
	uint16_t	reserved5;
	uint16_t	iopb_offset;	// PEANUT BUTTER !!!
} __attribute__((packed)); // i will never understand why it does (()) instead of () like a normal function

void gdt_init(void); // void because theres NOTHING THERE YET NIMROD

#endif
