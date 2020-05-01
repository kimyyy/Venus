	.file	"main.cpp"
	.text
	.globl	_Z5panicPKw
	.def	_Z5panicPKw;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z5panicPKw
_Z5panicPKw:
.LFB0:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	16(%rbp), %rcx
	call	_Z4putsPKw
.L2:
	jmp	.L2
	.seh_endproc
	.section .rdata,"dr"
	.align 2
.LC0:
	.ascii "m\0a\0l\0l\0o\0c\0\0\0"
	.text
	.globl	_Z6mallocm
	.def	_Z6mallocm;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z6mallocm
_Z6mallocm:
.LFB1:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	movq	.refptr.ST(%rip), %rax
	movq	(%rax), %rax
	movq	96(%rax), %rax
	movq	64(%rax), %rax
	movl	16(%rbp), %edx
	leaq	-16(%rbp), %rcx
	movq	%rcx, %r8
	movl	$2, %ecx
	call	*%rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	leaq	.LC0(%rip), %rdx
	movq	%rax, %rcx
	call	_Z6assertyPKw
	movq	-16(%rbp), %rax
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
	.align 2
.LC1:
	.ascii "f\0r\0e\0e\0\0\0"
	.text
	.globl	_Z4freePv
	.def	_Z4freePv;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z4freePv
_Z4freePv:
.LFB2:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	.refptr.ST(%rip), %rax
	movq	(%rax), %rax
	movq	96(%rax), %rax
	movq	72(%rax), %rax
	movq	16(%rbp), %rcx
	call	*%rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	leaq	.LC1(%rip), %rdx
	movq	%rax, %rcx
	call	_Z6assertyPKw
	nop
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	_ZdlPv
	.def	_ZdlPv;	.scl	2;	.type	32;	.endef
	.seh_proc	_ZdlPv
_ZdlPv:
.LFB3:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	16(%rbp), %rcx
	call	_Z4freePv
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	_ZdlPvy
	.def	_ZdlPvy;	.scl	2;	.type	32;	.endef
	.seh_proc	_ZdlPvy
_ZdlPvy:
.LFB4:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	%rdx, 24(%rbp)
	movq	16(%rbp), %rcx
	call	_Z4freePv
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
	.align 2
.LC2:
	.ascii "n\0e\0w\0 \0f\0a\0i\0l\0e\0d\0\0\0"
	.text
	.globl	_Znwy
	.def	_Znwy;	.scl	2;	.type	32;	.endef
	.seh_proc	_Znwy
_Znwy:
.LFB5:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	16(%rbp), %rax
	movl	%eax, %ecx
	call	_Z6mallocm
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L9
	leaq	.LC2(%rip), %rcx
	call	_Z5panicPKw
.L9:
	movq	-8(%rbp), %rax
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	_Znay
	.def	_Znay;	.scl	2;	.type	32;	.endef
	.seh_proc	_Znay
_Znay:
.LFB6:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	16(%rbp), %rax
	movl	%eax, %ecx
	call	_Z6mallocm
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L12
	leaq	.LC2(%rip), %rcx
	call	_Z5panicPKw
.L12:
	movq	-8(%rbp), %rax
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
	.align 8
.LC3:
	.ascii "O\0p\0e\0n\0P\0r\0o\0t\0o\0c\0o\0l\0(\0l\0i\0p\0)\0\0\0"
	.align 8
.LC4:
	.ascii "l\0i\0p\0-\0>\0F\0i\0l\0e\0P\0a\0t\0h\0:\0 \0\0\0"
	.align 2
.LC5:
	.ascii "\15\0\12\0\0\0"
	.align 8
.LC6:
	.ascii "O\0p\0e\0n\0p\0r\0o\0t\0o\0c\0o\0l\0(\0d\0p\0p\0)\0\0\0"
	.align 2
.LC7:
	.ascii "d\0e\0v\0_\0p\0a\0t\0h\0:\0 \0\0\0"
	.align 2
.LC8:
	.ascii "t\0e\0s\0t\0.\0e\0f\0i\0\0\0"
	.align 8
