
	movq -0(%rbp), %r10
	subq $10, %r10
	movq %r10, -8(%rbp)
	movq -8(%rbp), %r10
	movq %r10, -16(%rbp)
f:
	enter $(88), $0
	mov %rdi, -8(%rbp)
	mov %rsi, -16(%rbp)
	movq -8(%rbp), %r10
	movq -16(%rbp), %r11
	cmp  %r11, %r10
	je  .L0
	movq $0, -24(%rbp)
	jmp  .L1

.L0:
	movq $1, -24(%rbp)

.L1:
	movq -24(%rbp), %r10
	movq $1, %r11
	cmp  %r10, %r11
	jne  .end_label0
	movq -8(%rbp), %rax

.end_label0:
	movq -8(%rbp), %r10
	movq -16(%rbp), %r11
	cmp  %r11, %r10
	jl  .L3
	movq $0, -32(%rbp)
	jmp  .L4

.L3:
	movq $1, -32(%rbp)

.L4:
	movq -32(%rbp), %r10
	movq $1, %r11
	cmp  %r10, %r11
	jne  .end_label1
	movq -8(%rbp), %r10
	addq $1, %r10
	movq %r10, -40(%rbp)
	mov -40(%rbp), %rdi
	mov -16(%rbp), %rsi
	call f
	movq -0(%rbp), %rax

.end_label1:
	mov -8(%rbp), %rdi
	movq -16(%rbp), %r10
	addq $1, %r10
	movq %r10, -48(%rbp)
	mov -48(%rbp), %rsi
	call f
	movq -0(%rbp), %rax
	movq -0(%rbp), %r10
	subq $1, %r10
	movq %r10, -56(%rbp)
	movq -8(%rbp), %r10
	subq -56(%rbp), %r10
	movq %r10, -64(%rbp)
	mov -64(%rbp), %rdi
	movq -16(%rbp), %r10
	imulq $2, %r10
	movq %r10, -72(%rbp)
	mov -72(%rbp), %rsi
	call f
	mov %rax, %rdi
	movq -16(%rbp), %r10
	addq $1, %r10
	movq %r10, -80(%rbp)
	mov -80(%rbp), %rsi
	call f
	movq -0(%rbp), %rax
	leave
	ret
inc:
	enter $(24), $0
	mov %rdi, -8(%rbp)
	movq -8(%rbp), %r10
	addq $1, %r10
	movq %r10, -16(%rbp)
	movq -16(%rbp), %rax
	leave
	ret

	.globl main
main:
	enter $(152), $0
	movq  $0, %rdx
	movq  $1, %rax
	movq  $2, %r10
	idivq %r10
	movq  %rdx, -8(%rbp)
	movq -8(%rbp), %r10
	movq %r10, -16(%rbp)
	movq  $0, %rdx
	movq  $1, %rax
	movq  $2, %r10
	idivq %r10
	movq  %rax, -24(%rbp)
	movq -24(%rbp), %r10
	movq %r10, -32(%rbp)
	movq $1, %r10
	movq $2, %r11
	cmp  %r11, %r10
	jl  .L6
	movq $0, -40(%rbp)
	jmp  .L7

.L6:
	movq $1, -40(%rbp)

.L7:
	movq -40(%rbp), %r10
	movq %r10, -48(%rbp)
	movq $1, %r10
	movq $2, %r11
	cmp  %r11, %r10
	jg  .L8
	movq $0, -56(%rbp)
	jmp  .L9

.L8:
	movq $1, -56(%rbp)

.L9:
	movq -56(%rbp), %r10
	movq %r10, -64(%rbp)
	movq $1, %r10
	movq $2, %r11
	cmp  %r11, %r10
	je  .L10
	movq $0, -72(%rbp)
	jmp  .L11

.L10:
	movq $1, -72(%rbp)

.L11:
	movq -72(%rbp), %r10
	movq %r10, -80(%rbp)
	movq $0, -136(%rbp)

.while_label2:
	movq $1, %r10
	movq $1, %r11
	cmp  %r10, %r11
	jne  .end_label2
	movq  $0, %rdx
	movq  -136(%rbp), %rax
	movq  $2, %r10
	idivq %r10
	movq  %rdx, -96(%rbp)
	movq -96(%rbp), %r10
	movq $0, %r11
	cmp  %r11, %r10
	je  .L13
	movq $0, -104(%rbp)
	jmp  .L14

.L13:
	movq $1, -104(%rbp)

.L14:
	movq -104(%rbp), %r10
	movq $1, %r11
	cmp  %r10, %r11
	jne  .end_label3
	movq -136(%rbp), %r10
	subq $1, %r10
	movq %r10, -112(%rbp)
	movq -112(%rbp), %r10
	movq %r10, -136(%rbp)

.end_label3:
	movq -136(%rbp), %r10
	addq $1, %r10
	movq %r10, -128(%rbp)
	movq -128(%rbp), %r10
	movq %r10, -136(%rbp)
	jmp .while_label2

.end_label2:
	movq $0, %r10
	movq $1, %r11
	cmp  %r11, %r10
	jl  .L17
	movq $0, -144(%rbp)
	jmp  .L18

.L17:
	movq $1, -144(%rbp)

.L18:
	movq -144(%rbp), %r10
	movq $1, %r11
	cmp  %r10, %r11
	jne  .else_label4
	mov $0, %rdi
	call print
	jmp .end_label4

.else_label4:
	mov $1, %rdi
	call inc
	mov %rax, %rdi
	call print
	movq -0(%rbp), %rax

.end_label4:
	leave
	ret