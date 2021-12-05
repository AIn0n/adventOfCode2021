#include "stdio.h"
#include "stdlib.h"
#include "list.h"
#define BINGO_DIM 5

GENERATE_LIST(int)
GENERATE_LIST(l_int)

void
read_int_line_into_list(FILE *f, l_int *list, const char* formatting)
{
	int n = 0;
	while (fscanf(f, formatting, &n) > 0) {
		
		append_back_int(list, n);
		const char c = getc(f);
		if (c == '\n')
			break;
		ungetc(c, f);
	}
}

void
read_bingo(FILE *f, l_l_int *list) {
	char c = '\0';
	while (1) {
		c = getc(f);
		if (c == EOF) {
			break;
		}
		ungetc(c, f);

		l_int tmp = {.first = NULL, .last = NULL};
		for (int i = 0; i < BINGO_DIM; ++i)
		{
			
			read_int_line_into_list(f, &tmp, "%i");
		}
		append_back_l_int(list, tmp);
	}
}

int main (void) {
//open file
	FILE *f = fopen("input.txt", "r");
	if (f == NULL)
		return 1;
//read first line into list
	l_int list = {.first = NULL, .last = NULL};
	read_int_line_into_list(f, &list, "%u,");
	l_l_int l = {.first = NULL, .last = NULL};
	read_bingo(f, &l);

//DEBUG display first line
	for (struct n_l_int* n = l.first; n != NULL; n = n->next) {
		for (struct n_int* m = n->data.first; m != NULL; m = m->next) {
			printf("%i ", m->data);
		}
			
		puts("");
	}
	destroy_int(&list);
	destroy_l_int(&l);
	fclose(f);
}