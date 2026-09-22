// wrote this on 200 mg of caffeine and a dream please feel free to submit an issue if this implementation is doodoo balls

#include "gdt.h" // ts so aura

static struct gdt_entry gdt[8]; 	// 78 my ass
static struct gdt_descriptor gdtr;
static struct tss_entry tss;

extern void gdt_reload(struct gdt_descriptor *gdtr);

static void set_gdt_entry(int idx, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
	gdt[idx].base_low	= (base & 0xFFFF);
	gdt[idx].base_middle	= (base >> 16) & 0xFF;
	gdt[idx].base_high	= (base >> 24) & 0xFF;
	gdt[idx].limit_low	= (limit & 0xFFFF);
	gdt[idx].granularity	= (limit >> 16) & 0x0F; 
	gdt[idx].granularity	|= gran & 0xF0;
	gdt[idx].access		= access;
}

void gdt_init(void) {
	set_gdt_entry(0,0,0,0,0);
	
	// kernel code/data section
	set_gdt_entry(1,0,0xFFFFFFFF,0x9A,0xAF); // code
	set_gdt_entry(2,0,0xFFFFFFFF,0x92,0xCF); // data

	// userspace data/code
	set_gdt_entry(3,0,0xFFFFFFFF,0xF2,0xCF); // data
	set_gdt_entry(4,0,0xFFFFFFFF,0xFA,0xAF); // code
	
	// TSS is 16 bytes in 64-bit mode
	uint64_t tss_base = (uint64_t)&tss;
	uint32_t tss_limit = sizeof(tss) - 1;

	set_gdt_entry(5,(uint32_t)tss_base,tss_limit,0x89,0x00);
	// upper 64 bits of TSS base in slot 6 casted directly
	struct gdt_entry *tss_high = &gdt[6];
	*(uint64_t*)tss_high = (tss_base >> 32);

	gdtr.limit	 = sizeof(gdt) - 1;
	gdtr.base	 = (uint64_t)&gdt;

	gdt_reload(&gdtr);

	// load TSS sector w/ inline asm
	__asm__ volatile("ltr %0" :: ((uint16_t)0x28));
}
