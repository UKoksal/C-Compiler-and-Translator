.data
.text
.globl f
f:
.set noreorder
.set nomacro
addiu $sp, $sp, -8
sw $31, 4($sp)
sw $fp, 0($sp)
move $fp, $sp
addiu $sp, $sp, -4
nop
li $2, 1
beq $2, $0,_falseLabel_3
nop
li $2, 11
b fEnd 
nop
b _trueLabel_2
nop
_falseLabel_3:
li $2, 10
b fEnd 
nop
_trueLabel_2:
li $2, 0
fEnd:
addiu $sp, $sp, 4
move $sp, $fp
lw $31, 4($sp)
lw $fp, 0($sp)
addiu $sp, $sp, 8
j $31
.set macro
.set reorder
