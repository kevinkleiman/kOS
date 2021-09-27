; Define null, code, data, and stack segment descriptors
gdt_null_descriptor:
    dd 0
    dd 0
gdt_code_descriptor:
    dw 0xFFFF
    dw 0
    db 0
    db 0b10011010 ; type flags (code, last 4 bits)
    db 0
    db 0b11001111
    db 0
gdt_data_descriptor:
    dw 0xFFFF
    dw 0
    db 0
    db 0b10010010 ; type flags (data, last 4 bits)
    db 0
    db 0b11001111
    db 0

gdt_end:

gdt_descriptor:
    gdt_size:
        dw gdt_end - gdt_null_descriptor - 1
        dd gdt_null_descriptor

CODE_SEGMENT equ gdt_code_descriptor - gdt_null_descriptor
DATA_SEGMENT equ gdt_data_descriptor - gdt_null_descriptor


