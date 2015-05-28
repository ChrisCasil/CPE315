#Lab1b
#Chris Casil

   .data
   value: .byte 40, 33, -127, 122, 4, 0, 16, 24, 32, -5, 123  

   .text

main: li $t9, 0
      la $t3, value
      addi $t5, $zero, 11

loop: lb $t2, 0($t3)
      add $t9, $t9, $t2
      addi $t3, $t3, 1
      addi $t5, $t5, -1
      bnez $t5, loop


   #prints out sum to console
   li $v0, 1
   add $a0, $t9, $zero
   syscall

   #Exit
   li $v0, 10
   syscall