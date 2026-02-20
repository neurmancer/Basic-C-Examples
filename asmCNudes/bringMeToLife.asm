	.file	"bringMeToLife.c"
	.intel_syntax noprefix
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	endbr64
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 3632
	mov	rax, QWORD PTR fs:40
	mov	QWORD PTR -8[rbp], rax
	xor	eax, eax
	lea	rdx, -3616[rbp]
	mov	eax, 0
	mov	ecx, 450
	mov	rdi, rdx
	rep stosq
	movabs	rax, 2336912335026220872
	movabs	rdx, 2334383527001681785
	mov	QWORD PTR -3616[rbp], rax
	mov	QWORD PTR -3608[rbp], rdx
	movabs	rax, 2340021467471965801
	movabs	rdx, 7739836321243691365
	mov	QWORD PTR -3600[rbp], rax
	mov	QWORD PTR -3592[rbp], rdx
	movabs	rax, 7214887985004617829
	movabs	rdx, 272519819119
	mov	QWORD PTR -3584[rbp], rax
	mov	QWORD PTR -3576[rbp], rdx
	mov	QWORD PTR -3568[rbp], 0
	mov	QWORD PTR -3560[rbp], 0
	mov	QWORD PTR -3552[rbp], 0
	mov	QWORD PTR -3544[rbp], 0
	mov	QWORD PTR -3536[rbp], 0
	mov	QWORD PTR -3528[rbp], 0
	mov	QWORD PTR -3520[rbp], 0
	mov	QWORD PTR -3512[rbp], 0
	mov	QWORD PTR -3504[rbp], 0
	movabs	rax, 2334956330749617484
	movabs	rdx, 7959953342232620921
	mov	QWORD PTR -3496[rbp], rax
	mov	QWORD PTR -3488[rbp], rdx
	movabs	rax, 8749685314117593376
	movabs	rdx, 435711599392
	mov	QWORD PTR -3480[rbp], rax
	mov	QWORD PTR -3472[rbp], rdx
	mov	QWORD PTR -3464[rbp], 0
	mov	QWORD PTR -3456[rbp], 0
	mov	QWORD PTR -3448[rbp], 0
	mov	QWORD PTR -3440[rbp], 0
	mov	QWORD PTR -3432[rbp], 0
	mov	QWORD PTR -3424[rbp], 0
	mov	QWORD PTR -3416[rbp], 0
	mov	QWORD PTR -3408[rbp], 0
	mov	QWORD PTR -3400[rbp], 0
	mov	QWORD PTR -3392[rbp], 0
	mov	QWORD PTR -3384[rbp], 0
	movabs	rax, 2830829460862101591
	movabs	rdx, 7885630759638164854
	mov	QWORD PTR -3376[rbp], rax
	mov	QWORD PTR -3368[rbp], rdx
	movabs	rax, 7887331407997116517
	mov	edx, 98
	mov	QWORD PTR -3360[rbp], rax
	mov	QWORD PTR -3352[rbp], rdx
	mov	QWORD PTR -3344[rbp], 0
	mov	QWORD PTR -3336[rbp], 0
	mov	QWORD PTR -3328[rbp], 0
	mov	QWORD PTR -3320[rbp], 0
	mov	QWORD PTR -3312[rbp], 0
	mov	QWORD PTR -3304[rbp], 0
	mov	QWORD PTR -3296[rbp], 0
	mov	QWORD PTR -3288[rbp], 0
	mov	QWORD PTR -3280[rbp], 0
	mov	QWORD PTR -3272[rbp], 0
	mov	QWORD PTR -3264[rbp], 0
	movabs	rax, 2338623227866409303
	movabs	rdx, 119251636789345
	mov	QWORD PTR -3256[rbp], rax
	mov	QWORD PTR -3248[rbp], rdx
	mov	QWORD PTR -3240[rbp], 0
	mov	QWORD PTR -3232[rbp], 0
	mov	QWORD PTR -3224[rbp], 0
	mov	QWORD PTR -3216[rbp], 0
	mov	QWORD PTR -3208[rbp], 0
	mov	QWORD PTR -3200[rbp], 0
	mov	QWORD PTR -3192[rbp], 0
	mov	QWORD PTR -3184[rbp], 0
	mov	QWORD PTR -3176[rbp], 0
	mov	QWORD PTR -3168[rbp], 0
	mov	QWORD PTR -3160[rbp], 0
	mov	QWORD PTR -3152[rbp], 0
	mov	QWORD PTR -3144[rbp], 0
	movabs	rax, 7598251453016209741
	movabs	rdx, 7306365212199954292
	mov	QWORD PTR -3136[rbp], rax
	mov	QWORD PTR -3128[rbp], rdx
	movabs	rax, 7885648055560464752
	movabs	rdx, 7142820551011628901
	mov	QWORD PTR -3120[rbp], rax
	mov	QWORD PTR -3112[rbp], rdx
	mov	QWORD PTR -3104[rbp], 6581359
	mov	QWORD PTR -3096[rbp], 0
	mov	QWORD PTR -3088[rbp], 0
	mov	QWORD PTR -3080[rbp], 0
	mov	QWORD PTR -3072[rbp], 0
	mov	QWORD PTR -3064[rbp], 0
	mov	QWORD PTR -3056[rbp], 0
	mov	QWORD PTR -3048[rbp], 0
	mov	QWORD PTR -3040[rbp], 0
	mov	QWORD PTR -3032[rbp], 0
	mov	QWORD PTR -3024[rbp], 0
	movabs	rax, 8032487060389785173
	movabs	rdx, 7575164998614655093
	mov	QWORD PTR -3016[rbp], rax
	mov	QWORD PTR -3008[rbp], rdx
	movabs	rax, 2334397761731174516
	movabs	rdx, 7233173991608053345
	mov	QWORD PTR -3000[rbp], rax
	mov	QWORD PTR -2992[rbp], rdx
	movabs	rax, 7738135658831833376
	movabs	rdx, 435627714592
	mov	QWORD PTR -2984[rbp], rax
	mov	QWORD PTR -2976[rbp], rdx
	mov	QWORD PTR -2968[rbp], 0
	mov	QWORD PTR -2960[rbp], 0
	mov	QWORD PTR -2952[rbp], 0
	mov	QWORD PTR -2944[rbp], 0
	mov	QWORD PTR -2936[rbp], 0
	mov	QWORD PTR -2928[rbp], 0
	mov	QWORD PTR -2920[rbp], 0
	mov	QWORD PTR -2912[rbp], 0
	mov	QWORD PTR -2904[rbp], 0
	movabs	rax, 2334391967769387351
	movabs	rdx, 7235441194394742901
	mov	QWORD PTR -2896[rbp], rax
	mov	QWORD PTR -2888[rbp], rdx
	movabs	rax, 2334402142777385061
	mov	edx, 2712941
	mov	QWORD PTR -2880[rbp], rax
	mov	QWORD PTR -2872[rbp], rdx
	mov	QWORD PTR -2864[rbp], 0
	mov	QWORD PTR -2856[rbp], 0
	mov	QWORD PTR -2848[rbp], 0
	mov	QWORD PTR -2840[rbp], 0
	mov	QWORD PTR -2832[rbp], 0
	mov	QWORD PTR -2824[rbp], 0
	mov	QWORD PTR -2816[rbp], 0
	mov	QWORD PTR -2808[rbp], 0
	mov	QWORD PTR -2800[rbp], 0
	mov	QWORD PTR -2792[rbp], 0
	mov	QWORD PTR -2784[rbp], 0
	movabs	rax, 2340021467421106499
	movabs	rdx, 7236828442999480686
	mov	QWORD PTR -2776[rbp], rax
	mov	QWORD PTR -2768[rbp], rdx
	movabs	rax, 7308533390442066720
	movabs	rdx, 7526676531636233760
	mov	QWORD PTR -2760[rbp], rax
	mov	QWORD PTR -2752[rbp], rdx
	movabs	rax, 2891429099776254053
	movabs	rdx, 2334391967769387383
	mov	QWORD PTR -2744[rbp], rax
	mov	QWORD PTR -2736[rbp], rdx
	mov	QWORD PTR -2728[rbp], 2715765
	mov	QWORD PTR -2720[rbp], 0
	mov	QWORD PTR -2712[rbp], 0
	mov	QWORD PTR -2704[rbp], 0
	mov	QWORD PTR -2696[rbp], 0
	mov	QWORD PTR -2688[rbp], 0
	mov	QWORD PTR -2680[rbp], 0
	mov	QWORD PTR -2672[rbp], 0
	mov	QWORD PTR -2664[rbp], 0
	movabs	rax, 7070784924573526338
	movabs	rdx, 2337214414101376876
	mov	QWORD PTR -2656[rbp], rax
	mov	QWORD PTR -2648[rbp], rdx
	movabs	rax, 7142789445701236082
	movabs	rdx, 7737596616070622817
	mov	QWORD PTR -2640[rbp], rax
	mov	QWORD PTR -2632[rbp], rdx
	movabs	rax, 177980383333
	mov	edx, 0
	mov	QWORD PTR -2624[rbp], rax
	mov	QWORD PTR -2616[rbp], rdx
	mov	QWORD PTR -2608[rbp], 0
	mov	QWORD PTR -2600[rbp], 0
	mov	QWORD PTR -2592[rbp], 0
	mov	QWORD PTR -2584[rbp], 0
	mov	QWORD PTR -2576[rbp], 0
	mov	QWORD PTR -2568[rbp], 0
	mov	QWORD PTR -2560[rbp], 0
	mov	QWORD PTR -2552[rbp], 0
	mov	QWORD PTR -2544[rbp], 0
	movabs	rax, 5269323106193139010
	movabs	rdx, 7959303536447021856
	mov	QWORD PTR -2536[rbp], rax
	mov	QWORD PTR -2528[rbp], rdx
	movabs	rax, 7022000363606536036
	movabs	rdx, 45515599275382
	mov	QWORD PTR -2520[rbp], rax
	mov	QWORD PTR -2512[rbp], rdx
	mov	QWORD PTR -2504[rbp], 0
	mov	QWORD PTR -2496[rbp], 0
	mov	QWORD PTR -2488[rbp], 0
	mov	QWORD PTR -2480[rbp], 0
	mov	QWORD PTR -2472[rbp], 0
	mov	QWORD PTR -2464[rbp], 0
	mov	QWORD PTR -2456[rbp], 0
	mov	QWORD PTR -2448[rbp], 0
	mov	QWORD PTR -2440[rbp], 0
	mov	QWORD PTR -2432[rbp], 0
	mov	QWORD PTR -2424[rbp], 0
	movabs	rax, 2334391967770108243
	movabs	rdx, 7307218078032425574
	mov	QWORD PTR -2416[rbp], rax
	mov	QWORD PTR -2408[rbp], rdx
	movabs	rax, 7453010330695724576
	movabs	rdx, 7305437165694437664
	mov	QWORD PTR -2400[rbp], rax
	mov	QWORD PTR -2392[rbp], rdx
	mov	QWORD PTR -2384[rbp], 1701670755
	mov	QWORD PTR -2376[rbp], 0
	mov	QWORD PTR -2368[rbp], 0
	mov	QWORD PTR -2360[rbp], 0
	mov	QWORD PTR -2352[rbp], 0
	mov	QWORD PTR -2344[rbp], 0
	mov	QWORD PTR -2336[rbp], 0
	mov	QWORD PTR -2328[rbp], 0
	mov	QWORD PTR -2320[rbp], 0
	mov	QWORD PTR -2312[rbp], 0
	mov	QWORD PTR -2304[rbp], 0
	movabs	rax, 8386098829110767438
	movabs	rdx, 2339461051476625696
	mov	QWORD PTR -2296[rbp], rax
	mov	QWORD PTR -2288[rbp], rdx
	movabs	rax, 7865335677966182519
	movabs	rdx, 8391735975095138080
	mov	QWORD PTR -2280[rbp], rax
	mov	QWORD PTR -2272[rbp], rdx
	mov	QWORD PTR -2264[rbp], 0
	mov	QWORD PTR -2256[rbp], 0
	mov	QWORD PTR -2248[rbp], 0
	mov	QWORD PTR -2240[rbp], 0
	mov	QWORD PTR -2232[rbp], 0
	mov	QWORD PTR -2224[rbp], 0
	mov	QWORD PTR -2216[rbp], 0
	mov	QWORD PTR -2208[rbp], 0
	mov	QWORD PTR -2200[rbp], 0
	mov	QWORD PTR -2192[rbp], 0
	mov	QWORD PTR -2184[rbp], 0
	movabs	rax, 2841315493291585369
	movabs	rdx, 7791355394590908532
	mov	QWORD PTR -2176[rbp], rax
	mov	QWORD PTR -2168[rbp], rdx
	movabs	rax, 28548958556414309
	mov	edx, 0
	mov	QWORD PTR -2160[rbp], rax
	mov	QWORD PTR -2152[rbp], rdx
	mov	QWORD PTR -2144[rbp], 0
	mov	QWORD PTR -2136[rbp], 0
	mov	QWORD PTR -2128[rbp], 0
	mov	QWORD PTR -2120[rbp], 0
	mov	QWORD PTR -2112[rbp], 0
	mov	QWORD PTR -2104[rbp], 0
	mov	QWORD PTR -2096[rbp], 0
	mov	QWORD PTR -2088[rbp], 0
	mov	QWORD PTR -2080[rbp], 0
	mov	QWORD PTR -2072[rbp], 0
	mov	QWORD PTR -2064[rbp], 0
	movabs	rax, 2334386830921003586
	movabs	rdx, 2334391967937752681
	mov	QWORD PTR -2056[rbp], rax
	mov	QWORD PTR -2048[rbp], rdx
	movabs	rax, 7308041941661544033
	movabs	rdx, 7809634769681345824
	mov	QWORD PTR -2040[rbp], rax
	mov	QWORD PTR -2032[rbp], rdx
	mov	QWORD PTR -2024[rbp], 0
	mov	QWORD PTR -2016[rbp], 0
	mov	QWORD PTR -2008[rbp], 0
	mov	QWORD PTR -2000[rbp], 0
	mov	QWORD PTR -1992[rbp], 0
	mov	QWORD PTR -1984[rbp], 0
	mov	QWORD PTR -1976[rbp], 0
	mov	QWORD PTR -1968[rbp], 0
	mov	QWORD PTR -1960[rbp], 0
	mov	QWORD PTR -1952[rbp], 0
	mov	QWORD PTR -1944[rbp], 0
	movabs	rax, 7072938843391488578
	movabs	rdx, 7308533132493220210
	mov	QWORD PTR -1936[rbp], rax
	mov	QWORD PTR -1928[rbp], rdx
	movabs	rax, 8031079397675837472
	movabs	rdx, 435509881888
	mov	QWORD PTR -1920[rbp], rax
	mov	QWORD PTR -1912[rbp], rdx
	mov	QWORD PTR -1904[rbp], 0
	mov	QWORD PTR -1896[rbp], 0
	mov	QWORD PTR -1888[rbp], 0
	mov	QWORD PTR -1880[rbp], 0
	mov	QWORD PTR -1872[rbp], 0
	mov	QWORD PTR -1864[rbp], 0
	mov	QWORD PTR -1856[rbp], 0
	mov	QWORD PTR -1848[rbp], 0
	mov	QWORD PTR -1840[rbp], 0
	mov	QWORD PTR -1832[rbp], 0
	mov	QWORD PTR -1824[rbp], 0
	mov	DWORD PTR -3620[rbp], 0
	jmp	.L2
.L3:
	lea	rcx, -3616[rbp]
	mov	eax, DWORD PTR -3620[rbp]
	movsx	rdx, eax
	mov	rax, rdx
	sal	rax, 4
	sub	rax, rdx
	sal	rax, 3
	add	rax, rcx
	mov	rdi, rax
	call	puts@PLT
	mov	edi, 222222
	call	usleep@PLT
	add	DWORD PTR -3620[rbp], 1
.L2:
	cmp	DWORD PTR -3620[rbp], 14
	jle	.L3
	mov	eax, 0
	mov	rdx, QWORD PTR -8[rbp]
	sub	rdx, QWORD PTR fs:40
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
