	.globl main
main:
	enter $(8 * 11), $0
	movq $128, -8(%rbp)
	movq $129, -16(%rbp)
	movq -8(%rbp), %r10
	movq %r10, -24(%rbp)
	movq $1, -32(%rbp)
	movq $0, -40(%rbp)
	mov -8(%rbp), %edi
	call print
	mov -16(%rbp), %edi
	call print
	mov -32(%rbp), %edi
	call print
	mov -40(%rbp), %edi
	call print
	movq -8(%rbp), %r10
	add -16(%rbp), %r10
	movq %r10, -48(%rbp)
	mov -48(%rbp), %edi
	call print
	movq -8(%rbp), %r10
	imul -16(%rbp), %r10
	movq %r10, -56(%rbp)
	mov -56(%rbp), %edi
	call print
	movq -32(%rbp), %r10
	movq $1, %r11
	cmp %r10, %r11
	je .L1
	movq -40(%rbp), %r10
	movq $1, %r11
	cmp %r10, %r11
	je .L1
	movq $0, -64(%rbp)
	jmp .L2
.L1:
	movq $1, -64(%rbp)
.L2:
	mov -64(%rbp), %edi
	call print
	movq -32(%rbp), %r10
	movq $1, %r11
	cmp %r10, %r11
	je .L3
	movq -32(%rbp), %r10
	movq $1, %r11
	cmp %r10, %r11
	je .L3
	movq $0, -72(%rbp)
	jmp .L4
.L3:
	movq $1, -72(%rbp)
.L4:
	mov -72(%rbp), %edi
	call print
	movq -32(%rbp), %r10
	movq $1, %r11
	cmp %r10, %r11
	je .L5
	movq $0, -80(%rbp)
	jmp .L7

.L5:
	movq -40(%rbp), %r10
	movq $1, %r11
	cmp %r10, %r11
	je .L6
	movq $0, -80(%rbp)
	jmp .L7

.L6:
	movq $1, -80(%rbp)

.L7:
	mov -80(%rbp), %edi
	call print
	movq -40(%rbp), %r10
	movq $1, %r11
	cmp %r10, %r11
	je .L8
	movq $0, -88(%rbp)
	jmp .L10

.L8:
	movq -40(%rbp), %r10
	movq $1, %r11
	cmp %r10, %r11
	je .L9
	movq $0, -88(%rbp)
	jmp .L10

.L9:
	movq $1, -88(%rbp)

.L10:
	mov -88(%rbp), %edi
	call print
	mov -24(%rbp), %edi
	call print
	movq $0, %rax
	leave
	ret
