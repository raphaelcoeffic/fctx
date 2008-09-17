/* 
====================================================================
Copyright (c) 2008 Ian Blumel.  All rights reserved.

This software is licensed as described in the file LICENSE, which
you should have received as part of this distribution.  
====================================================================
File: mkbigtest.c

This file will generate a large "unit tests" file which can be used for
load testing.
*/

/* Keep MicroSoft compilers "quiet". */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

/* This should define a fairly reasonably large test file. Files with more 
unit tests should probably be fragmented. Right now the slow down is 
basically the time it takes to compile the file. */
#define NUM_TESTS 1024

#define TEST_STRING \
   "This is a really, really really long string that I thought would"\
   "give some meat to the tests. I could even make this longer by adding"\
   "more jibberish, but that would probablly be really, really silly."\
   "What I should be doing is coming up with a meater test."
#define FILE_NAME "test_big.c"

int 
main(int argc, char *argv[]) {
   int test_i =0;
   FILE *f = fopen(FILE_NAME, "wt");
   
   if ( f == NULL ) {
      fprintf(stderr, "unable to open 'test_big.c'");
      return 1;
   }

   printf("writing '%s'...", FILE_NAME);
   fprintf(f, "/* This file was generated by mkbigtest.c */\n");
   fprintf(f, "#include \"fft.h\"\n\n");

   fprintf(f, "FFT_BEGIN() {\n");
   
   fprintf(f, "  FFT_SUITE_BEGIN(big_one) {\n");

   for (test_i =0; test_i != NUM_TESTS; ++test_i ) {
      fprintf(f, "    FFT_TEST_BEGIN(test_%d) {\n", test_i+1);
      
      /* Want to test something with a wee bit of meat to it. */
      fprintf(
         f, 
         "      fft_chk(strcmp(\"%s_%d_%s\", \"%s_%d_%s\")==0);\n", 
         TEST_STRING,
         test_i, 
         TEST_STRING,
         TEST_STRING,
         test_i,
         TEST_STRING
         );
      
      fprintf(f, "    } FFT_TEST_END();\n");
   }

   fprintf(f, "  } FFT_SUITE_END();\n");
   fprintf(f, "} FFT_END();\n");

   printf("OK.\n");

   fclose(f);
   f =NULL;

   return 0;
}
