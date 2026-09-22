#ifndef IDT_H
#define IDT_H

#include <stdint.h> // they let you smuggle this c header in when doing freestanding c lmao


struct idt_entry {
	uint16_t isr_low;	// target offset bits 0-15
	uint16_t kernel_cs;	// cs selector in gdt (0x08)
	uint8_t ist;		// bits 0-2: ist offset in tss (0 = disable), bits 3-7: reserved (0 always)
	uint8_t attributes;	// gate type, dpl, present bit (ex. 0x8e for r0 int gate)
	uint16_t isr_mid;	// target offset bits 16-31
	uint32_t isr_high;	// target offest bits 32-63
	uint32_t reserved;	// must be 0 or #GP occurs
} __attribute__((packed)); // needless byte padding mitigation

struct idt_descriptor {
	uint16_t limit;
	uint64_t base;
} __attribute__((packed));

void idt_init(void);
void set_idt_gate(uint8_t vector, void *isr, uint8_t flags, uint8_t ist);

#endif

// stdint.h > generic c data types
