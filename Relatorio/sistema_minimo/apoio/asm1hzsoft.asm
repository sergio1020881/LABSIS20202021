/* 
 *  _1hzasmsoftware.asm
 *  Author: Sergio
 */

.INCLUDE<M88DEF.INC>
.ORG 0
	LDI R16, HIGH(RAMEND)
	OUT SPH, R16
	LDI R16, LOW(RAMEND)
	OUT SPL, R16
	LDI R16, (1<<6)
	LDI R17, (1<<6)
	SBI DDRD, 6

BACK:
	EOR R16, R17
	OUT PORTD, R16
	RCALL DELAY_HalfSec
	RJMP BACK
DELAY_HalfSec:
	LDI R20, 32 ;32
L1:	LDI R21, 100 ;100
L2:	LDI R22, 250 ;250
L3:
	NOP
	NOP
	DEC R22
	BRNE L3 ;fall threw

	DEC R21
	BRNE L2 ;fall threw

	DEC R20
	BRNE L1 ;fall threw and exit
	RET
;EOF
