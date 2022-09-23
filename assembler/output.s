	.globl main
main:
	enter $(8 * 6), $0
	movq $1, -8(%rbp)
	movq $0, -16(%rbp)
	movq -8(%rbp), %r10
	movq $1, %r11
	cmp %r10, %r11
	je .L1
	movq $0, -40(%rbp)
	jmp .L3

.L1:
	movq -16(%rbp), %r10
	movq $1, %r11
	cmp %r10, %r11
	je .L2
	movq $0, -40(%rbp)
	jmp .L3

.L2:
	movq $1, -40(%rbp)

.L3:
	movq -40(%rbp), %r10
	movq %r10, -24(%rbp)
	movq -8(%rbp), %r10
	movq $1, %r11
	cmp %r10, %r11
	je .L4
	movq -16(%rbp), %r10
	movq $1, %r11
	cmp %r10, %r11
	je .L4
	movq $0, -48(%rbp)
	jmp .L5
.L4:
	movq $1, -48(%rbp)
.L5:
	movq -48(%rbp), %r10
	movq %r10, -32(%rbp)
	mov $0, %rax
	call printInt
	movq $0, %rax
	leave
	ret
