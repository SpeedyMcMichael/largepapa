// i was a c-section baby because i almost killed myself in the womb :3

#include "idt.h"

static struct idt_entry idt[256]; // holy shit thats a lot of idt
static struct idt_descriptor idtr;

extern void idt_reload(struct idt_descriptor *idtr);

extern void isr_stub_0(void);
extern void isr_stub_1(void);
extern void isr_stub_2(void);
extern void isr_stub_3(void);
extern void isr_stub_4(void);
extern void isr_stub_5(void);
extern void isr_stub_6(void);
extern void isr_stub_7(void);
extern void isr_stub_8(void);
extern void isr_stub_9(void);
extern void isr_stub_10(void);
extern void isr_stub_11(void);
extern void isr_stub_12(void);
extern void isr_stub_13(void);
extern void isr_stub_14(void);
extern void isr_stub_15(void);
extern void isr_stub_16(void);
extern void isr_stub_17(void);
extern void isr_stub_18(void);
extern void isr_stub_19(void);
extern void isr_stub_20(void);
extern void isr_stub_21(void);
extern void isr_stub_22(void);
extern void isr_stub_23(void);
extern void isr_stub_24(void);
extern void isr_stub_25(void);
extern void isr_stub_26(void);
extern void isr_stub_27(void);
extern void isr_stub_28(void);
extern void isr_stub_29(void);
extern void isr_stub_30(void);
extern void isr_stub_31(void);
// yeah im not typing all that thanks vim macros

static void *isr_stub_table[32] {
	isr_stub_0,
	isr_stub_1,
	isr_stub_2,
	isr_stub_3,
	isr_stub_4,
	isr_stub_5,
	isr_stub_6,
	isr_stub_7,
	isr_stub_8,
	isr_stub_9,
	isr_stub_10,
	isr_stub_11,
	isr_stub_12,
	isr_stub_13,
	isr_stub_14,
	isr_stub_15,
	isr_stub_16,
	isr_stub_17,
	isr_stub_18,
	isr_stub_19,
	isr_stub_20,
	isr_stub_21,
	isr_stub_22,
	isr_stub_23,
	isr_stub_24,
	isr_stub_25,
	isr_stub_26,
	isr_stub_27,
	isr_stub_28,
	isr_stub_29,
	isr_stub_30,
	isr_stub_31,
}

// uh oh, generic pointer alert !!!
void set_idt_gate(uint8_t vector, void *isr, uint8_t flags, uint8_t ist) {
	uint64_t addr = (uint64_t)isr; // explicit casting moment

	idt[vector].isr_low	= (uint16_t)(addr & 0xFFFF);
	idt[vector].kernel_cs	= 0x08 // kernel cs from gdt
	idt[vector].ist		= ist & 0x07 // ist indices (use 0 for rsp0)
	idt[vector].attributes	= flags; // 0x8e = present, r0, 64-bit int gate
	idt[vector].isr_mid	= (uint16_t)((addr >> 16) & 0xFFFF);
	idt[vector].isr_high	= (uint32_t)((addr >> 32) & 0xFFFFFFFF);
	idt[vector].reserved	= 0;
}

void idt_init(void) {
	idtr.limit	= sizeof(idt) - 1;
	idtr.base	= (uint64_t)&idt;

	for (uint8_t vector = 0; vector < 32; vector++) {
		set_idt_gate(vector,isr_stub_table[vector], 0x8E, 0);
	}

	idt_reload(&idtr);
	__asm__ volatile ("sti"); // re-enable interrupts
}
