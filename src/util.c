#include "include/util.h"

void util_die(const char* fmt, ...) {
   va_list ap;
   fprintf(stderr, "[\e[31m==\e[0m] ");
   va_start(ap, fmt);
   vfprintf(stderr, fmt, ap);
   va_end(ap);
   fprintf(stderr, "\n");
   exit(1);
}

void util_log(const char* fmt, ...) {
   va_list ap;
   fprintf(stderr, "[\e[36m===\e[0m] ");
   va_start(ap, fmt);
   vfprintf(stderr, fmt, ap);
   va_end(ap);
   fprintf(stderr, "\n");
}

char* util_get_src(char* arg) {
   if (arg) {
      FILE* f = fopen(arg, "rb");
      return util_src_from_fpath(f);
   } else {
      return util_src_from_stdin();
   }
}

char* util_src_from_stdin() {
   size_t  len = 0;
   char* src = calloc(len, sizeof(char));

   while (src[len - 1] != '%') {
      char c = getchar();
      src = realloc(src, (len + sizeof(char)));
      memcpy(src + len, &c, sizeof(char));
      len += sizeof(char);
   }

   src[len - 1] = '\0'; // drop the last '%' char

   return src;
}

char* util_src_from_fpath(FILE* f) {
   if (!f) {
      util_die("source file not found");
   }

   fseek(f, 0L, SEEK_END);
   long fsize = ftell(f);
   rewind(f);

   char* src = calloc(1, fsize + 1);

   if ((fread(src, fsize, 1, f) != 1) || !src) {
      fclose(f);
      free(src);
      util_die("could not read source file");
   }

   return src;
}
