#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>
#include <unistd.h>
#include "tokenizer.h"


/*
  sample code to demonstrate the tokenizer. 
  ex: lw $s20 32($s1)
  gives out
  lw
  $s0
  32($s1)
*/

#define MAX_LINE_LENGTH 1024

void parse_file(char *config_file);

int32_t main(int argc, char *argv[])
{
  if (argc < 2)
    {
      printf("usage: %s <input file>\n", argv[0]);
      exit(-1);
    }

  parse_file(argv[1]);
  exit(0);
}

void parse_file(char *src_file)
{
  char line[MAX_LINE_LENGTH + 1];
  char *tok_ptr, *ret, *token = NULL;
  int32_t line_num = 1;
  FILE *fptr;

  fptr = fopen(src_file, "r");
  if (fptr == NULL)
    {
      printf("unable to open file %s. aborting ...\n", src_file);
      exit(-1);
    }

  while (1)
    {
	  // safe way to do file input
      if ((ret = fgets(line, MAX_LINE_LENGTH, fptr)) == NULL) break;
      line[MAX_LINE_LENGTH] = 0;

      tok_ptr = line;
      if (strlen(line) == MAX_LINE_LENGTH)
	{
	  printf("line %d in %s: line is too long. ignoring line ...\n",
		 line_num, src_file);
	  line_num++;
	  continue;
	}

      /* parse the tokens within a line */
      while (1)
	{
	  token = parse_token(tok_ptr, " \n\t", &tok_ptr, NULL);
	  if (token == NULL || *token == '#') /* blank line or comment begins here. go to the next line */
	    {
	      line_num ++;
	      free(token);
	      break;
	    }
	  
	  printf("token: %s\n", token);
	  free(token);
	}
    }
   
  printf("parsed %d lines in the file %s\n", line_num, src_file);
  fclose(fptr);
}

