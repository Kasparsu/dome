#include <stdio.h>

int main() {
   setvbuf (stdout, NULL, _IONBF, 0);


   /* my first program in C */
   printf("Hello, World! \n");
   fprintf(stderr, "Hello, please enter your age\n");
   fflush( stdout );
   return 0;
}