#Dennis Wong 
#Chris Casil
.data
	val1:	.word		50,100,150,200
	val2:	.word		50,100
	val3:	.word		50,100,150,200
.text
.globl main

main: 
	la 		$t0, val1		#load address of val1 into $t0
	
	lw		$a0, 0($t0)		#load value of val1 into $a0
	addi	$t0, 4			#offset to change value
	lw 		$a1, 0($t0)		#load value of val1 into $a1
	addi	$t0, 4			#offset val1 to change value
	lw		$a2, 0($t0)		#load value of val1 into $a2
	addi	$t0, 4			#offset val1 to change value
	lw		$t0, 0($t0)		#load value of val1 into $a3

	jal DOUBLE_ADD			#jump to first function, double_add

	move	$s0, $v0		#store high value in $s0
	move 	$s1, $v1 		#store low value in $s1

	li 		$v0, 1 			#print the high value
	move	$a0, $s0
	syscall

	li 		$v0, 1 			#print the low value
	move	$a0, $s1
	syscall

	la 		$t0, val2		#load address of val2 into $t0
	lw 		$a0, 0($t0)		#load value of val2 into $a0
	addi 	$t0, 4 			#offset value of val2 to change value
	lw 		$a1, 0($t0)		#load value of val2 into $a1

	jal DOUBLE_NEGATE		#jump to second function, double_negate

	move 	$s0, $v0		#store high value in $s0
	move 	$s1, $v1 		#store low value in #s1

	li 		$v0, 1 			#print high value
	move 	$a0, $s0
	syscall

	li 		$v0, 1 			#print low value
	move 	$a0, $s1
	syscall
	
	#code for DOUBLE_SUB
	la 		$t0, val3		#load address of val1 into $t0
	
	lw		$a0, 0($t0)		#load value of val1 into $a0
	addi	$t0, 4			#offset to change value
	lw 		$a1, 0($t0)		#load value of val1 into $a1
	addi	$t0, 4			#offset val1 to change value
	lw		$a2, 0($t0)		#load value of val1 into $a2
	addi	$t0, 4			#offset val1 to change value
	lw		$t0, 0($t0)		#load value of val1 into $a3

	jal DOUBLE_SUB

	move	$s0, $v0		#store high value in $s0
	move 	$s1, $v1 		#store low value in $s1

	li 		$v0, 1 			#print the high value
	move	$a0, $s0
	syscall

	li 		$v0, 1 			#print the low value
	move	$a0, $s1
	syscall

	li $v0, 10
	syscall
	

DOUBLE_ADD:
	addu 	$v1, $a1, $a3	#add least significant word and store in $v1
	sltu 	$v0, $v1, $a3	#set carry in bit, stored in $v0
	addu	$v0, $v0, $a2	#add second most significant word ($a2) and store in $v0
	addu	$v0, $v0, $a0	#add most significant word ($a0) and store in $v0
	jr		$ra 

DOUBLE_NEGATE:
	li 		$t2, 0xFFFFFFFF
	li 		$t3, 0x00000001
	xor 	$a0, $a0, $t2	#invert bit values of $a0
	xor 	$a1, $a1, $t2	#invert bit values of $a1

	add 	$v1, $a1, $t3	#add least significant word to 1 (for 2's complement)
	sltu	$v0, $v1, $t3	#set carry flag if needed
	add 	$v0, $v0, $a0	#add most significant word to $v0
	jr		$ra

DOUBLE_SUB:
	move $t5, $a0			#move $a0 and $a1 to temp registers
	move $t6, $a1
	move $a0, $a2			#move #a2 and $a3 to $a0 and $a1 
	move $a1, $a3

	jal DOUBLE_NEGATE

	move $a0, $t5			#move $a0 and $a1 back to original registers 
	move $a1, $t6
	move $a2, $v0			#move results from $v0 and $v1 to $a2 and $a3
	move $a3, $v1

	jal DOUBLE_ADD
	jr $ra
