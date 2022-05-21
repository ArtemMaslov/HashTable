global HashTable_HashCRC32_Asm

section .text

;---------------------------------------------------------------
; Calculate CRC32 for 128 bit data.
;
; Entry: rcx - data address.
;
; Return: eax - calculated CRC32.
;
; Destr: rax
;---------------------------------------------------------------
HashTable_HashCRC32_Asm:
		xor		eax, eax

		crc32	rax, qword [rcx]
		crc32	rax, qword [rcx + 8]

		ret