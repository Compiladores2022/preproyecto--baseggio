	.globl main
main:
	enter $(8 * 9), $0
	movq $1, %r10
	imul $2, %r10
	movq %r10, -8(%rbp)
	movq -8(%rbp), %r10
	imul $3, %r10
	movq %r10, -16(%rbp)
	movq -16(%rbp), %r10
	imul $4, %r10
	movq %r10, -24(%rbp)
	movq -24(%rbp), %r10
	imul $5, %r10
	movq %r10, -32(%rbp)
	movq -32(%rbp), %r10
	imul $6, %r10
	movq %r10, -40(%rbp)
	movq -40(%rbp), %r10
	imul $7, %r10
	movq %r10, -48(%rbp)
	movq -48(%rbp), %r10
	imul $8, %r10
	movq %r10, -56(%rbp)
	movq -56(%rbp), %r10
	imul $9, %r10
	movq %r10, -64(%rbp)
	movq -64(%rbp), %r10
	imul $10, %r10
	movq %r10, -72(%rbp)
	mov -72(%rbp), %edi
	call print
	movq $0, %rax
	leave
	ret
