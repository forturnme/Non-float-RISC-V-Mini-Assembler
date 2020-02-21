#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>
#include <unistd.h>
#include <math.h>

#define TEMP_FILE_NAME "kkumar91temp.txt"
#define MAX_LINE_LENGTH 256

/*
 * Description: Provides several utility methods that the assembler will use when assembling.
 */

char* int32_to_bin(int32_t val, int32_t numOfBits);

int count_num_occurances(const char* str, char character);

void reverse(char* input);

void zeroth_pass(char* src_file);

/*
 * =======================================================================================
 * Zeroth pass. This handles the case for extra credit when we have multiple data and text
 * segments. It goes through and first gathers all the text segments and does the same for 
 * the data sections. We will call the temp file we generate "kkumar91temp.txt" and we delete
 * the file after each use.
 *
 * =======================================================================================
 */
void zeroth_pass(char* src_file)
{
	FILE *src_fptr;
	FILE *dest_fptr;
	char line[MAX_LINE_LENGTH + 1];
	char *ret = NULL;
	int32_t text_part = FALSE;
	int32_t data_part = FALSE;

	// Open the file for reading.
	src_fptr = fopen(src_file, "r");
	if (src_fptr == NULL)
	{
		// Check to see if we were able to open the file successfully.
		printf("ERROR: Unable to open file %s. Aborting...\n", src_file);
		exit(-1);
	}
	// Open the file for writing.
	dest_fptr = fopen(TEMP_FILE_NAME, "w");
	if (dest_fptr == NULL)
	{
		// Check to see if we were able to open the file successfully.
		printf("ERROR: Unable to open file %s. Aborting...\n", TEMP_FILE_NAME);
		exit(-1);
	}

	// We do .text segment first
	//fputs(".text\n", dest_fptr);
	while ((ret = fgets(line, MAX_LINE_LENGTH, src_fptr)) != NULL)
	{
		text_part = TRUE;
		data_part = FALSE;
		// If we find a .data in the middle, loop until we find another .text
		if (strstr(line, ".data") != NULL || strstr(line, ".DATA") != NULL)
		{
			while ((ret = fgets(line, MAX_LINE_LENGTH, src_fptr)))
			{
				text_part = FALSE;
				data_part = TRUE;
				if (strstr(line, ".text") || strstr(line, ".TEXT"))
				{
					text_part = TRUE;
					fputs(".text", dest_fptr);
					char* temp1 = strstr(line, ".text");
					char* temp2 = strstr(line, ".TEXT");
					char* temp = (temp1==NULL)?temp2:temp1;
					fputs(temp+5, dest_fptr);
					break;
				}
			}
			text_part = TRUE;
		}
		else if (text_part == TRUE)
		{
			if (strstr(line, ".text") == NULL || strstr(line, ".TEXT") == NULL)
			{
				char* comment = strstr(line,":");
				if(comment!=NULL)// handle with labels
				{
					//*comment = "\n";
					char templine[MAX_LINE_LENGTH+1];
					strcpy(templine, line);
					templine[comment-line+1]='\n';
					templine[comment-line+2]='\0';
					fputs(templine, dest_fptr);
					fputs(comment+1, dest_fptr);
				}
				else fputs(line, dest_fptr);
			}
		}		
	}
	

	//fputs("nop\n.data\n", dest_fptr);
	//fputs("\n.data\n", dest_fptr);

	// Start over
	fclose(src_fptr);
	src_fptr = fopen(src_file, "r");

	if (src_fptr == NULL)
	{
		// Check to see if we were able to open the file successfully.
		printf("ERROR: Unable to open file %s. Aborting...\n", src_file);
		exit(-1);
	}

	while ((ret = fgets(line, MAX_LINE_LENGTH, src_fptr)) != NULL)
	{
		text_part = FALSE;
		data_part = TRUE;
		// If we find a .text within the .data section, look through until we reach data again.
		if (strstr(line, ".text") != NULL || strstr(line, ".TEXT") != NULL)
		{
			while ((ret = fgets(line, MAX_LINE_LENGTH, src_fptr)) != NULL)
			{
				text_part = TRUE;
				data_part = FALSE;
				if (strstr(line, ".data") || strstr(line, ".DATA"))
				{
					data_part = TRUE;
					break;
				}
			}
				
			data_part = TRUE;
		}
		else if (data_part == TRUE )
		{
			if(strstr(line, ".data") != NULL || strstr(line, ".DATA") != NULL)
			{
				fputs(".data", dest_fptr);
				char* temp1 = strstr(line, ".data");
				char* temp2 = strstr(line, ".DATA");
				char* temp = (temp1==NULL)?temp2:temp1;
				fputs(temp+5, dest_fptr);
			}
			else fputs(line, dest_fptr);	
		}		
	}
		
	fclose(src_fptr);
	fclose(dest_fptr);
}

/*
 * ============================================================================
 *
 * Converts a given integer value using the given numOfBits. Method: Loop until 
 * the value given is not 0, shift left by one each iteration. And it with a mask
 * of 1 and add a one to our output. Reverse the string at the end.
 *
 * ============================================================================
 */
char* int32_to_bin(int32_t val, int32_t numOfBits)
{
	char* output = (char*)(malloc(numOfBits + 1));
	memset(output,0,numOfBits + 1);//init
	int mask = 1;
	int count = 0;
	int32_t num = val;
	int neg_flag = FALSE;
	if (num < 0)
		neg_flag = TRUE;
	while (num != 0)
	{
		if (num == -1 && neg_flag == TRUE)
			break;
		int temp = num & mask;
		if (temp == 0)
		{
			strcat(output, "0"); 
			num = num >> 1;
			count++;
		}
		else
		{
			strcat(output, "1");
			num = num >> 1;
			count++;
		}
	}
	while (count < numOfBits)
	{
		// Sign extension
		if (neg_flag == TRUE)
		{
			strcat(output, "1");
			count++;
		}
		else
		{
			strcat(output, "0");
			count++;
		}
	}
	output[strlen(output)] = '\0';
	reverse(output);
	return output;
}

/*
 * =========================================================================
 * Counts the number of occcurances of a specifc character in a given string.
 * Simply loops through and finds all the characters that match the given one.
 * =========================================================================
 */
int count_num_occurances(const char* str, char character)
{
	int count = 0;
	const char* i = str;
	while (1)
	{
		if (*i == character)
			count++;
		if (*i == '\n' || *i == '\0' || *i == '#')
			break;
		i++;
	}
	return count;
}

/*
 * =========================================================================
 * Reverses a given string. 
 * =========================================================================
 */
void reverse(char* str)
{
	int start, end;
	char temp;
	start = temp = 0;
	end = strlen(str) - 1;
	
	while (start < end)
	{
		// Swap start and end
		temp = str[start];
		str[start++] = str[end];
		str[end--] = temp;
	}
 }
