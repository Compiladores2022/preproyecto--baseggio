	.globl main
main:
	enter $(440), $0
	movq $0, -432(%rbp)
	movq $1, %r10
	addq $0, %r10
	movq %r10, -16(%rbp)
	movq -16(%rbp), %r10
	movq %r10, -24(%rbp)
	movq $1, %r10
	subq $0, %r10
	movq %r10, -32(%rbp)
	movq -32(%rbp), %r10
	movq %r10, -40(%rbp)
	movq $0, %r10
	subq $1, %r10
	movq %r10, -48(%rbp)
	movq -48(%rbp), %r10
	movq %r10, -56(%rbp)
	movq $2, %r10
	imulq $15, %r10
	movq %r10, -64(%rbp)
	movq -64(%rbp), %r10
	movq %r10, -72(%rbp)
	movq $15, %r10
	imulq $2, %r10
	movq %r10, -80(%rbp)
	movq -80(%rbp), %r10
	movq %r10, -88(%rbp)
	movq $340, %r10
	imulq $340, %r10
	movq %r10, -96(%rbp)
	movq -96(%rbp), %r10
	movq %r10, -104(%rbp)
	movq  $0, %rdx
	movq  $4, %rax
	movq  $2, %r10
	idivq %r10
	movq  %rax, -112(%rbp)
	movq -112(%rbp), %r10
	movq %r10, -120(%rbp)
	movq  $0, %rdx
	movq  $150, %rax
	movq  $5, %r10
	idivq %r10
	movq  %rax, -128(%rbp)
	movq -128(%rbp), %r10
	movq %r10, -136(%rbp)
	movq  $0, %rdx
	movq  $150, %rax
	movq  $5, %r10
	idivq %r10
	movq  %rdx, -144(%rbp)
	movq -144(%rbp), %r10
	movq %r10, -152(%rbp)
	movq  $0, %rdx
	movq  $12345, %rax
	movq  $7, %r10
	idivq %r10
	movq  %rdx, -160(%rbp)
	movq -160(%rbp), %r10
	movq %r10, -168(%rbp)
	movq $1, %r10
	movq $1, %r11
	cmp %r10, %r11
	je .L0
	movq $1, %r10
	movq $1, %r11
	cmp %r10, %r11
	je .L0
	movq $0, -176(%rbp)
	jmp .L1
.L0:
	movq $1, -176(%rbp)
.L1:
	movq -176(%rbp), %r10
	movq %r10, -184(%rbp)
	movq $1, %r10
	movq $1, %r11
	cmp %r10, %r11
	je .L2
	movq $0, %r10
	movq $1, %r11
	cmp %r10, %r11
	je .L2
	movq $0, -192(%rbp)
	jmp .L3
.L2:
	movq $1, -192(%rbp)
.L3:
	movq -192(%rbp), %r10
	movq %r10, -200(%rbp)
	movq $0, %r10
	movq $1, %r11
	cmp %r10, %r11
	je .L4
	movq $1, %r10
	movq $1, %r11
	cmp %r10, %r11
	je .L4
	movq $0, -208(%rbp)
	jmp .L5
.L4:
	movq $1, -208(%rbp)
.L5:
	movq -208(%rbp), %r10
	movq %r10, -216(%rbp)
	movq $0, %r10
	movq $1, %r11
	cmp %r10, %r11
	je .L6
	movq $0, %r10
	movq $1, %r11
	cmp %r10, %r11
	je .L6
	movq $0, -224(%rbp)
	jmp .L7
.L6:
	movq $1, -224(%rbp)
.L7:
	movq -224(%rbp), %r10
	movq %r10, -232(%rbp)
	movq $1, %r10
	movq $1, %r11
	cmp %r10, %r11
	je .L8
	movq $0, -240(%rbp)
	jmp .L10

.L8:
	movq $1, %r10
	movq $1, %r11
	cmp %r10, %r11
	je .L9
	movq $0, -240(%rbp)
	jmp .L10

.L9:
	movq $1, -240(%rbp)

.L10:
	movq -240(%rbp), %r10
	movq %r10, -248(%rbp)
	movq $1, %r10
	movq $1, %r11
	cmp %r10, %r11
	je .L11
	movq $0, -256(%rbp)
	jmp .L13

.L11:
	movq $0, %r10
	movq $1, %r11
	cmp %r10, %r11
	je .L12
	movq $0, -256(%rbp)
	jmp .L13

.L12:
	movq $1, -256(%rbp)

.L13:
	movq -256(%rbp), %r10
	movq %r10, -264(%rbp)
	movq $0, %r10
	movq $1, %r11
	cmp %r10, %r11
	je .L14
	movq $0, -272(%rbp)
	jmp .L16

