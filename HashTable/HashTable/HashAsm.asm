global HashTable_HashCRC32_Asm

section .text

;---------------------------------------------------------------
; Calculate CRC32.
;
; Entry: rcx - __m128i pointer.
;
; Return: eax - calculated CRC32.
;
; Destr: rax, rcx, rdx, r8, r9, r10, r11.
;---------------------------------------------------------------
HashTable_HashCRC32_Asm:
		mov	r11d, -1  ; r11d = 0xFFFFFFFF;
		mov	eax, r11d ; eax  = 0xFFFFFFFF;
		
		mov	r9, 0     ; r9   = counter;
		mov	r8, rcx   ; r8   = dataPtr;
		
		lea	r10, [rel Crc32Table] ; r10 = address of Crc32Table
		
		; for (size_t st = 0; data[st] && st < 16; st++)
.forCondition:

		cmp	byte [r8], 0 ; if (data[st] == 0) return;
		je .endFor

		cmp	r9, 16
		jae	.endFor

		; for body:
		
		movzx rcx, byte [r8] ; rcx = *data
		
		xor	rcx, rax ; rcx = (rax ^ *data++)
		shr	rax, 8   ; rax >>= 8;
		
		movzx edx, cl ; edx = (eax ^ *data++) & 0xFF;
		
		mov	ecx, dword [r10 + rdx * 4] ; ecx = Crc32Table[(eax ^ *data++) & 0xFF];
		
		; eax = (eax >> 8) ^ Crc32Table[(eax ^ *data++) & 0xFF];
		xor rax, rcx
	
		; step: 
		inc r8
		inc r9
		
		jmp .forCondition
	
.endFor:

		xor	rax, r11 ; eax ^= 0xFFFFFFFF;
	
		ret
;---------------------------------------------------------------

section .data

