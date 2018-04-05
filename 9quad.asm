; Assignment to calculate root of quadratic equation
;---------------------------------------------------------------------------
;---------------------------------------------------------------------------
section .data

	discrmsg db 10,"Discriminent:" ; displaying discriminent
	discrmsg_len equ $-discrmsg



	r1msg db 10,"Roots are Real: first root:" ; displaying root1
	r1msg_len equ $-r1msg
	
	r2msg db 10,"Roots are Real: second root:" ; displaying root1
	r2msg_len equ $-r2msg

	imsg db 10,"Roots are imaginary :" 	
	imsg_len equ $-imsg
	
	omsg db 10,"Only one root :" 	
	omsg_len equ $-omsg

	dpoint db '.'
	hdec dq 10000	; 4 digits after decimal point
	nline db 10

	a dd 7.0
	b dd 9.0
	c dd 11.0

;---------------------------------------------------------------------------
section .bss                                                                                                                                                                                                                                                                                                                                                                                                                                                                
	dispbuff resb 1

	resbuff rest 1 

	temp_ans resd 1
	temp_ans1 resd 1

	const resw 1



%macro display 2
	mov	eax,4		;print
	mov	ebx,1		;stdout/screen
	mov	ecx,%1	;msg
	mov	edx,%2	;msg_len
	int 80h
%endmacro

%macro exit 0
	mov eax,1
	int 80h
%endmacro

;-----------------------------------------------------------------------------
section .text

global _start

_start: 

	finit 		;initialize the co-processor
	fldz 		; load 0.0 on the stack
	fld dword[b]	; get b on top of stack
	fst st1		; store b on st1
	fmul 		; b^2 result is on st1
	fst st1		; store result in st1
	fld dword[a]	; get a on top of stack
	fmul dword[c]	; multiply a*c
	mov word[const],4	; move 4 into const
	fimul word[const]	; multiply 4* earlier multiplied(a*c) result on stack
	fchs			; make it -ve as -4ac in formula
	fadd st1		; add b^2 to it ( we have now result of b^2-4ac )
	fst dword[temp_ans]	; store it in temp-ans
	fst dword[temp_ans1]	; store it in temp-ans1
	
	display discrmsg,discrmsg_len
	call dispres		; displaying the discriminant
	
	fld dword[temp_ans]
	ftst 
	fstsw ax
	sahf
	ja Realroots
	jb imagienaryroots
	jz oneroot
	
	
	
	
oneroot: 

	fld dword[b]		;load b
	fchs			; -b
	
	fst st1			; store this to st1 - numerator
	fld dword[a]		; load a
	mov word[const],2	; take 2 value in const
	
	fimul word[const]	; multiply 2*a - result on stack
	fxch st1		; exchange st0 and st1
	fdiv st1		; divide st0 by st1, result on st0 
	
	display omsg,omsg_len	; display the result
	call dispres

jmp end


Realroots:

	fld dword[temp_ans]	;load stack with this value
	fsqrt			; take square root
	fst st1			; store the result in st1 (sq root of b^2-4ad on st1)
	fld dword[b]		;load b
	fchs			; -b
	fadd st1		; -b + ( sq.root result earlir stored in st1)
	fst st1			; store this to st1 - numerator
	fld dword[a]		; load a
	mov word[const],2	; take 2 value in const
	fimul word[const]	; multiply 2*a - result on stack
	fxch st1		; exchange st0 and st1
	fdiv st1		; divide st0 by st1, result on st0 
	
	display r1msg,r1msg_len	; display the result
	call dispres


	fld dword[temp_ans1]	; load stack with b^2 -4ac	
	fsqrt			; take square root
	fchs			; make it -ve (2nd root)
	fst st1			; store it to st1
	fld dword[b]		; load b
	fchs			; -b
	fadd st1		; -b - ( sq.root result earlir stored in st1)
	fst st1			; store this to st1 - numerator
	fld dword[a]		; load a
	mov word[const],2	; take 2 value in const
	fimul word[const]	; multiply 2*a - result on stack
	fxch st1		; exchange st0 and st1
	fdiv st1		; divide st0 by st1, result on st0 

	
	display r2msg,r2msg_len
	call dispres

jmp end




imagienaryroots:

display imsg,imsg_len
	
	
	


end: 	exit
      	

;----------------------------------------------------------------------------------
disp8_proc: 
	mov edi,dispbuff	;form the ascii value to disply in dispbuff
	mov ecx,02		; count 2 for 2 digits
back:   rol bl,04 		; lower nibble
	mov dl,bl 
	and dl,0FH 
	cmp dl,09
	jbe next1 
	add dl,07H
next1:  add dl,30H 
	mov [edi],dl	;store the num in ascii 
	inc edi 
	loop back 
	ret
;-----------------------------------------------------------------------------------
dispres: 
	fimul dword[hdec] 	;multiply by multiple of 10 to get decimal places
	fbstp tword[resbuff]	; store the result in resbuff
	xor ecx,ecx 		
	mov ecx,8		; loop till 8 for the mantissa part as 4 decimal places
	mov esi,resbuff+9	; from the 9th byte, display backwards 
   up2: push ecx		; push ecx and esi changed in display proc + macro
	push esi 	
	mov bl,[esi]		; get first 2 digits
	call disp8_proc 	; convert to ascii
	display dispbuff,2	;display two digits	
	pop esi 		;get esi
	dec esi 		; dec to go to next two digits
	pop ecx 		; loop counter
	loop up2 	
	display dpoint,1	; show decimal point
	mov bl,[esi]		; get remaining digits after the decimal point
	push esi 
	call disp8_proc		
	display dispbuff,2 	
	pop esi
	dec esi	
	mov bl,[esi]
	call disp8_proc
	display dispbuff,2 
	display nline,1
	ret


;-----------------------------------------------------------------------------------------------------
;prachi@prachi:~/Desktop/MIL-2016-17/NDP$ nasm -f elf ndp-root3.asm
;prachi@prachi:~/Desktop/MIL-2016-17/NDP$ ld -m elf_i386 -o ndp-root3 ndp-root3.o
;prachi@prachi:~/Desktop/MIL-2016-17/NDP$ ./ndp-root3

;Discriminent:8000000000000023.0000

;Root 1:0000000000000000.4490

;Root 2:8000000000000001.9490
;prachi@prachi:~/Desktop/MIL-2016-17/NDP$ 





