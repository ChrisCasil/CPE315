/* Dennis Wong */
/* Christopher Casil */
/* Lab 4 */
#include <stdio.h>
#include <stdlib.h>
#include <Math.h>

int main() {
   int bias = 1023; // bias
   int *carry, *shift; //pointers to indicate the carry value/shifting amount
   int diff, tempBits, mask; //difference between exponent values, specific bits to be saved, and mask value
   unsigned int ahi, alo, bhi, blo; //64 bit values, separated into 2 ints
   scanf("%x %x %x %x", &ahi, &alo, &bhi, &blo); //obtain user input for values to conduct operations on

   //Get the exponents
   int aExp = ahi & 0x7FF00000;
   int bExp = bhi & 0x7FF00000;

   //Get the signed bits
   int aSign = ahi & 0x80000000;
   int bSign = bhi & 0x80000000;

   //Isolate Mantissa from the rest of the value and add hidden 1
   ahi = ahi & 0x000FFFFF;
   ahi += 0x00100000;
   bhi = bhi & 0x000FFFFF;
   bhi += 0x00100000;


   if(aSign) { //check for 2's complement for a
      alo ^= 0xFFFFFFFF;
      ahi ^= 0xFFFFFFFF;
      if (alo == 0xFFFFFFFF) {
         ahi += 1;
      }
      alo += 1;
   }

   if(bSign) { //check for 2's complement for b
      blo ^= 0xFFFFFFFF;
      bhi ^= 0xFFFFFFFF;
      if (blo == 0xFFFFFFFF) {
         bhi += 1;
      }
      blo += 1;
   }

   //subtract bias(1023) from each exponent
   aExp = aExp >> 20;
   aExp -= bias;
   bExp = bExp >> 20;
   bExp -= bias;

   //check for lower exponent and shift lower mantissa to the right
   if(aExp > bExp) {
      diff = aExp - bExp;  //Calculate the difference between the two exponents
      mask = masker(diff); //Create a custom mask based upon the difference
      tempBits = ahi | mask; //
      bhi = bhi >> diff;
      blo = blo >> diff;
      blo |= (tempBits << (32 - diff));
      bExp = aExp;
   }
   else {
      diff = bExp - aExp;
      mask = masker(diff);
      tempBits = blo | mask;
      ahi = ahi >> diff;
      alo = alo >> diff;
      alo |= (tempBits << (32 - diff));
      aExp = bExp;
   }

   int addhi = add(ahi, bhi, carry);
   *carry = 0;
   int addlo = add(alo, blo, carry);

   if (*carry){
      addhi += 1;
   }

   int tempAdd = normalize(addhi, shift);
   mask = masker(*shift);
   tempBits = addlo | (mask << (32 - *shift));
   addlo = addlo << *shift;
   addhi = addhi << *shift;
   addhi |= (tempBits >> (32 - *shift));
   int newExp = diff - *shift;
   addhi = addhi & 0x000FFFFF;
   newExp += 1023;
   addhi = (newExp << 20) | addhi;

   printf("%x %x\n", addhi, addlo);

   //SUBTRACT
   int subBhi = bhi ^ 0xFFFFFFFF;
   int subBlo = blo ^ 0xFFFFFFFF;
      if (subBlo == 0xFFFFFFFF) {
      subBhi += 1;
   }
   subBlo += 1;

   int subhi = add(ahi, subBhi, carry);
   *carry = 0;
   int sublo = add(alo, subBlo, carry);
   
   if (*carry){
      subhi += 1;
   }   

   *shift = 0;
   int tempSub = normalize(subhi, shift);
   mask = masker(*shift);
   tempBits = sublo | (mask << (32 - *shift));
   sublo = sublo << *shift;
   subhi = subhi << *shift;
   subhi |= (tempBits >> (32 - *shift));
   newExp = diff - *shift;
   subhi = subhi & 0x000FFFFF;
   newExp += 1023;
   subhi = (newExp << 20) | subhi;


   printf("%x %x\n", subhi, sublo);

   //MULTIPLY
   //Convert value A from IEEE 754 to Decimal
   double aDec = 0, bDec = 0; //Decimal representation of the value
   int cnt; //Counter Variable
   int mask = 0x00080000; //create a mask, with the 1 located at the top bit of the mantissa
   for(cnt = 0; cnt < 20; cnt++) { //Iterate through the mantissa and add appropriate value to aDec
      if(ahi & mask) {
         aDec += 1/(2 * (cnt + 1)); //Value to be added. Halved after each iteration
      }
      mask = mask >> 1; //Shifts the masking bit to the right after each iteration
   }
   mask = 0x80000000; //Sets masking bit to highest bit in second part of mantissa
   for(cnt = 0; cnt < 32; cnt++) { //Iterate through mantisdsa and add appropriate value to aDec
      if(alo & mask) {
         aDec += 1/(cnt + 21); //Value to be added. Halved after each iteration (added 23 to accomodate for prior 23 bits)
      }
      mask = mask >> 1; //Shifts masking bit to the right after each iteration
   }
   aDec += 1; //Add one for normalized
   aDec = aDec * pow(2, aExp); //Multiply aDec with power of two.

   //Convert value B from IEEE 754 to Decimal
   mask = 0x00080000; //Set masking with 1 located at the top of the Mantissa
   for(cnt = 0; cnt < 20; cnt++) { //Iterate through the mantissa and add appropriate value to bDec
      if(bhi & mask) {
         bDec += 1/(2 * (cnt + 1)); //Value to be added. Halved after each iteration.
      }
      mask = mask >> 1; //Shifts the masking bit to the right after each iteration.
   }
   mask = 0x80000000; //Sets masking bit to highest bit in the second part of the mantissa
   for(cnt = 0; cnt < 32; cnt++) { //Iterate through second half of mantissa and add proper value to bDec
      if(blo & mask) {
         bDec += 1/(cnt + 21); //Value to be added. Halved after each iteration (added 23 to accomodate for prior 23 bits)
      }
      mask = mask >> 1; //Shift masking bit to the right after each iteration
   }
   bDec += 1; //Add one normalized
   bDec = bDec * pow(2, aExp); //Multiply bDec with power of two

   double product = aDec * bDec;

   int newExp = 0;
   while(product > 2) {
      newExp++;
      product /= 2;
   }

   









}

int masker(int shiftAmt) {
   int custMask = 0;
   int i;0
   for(i=0; i < shiftAmt; i++) {
      custMask |= 1;
      custMask << 1;
   }
   return custMask;
}

int add(int high, int low, int *carry){
   add = high + low;
   if (add < high){
      *carry = 1;
   }
   return add;
}

int normalize(int num, int *shift){
   while (!(num & 0x00100000)){
      num = num << 1;
      *shift++;
   }
   return num;
}