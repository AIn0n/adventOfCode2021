#include "stdio.h"
#include "stdlib.h"
#include "list.h"
#define BINGO_DIM 5

typedef struct {
	int num;
	char b;
}
intbool;


GENERATE_LIST(intbool)
GENERATE_LIST(l_intbool)

void
read_int_line_into_list(FILE *f, l_intbool *list, const char* formatting)
{
	intbool n = {.num = 0, .b = 0};
	while (fscanf(f, formatting, &(n.num)) > 0) {
		append_back_intbool(list, n);
		const char c = getc(f);
		if (c == '\n')
			break;
		ungetc(c, f);
	}
}

void
read_bingo(FILE *f, l_l_intbool *list)
{
	char c = '\0';
	while (1) {
		c = getc(f);
		if (c == EOF)
			break;
		ungetc(c, f);

		l_intbool tmp = {.first = NULL, .last = NULL};
		for (int i = 0; i < BINGO_DIM; ++i) {
			read_int_line_into_list(f, &tmp, "%i");
		}
		append_back_l_intbool(list, tmp);
	}
}

int check_bingos(l_l_intbool *l, const int num)
{
	for (struct n_l_intbool *n = l->first; n != NULL; n = n->next) {
		for (struct n_intbool *m = n->data.first; m != NULL; m = m->next) {
			m->data.b = (num == m->data.num);
			printf("%i\n", (num == m->data.num));
		}
	}
}

int check_hor_ver(l_intbool *l) {
	int i = 0;
	for (struct n_intbool *n = l->first; n != NULL; n = n->next, ++i) {
		
	}
}

int main (void) 
{
//open file
	FILE *f = fopen("input.txt", "r");
	if (f == NULL)
		return 1;
//read first line into list
	l_intbool list = {.first = NULL, .last = NULL, .size = 0};
	read_int_line_into_list(f, &list, "%u,");
	l_l_intbool bingo = {.first = NULL, .last = NULL};
	read_bingo(f, &bingo);
	while (!is_empty_intbool(&list))
	{
		check_bingos(&bingo, pop_first_intbool(&list).num);
	}
	


//DEBUG display bingo
	while(!is_empty_l_intbool(&bingo)) {
		l_intbool m = pop_first_l_intbool(&bingo);
		while(!is_empty_intbool(&m)) {
			intbool ib =  pop_first_intbool(&m);
			printf("%i %i\n", ib.num, ib.b);
		}
		puts("");
	}
	destroy_intbool(&list);
	fclose(f);
}