; reminder: short as hell. proceed with caution

global idt_reload

section .text
idt_reload:
	lidt [rdi]
	ret ; goes back to c source 

; thats all. just pass 2 instructions. 
