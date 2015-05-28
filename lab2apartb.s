#Lab2a part b
#Chris Casil
#f(a,b,c) = a/4 + b + c*16

   .data
   A: .word -22 # 4 byte A
   B: .word -1 # 4 byte B
   C: .word 10 # 4 byte C

   .text

main: la $t0, A #load address of A and stores into t0
      lw $s0, 0($t0) #gets word at A and stores into s0

      la $t1, B #loads address of B and stores into t1
      lw $s1, 0($t1) #gets word at B and stores into s1
      
      la $t2, C #gets address of C and stores into t2
      lw $s2, 0($t2) #gets word at C and stores into s2

      li $t6, 16 #load immediate 16 to t6
      mult $s2, $t6 # C*16
      mflo $t7 # gets solution to C*16

      li $t5, 4 # loads immediate 4 into t5
      div $s0, $t5 # A/4
      mflo $s5 #gets solution of A/4 and stores into s5
      add $t9, $t7, $s1 #adds A/4 and B

   #adds and prints out solution to console
   li $v0, 1
   add $a0, $t9, $s5 #adds C*16 to the rest of the function
   syscall

   #Exit
   li $v0, 10
   syscall


   #OUTPUT: 154