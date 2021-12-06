#ifndef _LIST_H_
#define _LIST_H_

#define GENERATE_LIST(TYPE)		\
	struct n_##TYPE {			\
		struct n_##TYPE *next;	\
		struct n_##TYPE *prev;	\
		TYPE data;				\
	};							\
\
	typedef struct {			\
		struct n_##TYPE *first;	\
		struct n_##TYPE *last;	\
	}							\
	l_##TYPE;					\
\
	struct n_##TYPE*												\
	new_n_##TYPE(void)												\
	{																\
		return (struct n_##TYPE *) malloc(sizeof(struct n_##TYPE));	\
	}																\
\
	char												\
	is_empty_##TYPE(const l_##TYPE *l)					\
	{													\
		return l->first == NULL && l->first == l->last;	\
	}													\
\
	int											\
	append_back_##TYPE(l_##TYPE *l, TYPE n)		\
	{											\
		struct n_##TYPE *new = new_n_##TYPE();	\
		if (new == NULL || l == NULL)			\
			return -1;							\
		new->data = n;							\
		new->prev = l->last;					\
		new->next = NULL;						\
		if (is_empty_##TYPE(l))					\
			l->first = new;						\
		else									\
			l->last->next = new;				\
		l->last = new;							\
		return 0;								\
	}											\
\
	TYPE								\
	pop_first_##TYPE(l_##TYPE *l)		\
	{									\
		struct n_##TYPE *f = l->first;	\
		l->first = f->next;				\
		if (l->first != NULL)			\
			l->first->prev = NULL;		\
		else							\
			l->last = NULL;				\
		const TYPE ret = f->data;		\
		free(f);						\
		return ret;						\
	}									\
\
	TYPE										\
	get_##TYPE(const l_##TYPE *l, size_t idx)	\
	{											\
		struct n_##TYPE *tmp = l->first;		\
		for (int i = 0; i < idx; ++i)			\
			tmp = tmp->next;					\
		return tmp->data;						\
	}											\
\
	void							\
	destroy_##TYPE(l_##TYPE *l)		\
	{								\
		while (!is_empty_##TYPE(l))	\
			pop_first_##TYPE(l);	\
	}

#endif
