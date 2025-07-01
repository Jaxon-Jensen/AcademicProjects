# Name: Jaxon Jensen
# Student ID: 29966314
# All memory structures are placed after the
# .data assembler directive
.data
error_msg: .asciiz "Error value out of scope for increaseCnt"
out_msg: .asciiz "Result:\n"
semicolon: .asciiz ": "
newline: .asciiz "\n"
input: .word 2, 36, 27, 41, 18, 15, 5, 45, 23, 39, 2 # change these values(and size) to test your program
# This will store the count for each number (The size of this output must be 50 regardless of input's size)
output: .word 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
# Declare main as a global function
.globl main
# All program code is placed after the
# .text assembler directive
.text
# The label 'main' represents the starting point
main:
la $a0, input # $a0 base address of input array
li $a1, 11 # $a1 how many numbers are in the array
la $a2, output # $a2 base address of output array
jal countNumbers
jal printResult
li $v0, 10
syscall

# countNumbers function starts here
# t1 = i, t2 = &input[i], a3 = val
# v1 = return of function inc
countNumbers :
addi $sp, $sp, 4
sw $ra, 0($sp)
addi $t1, $zero, 0
addi $t2, $a0, 0
for :
bge $t1, $a1, endfor
lw $a3, 0($t2) 
jal increaseCnt
beq $v1, 0, ERROR
addi $t1, $t1, 1
addi $t2, $t2, 4
j for

endfor:
lw $ra, 0($sp)
addi $sp, $sp, -4
jr $ra


# increaseCnt function starts here
# t0 = &out[val] , t3 = out[val]
increaseCnt:
addi $sp, $sp, 4
sw $ra, 0($sp)
addi $v1, $zero, 0
bgt $a3, 49, endinc
blt $a3, 1, endinc
sll $a3, $a3, 2
add $t0, $a2, $a3
lw $t3, 0($t0)
addi $t3, $t3, 1
sw $t3, 0($t0)

addi $v1, $zero, 1
endinc:
lw $ra, 0($sp)
addi $sp, $sp, -4
jr $ra


# printResult function starts here
# t4 = i, t5 = &out[i], t6 = out[i]
printResult:
addi $sp, $sp, 4
sw $ra, 0($sp)
li $v0, 4
la $a0, out_msg
syscall
li $t4, 0
la $t5, 0($a2)
print_loop:
bge $t4, 49, print_loop_end
lw $t6, 0($t5)
beqz $t6, zero
li $v0, 1
addi $a0, $t4, 0
syscall
li $v0, 4
la $a0, semicolon
syscall
li $v0, 1
addi $a0, $t6, 0
syscall
li $v0, 4
la $a0, newline
syscall
zero:
addi $t4, $t4, 1
addi $t5, $t5, 4
j print_loop

print_loop_end:
lw $ra, 0($sp)
addi $sp, $sp, -4
jr $ra

ERROR: 
li $v0, 4
la $a0, error_msg
syscall
li $v0, 10
syscall
