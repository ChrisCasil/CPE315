#Lab1a
#Chris Casil

   .data
   value: .word 4155543, 3112 , -2, 1054, -33543, 1233, -433433, 10101, 16384 

   .text

main: li $t9, 0
      la $t3, value
      addi $t5, $zero, 9

loop: lw $t2, 0($t3)
      add $t9, $t9, $t2
      addi $t3, $t3, 4
      addi $t5, $t5, -1
      bnez $t5, loop


   #prints out sum to console
   li $v0, 1
   add $a0, $t9, $zero
   syscall

   #Exit
   li $v0, 10
   syscall