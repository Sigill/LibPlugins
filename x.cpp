#include <stdio.h>
#include <string.h>


extern "C" {
/* Let's provide some info about this plugin to the main program */
char info[] = "sample plugin 1";
char version[] = "0.0a";
/* This function takes a string, and reverses it */

void misc(char *workbuffer)
{
	unsigned int i, len = strlen(workbuffer);
	printf("X-plugin working..\n");  

	for ( i=0 ; i<len/2 ; i++ ) {
		char tmp = workbuffer[i];
		workbuffer[i] = workbuffer[len-i-1];
		workbuffer[len-i-1] = tmp;
	}
}
}
