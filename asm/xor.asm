section .text 
    global _start

print:
    push ebp
    mov ebp, esp

    %stacksize flat
    %arg buf_ptr:dword, count:dword

    mov edx, [count]
    mov ecx, [buf_ptr]
    mov ebx, 1
    mov eax, 4
    int 0x80

    mov esp, ebp
    pop ebp
    ret

encode_decode:
    push ebp
    mov ebp, esp

    %stacksize flat
    %arg buf_ptr:word, count:dword, key:dword

    mov eax, [buf_ptr]
    mov ecx, [count]
    mov edx, [key]

    next: ; xor loop
        xor [eax + ecx - 1], dl ; xor encodeing
        dec ecx
        jne next
    
    mov esp, ebp
    pop ebp
    ret

exit:
    mov eax, 1
    int 0x80

_start:
    mov eax, msg

    ; encode
    push 0xA
    push msg_len
    push eax
    call encode_decode

    ; print encoded message
    push msg_len
    push eax
    call print

    ; decode
    push 0xA
    push msg_len 
    push ecx
    call encode_decode

    ; print decoded message
    push msg_len
    mov byte[eax + msg_len - 1], 0xA ; append \n at the end of the line
    push eax
    call print

    jmp exit


section .data
    msg:      db 'MyImportantMessage', 0x0
    msg_len:  equ $-msg