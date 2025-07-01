# Please write your name and ID here
# Name:
# Student ID:

# All memory structures are placed after the
# .data assembler directive
.data
generated:		.word 0, 0, 0   # These numbers will be randomly generated (1 ~ 9)
input:			.word 0, 0, 0	# These numbers will be user's inputs (1 ~ 9)

# Declare main as a global function
.globl main 

# All program code is placed after the
# .text assembler directive
.text 		

# The label 'main' represents the starting point
main:
	la $a0, generated	# $a0 based address of array
	li $a1, 3			# Three random numbers
	li $a2, 0			# Duplicated numbers are not allowed

	jal generate

	#You must print the three random numbers after calling the generate funciton for debugging (testing)

	#You need to get inputs from users and store it into the array input. 
	#la $, input 

	#And you need to compare two arrays, "generated" and "input", to check the numbers of balls and strikes 
	#jal findBalls 
	#jal findStrikes

	#Write your code here

########################################
# findBalls () function starts here
# findBalls(int [] generated, int [] input) 
# return number of balls
findBalls:
	#Write your code here

	jal find

	#Write your code here

	jr $ra
	

########################################
# findStrikes () function starts here
# findStrikes(int [] generated, int [] input) 
# return number of strikes
findStrikes:
	#Write your code here

	jal find

	#Write your code here
	jr $ra


###################################################
# Copy your generate function you implemented 
# for the  previous project
generate:
	jr $ra
	
###################################################
# find (int arr[], int num, int cnt) function is given. 
# This funtion must be used for all functions, i.e., generate, findBalls, findStrikes, to check duplicated numbers. 
# Note, this funtion change $t8 and $t9 registers' values. To keep the state these values are stored in the stack and restored at the end of function call.
# Please let the instructor knows that if you found any bugs from this function.
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
	lw  $t9, 0($t9)
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