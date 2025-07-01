# Please write your name and ID here
# Name: Jaxon Jensen
# Student ID: 29966314
.data
enterGuess: .asciiz "\n\nEnter guess: "
newLine: .asciiz "\n"
badInputDuplicateMsg: .asciiz "Cannot have duplicate numbers\n"
badInputNotNumMsg: .asciiz "Only enter 1-9 ex) 123\n"
ballsThreeMsg: .asciiz "3 balls"
ballsMsg: .asciiz "2 balls"
ballMsg: .asciiz "1 ball"
strikeMsg: .asciiz "1 Strike "
strikeTwoMsg: .asciiz "2 Strikes "
winMsg: .asciiz "\nGood Job! Do you want to play again (Y/N)? "
outMsg: .asciiz "Out"
generated: .word 0, 0, 0 # These numbers will be randomly generated (1 ~ 9)
input: .word 1, 2, 3 # These numbers will be user's inputs (1 ~ 9)
user: .space 4
YN: .space 2
.globl main
.text

main:
la $a0, generated # $a0 based address of array
li $a1, 3 # $a1 how many numbers are generated
jal generate

addi $t0, $zero, 0
addi $s0, $a0, 0
li $v0, 1
printGenerate:
bge $t0, $a1, endPrintGenerate
lw $a0, ($s0)
syscall
addi $t0, $t0, 1
addi $s0, $s0, 4
j printGenerate

endPrintGenerate:
li $v0, 4
la $a0, newLine
syscall

guessLoop: # Prompt for user
la $a0, enterGuess
li $v0, 4
syscall # Reads only 3 bits from input and sends to next line

li $v0, 8
la $a0, user
li $a1, 4
syscall
li $v0, 4
la $a0, newLine
syscall

li $t4, 0 # i in the for loop
la $t5, user
la $t7, input
forInput:
bge $t4, 3, endForInput
lb $t6, 0($t5) #temp
addi $t6, $t6, -48 #convert to int
blt $t6, 1, badInputNotNum
bgt $t6, 9, badInputNotNum

la $a0, input #load parameters for find and run
move $a1, $t6
move $a2, $t4
jal find
bne $v0, -1, badInputDuplicate
sw $t6, 0($t7)
addi $t4, $t4, 1 #increment i and both addresses
addi $t5, $t5, 1
addi $t7, $t7, 4
j forInput
endForInput:

li $v0, 4
la $a0, newLine
syscall

la $a0, generated
la $a1, input
jal findStrikes
move $t9, $v0
beq $v0, 3, win 
beqz $v0, Balls
beq $v0, 1, oneStrike
j twoStrikes

win:
li $v0, 4
la $a0, winMsg
syscall

li $v0, 8 #read in and reset if asked
la $a0, YN
li $a1, 2
syscall
lb $t0, YN
li $v0, 4
la $a0, newLine
syscall
syscall
beq $t0, 89, main

li $v0, 10
syscall

oneStrike:
li $v0, 4
la $a0, strikeMsg
syscall
j Balls
twoStrikes:
li $v0, 4
la $a0, strikeTwoMsg
syscall

Balls:
la $a0, generated
la $a1, input
jal findBalls

beqz $v0, outCheck
beq $v0, 1, oneBall
beq $v0, 2, twoBall

li $v0, 4
la $a0, ballsThreeMsg
syscall
j guessLoop

outCheck:
bne $t9, 0, guessLoop
li $v0, 4
la $a0, outMsg
syscall
j guessLoop

twoBall:
li $v0, 4
la $a0, ballsMsg
syscall
j guessLoop

oneBall:
li $v0, 4
la $a0, ballMsg
syscall
j guessLoop

badInputDuplicate:
li $v0, 4
la $a0, badInputDuplicateMsg
syscall
j guessLoop

badInputNotNum:
li $v0, 4
la $a0, badInputNotNumMsg
syscall
j guessLoop

#generate() function starts here
# t0 = i, t1 = temp, t2 = current array address, s0 = passed a0, s1 = passed a1
generate:
addi $sp, $sp, -4
sw $ra, 0($sp)
addi $t2, $a0, 0
addi $s0, $a0, 0
addi $s1, $a1, 0
addi $a2, $a1, 0

li $t0, 0
randLoop:
bge $t0, $s1, endRandLoop
li $v0, 42
li $a1, 9
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
addi $sp, $sp, 4
jr $ra

#findBalls () function starts here
# t0 = cnt, t1 = i, t2 = &input[i], t3 = input[i]
findBalls:
addi $sp, $sp, -8
sw $ra, 0($sp)
sw $a1, 4($sp)

li $t0, 0
li $t1, 0
addi $t2, $a1, 0
lw $t3, 0($t2)
li $a2, 3
ballsLoop:
bge $t1, 3, endBallsLoop
addi $a1, $t3, 0

jal find

beq $v0, -1, bInc
beq $v0, $t1, bInc
addi $t0, $t0, 1

bInc:
addi $t1, $t1, 1
addi $t2, $t2, 4
lw $t3, 0($t2)
j ballsLoop

endBallsLoop:
addi $v0, $t0, 0

lw $a1, 4($sp)
lw $ra, 0($sp)
addi $sp, $sp, 8
jr $ra

#findfindStrikes () function starts here
# t0 = cnt, t1 = i, t2 = &input[i], t3 = input[i]
findStrikes:
addi $sp, $sp, -8
sw $ra, 0($sp)
sw $a1, 4($sp)

li $t0, 0
li $t1, 0
addi $t2, $a1, 0
lw $t3, 0($t2)
li $a2, 3
strikesLoop:
bge $t1, 3, endStrikesLoop
addi $a1, $t3, 0

jal find

bne $v0, $t1, sInc
addi $t0, $t0, 1

sInc:
addi $t1, $t1, 1
addi $t2, $t2, 4
lw $t3, 0($t2)
j strikesLoop

endStrikesLoop:
addi $v0, $t0, 0

lw $a1, 4($sp)
lw $ra, 0($sp)
addi $sp, $sp, 8
jr $ra

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