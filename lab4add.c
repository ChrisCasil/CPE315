#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
   unsigned int ahi, alo, bhi, blo;
   int bias = 1023;
   int aExp, bExp;
   int aSign, bSign;
   int diff, mask, tempBits;
   int carry, *shift;

    scanf("%x %x %x %x", &ahi, &alo, &bhi, &blo); //obtain user input for values to conduct operations on

   //Get the exponents
   aExp = ahi & 0x7FF00000;
   bExp = bhi & 0x7FF00000;

   //Get the signed bits
   aSign = ahi & 0x80000000;
   bSign = bhi & 0x80000000;

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
      printf("bhi %x\n", bhi);
      diff = aExp - bExp;  //Calculate the difference between the two exponents
      mask = masker(diff); //Create a custom mask based upon the difference
      tempBits = ahi & mask; //
      bhi = bhi >> diff;
      blo = blo >> diff;
      blo |= (tempBits << (32 - diff));
      bExp = aExp;

      printf("bhi after %x\n", bhi);
   }
   else {
      printf("bhi %x\n", bhi);
      diff = bExp - aExp;
      printf("diff... %d\n", diff);
      mask = masker(diff);
      tempBits = blo & mask;
      ahi = ahi >> diff;
      alo = alo >> diff;
      alo |= (tempBits << (32 - diff));
      aExp = bExp;
   }
   int addhi = ahi + bhi;
   printf("ahi... %x\n", ahi);
   printf("bhi... %x\n", bhi);
   printf("addhi %x\n", addhi);
   //int addhi = add(ahi, bhi, carry);
   carry = 0;
   int addlo = alo + blo;
   printf("alo... %x\n", alo);
   printf("blo... %x\n", blo);
   if (addlo < alo){
      carry = 1;
   }
   //int addlo = add(alo, blo, carry);

   if (carry){
      addhi += 1;
   }

   addhi = normalize(addhi, shift);
   printf("after normalize %x\n", addhi);
   mask = masker(*shift);
   tempBits = addlo & (mask << (32 - *shift));
   addlo = addlo << *shift;
   addhi = addhi << *shift;
   addhi |= (tempBits >> (32 - *shift));
   int newExp = aExp - *shift;
   addhi = addhi & 0x000FFFFF;
   newExp += 1023;
   addhi = (newExp << 20) | addhi;

   printf("%x %x\n", addhi, addlo);

}

int masker(int shiftAmt) {
   int custMask = 0;
   int i;
   for(i=0; i < shiftAmt; i++) {
      custMask |= 1;
      custMask << 1;
   }
   return custMask;
}

int add(int high, int low, int *carry){
   int add = high + low;
   if (add < high){
      *carry = 1;
   }
   return add;
}

int normalize(int num, int *shift){
   while (!(num & 0x00100000)){
      num = num << 1;
      printf("num %d\n", num);
      *shift++;
   }
   return num;
}