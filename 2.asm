section .data
msg1 db 10,"Enter the 5 nos. for the array block"
msglen1 equ $-msg1

msg2 db 10,"overlapped block transfer"
msglen2 equ $-msg2

msg3 db 10,"non overlapped block transfer"
msglen3 equ $-msg3

msg4 db 10,"enter any of the above choices"
msglen4 equ $-msg4

msg5 db 10,"the array after block transfer is"
msglen5 equ $-msg5

msg6 db 10,"enter position for block transfer"
msglen6 equ $-msg6

msg7 db 10,"EROOR:pleasew enter correct choice"
msglen7 equ $-msg7

msg8 db 10,10,"continue?"
msglen8 equ $-msg8

msg9 db 10,"exit"
msglen9 equ $-msg9

msg10 db 10,"enter choice"
msglen10 equ $-msg10

space db " "
sp_len equ $-space

arr1 times 80 db 0
arr2 times 80 db 0
cnt db 0

section .bss
num resb 5
buff resb 4
pos resb 2
choice resb 2
answer resb 2

%macro display 2
mov eax,4
mov ebx,1
mov ecx,%1
mov edx,%2
int 80h
%endmacro

%macro accept 2
mov eax,3
mov ebx,0
mov ecx,%1
mov edx,%2
int 80h
%endmacro

section .text
global _start
_start:
display msg2,msglen2
display msg3,msglen3
display msg4,msglen4
accept choice,2
sub byte[choice],30h
cmp byte[choice],01h
je overlap
cmp byte[choice],02h
je non_overlap

display msg7,msglen7
jmp _start
 
overlap:display msg1,msglen1
mov byte[cnt],05
mov edi,arr1

l1:accept num,5
mov ebx,[num]
mov [edi],ebx
add edi,4
dec byte[cnt]
jnz l1
mov esi,arr1
mov edi,arr1

display msg6,msglen6
accept pos,2
sub byte[pos],30h
dec byte[pos]
mov eax,0
mov byte[cnt],5

mov al,byte[cnt]

ll1:add esi,4
dec al
jnz ll1
sub esi,4
mov edi,esi
mov al,[pos]

ll2:add edi,4
dec al
jnz ll2

l2:mov eax,[esi]
mov [edi],eax
sub esi,04h
sub edi,04h
dec byte[cnt]
jnz l2

display msg5,msglen5
mov esi,arr1
mov byte[cnt],5
mov al,[pos]
add byte[cnt],al

l3:mov eax,[esi]
mov [buff],eax
display buff,4
display space,sp_len
add esi,04
dec byte[cnt]
jnz l3
jmp end

non_overlap:
display msg1,msglen1
mov byte[cnt],5
mov edi,arr1

l5:accept num,5
mov eax,[num]
mov [edi],eax
add edi,4
dec byte[cnt]
jnz l5
mov ecx,5
mov esi,arr1
mov edi,arr2

l6:mov eax,[esi]
mov [edi],eax
add esi,04
add edi,04
dec ecx
jnz l6

display msg5,msglen5
mov byte[cnt],5
mov esi,arr2

l4:mov eax,[esi]
mov[num],eax
display num,5
add esi,4
dec byte[cnt]
jnz l4

end:
mov eax,1
int 80h
