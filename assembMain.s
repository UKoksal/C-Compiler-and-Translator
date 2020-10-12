.text
.globl main
main:
.set noreorder
.set nomacro
addiu $sp, $sp, -8
sw $31, 4($sp)
sw $fp, 0($sp)
move $fp, $sp
#functioncall
jal f
nop
b mainEnd 
nop
li $2, 1
mainEnd:
move $sp, $fp
lw $31, 4($sp)
lw $fp, 0($sp)
addiu $sp, $sp, 8
j $31
.set macro
.set reorder