.LC9:
	.ascii "d\0e\0v\0_\0p\0a\0t\0h\0_\0m\0e\0r\0g\0e\0d\0:\0 \0\0\0"
	.align 2
.LC10:
	.ascii "L\0o\0a\0d\0I\0m\0a\0g\0e\0\0\0"
	.align 8
.LC11:
	.ascii "L\0o\0a\0d\0I\0m\0a\0g\0e\0:\0 \0S\0u\0c\0c\0e\0s\0s\0!\0\15\0\12\0\0\0"
	.align 2
.LC12:
	.ascii "s\0t\0a\0r\0t\0i\0m\0a\0g\0e\0\0\0"
	.align 8
.LC13:
	.ascii "s\0t\0a\0r\0t\0I\0m\0a\0g\0e\0:\0 \0S\0u\0c\0c\0e\0s\0s\0!\0\15\0\12\0\0\0"
	.text
	.globl	_Z10StartImagePv
	.def	_Z10StartImagePv;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z10StartImagePv
_Z10StartImagePv:
.LFB7:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$96, %rsp
	.seh_stackalloc	96
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	.refptr.ST(%rip), %rax
	movq	(%rax), %rax
	movq	96(%rax), %rax
	movq	280(%rax), %rax
	leaq	-40(%rbp), %rdx
	movl	$2, 40(%rsp)
	movq	$0, 32(%rsp)
	movq	16(%rbp), %r9
	movq	%rdx, %r8
	movq	.refptr.lip_guid(%rip), %rdx
	movq	16(%rbp), %rcx
	call	*%rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	leaq	.LC3(%rip), %rdx
	movq	%rax, %rcx
	call	_Z6assertyPKw
	leaq	.LC4(%rip), %rcx
	call	_Z4putsPKw
	movq	.refptr.DPTTP(%rip), %rax
	movq	(%rax), %rax
	movq	8(%rax), %rax
	movq	-40(%rbp), %rdx
	movq	32(%rdx), %rcx
	movl	$0, %r8d
	movl	$0, %edx
	call	*%rax
	movq	%rax, %rcx
	call	_Z4putsPKw
	leaq	.LC5(%rip), %rcx
	call	_Z4putsPKw
	movq	.refptr.ST(%rip), %rax
	movq	(%rax), %rax
	movq	96(%rax), %rax
	movq	280(%rax), %rax
	movq	-40(%rbp), %rdx
	movq	24(%rdx), %rcx
	leaq	-48(%rbp), %rdx
	movl	$2, 40(%rsp)
	movq	$0, 32(%rsp)
	movq	16(%rbp), %r9
	movq	%rdx, %r8
	movq	.refptr.dpp_guid(%rip), %rdx
	call	*%rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	leaq	.LC6(%rip), %rdx
	movq	%rax, %rcx
	call	_Z6assertyPKw
	leaq	.LC7(%rip), %rcx
	call	_Z4putsPKw
	movq	.refptr.DPTTP(%rip), %rax
	movq	(%rax), %rax
	movq	8(%rax), %rax
	movq	-48(%rbp), %rcx
	movl	$0, %r8d
	movl	$0, %edx
	call	*%rax
	movq	%rax, %rcx
	call	_Z4putsPKw
	leaq	.LC5(%rip), %rcx
	call	_Z4putsPKw
	movq	.refptr.DPFTP(%rip), %rax
	movq	(%rax), %rax
	movq	8(%rax), %rax
	leaq	.LC8(%rip), %rcx
	call	*%rax
	movq	%rax, -16(%rbp)
	movq	.refptr.DPUP(%rip), %rax
	movq	(%rax), %rax
	movq	24(%rax), %rax
	movq	-48(%rbp), %rcx
	movq	-16(%rbp), %rdx
	call	*%rax
	movq	%rax, -24(%rbp)
	leaq	.LC9(%rip), %rcx
	call	_Z4putsPKw
	movq	.refptr.DPTTP(%rip), %rax
	movq	(%rax), %rax
	movq	8(%rax), %rax
	movq	-24(%rbp), %rcx
	movl	$0, %r8d
	movl	$0, %edx
	call	*%rax
	movq	%rax, %rcx
	call	_Z4putsPKw
	leaq	.LC5(%rip), %rcx
	call	_Z4putsPKw
	movq	.refptr.ST(%rip), %rax
	movq	(%rax), %rax
	movq	96(%rax), %rax
	movq	200(%rax), %rax
	movq	-24(%rbp), %rcx
	leaq	-32(%rbp), %rdx
	movq	%rdx, 40(%rsp)
	movq	$0, 32(%rsp)
	movl	$0, %r9d
	movq	%rcx, %r8
	movq	16(%rbp), %rdx
	movl	$0, %ecx
	call	*%rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	leaq	.LC10(%rip), %rdx
	movq	%rax, %rcx
	call	_Z6assertyPKw
	leaq	.LC11(%rip), %rcx
	call	_Z4putsPKw
	movq	.refptr.ST(%rip), %rax
	movq	(%rax), %rax
	movq	96(%rax), %rax
	movq	208(%rax), %rax
	movq	-32(%rbp), %rcx
	movl	$0, %r8d
	movl	$0, %edx
	call	*%rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	leaq	.LC12(%rip), %rdx
	movq	%rax, %rcx
	call	_Z6assertyPKw
	leaq	.LC13(%rip), %rcx
	call	_Z4putsPKw
	nop
	addq	$96, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
	.align 2
