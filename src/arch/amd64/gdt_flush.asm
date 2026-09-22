; oh yeah we going into the depths of HELL for ts one lmao

global gdt_reload

section .text
gdt_reload:
	; sysv amd64 abi: first arg (struct gdt_descriptor*) in rdi
	lgdt [rdi]			; load gdtr w/ new base + limit

	; reload data segment regs w/ KDS (kernel data selector) (0x10 = slot 2)
	mov ax 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	; reload cs with KDS (0x08 = slot 1). push cs + target ret addr, exec retfq after
	push 0x08			; new cs selector
	lea rax, [rel .reload_cs]	; target instruct addr
	push rax
	retfq				; retfq pops rax into rip + 0x08 into cs

.reload_cs:
	ret				; anti-climatic as shit but just returns back to our C
