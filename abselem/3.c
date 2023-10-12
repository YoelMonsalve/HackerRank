#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long abssum(int * list, long offset, int pos, int psum, int neg, int nsum){
   long abssum = 0;

   if (offset > 0){
      for (int i = 0; i <= 2000; i++){
         abssum += abs(list[i]*(offset - 2000 + i));
      }
      abssum += offset*pos + psum;
   }
   else {
      for (int i = 2000; i <= 4000; i++){
         abssum += abs(list[i]*(offset - 2000 + i));
      }
      abssum -= offset*neg + nsum;
   }
   return abssum;
}

int main (void) {
   // get size of list
   int n;
   scanf("%d\n", &n);

   // get list
   int Ai = 0;
   int list[4001];
   int pos = 0;
   int psum = 0;
   int neg = 0;
   int nsum = 0;
   memset(list, 0, sizeof(int)*4001);
   for (int i = 0; i < n; i++){
      scanf("%d ", &Ai);
      list[2000+Ai]++;
      if (Ai > 0){
         pos++;
         psum += Ai;
      }
      if (Ai < 0){
         neg++;
         nsum += Ai;
      }
   }

   // get and process the queries
   int q;
   int x;
   int offset = 0;
   long abs = 0;

   scanf("%d\n", &q);
   for (int i = 0; i < q; i++){
      scanf("%d ", &x);
      offset += x;
      abs = abssum(list, offset, pos, psum, neg, nsum);
      fprintf(stdout, "%ld\n", abs);
   }

   return 0;
}
