# Please write your name and ID here
# Name: Jaxon Jensen
# Student ID: 29966314
# All memory structures are placed after the
# .data assembler directive
.data
generated: .word 0, 0, 0, 0, 0, 0 # These numbers will be randomly generated (1 ~ 45) for each iteration
input: .word 0, 0, 0, 0, 0, 0, 0 # These numbers will be user's inputs (1 ~ 45)
matching: .word 0, 0, 0, 0, 0, 0 # Storing matching numbers
newLine:      .asciiz "\n"
prize1:       .asciiz "All matches. 1st prize\n"
prize2:       .asciiz "2nd prize\n"
prize3:       .asciiz "3rd prize\n"
prize4:       .asciiz "4th prize\n"
prize5:       .asciiz "5th prize\n"
loseMsg:      .asciiz "Lose.\n"
noMatchMsg:   .asciiz "No matching numbers. Lose\n"
bonus:       .asciiz "and bounus ["
inPrompt:     .asciiz "Input number: "
drawPrompt:   .asciiz "How many drawings: "
drawStart:    .asciiz "Drawing started\n"
drawNum:      .asciiz "Drawing "
drawNumTwo:   .asciiz ": ["
comma:        .asciiz ", "
closeBracket: .asciiz "]: "
closePd:       .asciiz "]. "
matchingMsg:  .asciiz "Matching ["
# Declare main as a global function
.globl main
# All program code is placed after the
# .text assembler directive
.text
# The label 'main' represents the starting point
main:
li $t0, 0
la $t1, input
inputLoop:
bgt $t0, 6, endInput
la $a0, inPrompt
li $v0, 4
syscall
li $v0, 5            # read int
syscall
sw $v0, ($t1)
addi $t0, $t0,1
addi $t1, $t1,4
j inputLoop
endInput:

la $a0, drawPrompt
li $v0, 4
syscall
li $v0, 5            
syscall
addi $s0, $v0, 0

la $a0, drawStart
li $v0, 4
syscall

li $t0, 1
drawLoop:
bgt $t0, $s0, endDrawing
la $a0, generated
li $a1, 6
jal generate
jal sort
li $v0, 4
la $a0, drawNum
syscall
li $v0 1
addi $a0, $t0, 0
syscall
li $v0, 4
la $a0, drawNumTwo
syscall

li $t1, 0
la $t2, generated
printGenerate:
bge $t1, 5, endPrintGenerate
lw $a0, ($t2)
li $v0, 1
syscall
li $v0, 4
la $a0, comma
syscall
addi $t1, $t1, 1
addi $t2, $t2, 4
j printGenerate
endPrintGenerate:
lw $a0, ($t2)
li $v0, 1
syscall
li $v0, 4
la $a0, closeBracket
syscall
addi $t0, $t0, 1

jal drawing
j drawLoop
endDrawing:
li $v0, 10           # exit
syscall

drawing:
addi $sp, $sp, -4
sw $ra, 0($sp)
li $t3, 0 #index
la $t4, input
la $t5, matching
li $t6, 0 #num matches
li $t7, 0 #bonus 
la $a0, generated
li $a2, 6
matchLoop:
bge $t3, 7, endMatchLoop
lw $a1, ($t4)
jal find
beq $v0, -1, noMatch
beq $t3, 6, bonusNum
sw $a1, ($t5)
addi $t5, $t5, 4
addi $t6, $t6, 1
noMatch:
addi $t3, $t3, 1
addi $t4, $t4, 4
j matchLoop
bonusNum:
addi $t7, $t7, 1

endMatchLoop:
beqz $t6, noMatches
li $v0, 4
la $a0, matchingMsg
syscall
li $t4, 0
la $t5, matching
addi $t6, $t6, -1 
printMatches:
bge $t4, $t6, endPrintMatches
lw $a0, ($t5)
li $v0, 1
syscall
li $v0, 4
la $a0, comma
syscall
addi $t4, $t4, 1
addi $t5, $t5, 4
j printMatches
endPrintMatches:
lw $a0, ($t5)
li $v0, 1
syscall
li $v0, 4
la $a0, closePd
syscall
addi $t6, $t6, 1
beqz $t7, noBonus
li $v0, 4
la $a0, bonus
syscall
lw $a0, input+24
li $v0, 1
syscall
li $v0, 4
la $a0, closePd
syscall
noBonus:
j matchCheck