.L14:
	movq $1, %r10
	movq $1, %r11
	cmp %r10, %r11
	je .L15
	movq $0, -272(%rbp)
	jmp .L16

.L15:
	movq $1, -272(%rbp)

.L16:
	movq -272(%rbp), %r10
	movq %r10, -280(%rbp)
	movq $0, %r10
	movq $1, %r11
	cmp %r10, %r11
	je .L17
	movq $0, -288(%rbp)
	jmp .L19

.L17:
	movq $0, %r10
	movq $1, %r11
	cmp %r10, %r11
	je .L18
	movq $0, -288(%rbp)
	jmp .L19

.L18:
	movq $1, -288(%rbp)

.L19:
	movq -288(%rbp), %r10
	movq %r10, -296(%rbp)
	movq $0, %r10
	movq $1, %r11
	cmp  %r11, %r10
	jl  .L20
	movq $0, -304(%rbp)
	jmp  .L21

.L20:
	movq $1, -304(%rbp)

.L21:
	movq -304(%rbp), %r10
	movq %r10, -312(%rbp)
	movq $1, %r10
	movq $0, %r11
	cmp  %r11, %r10
	jl  .L22
	movq $0, -320(%rbp)
	jmp  .L23

.L22:
	movq $1, -320(%rbp)

.L23:
	movq -320(%rbp), %r10
	movq %r10, -328(%rbp)
	movq $0, %r10
	movq $1, %r11
	cmp  %r11, %r10
	jg  .L24
	movq $0, -336(%rbp)
	jmp  .L25

.L24:
	movq $1, -336(%rbp)

.L25:
	movq -336(%rbp), %r10
	movq %r10, -344(%rbp)
	movq $1, %r10
	movq $0, %r11
	cmp  %r11, %r10
	jg  .L26
	movq $0, -352(%rbp)
	jmp  .L27

.L26:
	movq $1, -352(%rbp)

.L27:
	movq -352(%rbp), %r10
	movq %r10, -360(%rbp)
	movq $0, %r10
	movq $1, %r11
	cmp  %r11, %r10
	je  .L28
	movq $0, -368(%rbp)
	jmp  .L29

.L28:
	movq $1, -368(%rbp)

.L29:
	movq -368(%rbp), %r10
	movq %r10, -376(%rbp)
	movq $1, %r10
	movq $0, %r11
	cmp  %r11, %r10
	je  .L30
	movq $0, -384(%rbp)
	jmp  .L31

.L30:
	movq $1, -384(%rbp)

.L31:
	movq -384(%rbp), %r10
	movq %r10, -392(%rbp)
	movq $1, %r10
	movq $1, %r11
	cmp  %r11, %r10
	je  .L32
	movq $0, -400(%rbp)
	jmp  .L33

.L32:
	movq $1, -400(%rbp)

.L33:
	movq -400(%rbp), %r10
	movq %r10, -408(%rbp)
	mov -24(%rbp), %edi
	call print
	mov -40(%rbp), %edi
	call print
	mov -56(%rbp), %edi
	call print
	mov -72(%rbp), %edi
	call print
	mov -88(%rbp), %edi
	call print
	mov -104(%rbp), %edi
	call print
	mov -120(%rbp), %edi
	call print
	mov -136(%rbp), %edi
	call print
	mov -152(%rbp), %edi
	call print
	mov -168(%rbp), %edi
	call print
	mov -184(%rbp), %edi
	call print
	mov -200(%rbp), %edi
	call print
	mov -216(%rbp), %edi
	call print
	mov -232(%rbp), %edi
	call print
	mov -248(%rbp), %edi
	call print
	mov -264(%rbp), %edi
	call print
	mov -280(%rbp), %edi
	call print
	mov -296(%rbp), %edi
	call print
	mov -312(%rbp), %edi
	call print
	mov -328(%rbp), %edi
	call print
	mov -344(%rbp), %edi
	call print
	mov -360(%rbp), %edi
	call print
	mov -376(%rbp), %edi
	call print
	mov -392(%rbp), %edi
	call print
	mov -408(%rbp), %edi
	call print

.while_label0:
	movq -432(%rbp), %r10
	movq $10, %r11
	cmp  %r11, %r10
	jl  .L35
	movq $0, -416(%rbp)
	jmp  .L36

.L35:
	movq $1, -416(%rbp)

.L36:
	movq -416(%rbp), %r10
	movq $1, %r11
	cmp  %r10, %r11
	jne  .end_label0
	mov -432(%rbp), %edi
	call print
	movq -432(%rbp), %r10
	addq $1, %r10
	movq %r10, -424(%rbp)
	movq -424(%rbp), %r10
	movq %r10, -432(%rbp)
	jmp .while_label0

.end_label0:
	leave
	ret