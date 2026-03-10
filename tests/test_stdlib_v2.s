	.text
	.file	"novus"
	.globl	Vector_init                     # -- Begin function Vector_init
	.p2align	4, 0x90
	.type	Vector_init,@function
Vector_init:                            # @Vector_init
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rbx
	.cfi_def_cfa_offset 16
	subq	$16, %rsp
	.cfi_def_cfa_offset 32
	.cfi_offset %rbx, -16
	movq	%rdi, %rbx
	movq	%rdi, (%rsp)
	movq	%rsi, 8(%rsp)
	leaq	(,%rsi,8), %rdi
	callq	malloc@PLT
	movq	%rax, (%rbx)
	movq	(%rsp), %rax
	movq	$0, 8(%rax)
	movq	(%rsp), %rax
	movq	8(%rsp), %rcx
	movq	%rcx, 16(%rax)
	addq	$16, %rsp
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	Vector_init, .Lfunc_end0-Vector_init
	.cfi_endproc
                                        # -- End function
	.globl	Vector_push                     # -- Begin function Vector_push
	.p2align	4, 0x90
	.type	Vector_push,@function
Vector_push:                            # @Vector_push
	.cfi_startproc
# %bb.0:                                # %entry
	movq	%rdi, -16(%rsp)
	movq	%rsi, -8(%rsp)
	movq	8(%rdi), %rax
	cmpq	16(%rdi), %rax
	jne	.LBB1_2
# %bb.1:                                # %then
	retq
.LBB1_2:                                # %ifcont
	movq	-16(%rsp), %rax
	movq	(%rax), %rcx
	movq	8(%rax), %rax
	movq	-8(%rsp), %rdx
	movq	%rdx, (%rcx,%rax,8)
	movq	-16(%rsp), %rax
	incq	8(%rax)
	retq
.Lfunc_end1:
	.size	Vector_push, .Lfunc_end1-Vector_push
	.cfi_endproc
                                        # -- End function
	.globl	Vector_get                      # -- Begin function Vector_get
	.p2align	4, 0x90
	.type	Vector_get,@function
Vector_get:                             # @Vector_get
	.cfi_startproc
# %bb.0:                                # %entry
	movq	%rdi, -8(%rsp)
	movq	%rsi, -16(%rsp)
	movq	(%rdi), %rax
	movq	(%rax,%rsi,8), %rax
	retq
.Lfunc_end2:
	.size	Vector_get, .Lfunc_end2-Vector_get
	.cfi_endproc
                                        # -- End function
	.globl	HashSet_init                    # -- Begin function HashSet_init
	.p2align	4, 0x90
	.type	HashSet_init,@function
HashSet_init:                           # @HashSet_init
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%r14
	.cfi_def_cfa_offset 16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	subq	$24, %rsp
	.cfi_def_cfa_offset 48
	.cfi_offset %rbx, -24
	.cfi_offset %r14, -16
	movq	%rdi, %rbx
	movq	%rdi, 8(%rsp)
	movq	%rsi, 16(%rsp)
	leaq	(,%rsi,8), %rdi
	callq	malloc@PLT
	movq	%rax, (%rbx)
	movq	8(%rsp), %rax
	movq	$0, 8(%rax)
	movq	8(%rsp), %rax
	movq	16(%rsp), %rcx
	movq	%rcx, 16(%rax)
	movq	$0, (%rsp)
	.p2align	4, 0x90
.LBB3_1:                                # %whilecond
                                        # =>This Inner Loop Header: Depth=1
	movq	(%rsp), %rax
	cmpq	16(%rsp), %rax
	jge	.LBB3_3
# %bb.2:                                # %whilebody
                                        #   in Loop: Header=BB3_1 Depth=1
	movq	8(%rsp), %rax
	movq	(%rax), %rbx
	movq	(%rsp), %r14
	xorl	%edi, %edi
	callq	malloc@PLT
	movq	%rax, (%rbx,%r14,8)
	incq	(%rsp)
	jmp	.LBB3_1
.LBB3_3:                                # %whileafter
	addq	$24, %rsp
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end3:
	.size	HashSet_init, .Lfunc_end3-HashSet_init
	.cfi_endproc
                                        # -- End function
	.globl	HashSet_hash                    # -- Begin function HashSet_hash
	.p2align	4, 0x90
	.type	HashSet_hash,@function
HashSet_hash:                           # @HashSet_hash
	.cfi_startproc
# %bb.0:                                # %entry
	movq	%rsi, %rax
	movq	%rdi, -8(%rsp)
	movq	%rsi, -16(%rsp)
	cqto
	idivq	16(%rdi)
	movq	%rdx, %rax
	retq
.Lfunc_end4:
	.size	HashSet_hash, .Lfunc_end4-HashSet_hash
	.cfi_endproc
                                        # -- End function
	.globl	HashSet_add                     # -- Begin function HashSet_add
	.p2align	4, 0x90
	.type	HashSet_add,@function
HashSet_add:                            # @HashSet_add
	.cfi_startproc
# %bb.0:                                # %entry
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movq	%rdi, (%rsp)
	movq	%rsi, 16(%rsp)
	movq	%rsp, %rdi
	callq	HashSet_hash@PLT
	movq	%rax, 8(%rsp)
	movq	(%rsp), %rax
	incq	8(%rax)
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end5:
	.size	HashSet_add, .Lfunc_end5-HashSet_add
	.cfi_endproc
                                        # -- End function
	.globl	HashMap_init                    # -- Begin function HashMap_init
	.p2align	4, 0x90
	.type	HashMap_init,@function