noMatches:
li $v0, 4
la $a0, noMatchMsg
syscall
j endMatchCheck

matchCheck:
li $v0, 4
blt $t6, 6, notSix
la $a0, prize1
syscall
j endMatchCheck
notSix:
blt $t6, 5, notFive
bnez $t7, thirdPrize
la $a0, prize3
syscall
j endMatchCheck
thirdPrize:
la $a0, prize2
syscall
j endMatchCheck
notFive:
blt $t6, 4, notFour
la $a0, prize4
syscall
j endMatchCheck
notFour:
blt $t6, 3, notThree
la $a0, prize5
syscall
j endMatchCheck
notThree:
la $a0, loseMsg
syscall

endMatchCheck:
addi $v0, $t6, 0
lw $ra, 0($sp)
addi $sp, $sp, 4
jr $ra

sort:
addi $sp, $sp, -20
sw $ra, 0($sp)
sw $t0, 4($sp) #start idx
sw $t1, 8($sp) #loop idx
sw $t2, 12($sp) #var 1
sw $t3, 16($sp) #var 2
li $t0, 5 
sortLoopOut:
beqz $t0, sortDone
li $t1, 0
sortLoopIn:
beq $t1, $t0, endSortLoopIn
sll $t1, $t1, 2
lw $t2, generated($t1)
lw $t3, generated+4($t1)
blt $t2,$t3, properOrder
sw $t2, generated+4($t1)
sw $t3, generated($t1)
properOrder:
srl $t1, $t1, 2
addi $t1, $t1, 1
j sortLoopIn
endSortLoopIn:
addi $t0, $t0, -1
j sortLoopOut

sortDone:
lw $ra, 0($sp)
lw $t0, 4($sp)
lw $t1, 8($sp)
lw $t2, 12($sp)
lw $t3, 16($sp)
addi $sp, $sp, 20
jr $ra


# t0 = i, t1 = temp, t2 = current array address, s0 = passed a0, s1 = passed a1
generate:
addi $sp, $sp, -20
sw $ra, 0($sp)
sw $t0, 4($sp)
sw $t1, 8($sp)
sw $t2, 12($sp)
sw $s0, 16($sp)
addi $t2, $a0, 0
addi $s0, $a0, 0
addi $s1, $a1, 0
addi $a2, $a1, 0

li $t0, 0
randLoop:
bge $t0, $s1, endRandLoop
li $v0, 42
li $a1, 45
syscall

addi $t1, $a0, 1
addi $a0, $s0, 0
addi $a1, $t1, 0

jal find
bne $v0, -1, randLoop
sw $t1, 0($t2)
addi $t2, $t2, 4
addi $t0, $t0, 1
j randLoop

endRandLoop:
addi $a0, $s0, 0
addi $a1, $s1, 0
lw $ra, 0($sp)
lw $t0, 4($sp)
lw $t1, 8($sp)
lw $t2, 12($sp)
lw $s0, 16($sp)
addi $sp, $sp, 20
jr $ra

# find (int arr[], int num, int cnt) function is given.
find:
addi $sp, $sp, -8
sw $t8, 4($sp)
sw $t9, 0($sp)
li $t8, 0
li $v0, -1

find_loop_start:
bge $t8, $a2, find_loop_end
sll $t9, $t8, 2
add $t9, $t9, $a0
lw $t9, 0($t9)
beq $t9, $a1, find_loop_found
addi $t8, $t8, 1
j find_loop_start

find_loop_found:
addi $v0, $t8, 0
find_loop_end:
lw $t8, 4($sp)
lw $t9, 0($sp)
addi $sp, $sp, 8
jr $ra
