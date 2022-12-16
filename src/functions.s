.section .text
.global outb
.type outb, @function

outb:
	push %ebp
	mov %esp, %ebp
	movw 8(%esp), %dx
	movb 12(%esp), %al
	outb %al, %dx
	pop %ebp
	xor %eax, %eax
	ret

.global inb
.type inb, @function

inb:
	push %ebp
	mov %esp, %ebp
	movw 8(%esp), %dx
	xor %eax, %eax
	inb %dx, %al
	pop %ebp
	ret
	



.global in16
.type in16, @function

in16:
	push %ebp
	mov %esp, %ebp
	movw 8(%esp), %dx
	xor %eax, %eax
	in %dx, %ax
	pop %ebp
	ret
	
.global out16
.type out16, @function

out16:
	push %ebp
	mov %esp, %ebp
	movw 8(%esp), %dx
	movw 12(%esp), %ax
	out %ax, %dx
	pop %ebp
	xor %eax, %eax
	ret
	
.global gdt_flush
.type gdt_flush, @function

gdt_flush:

	mov 4(%esp), %eax
	lgdt (%eax)
	
	mov $0x10, %ax
	mov %ax, %ds
	mov %eax, %es
	
	mov %eax, %fs
	mov %eax, %gs
	mov %eax, %ss
	
	
	jmp $0x08,$complete_flush
complete_flush:
	
	ret
	
.global idt_flush
.type idt_flush, @function

idt_flush:
	mov 4(%esp), %eax
	lidt (%eax)
	ret
	
.macro ISR_NOERR p
.global isr\p
.type isr\p, @function
isr\p:
	cli
	push $0
	push $\p
	jmp isr_common_stub
.endm

ISR_NOERR 0
ISR_NOERR 1
ISR_NOERR 2
ISR_NOERR 3
ISR_NOERR 4
ISR_NOERR 5
ISR_NOERR 6
ISR_NOERR 7
ISR_NOERR 8
ISR_NOERR 9

isr_common_stub:
	cli
	call isr_handler
	add $8, %esp
	sti
	iret
	
