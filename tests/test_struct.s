	.text
	.file	"novus"
	.globl	Point_set                       # -- Begin function Point_set
	.p2align	4, 0x90
	.type	Point_set,@function
Point_set:                              # @Point_set
	.cfi_startproc
# %bb.0:                                # %entry
	movq	%rdi, -16(%rsp)
	movq	%rsi, -8(%rsp)
	movq	%rdx, -24(%rsp)
	movq	%rsi, (%rdi)
	movq	-16(%rsp), %rax
	movq	-24(%rsp), %rcx
	movq	%rcx, 8(%rax)
	retq
.Lfunc_end0:
	.size	Point_set, .Lfunc_end0-Point_set
	.cfi_endproc
                                        # -- End function
	.globl	Point_area                      # -- Begin function Point_area
	.p2align	4, 0x90
	.type	Point_area,@function
Point_area:                             # @Point_area
	.cfi_startproc
# %bb.0:                                # %entry
	movq	%rdi, -8(%rsp)
	movq	(%rdi), %rax
	imulq	8(%rdi), %rax
	retq
.Lfunc_end1:
	.size	Point_area, .Lfunc_end1-Point_area
	.cfi_endproc
                                        # -- End function
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rbx
	.cfi_def_cfa_offset 16
	subq	$16, %rsp
	.cfi_def_cfa_offset 32
	.cfi_offset %rbx, -16
	movq	%rsp, %rbx
	movl	$10, %esi
	movl	$20, %edx
	movq	%rbx, %rdi
	callq	Point_set@PLT
	movq	%rbx, %rdi
	callq	Point_area@PLT
	cmpq	$200, %rax
	jne	.LBB2_3
# %bb.1:                                # %then
	xorl	%eax, %eax
	jmp	.LBB2_2
.LBB2_3:                                # %ifcont
	movl	$1, %eax
.LBB2_2:                                # %then
	addq	$16, %rsp
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end2:
	.size	main, .Lfunc_end2-main
	.cfi_endproc
                                        # -- End function
	.section	".note.GNU-stack","",@progbits
