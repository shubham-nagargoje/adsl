;Count the Positive and Negative Nuber from Array.

section .data
msg1 db 10,"Enter elements of Array:",10,13
msglen1 equ $-msg1
msg2 db 10," Elements of Array are:",10,13
msglen2 equ $-msg2
msg3 db 10,"Number of Positive elements are:"
msglen3 equ $-msg3
msg4 db 10,"Number of Negative elements are:" ,10,13
msglen4 equ $-msg4




nwln db 10
cnt db 0
pcnt db 0
ncnt db 0
arr1 times 80 db 0

section .bss
num resb 5
buff resb 5

%macro input 2
mov eax,3
mov ebx,0
mov ecx ,%1
mov edx,%2
int 80h
%endmacro

%macro output 2
mov eax,4
mov ebx,1
mov ecx,%1
mov edx,%2
int 80h
%endmacro

section .text
global _start
_start:
	output msg1,msglen1
	mov byte[cnt],5
	mov edi,arr1
l1: input num,5
	mov esi,num
	call ascii_original
	mov [edi],bx
	inc edi
	inc edi
	dec byte[cnt]
	jnz l1

	output msg2, msglen2
	mov byte[cnt],5
	mov esi,arr1
l2: mov bx,[esi]
	call original_ascii
	output nwln,1
	inc esi
	inc esi
	dec byte[cnt]
	jnz l2
	mov esi,arr1
	mov byte[cnt],5

l3: mov ax,[esi]
	and ax, 8000h
	jz l4
	inc byte[ncnt]
	jmp l5
l4: inc byte[pcnt]
l5:	inc esi
	inc esi
	dec byte[cnt]
	jnz l3
	output msg3,msglen3
	add byte [pcnt],30h
	output pcnt,1

	output msg4,msglen4
	add byte[ncnt],30h
	output ncnt,1
	
	mov eax,1
	int 80h

ascii_original:

	mov ecx,4
	mov ebx,0
	mov eax,0
up1:
	rol bx,4
	mov al,[esi]
	cmp al, 39h
	jbe down1
	sub al,07h
down1:
	sub al,30h
	add bx,ax
	inc esi
	loop up1
	ret
	
original_ascii:
	mov edi,buff
	mov ecx,4
up2:
	rol bx,4
	mov dl,bl
	and dl,0fh
	cmp dl,09h
	jbe down2
	add dl,07h
down2:
	add dl,30h
	mov[edi],dl
	inc edi
	loop up2
	output buff,4
	ret