.LC14:
	.ascii "A\0l\0l\0o\0c\0a\0t\0e\0P\0o\0o\0l\0\0\0"
	.align 2
.LC15:
	.ascii "F\0r\0e\0e\0P\0o\0o\0l\0\0\0"
	.text
	.globl	_Z15AllocateAndDrawv
	.def	_Z15AllocateAndDrawv;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z15AllocateAndDrawv
_Z15AllocateAndDrawv:
.LFB8:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$64, %rsp
	.seh_stackalloc	64
	.seh_endprologue
	movq	.refptr.ST(%rip), %rax
	movq	(%rax), %rax
	movq	96(%rax), %rax
	movq	64(%rax), %rax
	leaq	-32(%rbp), %rdx
	movq	%rdx, %r8
	movl	$262144, %edx
	movl	$2, %ecx
	call	*%rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	leaq	.LC14(%rip), %rdx
	movq	%rax, %rcx
	call	_Z6assertyPKw
	movq	-32(%rbp), %rax
	movq	%rax, -8(%rbp)
	movl	$0, -12(%rbp)
.L19:
	cmpl	$255, -12(%rbp)
	ja	.L16
	movl	$0, -16(%rbp)
.L18:
	cmpl	$255, -16(%rbp)
	ja	.L17
	movl	-12(%rbp), %eax
	movl	%eax, %edx
	movq	-8(%rbp), %rax
	movb	%dl, (%rax)
	movl	-16(%rbp), %eax
	movl	%eax, %edx
	movq	-8(%rbp), %rax
	movb	%dl, 1(%rax)
	movq	-8(%rbp), %rax
	movb	$0, 2(%rax)
	movq	-8(%rbp), %rax
	movb	$-1, 3(%rax)
	addq	$4, -8(%rbp)
	addl	$1, -16(%rbp)
	jmp	.L18
.L17:
	addl	$1, -12(%rbp)
	jmp	.L19
.L16:
	movq	-32(%rbp), %rax
	movl	$256, %r8d
	movl	$256, %edx
	movq	%rax, %rcx
	call	_Z3bltPhjj
	movq	.refptr.ST(%rip), %rax
	movq	(%rax), %rax
	movq	96(%rax), %rax
	movq	72(%rax), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rcx
	call	*%rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	leaq	.LC15(%rip), %rdx
	movq	%rax, %rcx
	call	_Z6assertyPKw
	nop
	addq	$64, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section	.text$_ZN7wStringC1EyPKw,"x"
	.linkonce discard
	.align 2
	.globl	_ZN7wStringC1EyPKw
	.def	_ZN7wStringC1EyPKw;	.scl	2;	.type	32;	.endef
	.seh_proc	_ZN7wStringC1EyPKw
