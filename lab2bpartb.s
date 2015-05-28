#Lab2b part b
#Chris Casil
#fff0 0nn0 0000 x000 000y 0000 0000 0000 
#0000 0000 0000 0000 0000 00xy 0fff 00nn 

   .data
   invalid: .asciiz "Invalid Input\n" #Invalid Input

   .text

main: li $t0, 0xC2008000 #loads desired value to t0

      li $t8, 0x19F7EFFF #checks for non-zero fields
      and $t7, $t8, $t0
      beq $zero, $t7, core #if invalid then exit

      la $a0, invalid #load address invalid from memory and store it into arguement register 0
      li $v0, 4 #loads the value 4 into register $v0 which is the op code for print string
      syscall

core: srl $t1, $t0, 25 #shifts value right by 25
      andi $t2, $t0, 0x1000 # and immediate to get y
      srl $t3, $t0, 19 #shift value right 19 to get x easier
      andi $t3, $t3, 1 #and immediate to get x

      srl $t4, $t2, 4 #shifts y right by 4 to get to right spot
      sll $t5, $t3, 9 #shifts x left by 10 to get to right spot

      or $t9, $t5, $t4 #or x and y and store in t9

   #prints out sum to console
   li $v0, 1
   or $a0, $t9, $t1 #or t9 with the shifted value
   syscall

   #Exit
   li $v0, 10
   syscall

   #OUTPUT: Invalid Input
   #        97