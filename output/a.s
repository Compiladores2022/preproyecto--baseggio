	.globl main
main:
	enter $32, $0
	movq $0, -8(%rbp)
	movq $1, -16(%rbp)
	movq -8(%rbp), %r10
	add -16(%rbp), %r10
	movq %r10, -24(%rbp)
	mov -24(%rbp), %edi
	call print
	movq $0, %rax
	leave
	ret
