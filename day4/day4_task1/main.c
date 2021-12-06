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
	for (struct n_l_intbool *n = l->first; n != NULL; n = n->next)
		for (struct n_intbool *m = n->data.first; m != NULL; m = m->next)
			m->data.b = (num == m->data.num) ? 1 : m->data.b;
}

int check(l_intbool *l, char hor)
{
	for (int i = 0; i < 5; ++i) {
		int counter = 0;
		for (int j = 0; j < 5; ++j)
			counter += get_intbool(l, ((hor)?
				( i + j * BINGO_DIM): 
				(j + i * BINGO_DIM))).b;
		if (counter == 5)
			return 1;
	}
	return 0;
}

int check_hor_ver(l_intbool *l) {
	return check(l, 1) || check(l, 0);
}

int count_bingo(l_intbool *l) {
	int sum = 0;
	for (struct n_intbool *n = l->first; n != NULL; n = n->next) {
		sum += n->data.b ? 0 : n->data.num;
	}
	return sum;
}

int main (void) 
{
//open file
	FILE *f = fopen("input.txt", "r");
	if (f == NULL)
		return 1;
	l_intbool list = {.first = NULL, .last = NULL};
	l_l_intbool bingo = {.first = NULL, .last = NULL};

	read_int_line_into_list(f, &list, "%u,");
	read_bingo(f, &bingo);

	char finished = 0;
	while (!is_empty_intbool(&list) && !finished) {
		const int num = pop_first_intbool(&list).num;
		check_bingos(&bingo, num);
		for (struct n_l_intbool *n = bingo.first; n != NULL; n = n->next) {
			if (check_hor_ver(&n->data)) {
				printf("%i\n",num * count_bingo(&n->data));
				finished = 1;
				break;
			}
		}
	}

	while(!is_empty_l_intbool(&bingo)) {
		l_intbool m = pop_first_l_intbool(&bingo);
		while(!is_empty_intbool(&m))
			pop_first_intbool(&m);
	}
	destroy_intbool(&list);
	fclose(f);
}