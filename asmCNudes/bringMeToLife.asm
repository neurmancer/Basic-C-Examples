	.file	"bringMeToLife.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$3632, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	-3616(%rbp), %rdx
	movl	$0, %eax
	movl	$450, %ecx
	movq	%rdx, %rdi
	rep stosq
	movabsq	$2336912335026220872, %rax
	movabsq	$2334383527001681785, %rdx
	movq	%rax, -3616(%rbp)
	movq	%rdx, -3608(%rbp)
	movabsq	$2340021467471965801, %rax
	movabsq	$7739836321243691365, %rdx
	movq	%rax, -3600(%rbp)
	movq	%rdx, -3592(%rbp)
	movabsq	$7214887985004617829, %rax
	movabsq	$272519819119, %rdx
	movq	%rax, -3584(%rbp)
	movq	%rdx, -3576(%rbp)
	movq	$0, -3568(%rbp)
	movq	$0, -3560(%rbp)
	movq	$0, -3552(%rbp)
	movq	$0, -3544(%rbp)
	movq	$0, -3536(%rbp)
	movq	$0, -3528(%rbp)
	movq	$0, -3520(%rbp)
	movq	$0, -3512(%rbp)
	movq	$0, -3504(%rbp)
	movabsq	$2334956330749617484, %rax
	movabsq	$7959953342232620921, %rdx
	movq	%rax, -3496(%rbp)
	movq	%rdx, -3488(%rbp)
	movabsq	$8749685314117593376, %rax
	movabsq	$435711599392, %rdx
	movq	%rax, -3480(%rbp)
	movq	%rdx, -3472(%rbp)
	movq	$0, -3464(%rbp)
	movq	$0, -3456(%rbp)
	movq	$0, -3448(%rbp)
	movq	$0, -3440(%rbp)
	movq	$0, -3432(%rbp)
	movq	$0, -3424(%rbp)
	movq	$0, -3416(%rbp)
	movq	$0, -3408(%rbp)
	movq	$0, -3400(%rbp)
	movq	$0, -3392(%rbp)
	movq	$0, -3384(%rbp)
	movabsq	$2830829460862101591, %rax
	movabsq	$7885630759638164854, %rdx
	movq	%rax, -3376(%rbp)
	movq	%rdx, -3368(%rbp)
	movabsq	$7887331407997116517, %rax
	movl	$98, %edx
	movq	%rax, -3360(%rbp)
	movq	%rdx, -3352(%rbp)
	movq	$0, -3344(%rbp)
	movq	$0, -3336(%rbp)
	movq	$0, -3328(%rbp)
	movq	$0, -3320(%rbp)
	movq	$0, -3312(%rbp)
	movq	$0, -3304(%rbp)
	movq	$0, -3296(%rbp)
	movq	$0, -3288(%rbp)
	movq	$0, -3280(%rbp)
	movq	$0, -3272(%rbp)
	movq	$0, -3264(%rbp)
	movabsq	$2338623227866409303, %rax
	movabsq	$119251636789345, %rdx
	movq	%rax, -3256(%rbp)
	movq	%rdx, -3248(%rbp)
	movq	$0, -3240(%rbp)
	movq	$0, -3232(%rbp)
	movq	$0, -3224(%rbp)
	movq	$0, -3216(%rbp)
	movq	$0, -3208(%rbp)
	movq	$0, -3200(%rbp)
	movq	$0, -3192(%rbp)
	movq	$0, -3184(%rbp)
	movq	$0, -3176(%rbp)
	movq	$0, -3168(%rbp)
	movq	$0, -3160(%rbp)
	movq	$0, -3152(%rbp)
	movq	$0, -3144(%rbp)
	movabsq	$7598251453016209741, %rax
	movabsq	$7306365212199954292, %rdx
	movq	%rax, -3136(%rbp)
	movq	%rdx, -3128(%rbp)
	movabsq	$7885648055560464752, %rax
	movabsq	$7142820551011628901, %rdx
	movq	%rax, -3120(%rbp)
	movq	%rdx, -3112(%rbp)
	movq	$6581359, -3104(%rbp)
	movq	$0, -3096(%rbp)
	movq	$0, -3088(%rbp)
	movq	$0, -3080(%rbp)
	movq	$0, -3072(%rbp)
	movq	$0, -3064(%rbp)
	movq	$0, -3056(%rbp)
	movq	$0, -3048(%rbp)
	movq	$0, -3040(%rbp)
	movq	$0, -3032(%rbp)
	movq	$0, -3024(%rbp)
	movabsq	$8032487060389785173, %rax
	movabsq	$7575164998614655093, %rdx
	movq	%rax, -3016(%rbp)
	movq	%rdx, -3008(%rbp)
	movabsq	$2334397761731174516, %rax
	movabsq	$7233173991608053345, %rdx
	movq	%rax, -3000(%rbp)
	movq	%rdx, -2992(%rbp)
	movabsq	$7738135658831833376, %rax
	movabsq	$435627714592, %rdx
	movq	%rax, -2984(%rbp)
	movq	%rdx, -2976(%rbp)
	movq	$0, -2968(%rbp)
	movq	$0, -2960(%rbp)
	movq	$0, -2952(%rbp)
	movq	$0, -2944(%rbp)
	movq	$0, -2936(%rbp)
	movq	$0, -2928(%rbp)
	movq	$0, -2920(%rbp)
	movq	$0, -2912(%rbp)
	movq	$0, -2904(%rbp)
	movabsq	$2334391967769387351, %rax
	movabsq	$7235441194394742901, %rdx
	movq	%rax, -2896(%rbp)
	movq	%rdx, -2888(%rbp)
	movabsq	$2334402142777385061, %rax
	movl	$2712941, %edx
	movq	%rax, -2880(%rbp)
	movq	%rdx, -2872(%rbp)
	movq	$0, -2864(%rbp)
	movq	$0, -2856(%rbp)
	movq	$0, -2848(%rbp)
	movq	$0, -2840(%rbp)
	movq	$0, -2832(%rbp)
	movq	$0, -2824(%rbp)
	movq	$0, -2816(%rbp)
	movq	$0, -2808(%rbp)
	movq	$0, -2800(%rbp)
	movq	$0, -2792(%rbp)
	movq	$0, -2784(%rbp)
	movabsq	$2340021467421106499, %rax
	movabsq	$7236828442999480686, %rdx
	movq	%rax, -2776(%rbp)
	movq	%rdx, -2768(%rbp)
	movabsq	$7308533390442066720, %rax
	movabsq	$7526676531636233760, %rdx
	movq	%rax, -2760(%rbp)
	movq	%rdx, -2752(%rbp)
	movabsq	$2891429099776254053, %rax
	movabsq	$2334391967769387383, %rdx
	movq	%rax, -2744(%rbp)
	movq	%rdx, -2736(%rbp)
	movq	$2715765, -2728(%rbp)
	movq	$0, -2720(%rbp)
	movq	$0, -2712(%rbp)
	movq	$0, -2704(%rbp)
	movq	$0, -2696(%rbp)
	movq	$0, -2688(%rbp)
	movq	$0, -2680(%rbp)
	movq	$0, -2672(%rbp)
	movq	$0, -2664(%rbp)
	movabsq	$7070784924573526338, %rax
	movabsq	$2337214414101376876, %rdx
	movq	%rax, -2656(%rbp)
	movq	%rdx, -2648(%rbp)
	movabsq	$7142789445701236082, %rax
	movabsq	$7737596616070622817, %rdx
	movq	%rax, -2640(%rbp)
	movq	%rdx, -2632(%rbp)
	movabsq	$177980383333, %rax
	movl	$0, %edx
	movq	%rax, -2624(%rbp)
	movq	%rdx, -2616(%rbp)
	movq	$0, -2608(%rbp)
	movq	$0, -2600(%rbp)
	movq	$0, -2592(%rbp)
	movq	$0, -2584(%rbp)
	movq	$0, -2576(%rbp)
	movq	$0, -2568(%rbp)
	movq	$0, -2560(%rbp)
	movq	$0, -2552(%rbp)
	movq	$0, -2544(%rbp)
	movabsq	$5269323106193139010, %rax
	movabsq	$7959303536447021856, %rdx
	movq	%rax, -2536(%rbp)
	movq	%rdx, -2528(%rbp)
	movabsq	$7022000363606536036, %rax
	movabsq	$45515599275382, %rdx
	movq	%rax, -2520(%rbp)
	movq	%rdx, -2512(%rbp)
	movq	$0, -2504(%rbp)
	movq	$0, -2496(%rbp)
	movq	$0, -2488(%rbp)
	movq	$0, -2480(%rbp)
	movq	$0, -2472(%rbp)
	movq	$0, -2464(%rbp)
	movq	$0, -2456(%rbp)
	movq	$0, -2448(%rbp)
	movq	$0, -2440(%rbp)
	movq	$0, -2432(%rbp)
	movq	$0, -2424(%rbp)
	movabsq	$2334391967770108243, %rax
	movabsq	$7307218078032425574, %rdx
	movq	%rax, -2416(%rbp)
	movq	%rdx, -2408(%rbp)
	movabsq	$7453010330695724576, %rax
	movabsq	$7305437165694437664, %rdx
	movq	%rax, -2400(%rbp)
	movq	%rdx, -2392(%rbp)
	movq	$1701670755, -2384(%rbp)
	movq	$0, -2376(%rbp)
	movq	$0, -2368(%rbp)
	movq	$0, -2360(%rbp)
	movq	$0, -2352(%rbp)
	movq	$0, -2344(%rbp)
	movq	$0, -2336(%rbp)
	movq	$0, -2328(%rbp)
	movq	$0, -2320(%rbp)
	movq	$0, -2312(%rbp)
	movq	$0, -2304(%rbp)
	movabsq	$8386098829110767438, %rax
	movabsq	$2339461051476625696, %rdx
	movq	%rax, -2296(%rbp)
	movq	%rdx, -2288(%rbp)
	movabsq	$7865335677966182519, %rax
	movabsq	$8391735975095138080, %rdx
	movq	%rax, -2280(%rbp)
	movq	%rdx, -2272(%rbp)
	movq	$0, -2264(%rbp)
	movq	$0, -2256(%rbp)
	movq	$0, -2248(%rbp)
	movq	$0, -2240(%rbp)
	movq	$0, -2232(%rbp)
	movq	$0, -2224(%rbp)
	movq	$0, -2216(%rbp)
	movq	$0, -2208(%rbp)
	movq	$0, -2200(%rbp)
	movq	$0, -2192(%rbp)
	movq	$0, -2184(%rbp)
	movabsq	$2841315493291585369, %rax
	movabsq	$7791355394590908532, %rdx
	movq	%rax, -2176(%rbp)
	movq	%rdx, -2168(%rbp)
	movabsq	$28548958556414309, %rax
	movl	$0, %edx
	movq	%rax, -2160(%rbp)
	movq	%rdx, -2152(%rbp)
	movq	$0, -2144(%rbp)
	movq	$0, -2136(%rbp)
	movq	$0, -2128(%rbp)
	movq	$0, -2120(%rbp)
	movq	$0, -2112(%rbp)
	movq	$0, -2104(%rbp)
	movq	$0, -2096(%rbp)
	movq	$0, -2088(%rbp)
	movq	$0, -2080(%rbp)
	movq	$0, -2072(%rbp)
	movq	$0, -2064(%rbp)
	movabsq	$2334386830921003586, %rax
	movabsq	$2334391967937752681, %rdx
	movq	%rax, -2056(%rbp)
	movq	%rdx, -2048(%rbp)
	movabsq	$7308041941661544033, %rax
	movabsq	$7809634769681345824, %rdx
	movq	%rax, -2040(%rbp)
	movq	%rdx, -2032(%rbp)
	movq	$0, -2024(%rbp)
	movq	$0, -2016(%rbp)
	movq	$0, -2008(%rbp)
	movq	$0, -2000(%rbp)
	movq	$0, -1992(%rbp)
	movq	$0, -1984(%rbp)
	movq	$0, -1976(%rbp)
	movq	$0, -1968(%rbp)
	movq	$0, -1960(%rbp)
	movq	$0, -1952(%rbp)
	movq	$0, -1944(%rbp)
	movabsq	$7072938843391488578, %rax
	movabsq	$7308533132493220210, %rdx
	movq	%rax, -1936(%rbp)
	movq	%rdx, -1928(%rbp)
	movabsq	$8031079397675837472, %rax
	movabsq	$435509881888, %rdx
	movq	%rax, -1920(%rbp)
	movq	%rdx, -1912(%rbp)
	movq	$0, -1904(%rbp)
	movq	$0, -1896(%rbp)
	movq	$0, -1888(%rbp)
	movq	$0, -1880(%rbp)
	movq	$0, -1872(%rbp)
	movq	$0, -1864(%rbp)
	movq	$0, -1856(%rbp)
	movq	$0, -1848(%rbp)
	movq	$0, -1840(%rbp)
	movq	$0, -1832(%rbp)
	movq	$0, -1824(%rbp)
	movl	$0, -3620(%rbp)
	jmp	.L2
.L3:
	leaq	-3616(%rbp), %rcx
	movl	-3620(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$4, %rax
	subq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$222222, %edi
	call	usleep@PLT
	addl	$1, -3620(%rbp)
.L2:
	cmpl	$14, -3620(%rbp)
	jle	.L3
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L5
	call	__stack_chk_fail@PLT
.L5:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
