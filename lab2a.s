#Lab2a part a
#Chris Casil
#f(a,b,c) = a/4 + b + c*16

   .data
   A: .word 3 # 4 byte A
   B: .word 16 # 4 byte B
   C: .word -4 # 4 byte C

   .text

main: la $t0, A #load address of A and stores into t0
      lw $s0, 0($t0) #gets word at A and stores into s0

      la $t1, B #loads address of B and stores into t1
      lw $s1, 0($t1) #gets word at B and stores into s1
      
      la $t2, C #gets address of C and stores into t2
      lw $s2, 0($t2) #gets word at C and stores into s2

      sll $t3, $s2, 4 #shifts C left by 4, C*16

      srl $t4, $s0, 2 #shifts A right by 2, A/4

      add $t9, $t3, $s1 #adds A/4 and B

   #adds and prints out solution to console
   li $v0, 1
   add $a0, $t9, $t4 #adds C*16 to the rest of the function
   syscall

   #Exit
   li $v0, 10
   syscall

   #OUTPUT: -48