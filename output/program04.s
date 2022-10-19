
foo:
	enter $(48), $0
	mov %rdi, -8(%rbp)
	mov %rsi, -16(%rbp)
	mov %rdx, -24(%rbp)
	movq -16(%rbp), %r10
	subq -24(%rbp), %r10
	movq %r10, -32(%rbp)
	movq -8(%rbp), %r10
	addq -32(%rbp), %r10
	movq %r10, -40(%rbp)
	movq -40(%rbp), %rax
	leave
	ret

	.globl main
main:
	enter $(64), $0
	movq $1, -8(%rbp)
	movq $1, %r10
	cmp  $0, %r10
	je  .L0
	movq $1, -16(%rbp)
	jmp  .L1

.L0:
	movq $0, -16(%rbp)

.L1:
	movq -16(%rbp), %r10
	movq %r10, -24(%rbp)
	movq $1, %r10
	cmp  -8(%rbp), %r10
	je  .L2
	movq $1, -32(%rbp)
	jmp  .L3

.L2:
	movq $0, -32(%rbp)

.L3:
	movq -32(%rbp), %r10
	movq %r10, -40(%rbp)
	movq $1, %r10
	cmp  -40(%rbp), %r10
	je  .L4
	movq $1, -48(%rbp)
	jmp  .L5

.L4:
	movq $0, -48(%rbp)

.L5:
	movq -48(%rbp), %r10
	movq %r10, -56(%rbp)
	mov -8(%rbp), %rdi
	call print_bool
	mov -24(%rbp), %rdi
	call print_bool
	mov -40(%rbp), %rdi
	call print_bool
	mov -56(%rbp), %rdi
	call print_bool
	leave
	ret