HashMap_init:                           # @HashMap_init
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rbx
	.cfi_def_cfa_offset 16
	subq	$16, %rsp
	.cfi_def_cfa_offset 32
	.cfi_offset %rbx, -16
	movq	%rdi, %rbx
	movq	%rdi, (%rsp)
	movq	%rsi, 8(%rsp)
	leaq	(,%rsi,8), %rdi
	callq	malloc@PLT
	movq	%rax, (%rbx)
	movq	(%rsp), %rbx
	movq	8(%rsp), %rdi
	shlq	$3, %rdi
	callq	malloc@PLT
	movq	%rax, 8(%rbx)
	movq	(%rsp), %rax
	movq	$0, 16(%rax)
	movq	(%rsp), %rax
	movq	8(%rsp), %rcx
	movq	%rcx, 24(%rax)
	addq	$16, %rsp
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end6:
	.size	HashMap_init, .Lfunc_end6-HashMap_init
	.cfi_endproc
                                        # -- End function
	.globl	HashMap_put                     # -- Begin function HashMap_put
	.p2align	4, 0x90
	.type	HashMap_put,@function
HashMap_put:                            # @HashMap_put
	.cfi_startproc
# %bb.0:                                # %entry
	movq	%rdi, -24(%rsp)
	movq	%rsi, -8(%rsp)
	movq	%rdx, -16(%rsp)
	movq	(%rdi), %rax
	movq	16(%rdi), %rcx
	movq	%rsi, (%rax,%rcx,8)
	movq	-24(%rsp), %rax
	movq	8(%rax), %rcx
	movq	16(%rax), %rax
	movq	-16(%rsp), %rdx
	movq	%rdx, (%rcx,%rax,8)
	movq	-24(%rsp), %rax
	incq	16(%rax)
	retq
.Lfunc_end7:
	.size	HashMap_put, .Lfunc_end7-HashMap_put
	.cfi_endproc
                                        # -- End function
	.globl	HashMap_get                     # -- Begin function HashMap_get
	.p2align	4, 0x90
	.type	HashMap_get,@function
HashMap_get:                            # @HashMap_get
	.cfi_startproc
# %bb.0:                                # %entry
	movq	%rdi, -16(%rsp)
	movq	%rsi, -8(%rsp)
	movq	$0, -24(%rsp)
	.p2align	4, 0x90
.LBB8_1:                                # %whilecond
                                        # =>This Inner Loop Header: Depth=1
	movq	-24(%rsp), %rax
	movq	-16(%rsp), %rcx
	cmpq	16(%rcx), %rax
	jge	.LBB8_4
# %bb.2:                                # %whilebody
                                        #   in Loop: Header=BB8_1 Depth=1
	movq	-16(%rsp), %rax
	movq	(%rax), %rax
	movq	-24(%rsp), %rcx
	movq	(%rax,%rcx,8), %rax
	cmpq	-8(%rsp), %rax
	je	.LBB8_5
# %bb.3:                                # %ifcont
                                        #   in Loop: Header=BB8_1 Depth=1
	incq	-24(%rsp)
	jmp	.LBB8_1
.LBB8_4:                                # %whileafter
	xorl	%eax, %eax
	retq
.LBB8_5:                                # %then
	movq	-16(%rsp), %rax
	movq	8(%rax), %rax
	movq	-24(%rsp), %rcx
	movq	(%rax,%rcx,8), %rax
	retq
.Lfunc_end8:
	.size	HashMap_get, .Lfunc_end8-HashMap_get
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
	subq	$32, %rsp
	.cfi_def_cfa_offset 48
	.cfi_offset %rbx, -16
	movq	%rsp, %rbx
	movl	$10, %esi
	movq	%rbx, %rdi
	callq	HashMap_init@PLT
	movl	$1, %esi
	movl	$100, %edx
	movq	%rbx, %rdi
	callq	HashMap_put@PLT
	movl	$2, %esi
	movl	$200, %edx
	movq	%rbx, %rdi
	callq	HashMap_put@PLT
	movl	$1, %esi
	movq	%rbx, %rdi
	callq	HashMap_get@PLT
	cmpq	$100, %rax
	jne	.LBB9_3
# %bb.1:                                # %then
	movq	%rsp, %rdi
	movl	$2, %esi
	callq	HashMap_get@PLT
	cmpq	$200, %rax
	jne	.LBB9_3
# %bb.2:                                # %then1
	leaq	.L__unnamed_1(%rip), %rdi
	xorl	%esi, %esi
	xorl	%edx, %edx
	xorl	%ecx, %ecx
	xorl	%eax, %eax
	callq	printf@PLT
	xorl	%eax, %eax
	jmp	.LBB9_4
.LBB9_3:                                # %ifcont2
	movl	$1, %eax
.LBB9_4:                                # %ifcont2
	addq	$32, %rsp
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end9:
	.size	main, .Lfunc_end9-main
	.cfi_endproc
                                        # -- End function
	.type	.L__unnamed_1,@object           # @0
	.section	.rodata.str1.1,"aMS",@progbits,1
.L__unnamed_1:
	.asciz	"HashSet and HashMap test passed\n"
	.size	.L__unnamed_1, 33

	.section	".note.GNU-stack","",@progbits
