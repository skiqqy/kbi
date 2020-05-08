#include<stdlib.h>
#include<stdio.h>

int main(int argc, char *argv[]) {
	FILE *fp;
	char *buffer;
	int index, instr, windex, *wpos, wpos_sz, buff_sz;
	int *ptr, *pf;

	index = 0;
	windex = -1;
	wpos = malloc(sizeof(int));
	wpos_sz = 2;
	buffer = malloc(sizeof(char)*256);
	buff_sz = 256;
	ptr = calloc(10000, sizeof(int));
	pf = ptr;

	fp = fopen(argv[1], "r");

	instr = getc(fp);
	//first read into buffer.
	
	while (instr != EOF) {
		if (index == buff_sz) {
			buff_sz *= 2;
			buffer = realloc(buffer, sizeof(char)*buff_sz);
		}
		buffer[index++] = instr;
		instr = getc(fp);
	}
	buffer[index] = 0;
	fclose(fp);

	//start intepreter.
	index = 0;

	instr = buffer[index];
	while (instr) {
		switch (instr) {
			case '+':
				(*ptr)++;
				break;
			case '-':
				(*ptr)--;
				break;
			case ',':
				*ptr = fgetc(stdin);
				break;
			case '.':
				printf("%c", *ptr);
				break;
			case '>':
				ptr++;
				break;
			case '<':
				ptr--;
				break;
			case '[':
				windex++;
				if (windex == wpos_sz) {
					wpos_sz *= 2;
					wpos = realloc(wpos, sizeof(int)*wpos_sz);
				}
				wpos[windex] = index;
				break;
			case ']':
				if (*ptr) {
					//restart loop
					index = wpos[windex];
				} else {
					windex--;
				}
				break;
		}
		instr = buffer[++index];
	}
	
	free(pf);
	free(buffer);
	free(wpos);
	return EXIT_SUCCESS;
}
