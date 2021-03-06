NAME PROG1
STACK SEGMENT STACK
	STA DB 50 DUP(?)
	TOP EQU LENGTH STA
STACK ENDS

DATA SEGMENT
	NUM DW 0011101000000111B
	NOTES DB 'The result is:','$'
DATA ENDS

CODE SEGMENT
	ASSUME CS:CODE,DS:DATA,ES:DATA,SS:STACK
START:
	MOV AX,DATA
	MOV DS,AX
	MOV AX,STACK
	MOV SS,AX
	MOV SP,TOP
	LEA DX,NOTES;MOV DX,OFFSET NOTES
	MOV AH,09H
	INT 21H
	MOV BX,NUM
	MOV CH,4
ROTATE:
	MOV CL,4
	ROL BX,CL
	MOV AL,BL
	AND AL,0FH
	ADD AL,30H
	CMP AL,'9'
	JLE DISPLAY
	ADD AL,07H
DISPLAY:
	MOV DL,AL
	MOV AH,2
	INT 21H
	DEC CH
	JNZ ROTATE
	MOV AX,4C00H
	INT 21H
CODE ENDS

END START