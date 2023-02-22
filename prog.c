#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ringbuf.h"

#define chkErr(FUNCTION_CALL)   \
do                              \
{                               \
    if((FUNCTION_CALL)<0)       \
    {                           \
        fprintf(stderr,"%s returned an error\n",#FUNCTION_CALL); \
        exit(EXIT_FAILURE);      \
    }                           \
}                               \
while(0)


int main(int argc, char** argv) {
	char *space = " ";
	long unsigned int buflen = 0UL;
	for (int i = 1; i < argc; i++) {
		buflen += strlen(argv[i]); //add length of argument
		buflen++;
	}
	ringbuf_t *buf = ringbuf_create(buflen);
	if (!buf) {
		fprintf(stderr,"Coulnd't allocate Ringbuffer!");
		exit(EXIT_FAILURE);
	}
	for (int i = 1; i < argc; i++) {
		char* data = malloc(strlen(argv[i]));
		strcpy(data,argv[i]);
		chkErr(ringbuf_append(buf,data,sizeof(char)*strlen(argv[i])));
		chkErr(ringbuf_append(buf,space,sizeof(char)));
		free(data);
	}
	char *target = malloc(buflen); //max length all arguments if one sentence is input
	chkErr(ringbuf_pop_delimited(buf,'.',target,buflen));
	printf("%s\n",target);
	ringbuf_delete(buf);
	return 0;
}

