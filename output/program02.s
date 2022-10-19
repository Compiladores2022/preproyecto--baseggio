
	movq $0, -8(%rbp)
	movq $1, -16(%rbp)
	movq $1, -24(%rbp)
	movq $0, -32(%rbp)
foo_1:
	enter $(40), $0
	mov %rdi, -8(%rbp)
	mov %rsi, -16(%rbp)
	movq -16(%rbp), %r10
	subq -8(%rbp), %r10
	movq %r10, -24(%rbp)
	movq -8(%rbp), %r10
	addq -24(%rbp), %r10
	movq %r10, -32(%rbp)
	movq -32(%rbp), %rax
	leave
	ret
foo_2:
	enter $(40), $0
	mov %rdi, -8(%rbp)
	mov %rsi, -16(%rbp)
	movq $0, %r10
	movq $1, %r11
	cmp %r10, %r11
	je .L0
	movq $0, -24(%rbp)
	jmp .L2

.L0:
	movq -8(%rbp), %r10
	movq $1, %r11
	cmp %r10, %r11
	je .L1
	movq $0, -24(%rbp)
	jmp .L2

.L1:
	movq $1, -24(%rbp)

.L2:
	movq -24(%rbp), %r10
	movq $1, %r11
	cmp %r10, %r11
	je .L3
	movq $0, -32(%rbp)
	jmp .L5

.L3:
	movq -16(%rbp), %r10
	movq $1, %r11
	cmp %r10, %r11
	je .L4
	movq $0, -32(%rbp)
	jmp .L5

.L4:
	movq $1, -32(%rbp)

.L5:
	movq -32(%rbp), %rax
	leave
	ret
foo_3:
	enter $(8), $0
	mov $123456789, %rdi
	call print
	leave
	ret

	.globl main
main:
	enter $(48), $0
	call get_int
	movq -0(%rbp), %r10
	movq %r10, -8(%rbp)
	movq $0, -16(%rbp)

.while_label0:
	movq $1, %r10
	movq $1, %r11
	cmp  %r10, %r11
	jne  .end_label0
	mov $0, %rdi
	call print
	jmp .while_label0

.end_label0:
	movq -8(%rbp), %r10
	movq $0, %r11
	cmp  %r11, %r10
	je  .L8
	movq $0, -24(%rbp)
	jmp  .L9

.L8:
	movq $1, -24(%rbp)

.L9:
	movq -24(%rbp), %r10
	movq $1, %r11
	cmp  %r10, %r11
	jne  .else_label1
	mov $1, %rdi
	call print
	jmp .end_label1

.else_label1:
	movq -8(%rbp), %r10
	movq $1, %r11
	cmp  %r11, %r10
	je  .L11
	movq $0, -32(%rbp)
	jmp  .L12

.L11:
	movq $1, -32(%rbp)

.L12:
	movq -32(%rbp), %r10
	movq $1, %r11
	cmp  %r10, %r11
	jne  .else_label2
	mov $2, %rdi
	call print
	jmp .end_label2

.else_label2:
	movq -8(%rbp), %r10
	movq $2, %r11
	cmp  %r11, %r10
	je  .L14
	movq $0, -40(%rbp)
	jmp  .L15

.L14:
	movq $1, -40(%rbp)

.L15:
	movq -40(%rbp), %r10
	movq $1, %r11
	cmp  %r10, %r11
	jne  .end_label3
	mov $4, %rdi
	call print

.end_label3:

.end_label2:

.end_label1:
	leave
	ret