_ZN7wStringC1EyPKw:
.LFB11:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	%rdx, 24(%rbp)
	movq	%r8, 32(%rbp)
	movq	16(%rbp), %rax
	movq	24(%rbp), %rdx
	movq	%rdx, 8(%rax)
	movq	16(%rbp), %rax
	movq	8(%rax), %rdx
	movq	16(%rbp), %rax
	movq	%rdx, 16(%rax)
	movq	16(%rbp), %rax
	movq	8(%rax), %rax
	addq	$1, %rax
	movabsq	$4611686018427387900, %rdx
	cmpq	%rdx, %rax
	ja	.L21
	addq	%rax, %rax
	jmp	.L23
.L21:
	call	__cxa_throw_bad_array_new_length
.L23:
	movq	%rax, %rcx
	call	_Znay
	movq	%rax, %rdx
	movq	16(%rbp), %rax
	movq	%rdx, (%rax)
	movq	16(%rbp), %rax
	movq	(%rax), %rdx
	movq	32(%rbp), %rax
	movq	%rax, %rcx
	call	_Z6strcpyPKwPw
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
	.align 2
.LC16:
	.ascii "H\0e\0l\0l\0o\0\0\0"
	.text
	.globl	efi_main
	.def	efi_main;	.scl	2;	.type	32;	.endef
	.seh_proc	efi_main
efi_main:
.LFB12:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$64, %rsp
	.seh_stackalloc	64
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	%rdx, 24(%rbp)
	movq	24(%rbp), %rax
	movq	%rax, %rcx
	call	_Z8efi_initP14EfiSystemTable
	call	_Z11ClearScreenv
	leaq	-32(%rbp), %rax
	leaq	.LC16(%rip), %r8
	movl	$20, %edx
	movq	%rax, %rcx
	call	_ZN7wStringC1EyPKw
	movq	-32(%rbp), %rax
	movq	%rax, %rcx
	call	_Z4putsPKw
.L25:
	jmp	.L25
	.seh_endproc
	.ident	"GCC: (GNU) 7.3-win32 20180312"
	.def	_Z4putsPKw;	.scl	2;	.type	32;	.endef
	.def	_Z6assertyPKw;	.scl	2;	.type	32;	.endef
	.def	_Z3bltPhjj;	.scl	2;	.type	32;	.endef
	.def	__cxa_throw_bad_array_new_length;	.scl	2;	.type	32;	.endef
	.def	_Z6strcpyPKwPw;	.scl	2;	.type	32;	.endef
	.def	_Z8efi_initP14EfiSystemTable;	.scl	2;	.type	32;	.endef
	.def	_Z11ClearScreenv;	.scl	2;	.type	32;	.endef
	.section	.rdata$.refptr.DPUP, "dr"
	.globl	.refptr.DPUP
	.linkonce	discard
.refptr.DPUP:
	.quad	DPUP
	.section	.rdata$.refptr.DPFTP, "dr"
	.globl	.refptr.DPFTP
	.linkonce	discard
.refptr.DPFTP:
	.quad	DPFTP
	.section	.rdata$.refptr.dpp_guid, "dr"
	.globl	.refptr.dpp_guid
	.linkonce	discard
.refptr.dpp_guid:
	.quad	dpp_guid
	.section	.rdata$.refptr.DPTTP, "dr"
	.globl	.refptr.DPTTP
	.linkonce	discard
.refptr.DPTTP:
	.quad	DPTTP
	.section	.rdata$.refptr.lip_guid, "dr"
	.globl	.refptr.lip_guid
	.linkonce	discard
.refptr.lip_guid:
	.quad	lip_guid
	.section	.rdata$.refptr.ST, "dr"
	.globl	.refptr.ST
	.linkonce	discard
.refptr.ST:
	.quad	ST
