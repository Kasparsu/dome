#include <stdio.h>

int main() {
   setbuf(stdout, NULL);
   /* my first program in C */
   printf("Hello, World! \n");
   fflush( stdout );
   return 0;
}