Crc32Table:
	DD  000000000H
	DD	077073096H
	DD	0ee0e612cH
	DD	0990951baH
	DD	0076dc419H
	DD	0706af48fH
	DD	0e963a535H
	DD	09e6495a3H
	DD	00edb8832H
	DD	079dcb8a4H
	DD	0e0d5e91eH
	DD	097d2d988H
	DD	009b64c2bH
	DD	07eb17cbdH
	DD	0e7b82d07H
	DD	090bf1d91H
	DD	01db71064H
	DD	06ab020f2H
	DD	0f3b97148H
	DD	084be41deH
	DD	01adad47dH
	DD	06ddde4ebH
	DD	0f4d4b551H
	DD	083d385c7H
	DD	0136c9856H
	DD	0646ba8c0H
	DD	0fd62f97aH
	DD	08a65c9ecH
	DD	014015c4fH
	DD	063066cd9H
	DD	0fa0f3d63H
	DD	08d080df5H
	DD	03b6e20c8H
	DD	04c69105eH
	DD	0d56041e4H
	DD	0a2677172H
	DD	03c03e4d1H
	DD	04b04d447H
	DD	0d20d85fdH
	DD	0a50ab56bH
	DD	035b5a8faH
	DD	042b2986cH
	DD	0dbbbc9d6H
	DD	0acbcf940H
	DD	032d86ce3H
	DD	045df5c75H
	DD	0dcd60dcfH
	DD	0abd13d59H
	DD	026d930acH
	DD	051de003aH
	DD	0c8d75180H
	DD	0bfd06116H
	DD	021b4f4b5H
	DD	056b3c423H
	DD	0cfba9599H
	DD	0b8bda50fH
	DD	02802b89eH
	DD	05f058808H
	DD	0c60cd9b2H
	DD	0b10be924H
	DD	02f6f7c87H
	DD	058684c11H
	DD	0c1611dabH
	DD	0b6662d3dH
	DD	076dc4190H
	DD	001db7106H
	DD	098d220bcH
	DD	0efd5102aH
	DD	071b18589H
	DD	006b6b51fH
	DD	09fbfe4a5H
	DD	0e8b8d433H
	DD	07807c9a2H
	DD	00f00f934H
	DD	09609a88eH
	DD	0e10e9818H
	DD	07f6a0dbbH
	DD	0086d3d2dH
	DD	091646c97H
	DD	0e6635c01H
	DD	06b6b51f4H
	DD	01c6c6162H
	DD	0856530d8H
	DD	0f262004eH
	DD	06c0695edH
	DD	01b01a57bH
	DD	08208f4c1H
	DD	0f50fc457H
	DD	065b0d9c6H
	DD	012b7e950H
	DD	08bbeb8eaH
	DD	0fcb9887cH
	DD	062dd1ddfH
	DD	015da2d49H
	DD	08cd37cf3H
	DD	0fbd44c65H
	DD	04db26158H
	DD	03ab551ceH
	DD	0a3bc0074H
	DD	0d4bb30e2H
	DD	04adfa541H
	DD	03dd895d7H
	DD	0a4d1c46dH
	DD	0d3d6f4fbH
	DD	04369e96aH
	DD	0346ed9fcH
	DD	0ad678846H
	DD	0da60b8d0H
	DD	044042d73H
	DD	033031de5H
	DD	0aa0a4c5fH
	DD	0dd0d7cc9H
	DD	05005713cH
	DD	0270241aaH
	DD	0be0b1010H
	DD	0c90c2086H
	DD	05768b525H
	DD	0206f85b3H
	DD	0b966d409H
	DD	0ce61e49fH
	DD	05edef90eH
	DD	029d9c998H
	DD	0b0d09822H
	DD	0c7d7a8b4H
	DD	059b33d17H
	DD	02eb40d81H
	DD	0b7bd5c3bH
	DD	0c0ba6cadH
	DD	0edb88320H
	DD	09abfb3b6H
	DD	003b6e20cH
	DD	074b1d29aH
	DD	0ead54739H
	DD	09dd277afH
	DD	004db2615H
	DD	073dc1683H
	DD	0e3630b12H
	DD	094643b84H
	DD	00d6d6a3eH
	DD	07a6a5aa8H
	DD	0e40ecf0bH
	DD	09309ff9dH
	DD	00a00ae27H
	DD	07d079eb1H
	DD	0f00f9344H
	DD	08708a3d2H
	DD	01e01f268H
	DD	06906c2feH
	DD	0f762575dH
	DD	0806567cbH
	DD	0196c3671H
	DD	06e6b06e7H
	DD	0fed41b76H
	DD	089d32be0H
	DD	010da7a5aH
	DD	067dd4accH
	DD	0f9b9df6fH
	DD	08ebeeff9H
	DD	017b7be43H
	DD	060b08ed5H
	DD	0d6d6a3e8H
	DD	0a1d1937eH
	DD	038d8c2c4H
	DD	04fdff252H
	DD	0d1bb67f1H
	DD	0a6bc5767H
	DD	03fb506ddH
	DD	048b2364bH
	DD	0d80d2bdaH
	DD	0af0a1b4cH
	DD	036034af6H
	DD	041047a60H
	DD	0df60efc3H
	DD	0a867df55H
	DD	0316e8eefH
	DD	04669be79H
	DD	0cb61b38cH
	DD	0bc66831aH
	DD	0256fd2a0H
	DD	05268e236H
	DD	0cc0c7795H
	DD	0bb0b4703H
	DD	0220216b9H
	DD	05505262fH
	DD	0c5ba3bbeH
	DD	0b2bd0b28H
	DD	02bb45a92H
	DD	05cb36a04H
	DD	0c2d7ffa7H
	DD	0b5d0cf31H
	DD	02cd99e8bH
	DD	05bdeae1dH
	DD	09b64c2b0H
	DD	0ec63f226H
	DD	0756aa39cH
	DD	0026d930aH
	DD	09c0906a9H
	DD	0eb0e363fH
	DD	072076785H
	DD	005005713H
	DD	095bf4a82H
	DD	0e2b87a14H
	DD	07bb12baeH
	DD	00cb61b38H
	DD	092d28e9bH
	DD	0e5d5be0dH
	DD	07cdcefb7H
	DD	00bdbdf21H
	DD	086d3d2d4H
	DD	0f1d4e242H
	DD	068ddb3f8H
	DD	01fda836eH
	DD	081be16cdH
	DD	0f6b9265bH
	DD	06fb077e1H
	DD	018b74777H
	DD	088085ae6H
	DD	0ff0f6a70H
	DD	066063bcaH
	DD	011010b5cH
	DD	08f659effH
	DD	0f862ae69H
	DD	0616bffd3H
	DD	0166ccf45H
	DD	0a00ae278H
	DD	0d70dd2eeH
	DD	04e048354H
	DD	03903b3c2H
	DD	0a7672661H
	DD	0d06016f7H
	DD	04969474dH
	DD	03e6e77dbH
	DD	0aed16a4aH
	DD	0d9d65adcH
	DD	040df0b66H
	DD	037d83bf0H
	DD	0a9bcae53H
	DD	0debb9ec5H
	DD	047b2cf7fH
	DD	030b5ffe9H
	DD	0bdbdf21cH
	DD	0cabac28aH
	DD	053b39330H
	DD	024b4a3a6H
	DD	0bad03605H
	DD	0cdd70693H
	DD	054de5729H
	DD	023d967bfH
	DD	0b3667a2eH
	DD	0c4614ab8H
	DD	05d681b02H
	DD	02a6f2b94H
	DD	0b40bbe37H
	DD	0c30c8ea1H
	DD	05a05df1bH
	DD	02d02ef8dH