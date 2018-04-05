section .data
	meanmsg db 10,"Mean value is:" 
	meanmsg_len equ $-meanmsg

	sdmsg db 10,"Standard deviation is:" 
	sdmsg_len equ $-sdmsg

	varmsg db 10,"Variance is:"
	varmsg_len equ $-varmsg

	array dd 50.00,40.00,30.00,20.00,10.00 ; array
	arraycnt dw 05 ;array size

	dpoint db '.'
	dech dq 100 ;multiplication factor for display with decimal point
	nline db 10
	
section .bss                                                                                                                                                                                                                                                                                                                                                                                                                                                                
	dispbuff resb 1
	result  resd 1 
	resbuff rest 1  ;reserve 10 bytes - 80 bits - required to display result
	variance resd 1
	temp_cnt resb 1
	temp_mul resd 1
	mean resd 1 


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

section .text

global _start

_start: 

	finit 		
	fldz 		
	mov esi,0	
	mov ebx,array	
	xor ecx,ecx 	
	mov ecx,[arraycnt]	
	mov [temp_cnt],ecx	
	dec byte [temp_cnt]	
	fld dword[ebx]		
	inc esi			
up:	fadd dword[ebx+esi*4]	
				
	inc esi			
	dec byte [temp_cnt]	
	cmp byte [temp_cnt],0	
	jnz up			
	
	fidiv word[arraycnt]	
	fst dword[mean]		

	display meanmsg,meanmsg_len	
	call dispres			

	mov ecx,[arraycnt] 		
	mov [temp_cnt],ecx		
	mov ebx,array 			
	mov esi,00 			
	fldz
	
	mov dword[temp_mul],0		
up1: 	fldz				
	fld dword[ebx+esi*4]		
	fsub dword[mean]		
	fst st1				
	fmul 				
	fadd dword[temp_mul]		
	fst dword[temp_mul]		
	
next:	inc esi				
	dec byte[temp_cnt]		
	cmp byte [temp_cnt],0		
	jnz up1				
					
					
		
	fidiv word[arraycnt]		
					
	fst dword[variance]		

	display varmsg,varmsg_len	
	call dispres			


	fld dword[variance]		
	fsqrt 				
	

	display sdmsg,sdmsg_len		
	call dispres			

end: 	exit				
      	

disp8_proc: 
	mov edi,dispbuff	
	mov ecx,02		
back: rol bl,04 		
	mov dl,bl 		
	and dl,0FH 		
	cmp dl,09		
	jbe next1 		
	add dl,07H		
next1:  add dl,30H 
	mov [edi],dl		
	inc edi 		 
	loop back 
	ret

dispres: 
	fimul dword[dech]	
	fbstp tword[resbuff]	
	xor ecx,ecx 		
	mov ecx,9		
	mov esi,resbuff+9	

   up2: push ecx		
	push esi 		
	mov bl,[esi]		
	call disp8_proc 	
	display dispbuff,2	
	pop esi 		
	dec esi 		
	pop ecx 		
	loop up2 		
	display dpoint,1	
	mov bl,[resbuff] 	
	call disp8_proc
	display dispbuff,2 
	display nline,1		
	ret



