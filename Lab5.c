#include <stdio.h>
/* Chris Casil and Dennis Wong */
/* Cache emulation - statistics generation */
/* Generated for CSC 315 Lab 5 */

/* cache sizes */
#define CACHE_SIZE1 16
#define CACHE_SIZE2 256
/* struct to represent an entry in the cache */
typedef struct cacheEntry
{
  int *pointer;
}cacheEntry;

/* static variables, with an array to represent the cache,
 * 2 ints to represent the hits and misses 
 * 2 ints to represent the reads and writes */
static cacheEntry cache[CACHE_SIZE1];
static int hit=0, miss=0;
static int read=0, write=0;

/* reads the value and determines if it has been read and is in the cache already.
 * If it is, hit is incremented. Otherwise, miss is incremented.
 */
int mem_read(int *mp){
  read++;
  printf("Memory read from location %p\n", mp);
  int i, found = 0;
  for(i=0; i < CACHE_SIZE1; i++) {
    if(mp == cache[i].pointer) {
      found = 1;
    }
  }
  if(found) {
    hit++;
  }
  else {
    miss++;
    for(i=0; i < CACHE_SIZE1 && !found; i++){
      if(!cache[i].pointer){
        cache[i].pointer = mp;

        found = 1;
      }
    }
  }
  if(!found){
    cache[0].pointer = mp;
  }
    return 0;
}

/* reads the value and determines if it has been read and is in the cache already.
 * If it is, hit is incremented. Otherwise, miss is incremented.
 */
int mem_write(int *mp){
  write++;
  printf("Memory read from location %p\n", mp);
  int i, found = 0;
  for(i=0; i < CACHE_SIZE1; i++) {
    if(mp == cache[i].pointer) {
      found = 1;
    }
  }
  if(found) {
    hit++;
  }
  else {
    miss++;
    for(i=0; i < CACHE_SIZE1 && !found; i++){
      if(!cache[i].pointer){
        cache[0].pointer = mp;
        found = 1;
      }
    }
  }
  if(!found){
    cache[0].pointer = mp;
  }
    return 0;
  }




int main(){
    int a[10][10], b[10][10], mult[10][10], r1, c1, r2, c2, i, j, k;
    

    int *mp1, *mp2, *mp3;

    printf("Size of pointer is: %d\n\n", sizeof(mp1));

    printf("Enter rows and column for first matrix: ");
    scanf("%d%d", &r1, &c1);
    printf("Enter rows and column for second matrix: ");
    scanf("%d%d",&r2, &c2);

/* If colum of first matrix in not equal to row of second matrix, asking user to enter the size of matrix again. */
    while (c1!=r2)
    {
        printf("Error! column of first matrix not equal to row of second.\n");
        printf("Enter rows and column for first matrix: ");
        scanf("%d%d", &r1, &c1);
        printf("Enter rows and column for second matrix: ");
        scanf("%d%d",&r2, &c2);
    }

    for(i=0; i<CACHE_SIZE1; i++){
      cache[i].pointer = NULL;
    }
    


/* Storing elements of first matrix. */
    printf("\nEnter elements of matrix 1:\n");
    for(i=0; i<r1; ++i)
    for(j=0; j<c1; ++j)
    {
//        printf("Enter elements a%d%d: ",i+1,j+1);
//        scanf("%d",&a[i][j]);
   a[i][j] = i+j; // build sample data

    }

/* Storing elements of second matrix. */
    printf("\nEnter elements of matrix 2:\n");
    for(i=0; i<r2; ++i)
    for(j=0; j<c2; ++j)
    {
//        printf("Enter elements b%d%d: ",i+1,j+1);
//        scanf("%d",&b[i][j]);

         b[i][j] = 10 + i + j;
    }

/* Initializing elements of matrix mult to 0.*/
    for(i=0; i<r1; ++i)
    for(j=0; j<c2; ++j)
    {
       mult[i][j]=0;
    }

/* Multiplying matrix a and b and storing in array mult. */
    for(i=0; i<r1; ++i)
    for(j=0; j<c2; ++j)
    for(k=0; k<c1; ++k)
    {
  
    mp1 = &mult[i][j];
    mp2 = &a[i][k];
    mp3 = &b[k][j];   


   mem_read(mp1);
   mem_read(mp2);
   mem_read(mp3);
   mult[i][j]+=a[i][k]*b[k][j];
   mem_write(mp1); 
   }

/* Displaying the multiplication of two matrix. */
    printf("\nOutput Matrix:\n");
    for(i=0; i<r1; ++i)
    for(j=0; j<c2; ++j)
    {
        printf("%d  ",mult[i][j]);
        if(j==c2-1)
            printf("\n\n");
    }

    printf("hit: %d, miss: %d, read: %d, write: %d\n", hit, miss, read, write);
    return 0;
}