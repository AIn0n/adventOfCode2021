#include "stdio.h"
#include "stdlib.h"
#include "list.h"
#define BINGO_DIM 5

typedef struct {
	int num;
	char b;
}
ib;

GENERATE_LIST(ib)
GENERATE_LIST(l_ib)

void
read_int_line_into_list(FILE *f, l_ib *list, const char* formatting)
{
	ib n = {.num = 0, .b = 0};
	while (fscanf(f, formatting, &(n.num)) > 0) {
		append_back_ib(list, n);
		const char c = getc(f);
		if (c == '\n')
			break;
		ungetc(c, f);
	}
}

void
read_bingo(FILE *f, l_l_ib *list)
{
	char c = '\0';
	while (1) {
		c = getc(f);
		if (c == EOF)
			break;
		ungetc(c, f);

		l_ib tmp = {.first = NULL, .last = NULL};
		for (int i = 0; i < BINGO_DIM; ++i)
			read_int_line_into_list(f, &tmp, "%i");
		append_back_l_ib(list, tmp);
	}
}

int check_bingos(l_l_ib *l, const int num)
{
	for (struct n_l_ib *n = l->first; n != NULL; n = n->next)
		for (struct n_ib *m = n->data.first; m != NULL; m = m->next)
			m->data.b = num == m->data.num ? 1 : m->data.b;
}

int check(l_ib *l, char hor)
{
	for (int i = 0; i < 5; ++i) {
		int counter = 0;
		for (int j = 0; j < 5; ++j)
			counter += get_ib(l, hor ?
				( i + j * BINGO_DIM): (j + i * BINGO_DIM)).b;
		if (counter == 5)
			return 1;
	}
	return 0;
}

int check_hor_ver(l_ib *l)
{
	return check(l, 1) || check(l, 0);
}

int count_bingo(l_ib *l)
{
	int sum = 0;
	for (struct n_ib *n = l->first; n != NULL; n = n->next)
		sum += n->data.b ? 0 : n->data.num;
	return sum;
}

int main (void) 
{
//open file
	FILE *f = fopen("input.txt", "r");
	if (f == NULL)
		return 1;
	l_ib list = {.first = NULL, .last = NULL};
	l_l_ib bingo = {.first = NULL, .last = NULL};

	read_int_line_into_list(f, &list, "%u,");
	read_bingo(f, &bingo);

	while (!is_empty_ib(&list)) {
		const int num = pop_first_ib(&list).num;
		check_bingos(&bingo, num);
		for (struct n_l_ib *n = bingo.first; n != NULL; n = n->next)
			if (!is_empty_ib(&n->data) && check_hor_ver(&n->data)) {
				printf("%i\n", num * count_bingo(&n->data));
				destroy_ib(&n->data);
			}
	}

	while(!is_empty_l_ib(&bingo)) {
		l_ib m = pop_first_l_ib(&bingo);
		while(!is_empty_ib(&m))
			pop_first_ib(&m);
	}
	destroy_ib(&list);
	fclose(f);
}