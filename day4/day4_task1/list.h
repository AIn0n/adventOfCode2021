#ifndef _LIST_H_
#define _LIST_H_

#define GENERATE_LIST(TYPE)			\
	struct n_##TYPE {			\
		struct n_##TYPE *next;	\
		struct n_##TYPE *prev;	\
		TYPE data;			\
	};					\
\
	typedef struct {			\
		struct n_##TYPE *first;	\
		struct n_##TYPE *last;	\
	}					\
	l_##TYPE;				\
\
	struct n_##TYPE*			\
	new_n_##TYPE(void)			\
	{					\
		struct n_##TYPE *new = (struct n_##TYPE *) 	\
			malloc(sizeof(struct n_##TYPE));		\
		return new;						\
	}								\
\
	int								\
	append_back_##TYPE(l_##TYPE *l, TYPE n)				\
	{								\
		struct n_##TYPE *new = new_n_##TYPE();		\
		if (new == NULL || l == NULL)			\
			return 1;					\
		new->data = n;						\
		new->prev = l->last;					\
		new->next = NULL;					\
		if (l->first == NULL && l->last == NULL)		\
			l->first = new;				\
		else							\
			l->last->next = new;				\
		l->last = new;					\
		return 0;						\
	}								\
\
	void								\
	destroy_##TYPE(l_##TYPE *l)					\
	{								\
		for (struct n_##TYPE *n = l->first; n != NULL;) {\
            struct n_##TYPE *tmp = n->next;\
            free(n);						\
            n = tmp;                        \
        }                               \
        l->first = NULL;              \
        l->last = NULL;              \
	}


#endif
