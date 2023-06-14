#include "include/util.h"
#include "include/bf.h"

void bf_run(char* src, FILE* out) {
   fprintf(out, "#include <stdio.h>\n");
   fprintf(out, "#include <stdlib.h>\n");

   fprintf(out, "int main(){\n");
   fprintf(out, "char b[30000];\n");   // create memory buffer
   fprintf(out, "char*p=b;\n");        // create pointer

   while (*src != '\0') {
      switch (*src) {
         case '>': fprintf(out, "p++;\n");         break;   // move pointer right
         case '<': fprintf(out, "p--;\n");         break;   // move pointer left
         case '+': fprintf(out, "++*p;\n");        break;   // increment cell
         case '-': fprintf(out, "--*p;\n");        break;   // decrement cell
         case '[': fprintf(out, "while(*p){\n");   break;   // begin loop
         case ']': fprintf(out, "}\n");            break;   // end loop
         case '.': fprintf(out, "putchar(*p);\n"); break;   // print cell
         case ',': fprintf(out, "*p=getchar();\n");break;   // set cell from stdin
         // ignore all other chars
      }
      src++;
   }

   fprintf(out, "exit(0);\nreturn 0;\n}\n");
}

int main(int argc, char** argv) {
   char* src = (argc - 1)?
      util_src_from_fpath(fopen(argv[1], "rb")):
      util_src_from_stdin();

   bf_run(src, stdout);
   free(src);
   return 0;
}
