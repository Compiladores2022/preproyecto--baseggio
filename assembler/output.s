	.globl main
main:
	enter $(8 * 6), $0
	mov $1, -8(%rbp)
	mov $0, -16(%rbp)
	mov -8(%rbp), %r10
	mov $1, %r11
	cmp %r10, %r11
	je .L1
	mov $0, -40(%rbp)
	jmp .L3

.L1:
	mov -16(%rbp), %r10
	mov $1, %r11
	cmp %r10, %r11
	je .L2
	mov $0, -40(%rbp)
	jmp .L3

.L2:
	mov $1, -40(%rbp)

.L3:
	mov -40(%rbp), -24(%rbp)
	mov -8(%rbp), %r10
	mov $1, %r11
	cmp %r10, %r11
	je .L4
	mov -16(%rbp), %r10
	mov $1, %r11
	cmp %r10, %r11
	je .L4
	mov $0, -48(%rbp)
	jmp .L5
.L4:
	mov $1, -48(%rbp)
.L5:
	mov -48(%rbp), -32(%rbp)
	mov $0, %rax
	leave
	ret
