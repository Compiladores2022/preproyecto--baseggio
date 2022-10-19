
gcd:
	enter $(112), $0
	mov %rdi, -8(%rbp)
	mov %rsi, -16(%rbp)
	movq $1, -104(%rbp)
	movq $2, -32(%rbp)
	movq -8(%rbp), %r10
	movq $0, %r11
	cmp  %r11, %r10
	je  .L0
	movq $0, -40(%rbp)
	jmp  .L1

.L0:
	movq $1, -40(%rbp)

.L1:
	movq -16(%rbp), %r10
	movq $0, %r11
	cmp  %r11, %r10
	je  .L2
	movq $0, -48(%rbp)
	jmp  .L3

.L2:
	movq $1, -48(%rbp)

.L3:
	movq -40(%rbp), %r10
	movq $1, %r11
	cmp %r10, %r11
	je .L4
	movq -48(%rbp), %r10
	movq $1, %r11
	cmp %r10, %r11
	je .L4
	movq $0, -56(%rbp)
	jmp .L5
.L4:
	movq $1, -56(%rbp)
.L5:
	movq -56(%rbp), %r10
	movq $1, %r11
	cmp  %r10, %r11
	jne  .end_label0
	movq $2147483647, %rax

.end_label0:

.while_label1:
	movq  $0, %rdx
	movq  -8(%rbp), %rax
	movq  -32(%rbp), %r10
	idivq %r10
	movq  %rdx, -64(%rbp)
	movq -64(%rbp), %r10
	movq $0, %r11
	cmp  %r11, %r10
	je  .L8
	movq $0, -72(%rbp)
	jmp  .L9

.L8:
	movq $1, -72(%rbp)

.L9:
	movq  $0, %rdx
	movq  -16(%rbp), %rax
	movq  -32(%rbp), %r10
	idivq %r10
	movq  %rdx, -80(%rbp)
	movq -80(%rbp), %r10
	movq $0, %r11
	cmp  %r11, %r10
	je  .L10
	movq $0, -88(%rbp)
	jmp  .L11

.L10:
	movq $1, -88(%rbp)

.L11:
	movq -72(%rbp), %r10
	movq $1, %r11
	cmp %r10, %r11
	je .L12
	movq $0, -96(%rbp)
	jmp .L14

.L12:
	movq -88(%rbp), %r10
	movq $1, %r11
	cmp %r10, %r11
	je .L13
	movq $0, -96(%rbp)
	jmp .L14

.L13:
	movq $1, -96(%rbp)

.L14:
	movq -96(%rbp), %r10
	movq $1, %r11
	cmp  %r10, %r11
	jne  .end_label1
	movq -32(%rbp), %r10
	movq %r10, -104(%rbp)
	jmp .while_label1

.end_label1:
	movq -104(%rbp), %rax
	leave
	ret

	.globl main
main:
	enter $(40), $0
	call get_int
	movq -0(%rbp), %r10
	movq %r10, -8(%rbp)
	call get_int
	movq -0(%rbp), %r10
	movq %r10, -16(%rbp)
	mov -8(%rbp), %rdi
	mov -16(%rbp), %rsi
	call gcd
	mov %rax, %rdi
	call print
	movq $1, %r10
	movq $0, %r11
	cmp  %r11, %r10
	jl  .L16
	movq $0, -24(%rbp)
	jmp  .L17

.L16:
	movq $1, -24(%rbp)

.L17:
	movq -24(%rbp), %r10
	movq $1, %r11
	cmp  %r10, %r11
	jne  .end_label2
	call get_int
	movq -0(%rbp), %r10
	movq %r10, -32(%rbp)

.end_label2:
	leave
	ret